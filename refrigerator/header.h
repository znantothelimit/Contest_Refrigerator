#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCT 128	//냉장고 최대 용량
#define MAX_CATEGORY 10
#define BUF 128

// 상품 구조체
typedef struct prod{
	char* category;
	char* small_category;
	char* name;
	time_t stored_time;
	time_t exp_time;
	int tag;
}PROD;

//소분류 카테고리 구조체
typedef struct small_category {
	char* name;
	unsigned int exp_date;//소분류의 대략적 유통기한
}S_CATE;

//대분류 카테고리 구조체
typedef struct category {
	char* name;
	S_CATE* arr_small_category;
}CATE;

