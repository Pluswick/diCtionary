#ifndef MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 31  // �ؽ� ���̺� ũ��

// Word ����ü ����
typedef struct Word {
    char* eng;            // Ű
    char* kor;            // ��
    struct Word* next;    // ü�̴��� ���� ������
} Word;

// HashTable ����ü ����
typedef struct {
    Word** slots;         // �ؽ� ���̺��� ���� �迭
} HashTable;

// ����� ���� �ؽ� �Լ�
unsigned int custom_hash_function(unsigned int user_hash);

// �ؽ� ���̺� ���� �Լ�
HashTable* create_table();

// �ؽ� ���̺� �޸� ����
void free_table(HashTable* table);

#endif // !MEMORY_H