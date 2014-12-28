#include <stdio.h>

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    int *cur_age = ages;
    char **cur_name = names;

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for(i = 0; i < count; i++) {
        printf("%s has %d years alive.\n", *(cur_name + i), *(cur_age + i));
    }

    printf("---\n");

    // setup the pointers to the start of the arrays

    // second way using pointers
    for(i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }

    printf("---\n");

    // third way, pointers are just arrays
    for(i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    for(cur_name = names, cur_age = ages;
            (cur_age - ages) < count;   //my address minus the default address - that is the address of the first element
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }

    // The final thing to grasp at this stage is that you can use either syntax 
    // for most array or pointer operations. You can take a pointer to something, but use the array 
    // syntax for accessing it. You can take an array and do pointer arithmetic with it i.e cur_age - ages
    
    // this extra credit was initially terrible because i forgot to reset cur_name and cur_age
    // which resulted in a sweet seg fault party.
    for(cur_name = names, cur_age = ages, i = 0; i < count; i++) {
       printf("%s has address %p and their age %d has address %p\n",
               *(cur_name+i), &cur_name[i],
               *(cur_age+i), &cur_age[i]);
    }

    return 0;
}
