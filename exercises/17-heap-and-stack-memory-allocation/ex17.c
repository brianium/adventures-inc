#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// create constants via c pre processor
#define MAX_DATA 512
#define MAX_ROWS 100

// define an Address struct
struct Address {
    // create an int property to store an id
    int id;
    
    // create an int property to use as a boolean flag
    int set;

    // create a byte array as large as the MAX_DATA constant to store a name
    char name[MAX_DATA];

    // create a byte array as large as the MAX_DATA constant to store an email
    char email[MAX_DATA];
};

// define a Database struct
struct Database {

    // define an array of Address structs of size MAX_ROWS
    struct Address rows[MAX_ROWS];
};

// define a Connection struct
struct Connection {

    // define a file property that points to a FILE struct - located in stdio.h
    FILE *file;
    
    // define a property that points to a Database struct
    struct Database *db;
};

// define a function to exit the program
void die(const char *message)
{
    // check if an external errno variable has been set
    if(errno) {

        // if so print the error message with perror - found in stdio.h apparently prints the custom
        // message before printing the system error
        perror(message);
    } else {
        // if there is no system error we just print the error using printf
        printf("ERROR: %s\n", message);
    }

    // exit the program with an error exit code
    exit(1);
}

// define a function to print an Address struct
void Address_print(struct Address *addr)
{
    // use printf to print the id int, name string, and email string
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

// define a function to read the contents of a file into the connections database
void Database_load(struct Connection *conn)
{
    // return the number of objects read - 1 or 0. expects to read 1 item with as many bytes as a database struct.
    // the bytes are read from the conn->file FILE and stored in the location of conn->db
    int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);

    // if the file was not read then exit
    if(rc != 1) die("Failed to load database.");
}

// define a function for creating a new connection and database
// or create a connection from an existing database file
struct Connection *Database_open(const char *filename, char mode)
{
    // initialize a new connection on the heap
    struct Connection *conn = malloc(sizeof(struct Connection));

    // if connection could not be initialzed then exit
    if(!conn) die("Memory error");

    // initialize a Database pointer on the db property
    conn->db = malloc(sizeof(struct Database));

    // if the Database could not be initialized then exit
    if(!conn->db) die("Memory error");

    // if the mode is create mode
    if(mode == 'c') {
        // then use fopen to get a FILE pointer to the specified filename for writing - stdio.h
        conn->file = fopen(filename, "w");
    } else {
        // otherwise use fopen to get a FILE pointer to the specified filename for reading and writing
        conn->file = fopen(filename, "r+");

        // if the file was successfully read
        if(conn->file) {
            // then read the contents of the file into the connection's Database
            Database_load(conn);
        }
    }

    // if there is no FILE pointer on the connection then exit the program
    if (!conn->file) die("Failed to open the file");

    // return the connection pointer
    return conn;
}

// define a function to free up database resources
void Database_close(struct Connection *conn)
{
    // if the connection is non NULL
    if(conn) {
        // then close the FILE pointer on the connection if it is non NULL - stdio.h
        if(conn->file) fclose(conn->file);

        // if the Database pointer is non NULL - then free its memory
        if(conn->db) free(conn->db);

        // free the memory up for the Connection itself
        free(conn);
    }
}

// define a function to write the contents of the database to the connection file
void Database_write(struct Connection *conn)
{
    // set the file position to the beginnging of the file stream - stdio.h
    rewind(conn->file);
    
    // write the contents of the Database pointer to the FILE stream on connection
    int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);

    // if 1 object was not written, there was an error and we exit the program
    if(rc != 1) die("Failed to write database");

    // force a write of all buffered data to the file - stdio.h
    rc = fflush(conn->file); 

    // fflush returns 0 on success. -1 represents EOF. If EOF is received, then exit the program
    if(rc == -1) die("Cannot flush database");
}

