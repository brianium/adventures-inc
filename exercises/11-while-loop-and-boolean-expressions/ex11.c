#include <stdio.h>

int main(int argc, char *argv[])
{
    
    // lets make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };
    
    int i = argc;
    int num_states = 4;
    while (i > 0) {
        if (i - 1 < num_states) {
            states[i - 1] = argv[i - 1];
        }
        i--;
    }

    i = num_states;
    while (i > 0) {
        printf("state %d: %s\n", i - 1 , states[i - 1]);
        i--;
    }

    return 0;
}
