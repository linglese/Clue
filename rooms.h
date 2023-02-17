#include "../items/items.h"

typedef struct room *Room;

extern Room new_room(char *name, Room north, Room south, Room east, Room west, Item itemList, Item characterList);
extern Room generate_board();
extern char* Room_get_name(Room room);
extern Room Room_get_north(Room room);
extern Room Room_get_south(Room room);
extern Room Room_get_east(Room room);
extern Room Room_get_west(Room room);
extern Item Room_get_itemList(Room room);
extern Item Room_get_characters(Room room);
extern Item* generate_character_heads();
extern void shuffle_char_array(char** array, int size);

extern char *character_names[9];
extern char *room_names[9];