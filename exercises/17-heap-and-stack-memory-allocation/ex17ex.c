#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// define an Address struct
struct Address {
    // create an int property to store an id
    int id;
    
    // create an int property to use as a boolean flag
    int set;

    // a name string
    char *name;

    // an email string
    char *email;
};

// define a Database struct
struct Database {

    // define an array of Address structs of dynamic size
    struct Address *rows;

    int max_rows;

    int max_size;
};

// define a Connection struct
struct Connection {

    // define a file property that points to a FILE struct - located in stdio.h
    FILE *file;
    
    // define a property that points to a Database struct
    struct Database *db;
};

// forward declaration for Database_close function
void Database_close(struct Connection *conn);


// define a function to exit the program
void die(const char *message, struct Connection *conn)
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
    Database_close(conn);
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

    conn->db->rows = malloc(conn->db->max_rows * sizeof(struct Address));

    int i = 0;
    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];

        // have to initialize placeholders - why can't i just do
        // addr->name = malloc(...) and addr->email = malloc(...)
        fread(addr, sizeof(struct Address), 1, conn->file);

        addr->name = malloc(conn->db->max_size * sizeof(char));
        addr->email = malloc(conn->db->max_size * sizeof(char));

        //for some reason I cant do addr->name or addr->email here after malloc,
        //i have to use placeholders *name and *email
        fread(addr->name, sizeof(char), conn->db->max_size, conn->file);
        fread(addr->email, sizeof(char), conn->db->max_size, conn->file);
    }

    // if the file was not read then exit
    if(rc != 1) die("Failed to load database.", conn);
}

// define a function for creating a new connection and database
// or create a connection from an existing database file
struct Connection *Database_open(const char *filename, char mode)
{
    // initialize a new connection on the heap
    struct Connection *conn = malloc(sizeof(struct Connection));

    // if connection could not be initialzed then exit
    if(!conn) die("Memory error", conn);

    // initialize a Database pointer on the db property
    conn->db = malloc(sizeof(struct Database));

    // if the Database could not be initialized then exit
    if(!conn->db) die("Memory error", conn);

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
    if (!conn->file) die("Failed to open the file", conn);

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

        if (conn->db->rows) free(conn->db->rows);

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

    int i = 0;
    for(i = 0; i < conn->db->max_rows; i++) {
        struct Address *addr = &conn->db->rows[i];
        fwrite(addr, sizeof(struct Address), 1, conn->file);
        fwrite(addr->name, sizeof(char), conn->db->max_size, conn->file);
        fwrite(addr->email, sizeof(char), conn->db->max_size, conn->file);
    }

    // if 1 object was not written, there was an error and we exit the program
    if(rc != 1) die("Failed to write database", conn);

    // force a write of all buffered data to the file - stdio.h
    rc = fflush(conn->file); 

    // fflush returns 0 on success. -1 represents EOF. If EOF is received, then exit the program
    if(rc == -1) die("Cannot flush database", conn);
}

// define a function to initialize the connection's database
void Database_create(struct Connection *conn, int max_size, int max_rows)
{
    int i = 0;

    struct Database *db = conn->db;
    db->max_size = max_size;
    db->max_rows = max_rows;
    db->rows = malloc(max_rows * sizeof(struct Address));

    // loop max_rows times
    for(i = 0; i < db->max_rows; i++) {
        // make a prototype to initialize an Address
        struct Address addr = {.id = i, .set = 0};
        addr.name = malloc(max_size * sizeof(char));
        addr.email = malloc(max_size * sizeof(char));
        // then just assign it to a database row
        db->rows[i] = addr;
    }
}

// define a function to write a record to the connections database
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    // get the address of the Address with index at id
    // you turn a value into a pointer with & "i.e the address operator"
    struct Address *addr = &conn->db->rows[id];

    // if the address already has already been set then exit with an error
    if(addr->set) die("Already set, delete it first", conn);

    // flag the address as having been set
    addr->set = 1;
    // WARNING: bug, read the "How To Break It" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_size * sizeof(char));
    //demonstrate the strncpy bug
    if(!res) die("Name copy failed", conn);

    // copy email passed in to the address's email - strncpy exists in string.h
    res = strncpy(addr->email, email, conn->db->max_size * sizeof(char));

    // if destination string not returned then exit program
    if(!res) die("Email copy failed", conn);
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
        die("ID is not set", conn);
    }
}

