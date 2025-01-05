//#include <stdio.h>
//#include <stdlib.h> // 메모리 할당
#include"ex.h"

struct dictionary* hashTable = NULL; 
#define DICTIONARY_SIZE = 100; // 사전의 총 길이

// 노드 구조체 선언
struct word {
    char* eng;
    char* kor;
    struct word* next; // 다음 노드를 가르키는 포인터
};
// 딕셔너리 구조체 선언
struct dictionary {
    struct word* first; // 딕셔너리 가장 앞에 있는 노드의 포인터
    int count; // 딕셔너리에 들어있는 노드의 개수
};

// 해쉬테이블 삽입될 때 새로 노드를 생성해주는 함수(초기화)
struct node* createNode(int key, int value){
    struct node* newNode;
    // 메모리 할당
    newNode = (struct node *)malloc(sizeof(struct node));
    // 사용자가 전해준 값을 대입
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL; // 생성할 때는 next를 NULL로 초기화

    return newNode;
}

// 해쉬함수 만들기. 단순히 key를 사전 길이로 나눈 나머지로 함수를 만듦.
int hashFunction(int key){
    return key%dictionary_SIZE;
}

// 새로 키 추가하는 함수
void add(int key, int value){
    // 어느 딕셔너리에 추가할지 인덱스를 계산
    int hashIndex = hashFunction(key);
    // 새로 노드 생성
    struct node* newNode = createNode(key, value);
    // 계산한 인덱스의 딕셔너리에 아무 노드도 없을 경우
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].head = newNode; // head를 교체
    }
    // 버켓에 다른 노드가 있을 경우 한칸씩 밀고 내가 헤드가 된다(실제로는 포인터만 바꿔줌)
    else{
        newNode->next = hashTable[hashIndex].head;
        hashTable[hashIndex].head = newNode;
        hashTable[hashIndex].count++;
    }
}

// 키를 삭제해주는 함수
void remove_key(int key){
    int hashIndex = hashFunction(key);
    // 삭제가 되었는지 확인하는 flag 선언
    int flag = 0;
    // 키를 찾아줄 iterator 선언
    struct node* node;
    struct node* before; // 노드가 지나간 바로 전 노드
    // 버켓의 head부터 시작
    node = hashTable[hashIndex].head;
    // 버켓을 순회하면서 key를 찾는다.
    while (node != NULL) // NULL 이 나올때까지 순회
    {
        if (node->key == key){
            // 포인터 바꿔주기 노드가 1 . 헤드인 경우 2 . 헤드가 아닌경우
            if (node == hashTable[hashIndex].head){
                hashTable[hashIndex].head = node->next; // 다음 노드가 이제 헤드
            }
            else{
                before->next = node->next; // 전노드가 이제 내 다음 노드를 가르킴
            }
            // 나머지 작업 수행
            hashTable[hashIndex].count--;
            free(node);
            flag = 1;
        }
        before = node; // 노드 바꿔주기 전에 저장
        node = node->next;
    }
    // flag의 값에 따라 출력 다르게 해줌
    if (flag == 1){ // 삭제가 되었다면
        printf("\n [ %d ] 이/가 삭제되었습니다. \n", key);
    }
    else{ // 키가 없어서 삭제가 안된 경우
        printf("\n [ %d ] 이/가 존재하지 않아 삭제하지 못했습니다.\n", key);
    }
}

// 키를 주면 value를 알려주는 함수
void search(int key){
    int hashIndex = hashFunction(key);
    struct node* node = hashTable[hashIndex].head;
    int flag = 0;
    while (node != NULL)
    {
        if (node->key == key){
            flag = 1;
            break;
        }
        node = node->next;
    }
    if (flag == 1){ // 키를 찾았다면
        printf("\n 키는 [ %d ], 값은 [ %d ] 입니다. \n", node->key, node->value);
    }
    else{
        printf("\n 존재하지 않은 키는 찾을 수 없습니다. \n");
    }
}



int main(){
    // 해시테이블 메모리 할당
    hashTable = (struct dictionary *)malloc(dictionary_SIZE * sizeof(struct dictionary));
    // 해시테이블 초기화
    for (int i = 0; i < dictionary_SIZE; i++) {
        hashTable[i].head = NULL;
        hashTable[i].count = 0;
    }
    int k, v;
    int ans = 0;
    printf("-----English Dictionary-----\n");
    printf("1. add\n2. delete\n3.key search\n4.value search\n");
    scanf("%d", &ans);
    if (ans==1)
    {
        printf("영단어를 입력하세요. (ex. apple 사과) : ");
        scanf("%d %d", &k, &v);
        add(k, v);
    }

    display();
    return 0;
}