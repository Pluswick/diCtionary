#include "ex.h"

struct dictionary* hashTable = NULL; 
#define DICTIONARY_SIZE 100 // 딕셔너리 총 길이

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 해쉬테이블 삽입될 때 새로 노드를 생성해주는 함수(초기화)
struct word* createNode(char* eng, char* kor) {
    struct word* newNode = (struct word *)malloc(sizeof(struct word)); // 메모리 할당
    newNode->eng = strdup(eng); // 문자열 복사
    newNode->kor = strdup(kor); // 문자열 복사
    newNode->next = NULL; // 생성할 때는 next를 NULL로 초기화
    return newNode;
}

// 해쉬함수 만들기. 단순히 key를 사전 길이로 나눈 나머지
int hashFunction(char* eng){
    return strlen(eng)%DICTIONARY_SIZE;
}

// 새 단어 추가 함수 (인덱스를 순차적으로 사용)
void addWord(char* eng, char* kor) {
    struct word* newNode = createNode(eng, kor); // 새로 노드 생성
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        if (hashTable[i].count == 0) { // 비어 있는 인덱스를 찾음
            hashTable[i].first = newNode;
            hashTable[i].count++;
            printf("\n[%s] : [%s] added to dictionary[%d]\n", eng, kor, i);
            return;
        }
    }
    printf("Dictionary is full. Cannot add [%s : %s]\n", eng, kor); // 딕셔너리가 꽉 찬 경우
}

// 단어 삭제 함수
void removeWord(char* eng) {
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        struct word* node = hashTable[i].first;
        struct word* before = NULL;
        while (node != NULL) {
            if (strcmp(node->eng, eng) == 0) { // 삭제할 단어를 찾음
                if (before == NULL) { // 첫 번째 노드인 경우
                    hashTable[i].first = node->next;
                } else {
                    before->next = node->next;
                }
                hashTable[i].count--;
                free(node->eng);
                free(node->kor);
                free(node);
                printf("\n[%s] has been removed from dictionary[%d]\n", eng, i);
                return;
            }
            before = node;
            node = node->next;
        }
    }
    printf("\n[%s] does not exist in the dictionary.\n", eng);
}

// 해시테이블 전체 출력 함수
void display() {
    struct word* iterator;
    int day = 0;
    printf("\n========= Dictionary DAY 1 =========\n");
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        iterator = hashTable[i].first;
        while (iterator != NULL) {
            if (day % 30 == 0) {
            printf("\n========= Dictionary DAY %d =========\n", day/30+1);
            }
            printf("word[%d] : %s | %s\n", i+1, iterator->eng, iterator->kor);
            iterator = iterator->next;
            day++;
        }
        
    }
}

// eng를 주면 kor를 알려주는 함수
void keysearch(char* eng){
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        struct word* node = hashTable[i].first;

        while (node != NULL) {
            if (strcmp(node->eng, eng) == 0) { // 단어 찾음
                printf("\n[ %s ] : [ %s ]\n", node->eng, node->kor);
                return;
            }
            node = node->next;
        }
    }
    printf("\nNo exist.\n");
}

// kor를 주면 eng를 알려주는 함수
void valsearch(char* kor){
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        struct word* node = hashTable[i].first;

        while (node != NULL) {
            if (strcmp(node->kor, kor) == 0) { // 뜻 찾음
                printf("\n[ %s ] : [ %s ]\n", node->kor, node->eng);
                return;
            }
            node = node->next;
        }
    }
    printf("\n No exist.\n");
}

int main() {
    // 해시테이블 메모리 할당
    hashTable = (struct dictionary *)malloc(DICTIONARY_SIZE * sizeof(struct dictionary));
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        hashTable[i].first = NULL;
        hashTable[i].count = 0;
    }
    
    char k[50], v[50];
    int ans = 0;
    printf("-----English Dictionary-----\n");
    while (1) {
        printf("\n1. add\n2. delete\n3. key search\n4. value search\n5. dictionary\n6. exit\n");
        scanf("%d", &ans);
        if (ans == 1) {
            printf("영단어를 입력하세요. (ex. apple 사과) : ");
            scanf("%s %s", k, v);
            addWord(k, v);
        } else if (ans == 2) {
            printf("삭제할 영단어를 입력하세요. : ");
            scanf("%s", k);
            removeWord(k);
        } else if (ans == 3) {
            printf("영단어로 검색 : ");
            scanf("%s", k);
            keysearch(k);
        } else if (ans == 4) {
            printf("의미로 검색 : ");
            scanf("%s", v);
            valsearch(v);
        } else if (ans == 5) {
            display();
        } else break;
    }

    // 메모리 정리
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        struct word* node = hashTable[i].first;
        while (node != NULL) {
            struct word* temp = node;
            node = node->next;
            free(temp->eng);
            free(temp->kor);
            free(temp);
        }
    }
    free(hashTable);

    return 0;
}
