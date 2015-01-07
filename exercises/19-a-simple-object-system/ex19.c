#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int main(int argc, char *argv[])
{
    // simple way to setup randomness
    srand(time(NULL));

    // make our map to work with
    Map *game = NEW(Map, "The Hall of the Minotaur.");

    printf("You enter the ");
    game->location->_(describe)(game->location);

    while(process_input(game)) {
    }

    return 0;
}
