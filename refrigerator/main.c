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
        printf("[�������� �ý��� �����]\n");
        printf("�����Է�[0] ���Է�[1] ��ǰ���Ȯ��[2] ��ǰ����[3] ������Ѱ˻�[4] >> ");
        scanf("%d", &input);

        // �����Է½�
        if (input == 0) {
            sys_store_0(arr_prod, count, array_category);
            count++;
        }

        // ���Է½�
        else if (input == 1) {
            sys_store_1(arr_prod, count, array_category);
            count++;
        }

        // ��ǰ���Ȯ��
        else if (input == 2) {
            sys_print_category_all(arr_prod, count, array_category);
        }

        // ���� ���
        else if (input == 3) {
            if (count == 0) printf("������ �׸��� �����ϴ�!\n");
            else {
                sys_printline();
                sys_print_category_all(arr_prod, count, array_category);
                printf("������ �׸��� index �Է� >> ");
                scanf("%d", &buf);
                sys_del(arr_prod, count, buf);
            }
        }
        
        // ������� �˻�
        else if (input == 4) {
            sys_checkexp(time(NULL), arr_prod, count);
        }

        else if (input == 5) {
            
        }

        else {
            printf("\n\n(error)�ٽ� �Է��ϼ���\n\n");
        }


	}


    
    for (int i = 0; i < count; i++) {
        free(arr_prod[i].category);
        free(arr_prod[i].small_category);
        free(arr_prod[i].name);
    }
    free(arr_prod);
    

}