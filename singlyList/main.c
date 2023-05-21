#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef int element;

typedef struct ListNode {
	element data;
	struct ListNode* link;
}ListNode;

void error(char* message) {
	fprintf(stderr, "%s\n", message);
	return;
}

ListNode* insert_first(ListNode* head, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}

ListNode* delete_first(ListNode* head) {
	ListNode* removed;
	if (head == NULL)
		return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

ListNode* delete(ListNode* head, ListNode* pre) {
	if (pre == NULL) {
		printf("Invalid position.\n");
		return head;
	}
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);
	return head;
}

int length(ListNode* head) {
	int length = 0;
	ListNode* current = head;

	while (current != NULL) {
		length++;
		current = current->link;
	}

	return length;
}

void print_list(ListNode* head) {
	printf("List: ");
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("%d->", p->data);
	printf("\n");
}

void print_menu(void) {
	printf("\nMenu\n");
	printf("1. Insert\n");
	printf("2. Delete\n");
	printf("3. Print\n");
	printf("0. Exit\n");
	printf("Enter the menu: ");
}

int main() {
	ListNode* head = NULL;
	ListNode* pre = NULL;
	int choice, data, pos;

	while (1) {
		print_menu();
		scanf_s("%d", &choice);

		switch (choice) {
		case 0:
			printf("Exit the program.\n");
			exit(0);

		case 1:
			printf("Enter the number and position: ");
			scanf_s("%d %d", &data, &pos);
			int len = length(head);
			int count = 0;
			if (pos != 0 && len == 0) {
				printf("List is empty. Insert at position 0\n");
				pos = 0;
			}
			else if (pos > len) {
				printf("The last index is %d. Insert at the end of the list.\n", len - 1);
				pos = len;
			}
			if (pos == 0)
				head = insert_first(head, data);
			else {
				pre = head;
				for (int i = 0; i < pos - 1; i++) {
					pre = pre->link;
					count++;
				}
				head = insert(head, pre, data);
				count++;
			}
			printf("\nMove along the link: %d\n", count);
			break;

		case 2:
			if (head == NULL) {
				printf("List is empty.\n");
				break;
			}
			else {
				int count = 0;
				printf("Enter the position to delete: ");
				scanf_s("%d", &pos);
				int len = length(head);
				if (pos < 0 || pos >= len) {
					printf("Invalid position.\n");
					break;
				}
				else if (pos == 0)
					head = delete_first(head);
				else {
					pre = head;
					for (int i = 0; i < pos - 1; i++) {
						pre = pre->link;
						count++;
					}
					head = delete(head, pre);
					count++;
				}
				printf("\nMove along the link: %d\n", count);
				break;
			}

		case 3:
			print_list(head);
			break;

		default:
			printf("Invalid Menu. Please select again. \n");
			while (getchar() != '\n');
			break;
		}
	}
}
