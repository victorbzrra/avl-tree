#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
};

/* Obtém o maior valor entre dois elementos */
int max(int a, int b) {
    if (a > b) {
        return a;
    }

    return b;
}

/* Calcula a altura de um nó */
int height(struct Node *node) {
    if (node == NULL) {
        return 0;
    }

    return 1 + max(height(node -> left), height(node -> right));
}

/* Obtém o bal de um um nó */
int getBalance(struct Node *node) {
    if (N == NULL) {
        return 0;
    }

    return height(node -> left) - height(node -> right);
}

void main() {

}