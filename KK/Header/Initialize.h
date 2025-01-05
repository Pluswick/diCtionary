#ifndef MEMORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 31  // 해시 테이블 크기

// Word 구조체 정의
typedef struct Word {
    char* eng;            // 키
    char* kor;            // 값
    struct Word* next;    // 체이닝을 위한 포인터
} Word;

// HashTable 구조체 정의
typedef struct {
    Word** slots;         // 해시 테이블의 슬롯 배열
} HashTable;

// 사용자 지정 해시 함수
unsigned int custom_hash_function(unsigned int user_hash);

// 해시 테이블 생성 함수
HashTable* create_table();

// 해시 테이블 메모리 해제
void free_table(HashTable* table);

#endif // !MEMORY_H