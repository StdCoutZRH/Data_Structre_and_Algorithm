#include<stdio.h>
#include<stdlib.h>

//Definition for singly-linked list.
struct ListNode {
	int val;
	struct ListNode *next;
};

/****************** 160.�ཻ���� *******************/

struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {
	struct ListNode*p = headA;
	struct ListNode*q = headB;

	int lena = 0;
	int lenb = 0;
	while (p != NULL)
	{
		++lena;
		p = p->next;
	}
	while (q != NULL)
	{
		++lenb;
		q = q->next;
	}

	int delta = lena >= lenb ? lena - lenb : lenb - lena;
	p = headA;
	q = headB;

	if (lena >= lenb)
	{
		for (int i = 0; i < delta; ++i)
		{
			p = p->next;
		}
	}
	else
	{
		for (int i = 0; i < delta; ++i)
		{
			q = q->next;
		}
	}

	while (q != NULL&&p != NULL)
	{
		if ((q->val == p->val) && (p == q))
			return q;
		q = q->next;
		p = p->next;
	}
	return NULL;
}

/****************** 206.��ת���� *******************/
struct ListNode* reverseList(struct ListNode* head){
	//���ֻ��0����1���ڵ㣬ֱ�ӷ���head
	if (head == NULL || head->next == NULL)
		return head;

	//���ֻ��2������3����ֱ�ӷ�ת
	if (head->next->next == NULL)
	{
		struct ListNode*pp = head->next;
		pp->next = head;
		head->next = NULL;
		head = pp;
		return head;
	}
	if (head->next->next->next == NULL)
	{
		struct ListNode*pp = head->next;
		struct ListNode*qq = head->next->next;
		pp->next = head;
		qq->next = pp;
		head->next = NULL;
		head = qq;
		return head;
	}

	//����3��������ת
	struct ListNode*p;
	struct ListNode*q;
	struct ListNode*r;
	p = head;
	q = p->next;
	r = q->next;

	while (r->next != NULL)
	{
		q->next = p;
		p = q;
		q = r;
		r = r->next;
	}
	q->next = p;
	r->next = q;
	head->next = NULL;
	head = r;

	return head;
}

/****************** 707.������� *******************/

typedef struct {
	struct ListNode*head;
	int length;
} MyLinkedList;

/** Initialize your data structure here. */
MyLinkedList* myLinkedListCreate() {
	MyLinkedList* p = (MyLinkedList*)malloc(sizeof(MyLinkedList));
	if (!p)
	{
		exit(-1);
	}
	p->head = NULL;
	p->length = 0;
	return p;
}

/** Get the value of the index-th node in the linked list. If the index is invalid, return -1. */
int myLinkedListGet(MyLinkedList* obj, int index) {
	if (index > obj->length - 1||index<0||obj->head==NULL)
		return -1;
	
	int i = 0;
	struct ListNode *p = obj->head;

	while (i < index && p->next != NULL)
	{
		p = p->next;
		i++;
		if (i == index) break;
	}

	if (i == index) 
		return p->val;
	else    
		return -1;
}

/** Add a node of value val before the first element of the linked list. After the insertion, the new node will be the first node of the linked list. */
void myLinkedListAddAtHead(MyLinkedList* obj, int val) {

	struct ListNode* p = (struct ListNode*)malloc(sizeof(struct ListNode));
	p->next = NULL;
	p->val = val;
	if (obj->head == NULL)
	{
		obj->head = p;
	}
	else
	{
		p->next = obj->head;
		obj->head = p;
	}
	obj->length++;
}

/** Append a node of value val to the last element of the linked list. */
void myLinkedListAddAtTail(MyLinkedList* obj, int val) {
	struct ListNode* p = (struct ListNode*)malloc(sizeof(struct ListNode));
	p->next = NULL;
	p->val = val;
	if (obj->head == NULL)
	{
		obj->head = p;
	}
	else
	{

		struct ListNode*q = obj->head;
		while (q->next != NULL)
		{
			q = q->next;
		}
		q->next = p;
	}
	obj->length++;
}

/** Add a node of value val before the index-th node in the linked list. If index equals to the length of linked list, the node will be appended to the end of linked list. If index is greater than the length, the node will not be inserted. */
void myLinkedListAddAtIndex(MyLinkedList* obj, int index, int val) {
	struct ListNode* p = (struct ListNode*)malloc(sizeof(struct ListNode));
	if (!p)
	{
		exit(-1);
	}

	p->next = NULL;
	p->val = val;
	if (index < 0)	//indexС��0����ͷ��㴦����
		myLinkedListAddAtHead(obj, val);
	if (obj->head == NULL)
	{
		if (index > 0)
		{
			return;
		}
		else
		{		
			obj->head = p;
			obj->length++;
			return;
		}
	}

	int i = 0;
	ListNode *pp = obj->head;
	ListNode *qq = NULL;

	// ���Ҵ������㼰����һ�����
	while (i < index && pp->next != NULL)
	{
		qq = pp;
		pp = pp->next;
		i++;

		if (i == index) break;
	}

	if (i == index)    // �ڴ�������ǰ����
	{
		if (i == 0) // ��ͷ�������
		{
			pp = p;
			pp->next = obj->head;
			obj->head = pp;
			obj->length++;
		}
		else // ������λ�ò���
		{
			qq->next = p;
			qq->next->next = pp;
			obj->length++;
		}
	}
	else if (i == index - 1)    // ������β����
	{
		pp->next = p;
		obj->length++;
	}
}

/** Delete the index-th node in the linked list, if the index is valid. */
void myLinkedListDeleteAtIndex(MyLinkedList* obj, int index) {
	if (index < 0 || obj->head == NULL) 
		return;

	int i = 0;
	struct ListNode *p = obj->head;
	struct ListNode *q = NULL;

	// ���Ҵ�ɾ����㼰����һ�����
	while (i < index && p->next != NULL)
	{
		q = p;
		p = p->next;
		i++;
		if (i == index) break;
	}

	if (i == index)
	{
		if (i == 0) // ɾ��ͷ���
		{
			obj->head = obj->head->next;
		}
		else  // ɾ���������
		{
			q->next = p->next;
			free(p);
		}
		obj->length--;
	}
}

// free list
void myLinkedListFree(MyLinkedList* obj) {
	if (obj->head == NULL)
		;
	else
	{
		free(obj->head);
	}
}

//print list
void print_list(MyLinkedList*obj)
{
	struct ListNode*p = obj->head;
	while (p != NULL)
	{
		printf("%d ", p->val);
		p = p->next;
	}
	printf("\n");
}
