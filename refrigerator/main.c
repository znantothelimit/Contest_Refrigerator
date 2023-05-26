#include "header.h"



S_CATE small_array_meat[MAX_CATEGORY] = {
    {"Chicken", 1},
    {"Beef", 10},
    {"Pork", 5},
};

S_CATE small_array_veget[MAX_CATEGORY] = {
    {"Onion", 7},
    {"Garlic", 10},
    {"Carrot", 14,},
    {"Mushroom", 5},
    {"Pepper", 5},
};

S_CATE small_array_fruit[MAX_CATEGORY] = {
    {"Apple", 21},
    {"Orange", 7},
    {"Watermelon", 14},
    {"Grape", 5},
    {"Strawberry", 10},
    {"Peer", 7},
};


S_CATE small_array_dairy[MAX_CATEGORY] = {
    {"Milk", 15},
    {"Egg", 45},
    {"Cheese", 180},
    {"Tofu", 14},
};


CATE array_category[MAX_CATEGORY] = {
    {"MEAT", small_array_meat},
    {"VEGET", small_array_veget},
    {"FRUIT", small_array_fruit},
    {"DAIRY", small_array_dairy},
};

int count = 0;
int buf = 0;

int main(void) {

    PROD* arr_prod = (PROD*)malloc(MAX_PRODUCT * sizeof(PROD));






    while (1) {


        int input = 0;
        printf("\n\n");
        sys_printline();
        printf("[선도관리 시스템 냉장고]\n");
        printf("간단입력[0] 상세입력[1] 상품목록확인[2] 상품삭제[3] 유통기한검사[4] >> ");
        scanf("%d", &input);

        // 간단입력시
        if (input == 0) {
            sys_store_0(arr_prod, count, array_category);
            count++;
        }

        // 상세입력시
        else if (input == 1) {
            sys_store_1(arr_prod, count, array_category);
            count++;
        }

        // 상품목록확인
        else if (input == 2) {
            sys_print_category_all(arr_prod, count, array_category);
        }

        // 삭제 모드
        else if (input == 3) {
            if (count == 0) printf("삭제할 항목이 없습니다!\n");
            else {
                sys_printline();
                sys_print_category_all(arr_prod, count, array_category);
                printf("삭제할 항목의 index 입력 >> ");
                scanf("%d", &buf);
                sys_del(arr_prod, count, buf);
            }
        }

        // 유통기한 검사
        else if (input == 4) {
            sys_checkexp(time(NULL), arr_prod, count);
        }

        else if (input == 5) {

        }

        else {
            printf("\n\n(error)다시 입력하세요\n\n");
        }


    }



    for (int i = 0; i < count; i++) {
        free(arr_prod[i].category);
        free(arr_prod[i].small_category);
        free(arr_prod[i].name);
    }
    free(arr_prod);


}