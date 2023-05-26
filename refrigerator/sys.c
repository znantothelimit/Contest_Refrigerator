#include "header.h"

void sys_printline() {
    for (int i = 0; i < 50; i++)
        printf("-");
    printf("\n");
}


// 배열에 상품을 추가하는 함수
void sys_add(PROD* products, int numProducts, const char* category, const char* small_category, const char* name, time_t stored_time, int exp_time, int tag) {
    // 구조체 배열의 크기를 늘리기 위해 realloc을 사용
    PROD* newProducts = (PROD*)realloc(products, (numProducts + 1) * sizeof(PROD));
    if (newProducts == NULL) {

        printf("(error)realloc 할당 에러!!\n");
        exit(1);
    }

    // 추가할 데이터를 새로운 구조체에 설정
    PROD newProduct;
    newProduct.category = _strdup(category); // 문자열 복사
    newProduct.small_category = _strdup(small_category); // 문자열 복사
    newProduct.name = _strdup(name); // 문자열 복사
    newProduct.stored_time = time(NULL);
    //newProduct.exp_time = time(NULL) + (exp_time * 86400);///////////실제 일 단위로 할 시 이 코드를 사용
    newProduct.exp_time = time(NULL) + (exp_time * 20);////////테스트용 코드
    newProduct.tag = tag;

    // 새로운 구조체를 배열의 마지막에 추가
    newProducts[numProducts] = newProduct;

    // 새로운 배열로 교체
    products = newProducts;
}



//전체 목록을 보여주는 함수
void sys_print_category_all(PROD arr_prod[], int count, CATE array_category[]) {
    sys_printline();
    printf("[현재 존재하는 카테고리 목록]\n");

    for (int i = 0; i < MAX_CATEGORY; i++) {
        if (array_category[i].name == NULL) break;
        printf("---%s---\n", array_category[i].name);
        for (int j = 0; j < MAX_PRODUCT; j++) {
            if (array_category[i].arr_small_category[j].name == NULL)break;
            printf("[%s]\t", array_category[i].arr_small_category[j].name);
            for (int k = 0; k < count; k++) {
                if (!strcmp(arr_prod[k].category, array_category[i].name) && !strcmp(arr_prod[k].small_category, array_category[i].arr_small_category[j].name))
                    printf("[%d]%s\nstore %s exp %s\n ", k, arr_prod[k].name, ctime(&arr_prod[k].stored_time), ctime(&arr_prod[k].exp_time));
            }
            printf("\n");
        }
        printf("\n");
    }
    for (int i = 0; i < count; i++) {
        if ((arr_prod[i].tag == 1) && (arr_prod[i].name != NULL)) {
            printf("\n---%s---\n", arr_prod[i].category);
            printf("[%s][%d]%s\nstore %s exp %s\n", arr_prod[i].small_category, i, arr_prod[i].name, ctime(&arr_prod[i].stored_time), ctime(&arr_prod[i].exp_time));
        }
    }


}


//대분류 카테고리 목록을 보여주는 함수
void sys_print_category_big(CATE array_category[]) {
    sys_printline();
    printf("[현재 존재하는 대분류 카테고리 목록]\n");

    for (int i = 0; i < MAX_CATEGORY; i++) {
        if (array_category[i].name == NULL) break;
        printf("no%2d %s\n", i, array_category[i].name);
    }
    printf("\n");
}

//소분류 카테고리 목록을 보여주는 함수
void sys_print_category_small(S_CATE arr_small_category[]) {
    sys_printline();
    printf("[현재 존재하는 중분류 카테고리 목록]\n");

    for (int i = 0; i < MAX_CATEGORY; i++) {
        if (arr_small_category[i].name == NULL)
            break;
        printf("no%2d %s\n", i, arr_small_category[i].name);
    }
    printf("\n");
}








