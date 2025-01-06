#ifndef EX_H
#define EX_H

#include <stdio.h>
#include <stdlib.h> // 메모리 할당
#include <string.h>

#define DICTIONARY_SIZE 100

struct word {
    char* eng;
    char* kor;
    struct word* next;
};

struct dictionary {
    struct word* first;
    int count;
};

struct word* createNode(char* eng, char* kor);
int hashFunction(char* eng);
void addWord(char* eng, char* kor);
void removeWord(char* eng);
void search(char* eng);
void display();

#endif //EX_H
