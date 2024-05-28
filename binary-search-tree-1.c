/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
\
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("--------------    [������]         [2023041030]    --------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr != NULL){ // ptr�� ����ִ��� �˻��Ѵ�.
		inorderTraversal(ptr->left); // �������� �̵��Ѵ�.
		printf(" [%d] ", ptr->key); // key���� ����Ѵ�.
		inorderTraversal(ptr->right); // ���������� �̵��Ѵ�.
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr != NULL){ // ptr�� ������� ���� ���
		printf(" [%d] ", ptr->key); // key���� ����Ѵ�.
		preorderTraversal(ptr->left); // �������� �̵��Ѵ�.
		preorderTraversal(ptr->right); // ���������� �̵��Ѵ�.
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr != NULL){
		postorderTraversal(ptr->left); // �������� �̵��Ѵ�.
		postorderTraversal(ptr->right); // ���������� �̵��Ѵ�.
		printf(" [%d] ", ptr->key); // ket���� ����Ѵ�.
	}

}


int insert(Node* head, int key)
{
	Node *node = (Node *)malloc(sizeof(Node)); // �� ��带 �����Ѵ�.
	node->key = key; // ����� key���� ���޵� key���� �Ҵ��Ѵ�.
	node->left = NULL; // ����� left���� NULL�� �ʱ�ȭ�Ѵ�.
	node->right = NULL; // ����� right���� NULL�� �ʱ�ȭ�Ѵ�.

	if(head->left == NULL){ // Ʈ���� ����ִ� ���
		head->left = node; // �� ��尡 ��Ʈ��尡 �ȴ�.
		return 1;
	}

	Node *n = head->left; // Ʈ���� Ž���� �����͸� �����Ѵ�.
	while (n != NULL){
		if(key == n->key){ // key���� ��ġ�� ���
			printf("Data is duplicated\n");
			return 1;
		}

		if(key < n->key){ // ���޵� key���� �� ���� ���
			if(n->left == NULL){ // ���� ��尡 ����ִ� ���
				n->left == node; // �� ��尡 ���� ��尡 �ȴ�.
				return 1;
			}
			else{ // ������� ���� ���
				n = n->left; // �������� �̵��Ѵ�.
			}
		}

		if(key > n->key){ // ���޵� key���� �� ū ���
			if(n->right == NULL){ // ������ ��尡 ����ִ� ���
				n->right = node; // �� ��尡 ������ ��尡 �ȴ�.
				return 1;
			}
			else{ // ������� ���� ���
				n = n->right; // ���������� �̵��Ѵ�.
			}
		}
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node *n = head->left; // Ʈ���� �̵��� �����͸� �����Ѵ�.
	Node *p = head; // ��带 ������ �����͸� �����Ѵ�.

	if(head == NULL){ // ����尡 ����ִ� ���
		printf("tree is empty.\n");
		return 0;
	}

	if(n == NULL){ // ��Ʈ��尡 ����ִ� ���
		printf("tree is empty.\n");
		return 0;
	}

	while(n != NULL){ // n�� NULL�� �� ������ �ݺ��Ѵ�.
		if(key == n->key){ // ���޹��� key���� ���� ����� ���
			if((n->left == NULL) && (n->right == NULL)){ // ��������� ���
				if(p->left == n){ // �θ����� ���� �ڽ��� ���
					p->left = NULL; // �θ����� ������ NULL�� ����Ų��.
					free(n); // �ڽĳ�带 �����Ѵ�.
					return 0;
				}
				else if(p->right == n){ // �θ����� ������ �ڽ��� ���
					p->right = NULL; // �θ����� �������� NULL�� ����Ų��.
					free(n); // �ڽĳ�带 �����Ѵ�.
					return 0;
				}
				else { // ������尡 �ƴ� ���
					printf("node is not a leafnode.\n");
					return 0;
				}
			}
		}

		if(key > n->key){ // ���޹��� key ���� �� Ŭ ���
			p = n; // p�� n�� ��ġ�� �̵��Ѵ�.
			n = n->right; // n�� ������ ���� �̵��Ѵ�.
		}
		else if(key < n->key){
			p = n; // p�� n�� ��ġ�� �̵��Ѵ�.
			n = n->left; // n�� ���� �븣�� �̵��Ѵ�.
		}
	}

	printf("key node is not exist in tree.\n"); // ���޹��� key ���� �ش��ϴ� ��尡 ���� ���
	return 0;

}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL || ptr->key == key){ // ptr�� ����ְų�, ���޹��� key���� ����� key���� ��ġ�ϴ� ���
		return ptr; // ptr�� ��ȯ�Ѵ�.
	}

	if(key < ptr->key){ // ���޹��� key���� ����� key������ ���� ���
		return searchRecursive(ptr->left, key); // ����� �������� �̵��Ѵ�.
	}

	else{
		return searchRecursive(ptr->right, key); // ����� ���������� �̵��Ѵ�.
	}
}

Node* searchIterative(Node* head, int key)
{
	Node *n = head->left; // Ʈ���� Ž���� �����͸� �����Ѵ�.

	while(n != NULL){ // n�� NULL�� �� ������ �ݺ��Ѵ�.
		if(key == n->key){ // ���޹��� key���� �������� key���� ��ġ�ϴ� ���
			return n; // n�� ��ȯ�Ѵ�.
		}
		if(key < n->key){ // ���޹��� key���� �������� key������ ���� ���
			n = n->left; // �����͸� �������� �̵��Ѵ�.
		}
		else{
			n = n->right; // �����͸� ���������� �̵��Ѵ�.
		}
	}

	return NULL; // ã�� ���� ��� NULL�� ��ȯ�Ѵ�.
}


int freeBST(Node* head)
{
	if(head == NULL){ // head�� NULL�� ���
		return 0;
	}
	if(head->left != NULL){ // ���� ��尡 NULL�� �ƴ� ���
		freeBST(head->left); // ���� �ڽĳ�带 �����Ѵ�.
	}
	if(head->right != NULL){ // ������ ��尡 NULL�� �ƴ� ���
		freeBST(head->right); // ������ �ڽĳ�带 �����Ѵ�.
	}

	free(head); // ��� ��带 �����Ѵ�.

	return 1;
}





