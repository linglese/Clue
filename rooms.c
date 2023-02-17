#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "rooms.h"
#include "../items/items.h"

struct room {
    char* name;
    Room North;
    Room South;
    Room East;
    Room West;
    Item itemList;
    Item characterList;
};

//  clue character names
char *character_names[9] = {
    "Miss_Scarlett",
    "Colonel_Mustard",
    "The_Reverend_Green",
    "Mrs._Peacock",
    "Professor_Plum",
    "NULL",
    "NULL",
    "NULL",
    "NULL",
};

char *room_names[9] = {"kitchen", "bathroom", "master bedroom", "flower room", "exotic cheese room", "corn maze", "tennis court", "bar", "gym"};

void shuffle_char_array(char** array, int n) {
    srand(time(NULL));
    int i;
    for (i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

Room new_room(char *name, Room north, Room south, Room east, Room west, Item itemList, Item characterList) {
    Room room = malloc(sizeof(struct room));
    room->name = name;
    room->North = north;
    room->South = south;
    room->East = east;
    room->West = west;
    room->itemList = itemList;
    room->characterList = characterList;
    return room;
}

char* Room_get_name(Room room) {
    return room->name;
}

Item Room_get_characters(Room room) {
    return room->characterList;
}

Room Room_get_north(Room room) {
    return room->North;
}

Room Room_get_south(Room room) {
    return room->South;
}

Room Room_get_east(Room room) {
    return room->East;
}

Room Room_get_west(Room room) {
    return room->West;
}

Item Room_get_itemList(Room room) {
    return room->itemList;
}

Room generate_board(Item* character_heads) {
    srand(time(NULL));
    // randomize the order of the rooms
    shuffle_char_array(room_names, 9);
    shuffle_char_array(item_names, 9);

    // create array of rooms
    Room** board = calloc(3, 3*sizeof(struct room));
    for (int i = 0; i < 3; i++) {
        Room* rooms = calloc(3, sizeof(struct room));
        for (int j = 0; j < 3; j++) {
            Item head = character_heads[i*3+j];
            add_item(head, character_names[i*3+j]);
            Room room = new_room(room_names[i*3+j], NULL, NULL, NULL, NULL, new_item("NULL", new_item(item_names[i*3+j], NULL)), head);
            rooms[j] = room;
        }
        board[i] = rooms;
    }

    // set the neighbors
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Room room = board[i][j];
            if (i > 0) {
                room->North = board[i - 1][j];
            }
            if (i < 2) {
                room->South = board[i + 1][j];
            }
            if (j > 0) {
                room->West = board[i][j - 1];
            }
            if (j < 2) {
                room->East = board[i][j + 1];
            }
        }
    }
    // set the return value
    Room first_room = board[rand() % 3][rand() % 3];

    // free the grid used to create the board
    for (int i = 0; i < 3; i++) {
        free(board[i]);
    }
    free(board);

    return first_room;
}
