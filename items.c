#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include "items.h"
#include "../rooms/rooms.h"

char* item_names[9] = {"knife", "candlestick", "revolver", "rope", "lead_pipe", "wrench", "NULL", "NULL", "NULL"};

struct item {
    Item next;
    char* name;
};

Item* generate_character_heads() {
    Item* head_nodes = calloc(9, sizeof(struct item));
    for (int i = 0; i < 9; i++) {
        head_nodes[i] = new_item("NULL", NULL);
    }
    return head_nodes;
}

Item new_item(char* name, Item next) {
    Item item = malloc(sizeof(struct item));
    item->name = name;
    item->next = next;
    return item;
}

void add_item(Item head, char* data) {
    Item this = head;
    while (this->next != NULL) {
        this = this->next;
    }
    this->next = new_item(data, NULL);
}

Item drop_item(Item head, char* data) {
    Item this = head;
    Item prev = NULL;
    while (this != NULL) {
        if (strcmp(this->name, data) == 0) {
            if (prev == NULL) {
                head = this->next;
            } else {
                prev->next = this->next;
            }
            free(this);
            return head;
        }
        prev = this;
        this = this->next;
    }
    return head;
}

Item get_item(Item head, char* data) {
    Item this = head;
    while (this != NULL) {
        if (strcmp(this->name, data) == 0) {
            return this;
        }
        this = this->next;
    }
    return NULL;
}

void print_items(Item head) {
    Item this = head;
    while (this != NULL) {
        if (strcmp(this->name, "NULL") != 0) {
            printf("%s\n", this->name);
        }
        this = this->next;
    }
}

char* Item_get_name(Item head) {
    return head->name;
}
