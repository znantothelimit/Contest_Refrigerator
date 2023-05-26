#include "header.h"

void sys_printline() {
    for (int i = 0; i < 50; i++)
        printf("-");
    printf("\n");
}


// �迭�� ��ǰ�� �߰��ϴ� �Լ�
void sys_add(PROD* products, int numProducts, const char* category, const char* small_category, const char* name, time_t stored_time, time_t exp_time, int tag) {
    // ����ü �迭�� ũ�⸦ �ø��� ���� realloc�� ���
    PROD* newProducts = (PROD*)realloc(products, sizeof(products) + sizeof(PROD));
    if (newProducts == NULL) {

        printf("(error)realloc �Ҵ� ����!!\n");
        exit(1);
    }

    // �߰��� �����͸� ���ο� ����ü�� ����
    PROD newProduct;
    newProduct.category = _strdup(category); // ���ڿ� ����
    newProduct.small_category = _strdup(small_category); // ���ڿ� ����
    newProduct.name = _strdup(name); // ���ڿ� ����
    newProduct.stored_time = time(NULL);
    newProduct.exp_time = newProduct.stored_time + (exp_time * 86400);
    newProduct.tag = tag;

    // ���ο� ����ü�� �迭�� �������� �߰�
    newProducts[numProducts] = newProduct;

    // ���ο� �迭�� ��ü
    products = newProducts;
}




//��ü ����� �����ִ� �Լ�
void sys_print_category_all(PROD arr_prod[], int count, CATE array_category[]) {
    sys_printline();
    printf("[���� �����ϴ� ī�װ� ���]\n");

    for (int i = 0; i < MAX_CATEGORY; i++) {
        if (array_category[i].name == NULL) break;
        printf("---%s---\n", array_category[i].name);
        for (int j = 0; j < MAX_PRODUCT; j++) {
            if (array_category[i].arr_small_category[j].name == NULL)break;
            printf("[%s]\n", array_category[i].arr_small_category[j].name);
            for (int k = 0; k < count; k++) {
                if (!strcmp(arr_prod[k].category, array_category[i].name) && !strcmp(arr_prod[k].small_category, array_category[i].arr_small_category[j].name)) {
                    printf("[%d]%s\nstored\t\t%s", k, arr_prod[k].name, ctime(&arr_prod[k].stored_time));
                    printf("exp\t\t%s\n", ctime(&arr_prod[k].exp_time));
                }

            }
            printf("\n");
        }
        printf("\n");
    }
    for (int i = 0; i < count; i++) {
        if ((arr_prod[i].tag == 1) && (arr_prod[i].name != NULL)) {
            printf("\n---%s---\n", arr_prod[i].category);
            printf("[%s]\n[%d]%s\nstore\t\t%s", arr_prod[i].small_category, i, arr_prod[i].name, ctime(&arr_prod[i].stored_time));
            printf("exp\t\t%s\n", ctime(&arr_prod[i].exp_time));
        }
    }


}


//��з� ī�װ� ����� �����ִ� �Լ�
void sys_print_category_big(CATE array_category[]) {
    sys_printline();
    printf("[���� �����ϴ� ��з� ī�װ� ���]\n");

    for (int i = 0; i < MAX_CATEGORY; i++) {
        if (array_category[i].name == NULL) break;
        printf("no%2d %s\n", i, array_category[i].name);
    }
    printf("\n");
}



//�Һз� ī�װ� ����� �����ִ� �Լ�
void sys_print_category_small(S_CATE arr_small_category[]) {
    sys_printline();
    printf("[���� �����ϴ� �ߺз� ī�װ� ���]\n");

    for (int i = 0; i < MAX_CATEGORY; i++) {
        if (arr_small_category[i].name == NULL)
            break;
        printf("no%2d %s\n", i, arr_small_category[i].name);
    }
    printf("\n");
}







// �׸� ���� �Լ�
void sys_del(PROD* arr_prod, int count, int index) {
    if (index < 0 || index > count) {
        printf("(error)��ȿ���� ���� �ε����Դϴ�.\n");
        return;
    }

    // ������ ����� �޸� ����
    free(arr_prod[index].category);
    free(arr_prod[index].small_category);
    free(arr_prod[index].name);


    // ������ ��� ������ ��ҵ��� ������ �� ĭ�� �̵�
    for (int i = index; i < count - 1; i++) {
        arr_prod[i] = arr_prod[i + 1];
    }


}



