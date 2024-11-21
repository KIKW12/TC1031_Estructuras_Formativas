/**
 * Nombre: Juan Enrique Ayala Zapata
 * Matricula: A01711235
 */

#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>
#include <queue>
#include <algorithm>

template <class T>
class BST {
private:
    struct Node {
        T value;
        Node* left;
        Node* right;

        Node(T val) : value(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

    // Helper functions
    void deleteTree(Node* node);
    void inOrder(Node* node, std::stringstream& aux) const;
    void preOrder(Node* node, std::stringstream& aux) const;
    void postOrder(Node* node, std::stringstream& aux) const;
    void levelOrder(Node* node, std::stringstream& aux) const;
    int getHeight(Node* node) const;
    std::string getAncestors(Node* node, T val, std::stringstream& aux) const;
    int getLevel(Node* node, T val, int level) const;

public:
    BST() : root(nullptr) {}
    ~BST() { deleteTree(root); }

    void add(T val);
    bool find(T val) const;
    std::string visit() const;
    int height() const;
    std::string ancestors(T val) const;
    int whatlevelamI(T val) const;
};

// Implementation of member functions

template <class T>
void BST<T>::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

template <class T>
void BST<T>::add(T val) {
    if (!root) {
        root = new Node(val);
        return;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current) {
        parent = current;
        if (val < current->value)
            current = current->left;
        else if (val > current->value)
            current = current->right;
        else
            return; // Value already exists
    }

    if (val < parent->value)
        parent->left = new Node(val);
    else
        parent->right = new Node(val);
}

template <class T>
bool BST<T>::find(T val) const {
    Node* current = root;
    while (current) {
        if (val == current->value)
            return true;
        else if (val < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

template <class T>
void BST<T>::inOrder(Node* node, std::stringstream& aux) const {
    if (node) {
        inOrder(node->left, aux);
        aux << node->value << " ";
        inOrder(node->right, aux);
    }
}

template <class T>
void BST<T>::preOrder(Node* node, std::stringstream& aux) const {
    if (node) {
        aux << node->value << " ";
        preOrder(node->left, aux);
        preOrder(node->right, aux);
    }
}

template <class T>
void BST<T>::postOrder(Node* node, std::stringstream& aux) const {
    if (node) {
        postOrder(node->left, aux);
        postOrder(node->right, aux);
        aux << node->value << " ";
    }
}

template <class T>
void BST<T>::levelOrder(Node* node, std::stringstream& aux) const {
    if (!node) return;

    std::queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        aux << current->value << " ";

        if (current->left)
            q.push(current->left);
        if (current->right)
            q.push(current->right);
    }
}

template <class T>
std::string BST<T>::visit() const {
    std::stringstream aux;
    
    aux << "[";
    preOrder(root, aux);
    aux.seekp(-1, std::ios_base::end);
    aux << "]\n[";
    
    inOrder(root, aux);
    aux.seekp(-1, std::ios_base::end);
    aux << "]\n[";
    
    postOrder(root, aux);
    aux.seekp(-1, std::ios_base::end);
    aux << "]\n[";
    
    levelOrder(root, aux);
    aux.seekp(-1, std::ios_base::end);
    aux << "]";
    
    return aux.str();
}

template <class T>
int BST<T>::getHeight(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(getHeight(node->left), getHeight(node->right));
}

template <class T>
int BST<T>::height() const {
    return getHeight(root);
}

template <class T>
std::string BST<T>::getAncestors(Node* node, T val, std::stringstream& aux) const {
    if (!node) return "";
    if (node->value == val) return aux.str();

    aux << node->value << " ";
    if (val < node->value)
        return getAncestors(node->left, val, aux);
    else
        return getAncestors(node->right, val, aux);
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
    aux << "[";
    std::string result = getAncestors(root, val, aux);
    if (!result.empty()) {
        aux.seekp(-1, std::ios_base::end);
        aux << "]";
        return aux.str();
    }
    return "[]";
}

template <class T>
int BST<T>::getLevel(Node* node, T val, int level) const {
    if (!node) return -1;
    if (node->value == val) return level;

    int leftLevel = getLevel(node->left, val, level + 1);
    if (leftLevel != -1) return leftLevel;

    return getLevel(node->right, val, level + 1);
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    return getLevel(root, val, 1);
}

#endif // BST_H