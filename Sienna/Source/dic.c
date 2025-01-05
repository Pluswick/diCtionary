#include "ex.h"

struct dictionary* hashTable = NULL; 
#define DICTIONARY_SIZE 100 // 딕셔너리 총 길이

// 해쉬테이블 삽입될 때 새로 노드를 생성해주는 함수(초기화)
struct word* createNode(char* eng, char* kor){
    struct word* newNode;
    newNode = (struct word *)malloc(sizeof(struct word)); // 메모리 할당
    // 사용자가 전해준 값을 대입
    newNode->eng = eng; //newNode의 eng 자리에 값 대입
    newNode->kor = kor;
    newNode->next = NULL; // 생성할 때는 next를 NULL로 초기화

    return newNode;
}

// 해쉬함수 만들기. 단순히 key를 사전 길이로 나눈 나머지
int hashFunction(char* eng){
    return strlen(eng)%DICTIONARY_SIZE;
}

// 새 단어 추가 함수
void addWord(char* eng, char* kor){
    // 어느 딕셔너리에 추가할지 인덱스를 계산
    int hashIndex = hashFunction(eng);
    struct word* newNode = createNode(eng, kor); // 새로 노드 생성
    // 계산한 인덱스의 딕셔너리에 아무 노드도 없을 경우
    if (hashTable[hashIndex].count == 0){
        hashTable[hashIndex].count = 1;
        hashTable[hashIndex].first = newNode; // head를 교체
    }
    // 딕셔너리에 다른 노드가 있을 경우 한칸씩 밀고 내가 헤드가 된다(실제로는 포인터만 바꿔줌)
    else{
        newNode->next = hashTable[hashIndex].first;
        hashTable[hashIndex].first = newNode;
        hashTable[hashIndex].count++;
    }
}

// 단어 삭제 함수
void removeWord(char* eng){
    int hashIndex = hashFunction(eng); // 어떤 딕셔너리에서 검색할지
    int flag = 0; // 삭제가 되었는지 확인하는 flag
    
    struct word* node; // 키를 찾아줄 iterator 선언, 현재 노드를 가리키는 포인터
    struct word* before; // 이전 노드를 가리키는 포인터
    
    node = hashTable[hashIndex].first; // 딕셔너리의 first부터 시작
    // 딕셔너리를 순회하면서 key를 비교
    while (node != NULL) // NULL 이 나올때까지 순회
    {
        if (strcmp(node->eng, eng) == 0){
            // 포인터 바꿔주기 노드가 1 . 헤드인 경우 2 . 헤드가 아닌경우
            if (node == hashTable[hashIndex].first){
                hashTable[hashIndex].first = node->next; // 다음 노드가 이제 헤드
            }
            else {
                before->next = node->next; // 전노드가 이제 내 다음 노드를 가르킴
            }
            // 나머지 작업 수행
            hashTable[hashIndex].count--; // 노드개수를 감소시켜 제거
            free(node); // 메모리 해제
            flag = 1;
        }
        before = node; // 노드 바꿔주기 전에 저장
        node = node->next;
    }
    if (flag == 1){ // 삭제된 경우
        printf("\n [ %s ] 이/가 삭제되었습니다. \n", eng);
    }
    else{ // 키가 없어서 삭제가 안된 경우
        printf("\n [ %s ] 이/가 존재하지 않아 삭제하지 못했습니다.\n", eng);
    }
}

// eng를 주면 kor를 알려주는 함수
void search(char* eng){
    int hashIndex = hashFunction(eng);
    struct word* node = hashTable[hashIndex].first;
    int flag = 0;

    while (node != NULL)
    {
        if (strcmp(node->eng, eng) == 0){
            flag = 1;
            break;
        }
        node = node->next;
    }
    if (flag == 1){ // 키를 찾았다면
        printf("\n [ %s ]의 의미는 [ %s ] 입니다. \n", node->eng, node->kor);
    }
    else{
        printf("\n 존재하지 않는 단어는 찾을 수 없습니다. \n");
    }
}

// 해시테이블 전체 출력 함수
void display(){
    struct word* iterator; // 반복자 선언
    printf("\n========= display start ========= \n");
    for (int i = 0; i<DICTIONARY_SIZE; i++){
        iterator = hashTable[i].first;
        printf("dictionary[%d] : ", i);
        while (iterator != NULL)
        {
            printf("(word : %s, mean : %s)  -> ", iterator->eng, iterator->kor);
            iterator = iterator->next;
        }
        printf("\n");
    }
}

int main(){
    // 해시테이블 메모리 할당
    hashTable = (struct dictionary *)malloc(DICTIONARY_SIZE * sizeof(struct dictionary));
    // 해시테이블 초기화
    for (int i = 0; i < DICTIONARY_SIZE; i++) {
        hashTable[i].first = NULL;
        hashTable[i].count = 0;
    }
    char k[50], v[50];
    int ans = 0;
    printf("-----English Dictionary-----\n");
    printf("1. add\n2. delete\n3.key search\n4.value search\n");
    scanf("%d", &ans);
    if (ans==1) {
        printf("영단어를 입력하세요. (ex. apple 사과) : ");
        scanf("%s %s", k, v);
        addWord(k, v);
    }

    display();
    return 0;
}
