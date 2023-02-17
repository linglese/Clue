typedef struct item *Item;

extern Item new_item(char* data, Item next);
extern void add_item(Item head, char* data);
extern Item drop_item(Item head, char* data);
extern Item get_item(Item head, char* data);
extern void print_items(Item head);
extern char* Item_get_name(Item head);

extern char* item_names[9];
