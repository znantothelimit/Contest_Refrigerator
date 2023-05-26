#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PRODUCT 128	//����� �ִ� �뷮
#define MAX_CATEGORY 10
#define BUF 128

// ��ǰ ����ü
typedef struct prod{
	char* category;
	char* small_category;
	char* name;
	time_t stored_time;
	time_t exp_time;
	int tag;
}PROD;

//�Һз� ī�װ� ����ü
typedef struct small_category {
	char* name;
	unsigned int exp_date;//�Һз��� �뷫�� �������
}S_CATE;

//��з� ī�װ� ����ü
typedef struct category {
	char* name;
	S_CATE* arr_small_category;
}CATE;

