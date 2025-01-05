#include "Initialize.h"

unsigned int custom_hash_function(unsigned int user_hash) {
    return user_hash % TABLE_SIZE;
}

HashTable* create_table() {
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    table->slots = (Word**)malloc(TABLE_SIZE * sizeof(Word*));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->slots[i] = NULL;
    }
    return table;
}

void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Word* current = table->slots[i];
        while (current) {
            Word* temp = current;
            current = current->next;
            free(temp->eng);
            free(temp);
        }
    }
    free(table->slots);
    free(table);
}
