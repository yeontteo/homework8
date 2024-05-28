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
		printf("--------------    [남연서]         [2023041030]    --------------\n");
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
	if(ptr != NULL){ // ptr이 비어있는지 검사한다.
		inorderTraversal(ptr->left); // 왼쪽으로 이동한다.
		printf(" [%d] ", ptr->key); // key값을 출력한다.
		inorderTraversal(ptr->right); // 오른쪽으로 이동한다.
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr != NULL){ // ptr이 비어있지 않은 경우
		printf(" [%d] ", ptr->key); // key값을 출력한다.
		preorderTraversal(ptr->left); // 왼쪽으로 이동한다.
		preorderTraversal(ptr->right); // 오른쪽으로 이동한다.
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr != NULL){
		postorderTraversal(ptr->left); // 왼쪽으로 이동한다.
		postorderTraversal(ptr->right); // 오른쪽으로 이동한다.
		printf(" [%d] ", ptr->key); // ket값을 출력한다.
	}

}


int insert(Node* head, int key)
{
	Node *node = (Node *)malloc(sizeof(Node)); // 새 노드를 생성한다.
	node->key = key; // 노드의 key값에 전달된 key값을 할당한다.
	node->left = NULL; // 노드의 left값을 NULL로 초기화한다.
	node->right = NULL; // 노드의 right값을 NULL로 초기화한다.

	if(head->left == NULL){ // 트리가 비어있는 경우
		head->left = node; // 새 노드가 루트노드가 된다.
		return 1;
	}

	Node *n = head->left; // 트리를 탐색할 포인터를 생성한다.
	while (n != NULL){
		if(key == n->key){ // key값이 겹치는 경우
			printf("Data is duplicated\n");
			return 1;
		}

		if(key < n->key){ // 전달된 key값이 더 작은 경우
			if(n->left == NULL){ // 왼쪽 노드가 비어있는 경우
				n->left == node; // 새 노드가 왼쪽 노드가 된다.
				return 1;
			}
			else{ // 비어있지 않을 경우
				n = n->left; // 왼쪽으로 이동한다.
			}
		}

		if(key > n->key){ // 전달된 key값이 더 큰 경우
			if(n->right == NULL){ // 오른쪽 노드가 비어있는 경우
				n->right = node; // 새 노드가 오른쪽 노드가 된다.
				return 1;
			}
			else{ // 비어있지 않은 경우
				n = n->right; // 오른쪽으로 이동한다.
			}
		}
	}
}

int deleteLeafNode(Node* head, int key)
{
	Node *n = head->left; // 트리를 이동할 포인터를 생성한다.
	Node *p = head; // 노드를 삭제할 포인터를 생성한다.

	if(head == NULL){ // 헤드노드가 비어있는 경우
		printf("tree is empty.\n");
		return 0;
	}

	if(n == NULL){ // 루트노드가 비어있는 경우
		printf("tree is empty.\n");
		return 0;
	}

	while(n != NULL){ // n이 NULL이 될 때까지 반복한다.
		if(key == n->key){ // 전달받은 key갓과 같은 노드일 경우
			if((n->left == NULL) && (n->right == NULL)){ // 리프노드일 경우
				if(p->left == n){ // 부모노드의 왼쪽 자식일 경우
					p->left = NULL; // 부모노드의 왼쪽이 NULL을 가리킨다.
					free(n); // 자식노드를 삭제한다.
					return 0;
				}
				else if(p->right == n){ // 부모노드의 오른쪽 자식일 경우
					p->right = NULL; // 부모노드의 오른쪽이 NULL을 가리킨다.
					free(n); // 자식노드를 삭제한다.
					return 0;
				}
				else { // 리프노드가 아닐 경우
					printf("node is not a leafnode.\n");
					return 0;
				}
			}
		}

		if(key > n->key){ // 전달받은 key 값이 더 클 경우
			p = n; // p가 n의 위치로 이동한다.
			n = n->right; // n이 오른쪽 노드로 이동한다.
		}
		else if(key < n->key){
			p = n; // p가 n의 위치로 이동한다.
			n = n->left; // n이 왼쪽 노르도 이동한다.
		}
	}

	printf("key node is not exist in tree.\n"); // 전달받은 key 값에 해당하는 노드가 없을 경우
	return 0;

}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL || ptr->key == key){ // ptr이 비어있거나, 전달받은 key값과 노드의 key값이 일치하는 경우
		return ptr; // ptr을 반환한다.
	}

	if(key < ptr->key){ // 전달받은 key값이 노드의 key값보다 작은 경우
		return searchRecursive(ptr->left, key); // 노드의 왼쪽으로 이동한다.
	}

	else{
		return searchRecursive(ptr->right, key); // 노드의 오른쪽으로 이동한다.
	}
}

Node* searchIterative(Node* head, int key)
{
	Node *n = head->left; // 트리를 탐색할 포인터를 생성한다.

	while(n != NULL){ // n이 NULL이 될 때까지 반복한다.
		if(key == n->key){ // 전달받은 key값과 포인터의 key값이 일치하는 경우
			return n; // n을 반환한다.
		}
		if(key < n->key){ // 전달받은 key값이 포인터의 key값보다 작은 경우
			n = n->left; // 포인터를 왼쪽으로 이동한다.
		}
		else{
			n = n->right; // 포인터를 오른쪽으로 이동한다.
		}
	}

	return NULL; // 찾지 못한 경우 NULL을 반환한다.
}


int freeBST(Node* head)
{
	if(head == NULL){ // head가 NULL인 경우
		return 0;
	}
	if(head->left != NULL){ // 왼쪽 노드가 NULL이 아닌 경우
		freeBST(head->left); // 왼쪽 자식노드를 해제한다.
	}
	if(head->right != NULL){ // 오른쪽 노드가 NULL이 아닌 경우
		freeBST(head->right); // 오른쪽 자식노드를 해제한다.
	}

	free(head); // 헤드 노드를 해제한다.

	return 1;
}