// define a function to initialize the connection's database
void Database_create(struct Connection *conn)
{
    int i = 0;

    // loop MAX_ROWS times
    for(i = 0; i < MAX_ROWS; i++) {
        // make a prototype to initialize an Address
        struct Address addr = {.id = i, .set = 0};
        // then just assign it to a database row
        conn->db->rows[i] = addr;
    }
}

// define a function to write a record to the connections database
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    // get the address of the Address with index at id
    // you turn a value into a pointer with & "i.e the address operator"
    struct Address *addr = &conn->db->rows[id];

    // if the address already has already been set then exit with an error
    if(addr->set) die("Already set, delete it first");

    // flag the address as having been set
    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, MAX_DATA);
    //demonstrate the strncpy bug
    if(!res) die("Name copy failed");

    // copy email passed in to the addresses email
    res = strncpy(addr->email, email, MAX_DATA);

    // if destination string not returned then exit program
    if(!res) die("Email copy failed");
}

// define a function to fetch a row from the connections database
void Database_get(struct Connection *conn, int id)
{
    // get a pointer to the Address identified by id
    struct Address *addr = &conn->db->rows[id];

    // if the address has been set
    if(addr->set) {
        // then print it
        Address_print(addr);
    } else {
        // otherwise exit program with an error
        die("ID is not set");
    }
}

// define a function to set the record identified by id back to an initialized state
// i.e unset it
void Database_delete(struct Connection *conn, int id)
{
    //initialize an Address on the stack
    struct Address addr = {.id = id, .set = 0};

    //set the record identified by id to the initialized value
    conn->db->rows[id] = addr;
}

// define a function to list the contents of the database
void Database_list(struct Connection *conn)
{
    int i = 0;

    // get the database on the connection
    struct Database *db = conn->db;

    // loop until MAX_ROWS
    for (i = 0; i < MAX_ROWS; i++) {
        // get a pointer to the Address at the given location
        struct Address *cur = &db->rows[i];

        // if the current Address has been set
        if(cur->set) {
            // then print it
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    // we need at least 3 arguments - if not then exit program
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]");

    // the first real argument is the database file name
    char *filename = argv[1];

    // the action to take is the first charactor of the 2nd real argument
    char action = argv[2][0];

    // get a connection for the filename passed in - either creating one (action c) or performing some other
    // action on an existing database
    struct Connection *conn = Database_open(filename, action);

    // intialize the id of the record being sought
    int id = 0;

    // if the number of arguments is greater than three, then the 3rd real argument
    // ASCII string is converted to an integer via atoi - stdlib.h
    if(argc > 3) id = atoi(argv[3]);

    // if the id is greater than the allowed MAX_ROWS constant, then exit the program
    if(id >= MAX_ROWS) die("There's not that many records.");

    //perform a task based on the action provided
    switch(action) {
        case 'c':
            // if the action is c for create, then we create a new database by filling it with prototypes
            Database_create(conn);

            // we then write the protyped data to file
            Database_write(conn);
            break;

        case 'g':
            // if the action is g for get we check to see if we have the right amount of arguments
            // if we dont we assume we are missing an ID and exit the program
            if(argc != 4) die("Need an id to get");

            // read the record identified by id from the connections database and print it
            Database_get(conn, id);
            break;

        case 's':
            // if the action is s for set we verify we have the right number of args
            // and exit if we do not
            if(argc != 6) die("Need id, name, email to set");

            // set the row identified by id with the values given in argv
            Database_set(conn, id, argv[4], argv[5]);

            // write the changes to the database file
            Database_write(conn);
            break;

        case 'd':
            // if the action is d for delete verify we have the right args
            // and exit the program if we do not
            if(argc != 4) die("Need id to delete");

            // zero fill the record identified by id
            Database_delete(conn, id);

            // write the changes to the database file
            Database_write(conn);
            break;

        case 'l':
            // if the action is l for list, then we list the contents of the database file.
            Database_list(conn);
            break;

        default:
            // if an invalid action was given then exit the program with a helpful error message
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list");
    }

    // free up allocated memory and close FILE streams
    Database_close(conn);

    return 0;
}
