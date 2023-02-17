#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rooms/rooms.h"
#include "items/items.h"

char* commands[7] = {
    "list",
    "look",
    "go",
    "take",
    "drop",
    "inventory",
    "clue"
};

struct player {
    Room currentRoom;
    Item inventory;
};

// picks a random non "NULL" string from an array of strings. 
char* pick_random_non_null(char** array, int size) {
    srand(time(NULL));
    int i = rand() % size;
    while (strcmp(array[i], "NULL") == 0) {
        i = rand() % size;
    }
    return array[i];
}

struct answer {
    char* character;
    char* room;
    char* item;
};

int main(int argc, char** argv) {
    // create character head nodes and save them for reference during clue command
    Item *character_heads = generate_character_heads();
    // instantiate the player and give them a random room
    struct player player = {generate_board(character_heads), new_item("NULL", NULL)};
    struct answer answer = {pick_random_non_null(character_names, 9), pick_random_non_null(room_names, 9), pick_random_non_null(item_names, 9)};
    int guesses = 0;
    int won = 0;
    while (guesses < 10 && !won) {
        char command[20];
        printf("\nWhat do you want to do? (type 'help' for help) -> ");
        scanf("%s", command);
        printf("\n");
        if (!strcmp(command, "help")) {
            printf("name a command to get help for. Available commands:\n");
            for(int i = 0; i < 7; i++) {
                printf("%s\n", commands[i]);
            }
            printf("\n-> ");
            scanf("%s", command);
            printf("\n");
            if (!strcmp(command, "list")) {
                printf("lists items, rooms, and characters in the game\n");
            }
            else if (!strcmp(command, "look")) {
                printf("lists the room the player is in as well as neighboring rooms\n");
            }
            else if (!strcmp(command, "go")) {
                printf("go <north, south, east, west> moves the player to the room in the specified direction\n");
            }
            else if (!strcmp(command, "take")) {
                printf("take <item> takes the specified item from the room and puts it in the player's inventory\n");
            }
            else if (!strcmp(command, "drop")) {
                printf("drop <item> drops the specified item from the player's inventory and puts it in the room\n");
            }
            else if (!strcmp(command, "inventory")) {
                printf("lists the items in the player's inventory\n");
            }
            else if (!strcmp(command, "clue")) {
                printf("clue <character> moves the character to the player's current room,\n\
                if the character of the answer is in the room of the player, the message 'Character Match' is printed,\n\
                if the item of the answer is in the room or the player's inventory, the message 'Item Match' is printed.\n\
                if all three match, the player wins the game\n");
            }
            else {
                printf ("invalid command\n");
                continue;
            }
        }
        else if (!strcmp(command, "list")) {
            printf("rooms:\n");
            for (int i = 0; i < 9; i++) {
                printf("%s, ", room_names[i]);
            }
            printf("\nitems:\n");
            for (int i = 0; i < 6; i++) {
                printf("%s, ", item_names[i]);
            }
            printf("\ncharacters:\n");
            for (int i = 0; i < 9; i++) {
                if (strcmp(character_names[i], "NULL")) {
                    printf("%s, ", character_names[i]);
                }
            }
            printf("\n");
        }
        else if (strcmp(command, "look") == 0) {
            printf("You are in the %s\n", Room_get_name(player.currentRoom));
            printf("\nYou can go:\n");
            if (Room_get_north(player.currentRoom) != NULL) {
                printf("north to the %s\n", Room_get_name(Room_get_north(player.currentRoom)));
            }
            if (Room_get_south(player.currentRoom) != NULL) {
                printf("south to the %s\n", Room_get_name(Room_get_south(player.currentRoom)));
            }
            if (Room_get_east(player.currentRoom) != NULL) {
                printf("east to the %s\n", Room_get_name(Room_get_east(player.currentRoom)));
            }
            if (Room_get_west(player.currentRoom) != NULL) {
                printf("west to the %s\n", Room_get_name(Room_get_west(player.currentRoom)));
            }
            printf("\nItems in the room:\n");
            print_items(Room_get_itemList(player.currentRoom));
            printf("\nCharacters in the room:\n");
            print_items(Room_get_characters(player.currentRoom));
        }
        else if (strcmp(command, "go") == 0) {
            while (1) {
                char direction[20];
                printf("Which direction? (north, south, east, west, stay) -> ");
                scanf("%s", direction);
                printf("\n");
                if (!strcmp(direction, "stay")) {
                    break;
                }
                else if (!strcmp(direction, "north")) {
                    if (Room_get_north(player.currentRoom) != NULL) {
                        player.currentRoom = Room_get_north(player.currentRoom);
                        break;
                    }
                    else {
                        printf("You can't go that way\n");
                    }
                }
                else if (!strcmp(direction, "south")) {
                    if (Room_get_south(player.currentRoom) != NULL) {
                        player.currentRoom = Room_get_south(player.currentRoom);
                        break;
                    }
                    else {
                        printf("You can't go that way\n");
                    }
                }
                else if (!strcmp(direction, "east")) {
                    if (Room_get_east(player.currentRoom) != NULL) {
                        player.currentRoom = Room_get_east(player.currentRoom);
                        break;
                    }
                    else {
                        printf("You can't go that way\n");
                    }
                }
                else if (!strcmp(direction, "west")) {
                    if (Room_get_west(player.currentRoom) != NULL) {
                        player.currentRoom = Room_get_west(player.currentRoom);
                        break;
                    }
                    else {
                        printf("You can't go that way\n");
                    }
                }
                else {
                    printf("invalid direction\n");
                }
            }
        }
        else if (strcmp("take", command) == 0) {
            while(1) {
                char item[20];
                printf("Pick an item. Available items:\n");
                print_items(Room_get_itemList(player.currentRoom));
                printf("none\n");
                printf("-> ");
                scanf("%s", item);
                if (!strcmp(item, "NULL")) {
                    printf("That item is not in the room\n");
                    continue;
                }
                if (!strcmp(item, "none")) {
                    break;
                }
                Room currentRoom = player.currentRoom;
                Item item_to_take = get_item(Room_get_itemList(currentRoom), item);
                if (item_to_take != NULL) {
                    drop_item(Room_get_itemList(currentRoom), item);
                    add_item(player.inventory, strcpy(malloc(strlen(item) + 1), item));
                    break;
                }
                else {
                    printf("That item is not in the room\n");
                }
            }
        }
        else if (strcmp("drop", command) == 0) {
            while(1) {
                char item[20];
                printf("Pick an item. Available items:\n");
                print_items(player.inventory);
                printf("none\n");
                printf("-> ");
                scanf("%s", item);
                if (!strcmp(item, "NULL")) {
                    printf("That item is not in your inventory\n");
                    continue;
                }
                if (!strcmp(item, "none")) {
                    break;
                }
                Room currentRoom = player.currentRoom;
                Item item_to_drop = get_item(player.inventory, item);
                if (item_to_drop != NULL) {
                    drop_item(player.inventory, item);
                    add_item(Room_get_itemList(currentRoom), strcpy(malloc(strlen(item) + 1), item));
                    break;
                }
                else {
                    printf("That item is not in your inventory\n");
                }
            }
        }
        else if (strcmp("inventory", command) == 0) {
            printf("Items in your inventory:\n");
            print_items(player.inventory);
        }
        else if (strcmp("clue", command) == 0) {
            int found = 0;
            int character_match = 0;
            int item_match = 0;
            int room_match = 0;
            while(!found) {
                char character[20];
                printf("\nGuess the character. Available characters are:\n");
                for (int i = 0; i < 9; i++) {
                    if (strcmp(character_names[i], "NULL")) {
                        printf("%s\n", character_names[i]);
                    }
                }
                printf("-> ");
                scanf("%s", character);
                printf("\n");
                if (!strcmp(character, "NULL")) {
                    printf("That character is not in the game\n");
                    continue;
                }
                Room currentRoom = player.currentRoom;
                for (int i = 0; i < 9; i++) {
                    Item character_to_move = get_item(character_heads[i], character);
                    if (character_to_move != NULL) {
                        drop_item(character_heads[i], character);
                        add_item(Room_get_characters(currentRoom), strcpy(malloc(strlen(character) + 1), character));
                        found = 1;
                    }
                }
                if (!found) {
                    printf("That character is not in the game\n");
                }
            }
            while (1) {
                char item[20];
                printf("Guess an item. Available items: ");
                print_items(player.inventory);
                print_items(Room_get_itemList(player.currentRoom));
                printf("none\n");
                printf("Which item? -> ");
                scanf("%s", item);
                printf("\n");
                Room currentRoom = player.currentRoom;
                if (!strcmp(item, "NULL")) {
                    printf("That item is not in the room or your inventory\n");
                    continue;
                }
                if (!strcmp(item, "none")) {
                    break;
                }
                if (get_item(Room_get_itemList(currentRoom), item) != NULL) {
                    item_match = 1;
                    break;
                }
                else if (get_item(player.inventory, item) != NULL) {
                    item_match = 1;
                    break;
                }
                else {
                    printf("That item is not in the room or your inventory\n");
                }
            }
            if (get_item(Room_get_characters(player.currentRoom), answer.character) != NULL) {
                printf("Character match!\n");
                character_match = 1;
            }
            if (item_match) {
                printf("Item match!\n");
            }
            if (Room_get_name(player.currentRoom) == answer.room) {
                printf("Room match!\n");
                room_match = 1;
            }
            if (character_match && item_match && room_match) {
                printf("You win!\n");
                break;
            } 
            
            guesses++;
            printf("You don't have the right answer yet\n");
            printf("Guesses left: %d\n", 10 - guesses);
        }
        else {
            printf ("invalid command\n");
        }
    }
}
