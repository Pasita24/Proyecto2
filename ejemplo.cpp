#include <iostream>
#include <map>
#include <vector>

using namespace std;

// Estructura para el nodo del árbol
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Función para insertar un elemento en el árbol binario de búsqueda
void bstInsert(Node*& root, int element, Node* parent = nullptr) {
    if (root == nullptr) {
        root = new Node(element);
        cout << element << " Insertado" << endl;
        return;
    }

    if (element < root->data) {
        bstInsert(root->left, element, root);
    } else if (element > root->data) {
        bstInsert(root->right, element, root);
    }
}

// Función para imprimir el árbol
void printTree(Node* root) {
    if (root == nullptr) return;

    printTree(root->left);
    cout << root->data << " ";
    printTree(root->right);
}

int main() {
    vector<int> elements = {5, 8, 10, 3, 1, 6, 9, 7, 2, 0, 4};

    Node* Root = nullptr;
    Root = new Node(elements[0]);
    cout << elements[0] << " Insertado como raíz del árbol" << endl;

    for (size_t i = 1; i < elements.size(); i++) {
        bstInsert(Root, elements[i]);
    }

    cout << "Estado final del árbol:" << endl;
    printTree(Root);
    cout << endl;

    return 0;
}
