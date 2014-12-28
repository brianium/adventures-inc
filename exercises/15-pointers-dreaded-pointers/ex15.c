#include <stdio.h>

void print_using_pointers(int *age, char **name, int count)
{
    int i = 0;
    while(i < count) {
        printf("%s has %d years alive.\n", *(name + i), *(age + i));
        i++;
    }
    printf("---\n");
}

void print_using_indexes(int *age, char **name, int count)
{
    int i = 0;
    while(i < count) {
        printf("%s is %d years old.\n", name[i], age[i]);
        i++;
    }
    printf("---\n");
}

void print_using_silly_pointers(int ages[], char *names[], int count)
{
    int *age = ages;
    char **name = names;
    while (age - ages < count) {
        printf("%s lived %d years so far.\n", *name, *age);
        name++;
        age++;
    }

}

void print_addresses(int ages[], char *names[], int count)
{
    int *age = ages;
    char **name = names;
    int i = 0;
    while(i < count) {
        printf("%s has address %p and their age %d has address %p\n",
               *(name+i), &name[i],
               *(age+i), &age[i]);
        i++;
    }
}

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

    print_using_pointers(cur_age, cur_name, count);
    print_using_pointers(cur_age, cur_name, count);
    print_using_indexes(cur_age, cur_name, count);
    print_using_silly_pointers(ages, names, count);

    // The final thing to grasp at this stage is that you can use either syntax 
    // for most array or pointer operations. You can take a pointer to something, but use the array 
    // syntax for accessing it. You can take an array and do pointer arithmetic with it i.e cur_age - ages
    
    // this extra credit was initially terrible because i forgot to reset cur_name and cur_age
    // which resulted in a sweet seg fault party.
    print_addresses(ages, names, count);

    return 0;
}