void Database_find(struct Connection *conn, char field, const char *value)
{
    int i = 0;
    struct Database *db = conn->db;
    switch (field) {
        case 'n':
            for(i = 0; i < db->max_rows; i++) {
                struct Address *addr = &db->rows[i];
                if (strcmp(addr->name, value) == 0) {
                    Address_print(addr);
                }
            }
            break;

        case 'e':
            for(i = 0; i < db->max_rows; i++) {
                struct Address *addr = &db->rows[i];
                if (strcmp(addr->email, value) == 0) {
                    Address_print(addr);
                }
            }
            break;

        default:
            die("Cannot search on given field", conn);
    }
}

// define a function to set the record identified by id back to an initialized state
// i.e unset it
void Database_delete(struct Connection *conn, int id)
{
    //initialize an Address on the stack
    struct Address addr = {.id = id, .set = 0};
    addr.name = malloc(conn->db->max_size * sizeof(char));
    addr.email = malloc(conn->db->max_size * sizeof(char));

    //set the record identified by id to the initialized value
    conn->db->rows[id] = addr;
}

// define a function to list the contents of the database
void Database_list(struct Connection *conn)
{
    int i = 0;

    // get the database on the connection
    struct Database *db = conn->db;

    // loop until max_rows 
    for (i = 0; i < db->max_rows; i++) {
        // get a pointer to the Address at the given location
        struct Address *cur = &db->rows[i];

        // if the current Address has been set
        if(cur->set) {
            // then print it
            Address_print(cur);
        }
    }
}


void Connection_check_id(struct Connection *conn, int id)
{
    struct Database *db = conn->db;
    if (id >= db->max_rows) {
        die("There is not that many records", conn);
    }
}

int main(int argc, char *argv[])
{
    // we need at least 3 arguments - if not then exit program
    if(argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

    // the first real argument is the database file name
    char *filename = argv[1];

    // the action to take is the first charactor of the 2nd real argument
    char action = argv[2][0];

    // get a connection for the filename passed in - either creating one (action c) or performing some other
    // action on an existing database
    struct Connection *conn = Database_open(filename, action);

    // intialize the id of the record being sought
    int id = 0;
    int max_size = 0;
    int max_rows = 0;
    char searchField = '\0';
 
    //perform a task based on the action provided
    switch(action) {
        case 'c':

            //max size is argv[3] and max_rows is argv[4]
            max_size = atoi(argv[3]);
            max_rows = atoi(argv[4]);

            // if the action is c for create, then we create a new database by filling it with prototypes
            Database_create(conn, max_size, max_rows);

            // we then write the protyped data to file
            Database_write(conn);
            break;

        case 'g':

            if(argc > 3) id = atoi(argv[3]);
            Connection_check_id(conn, id);

            // if the action is g for get we check to see if we have the right amount of arguments
            // if we dont we assume we are missing an ID and exit the program
            if(argc != 4) die("Need an id to get", conn);

            // read the record identified by id from the connections database and print it
            Database_get(conn, id);
            break;

        case 's':

            if(argc > 3) id = atoi(argv[3]);
            Connection_check_id(conn, id);

            // if the action is s for set we verify we have the right number of args
            // and exit if we do not
            if(argc != 6) die("Need id, name, email to set", conn);

            // set the row identified by id with the values given in argv
            Database_set(conn, id, argv[4], argv[5]);

            // write the changes to the database file
            Database_write(conn);
            break;

        case 'd':

            if(argc > 3) id = atoi(argv[3]);
            Connection_check_id(conn, id);

            // if the action is d for delete verify we have the right args
            // and exit the program if we do not
            if(argc != 4) die("Need id to delete", conn);

            // zero fill the record identified by id
            Database_delete(conn, id);

            // write the changes to the database file
            Database_write(conn);
            break;

        case 'l':
            // if the action is l for list, then we list the contents of the database file.
            Database_list(conn);
            break;

        case 'f':
            if (argc != 5) die("Find requires a search key and value", conn);
            searchField = argv[3][0];
            Database_find(conn, searchField, argv[4]);
            break;

        default:
            // if an invalid action was given then exit the program with a helpful error message
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
    }

    // free up allocated memory and close FILE streams
    Database_close(conn);

    return 0;
}
