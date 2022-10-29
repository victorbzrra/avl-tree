#include <stdio.h>
#include <stdlib.h>

#define True 1
#define False 0

typedef struct node {
	int key;
	int height;
	struct node * left;
	struct node * right;
}Node;

// variável global
int size_of_tree = 0;

/* Retorna o maior valor entre os elementos */
int max(int a, int b) {
    if (a > b) return a;
	return b;
}

/* Retorna a altura de um node */
int height(Node * node) {
	if (node == NULL) return 0;
	return 1 + max(height(node -> left), height(node -> right));
}

/* Cria e retorna um novo node */
Node * new_node(int key) {
	Node * node = (Node *) malloc(sizeof(Node));

	node -> key = key;
	node -> left = NULL;
	node -> right = NULL;
	node -> height = 0;
	
    return node;
}

/* Executa a rotação a direita */
Node * right_rotate(Node * root) {
	Node * node = root -> left;
    Node * aux = node -> right;

	node -> right = root;
	root -> left = aux;

	root -> height = height(root);
	node -> height = height(node);

	return node;
}

/* Executa a rotação a esquerda */
Node * left_rotate(Node * root) {
	Node * node = root -> right;
	Node * aux = node -> left;

	node -> left = root;
	root -> right = aux;

	root -> height = height(root);
	node -> height = height(node);

	return node;
}

/* Retorna o fator de bal de um node */
int get_balance(Node * node) {
	if (node == NULL) return 0;
	return height(node -> left) - height(node -> right);
}

/* Executa a inserção de um novo node */
Node * insert(Node * node, int key) {

	/* Caso em que a avl está vazia */
	if (node == NULL) return new_node(key);
	if (key < node -> key) node -> left = insert(node -> left, key);
	else if (key > node -> key) node -> right = insert(node -> right, key);
	else return node;

	/* Atualiza a altura do node anterior */
	node -> height = height(node);

	/* Obtém o fator de balanciamento do node anterior */
	int balance = get_balance(node);

	/* Caso Left Left (LL) */ 
	if (balance > 1 && key < node -> left -> key) return right_rotate(node);

	/* Caso Right Right (RR) */ 
	if (balance < -1 && key > node -> right -> key) return left_rotate(node);

	/* Caso Left Right (LR) */ 
	if (balance > 1 && key > node -> left -> key) {
		node -> left = left_rotate(node -> left);
		return right_rotate(node);
	}

	/* Caso Right Left (RL) */ 
	if (balance < -1 && key < node -> right -> key) {
		node -> right = right_rotate(node -> right);
		return left_rotate(node);
	}

	return node;
}

int verify(Node * root) {
	if (root != NULL && (root -> height <= 1 || root -> height >= -1)) {
		verify(root -> left);
		verify(root -> right);
	} else return False;
    return True;
}

int count(Node * root) {
    if (root != NULL) {
        size_of_tree += 1;
        count(root -> left);
        count(root -> right);
    }

    return size_of_tree;
}

Node * min_node(Node * node) {
    Node * target = node;
    while (target -> left != NULL) target = target -> left;
    
    return target;
}

Node * delete_node(Node * root, int key) {
    if (root == NULL) return root;
    if (key < root -> key) root -> left = delete_node(root -> left, key);
    else if (key > root -> key) root -> right = delete_node(root -> right, key);
    else {
        Node * aux = NULL;
        if ((root -> left == NULL || root -> right == NULL)) {
            aux = root -> left ? root -> left : root -> right;
            if (aux == NULL) {
                aux = root;
                root = NULL;
            } 
            else * root = * aux;
            free(aux);
        }
        else {
            aux = min_node(root -> right);
            root -> key = aux -> key;
            root -> right = delete_node(root -> right, aux -> key);
        }
    }

    if (root == NULL) {
        return root;
        root -> height = 1 + max(height(root -> left), height(root -> right));
        int balance = get_balance(root);

        if (balance > 1 && get_balance(root -> left) >= 0) return right_rotate(root);
        if (balance > 1 && get_balance(root -> left) < 0) {
            root -> left = left_rotate(root -> left);
            return right_rotate(root);
        }
        if (balance < -1 && get_balance(root -> right) <= 0) return left_rotate(root);
        if (balance < -1 && get_balance(root -> right) > 0) {
            root -> right = right_rotate(root -> right);
            return left_rotate(root);
        }
    }

    return root;
}

int main() {
    Node * root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    int verifyAVL = verify(root);
    printf("É AVL? %s\n", (verifyAVL == 1) ? "SIM" : "NÃO");
    printf("TAMANHO DA AVL: %d\n", count(root));

    size_of_tree = 0;
    delete_node(root, 30);

    verifyAVL = verify(root);
    printf("É AVL? %s\n", (verifyAVL == 1) ? "SIM" : "NÃO");
    printf("TAMANHO DA AVL: %d\n", count(root));

    return 0;
}