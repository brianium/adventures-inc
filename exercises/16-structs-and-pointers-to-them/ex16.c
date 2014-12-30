#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// define a Person structure
struct Person {
    // create a string property for the persons name
    char *name;

    // create an int property for the persons age
    int age;

    // create an in property for the persons height
    int height;

    // create an int property for the persons weight
    int weight;
};

// define a function for creating a person and returning a pointer to that person
struct Person *Person_create(char *name, int age, int height, int weight) 
{
    // allocate some memory for a new person struct
    struct Person *who = malloc(sizeof(struct Person));

    // verify that malloc did not return a null pointer
    assert(who != NULL);

    // assign a new chunk of memory to a duplicate version of the name string passed in
    who->name = strdup(name);

    // assign the age argument to the struct age property
    who->age = age;

    // assign the height arg to the height property
    who->height = height;

    // assign the weight arg to the weight property
    who->weight = weight;

    // return the pointer to this person
    return who;
}

// Define a function to free up memory used for a person
void Person_destroy(struct Person *who)
{
    // verify input is ok i.e not null
    assert(who != NULL);

    // free up memory set aside for name string
    free(who->name);

    // free up memory set aside for person struct
    free(who);
}

// Define function to print person
void Person_print(struct Person *who)
{
    //print the name string
    printf("Name: %s\n", who->name);

    //print the age int
    printf("\tAge: %d\n", who->age);

    //print the height int
    printf("\tHeight: %d\n", who->height);

    //print the weight int
    printf("\tWeight: %d\n", who->weight);
}

// define the main function of this program
int main(int argc, char *argv[])
{
    // make two people structures
    struct Person *joe = Person_create(
            "Joe Alex", 32, 64, 140);

    // make a person struct for frank
    struct Person *frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    // print out joe
    Person_print(joe);

    printf("Frank is at memory location %p:\n", frank);

    // print out frank
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe->age += 20;

    // decrement height by 2
    joe->height -= 2;

    // increment weight by 40
    joe->weight += 40;

    // print joe again
    Person_print(joe);

    // increment age by 20
    frank->age += 20;

    // increment weight by 20
    frank->weight += 20;

    // print frank again
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);

    // return a successful exit code
    return 0;
}