/*
*
*
*
*
*
*
*
* 이거 뭔가 이상하게 작동함 ㅡ,ㅡ
*/
// 항목 삭제 함수
void sys_del(PROD* arr_prod, int count, int index) {
    if (index < 0 || index > count) {
        printf("(error)유효하지 않은 인덱스입니다.\n");
        return;
    }

    // 삭제할 요소의 메모리 해제
    free(arr_prod[index].category);
    free(arr_prod[index].small_category);
    free(arr_prod[index].name);

    // 삭제한 요소 이후의 요소들을 앞으로 한 칸씩 이동
    for (int i = index; i < count - 1; i++) {
        arr_prod[i] = arr_prod[i + 1];
    }
}










// 상세입력 함수
void sys_store_1(PROD* arr_prod, int count, CATE array_category[]) {
    char buf0[BUF] = "";
    char buf1[BUF] = "";
    char buf2[BUF] = "";
    int buf3 = 0;

    sys_printline();
    printf("[상세입력모드]\n");
    printf("저장하려는 상품의 대분류 카테고리 입력 >> ");
    scanf("%s", buf0);

    printf("저장하려는 상품의 소분류 카테고리 입력 >> ");
    scanf("%s", buf1);

    printf("저장하려는 상품의 이름 입력 >> ");
    scanf("%s", buf2);

    printf("저장하려는 상품의 유통기한 입력(test) >> ");
    scanf("%d", &buf3);


    sys_add(arr_prod, count, buf0, buf1, buf2, time(NULL), buf3, 1);
    printf("Category: %s\n", arr_prod[count].category);
    printf("Small Category: %s\n", arr_prod[count].small_category);
    printf("Name: %s\n", arr_prod[count].name);
    printf("Stored Time: %s\n", ctime(&arr_prod[count].stored_time));
    printf("Expiration Time: %s\n", ctime(&arr_prod[count].exp_time));

    printf("확정[0] 취소[1] >> ");
    scanf("%d", &buf3);
    if (buf3 == 1) {
        sys_del(arr_prod, count, count);
    }

}



// 간단입력 함수
void sys_store_0(PROD* arr_prod, int count, CATE array_category[]) {

    int intbuf0 = 0;
    int intbuf1 = 0;
    int intbuf2 = 0;
    char buf[BUF] = "";

    sys_printline();
    printf("[간단입력모드]\n");
    sys_print_category_big(array_category);
    printf("저장하려는 상품의 대분류 카테고리 숫자 입력 >> ");
    scanf("%d", &intbuf0);

    sys_print_category_small(array_category[intbuf0].arr_small_category);
    printf("저장하려는 상품의 소분류 카테고리 숫자 입력 >> ");
    scanf("%d", &intbuf1);

    printf("상품명 입력 >> ");
    scanf("%s", buf);


    sys_add(arr_prod, count, array_category[intbuf0].name,
        array_category[intbuf0].arr_small_category[intbuf1].name,
        buf, time(NULL), array_category[intbuf0].arr_small_category[intbuf1].exp_date, 0);

    printf("Category: %s\n", arr_prod[count].category);
    printf("Small Category: %s\n", arr_prod[count].small_category);
    printf("Name: %s\n", arr_prod[count].name);
    printf("Stored Time: %s\n", ctime(&arr_prod[count].stored_time));
    printf("Expiration Time: %s\n", ctime(&arr_prod[count].exp_time));

    printf("확정[0] 취소[1] >> ");
    scanf("%d", &intbuf2);
    if (intbuf2 == 1) {
        sys_del(arr_prod, count, count);
    }

}



//유통기한이 지난 상품을 검사하는 함수
void sys_checkexp(time_t now_time, PROD* arr_prod, int count) {
    printf("현재 시간 : %s", ctime(&now_time));
    for (int i = 0; i < count; i++) {
        if (arr_prod[i].exp_time < now_time && arr_prod[i].name != NULL) {
            printf("유통기한 지난 상품 [%d]%s\nstore %s exp %s\n", i, arr_prod[i].name, ctime(&arr_prod[i].stored_time), ctime(&arr_prod[i].exp_time));
        }
    }
}