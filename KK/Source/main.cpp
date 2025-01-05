#include "Initialize.h"

int main() {
    // 해시 테이블 생성
    HashTable* table = create_table();
    printf("해시 테이블이 생성되었습니다.\n");

    // 사용자 지정 해시값 테스트
    unsigned int user_hash;
    printf("사용할 해시값을 입력하세요: ");
    scanf("%u", &user_hash);

    unsigned int index = custom_hash_function(user_hash);
    printf("사용자 지정 해시값 %u는 테이블의 %u번 슬롯에 매핑됩니다.\n", user_hash, index);

    // 메모리 해제
    free_table(table);
    printf("해시 테이블이 해제되었습니다.\n");

    return 0;
}