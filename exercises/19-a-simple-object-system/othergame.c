#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};

Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};

int Other_init(void *self)
{
    Map *map = self;

    // make some rooms for a small map
    Room *hall = NEW(Room, "The greater Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with minotaur");
    Room *kitchen = NEW(Room, "Kitchen, with rude dude");

    // put the bad guy in the arena
    arena->bad_guy = NEW(Monster, "The evil minotaur");
    kitchen->bad_guy = NEW(Monster, "The evil rude dude");

    // setup the map rooms
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    // start the map and the character off in the hall
    map->start = hall;
    map->location = hall;

    return 1;
}

Object MapProto = {
    .init = Other_init,
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