// �����Է� �Լ�
void sys_store_0(PROD* arr_prod, int count, CATE array_category[]) {

    int intbuf0 = 0;
    int intbuf1 = 0;
    int intbuf2 = 0;
    char* buf = (char*)malloc(sizeof(char) * BUF);

    memset(buf, ' ', BUF);

    sys_printline();
    printf("[�����Է¸��]\n");
    sys_print_category_big(array_category);
    printf("�����Ϸ��� ��ǰ�� ��з� ī�װ� ���� �Է� >> ");
    scanf("%d", &intbuf0);

    sys_print_category_small(array_category[intbuf0].arr_small_category);
    printf("�����Ϸ��� ��ǰ�� �Һз� ī�װ� ���� �Է� >> ");
    scanf("%d", &intbuf1);

    printf("��ǰ�� �Է� >> ");
    scanf("%s", buf);


    sys_add(arr_prod, count, array_category[intbuf0].name,
        array_category[intbuf0].arr_small_category[intbuf1].name,
        buf, time(NULL), array_category[intbuf0].arr_small_category[intbuf1].exp_date, 0);

    printf("Category: %s\n", arr_prod[count].category);
    printf("Small Category: %s\n", arr_prod[count].small_category);
    printf("Name: %s\n", arr_prod[count].name);
    printf("Stored Time: %s\n", ctime(&arr_prod[count].stored_time));
    printf("Expiration Time: %s\n", ctime(&arr_prod[count].exp_time));

    printf("Ȯ��[0] ���[1] >> ");
    scanf("%d", &intbuf2);
    if (intbuf2 == 1) {
        sys_del(arr_prod, count, count);
    }

    free(buf);

}






// ���Է� �Լ�
void sys_store_1(PROD* arr_prod, int count, CATE array_category[]) {
    char* buf0 = (char*)malloc(sizeof(char) * BUF);
    char* buf1 = (char*)malloc(sizeof(char) * BUF);
    char* buf2 = (char*)malloc(sizeof(char) * BUF);
    int buf3 = 0;

    sys_printline();
    printf("[���Է¸��]\n");
    printf("�����Ϸ��� ��ǰ�� ��з� ī�װ� �Է� >> ");
    scanf("%s", buf0);

    printf("�����Ϸ��� ��ǰ�� �Һз� ī�װ� �Է� >> ");
    scanf("%s", buf1);

    printf("�����Ϸ��� ��ǰ�� �̸� �Է� >> ");
    scanf("%s", buf2);

    printf("�����Ϸ��� ��ǰ�� ������� �Է�(test) >> ");
    scanf("%d", &buf3);


    sys_add(arr_prod, count, buf0, buf1, buf2, time(NULL), buf3, 1);
    printf("Category: %s\n", arr_prod[count].category);
    printf("Small Category: %s\n", arr_prod[count].small_category);
    printf("Name: %s\n", arr_prod[count].name);
    printf("Stored Time: %s\n", ctime(&arr_prod[count].stored_time));
    printf("Expiration Time: %s\n", ctime(&arr_prod[count].exp_time));

    printf("Ȯ��[0] ���[1] >> ");
    scanf("%d", &buf3);
    if (buf3 == 1) {
        sys_del(arr_prod, count, count);
    }

    free(buf0);
    free(buf1);
    free(buf2);

}







//��������� ���� ��ǰ�� �˻��ϴ� �Լ�
void sys_checkexp(time_t now_time, PROD* arr_prod, int count) {
    printf("���� �ð� : %s", ctime(&now_time));
    for (int i = 0; i < count; i++) {
        if (arr_prod[i].exp_time < now_time && arr_prod[i].name != NULL) {
            printf("������� ���� ��ǰ [%d]%s\nstore %s", i, arr_prod[i].name, ctime(&arr_prod[i].stored_time));
            printf("exp %s\n", ctime(&arr_prod[i].exp_time));
        }
    }
}