#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 노드 타입
typedef struct ListNode {
	int coef;
	int expon;
	struct ListNode* link;
}ListNode;

// 리스트 헤더 타입
typedef struct ListType {
	int size; // 노드 개수
	ListNode* head; // 처음으로
	ListNode* tail; // 마지막으로
}ListType;

// 오류 처리
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 리스트 헤더 생성 함수
ListNode* create()
{
	ListType* plist = (ListType*)malloc(sizeof(ListType));
	plist->size = 0;
	plist->head = plist->tail = NULL;
	return plist;
}

// 리스트 마지막에 coef와 expon 추가
void insert_last(ListType* plist, int coef, int expon)
{
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));

	if (temp == NULL) error("메모리 할당 에러");

	temp->coef = coef;
	temp->expon = expon;
	temp->link = NULL;

	if (plist->tail == NULL) {
		plist->head = plist->tail = temp;
	}
	else {
		plist->tail->link = temp;
		plist->tail = temp;
	}
	plist->size++;
}

// 다항식 2개 더하기
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{
	ListNode* a = plist1->head;
	ListNode* b = plist2->head;
	int sum;

	while (a && b)
	{
		if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum != 0) insert_last(plist3, sum, a->expon);
			a = a->link; b = b->link;
		}

		else if (a->expon > b->expon) {
			insert_last(plist3, a->coef, a->expon);
			a = a->link;
		}

		else {
			insert_last(plist3, b->coef, b->expon);
			b = b->link;
		}
	}

	for (; a != NULL; a = a->link) {
		insert_last(plist3, a->coef, a->expon);
	}
	for (; b != NULL; b->link) {
		insert_last(plist3, b->coef, b->expon);
	}
}

// 다항식 출력
void poly_print(ListType* plist)
{
	ListNode* p = plist->head;

	printf("--------------------\n");
	for (; p; p = p->link) {
		printf("%d^%d + ", p->coef, p->expon);
	}
	printf("\n");
}

int main()
{
	ListType* list1, * list2, * list3;

	list1 = create();
	list2 = create();
	list3 = create();
	
	// 문자열 2개 입력 변수
	char list1_enter[30];
	char list2_enter[30];

	// coef = 계수, expon = 지수
	int coef1 = 0;
	int expon1 = 0;
	int coef2 = 0;
	int expon2 = 0;

	printf("첫번째 다항식을 입력해주세요(ex.2x3+2x1+3x0) : ");
	scanf_s("%s",list1_enter,sizeof(list1_enter));
	printf("두번째 다항식을 입력해주세요(ex.2x3+2x1+3x0) : ");
	scanf_s("%s", list2_enter,sizeof(list2_enter));

	// x 앞에 있는 수는 계수 / 뒤에 있는 수는 지수로 저장하기
	for (int i = 1; i < 30; i++)
	{
		if (list1_enter[i] == 'x') {
			char *s1 = &list1_enter[i - 1];
			char *s2 = &list1_enter[i + 1];

			coef1 = atoi(s1);
			expon1 = atoi(s2);

			insert_last(list1, coef1, expon1);
		}

		if (list2_enter[i] == 'x') {
			char* s3 = &list2_enter[i - 1];
			char *s4 = &list2_enter[i + 1];

			coef2 = atoi(s3);
			expon2 = atoi(s4);

			insert_last(list2, coef2, expon2);
		}
	}

	printf(" %s\n", list1_enter); // 다항식 1 출력
	printf("+%s\n", list2_enter); // 다항식 2 출력
	poly_add(list1, list2, list3); // 다항식 1 + 다항식 2
	poly_print(list3); // 다항식 결과 출력
	
	free(list1); free(list2); free(list3);
}