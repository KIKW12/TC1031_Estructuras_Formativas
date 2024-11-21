/**
 * Nombre: Juan Enrique Ayala Zapata
 * Matricula: A01711235
 */

#ifndef SPLAY_H
#define SPLAY_H

#include <string>
#include <sstream>

template <class T> class SplayTree;

template <class T>
class Node {
private:
    T value;
    Node *left, *right, *parent;

    Node<T>* succesor();
    Node<T>* rot_right(Node<T>* child);
    Node<T>* rot_left(Node<T>* child);

public:
    Node(T val) : value(val), left(0), right(0), parent(0) {}
    Node(T val, Node<T> *le, Node<T> *ri, Node<T> *pa) : 
        value(val), left(le), right(ri), parent(pa) {}
    
    void print_tree(std::stringstream &aux) const;
    void preorder(std::stringstream &aux) const;
    void inorder(std::stringstream &aux) const;

    friend class SplayTree<T>;
};

template <class T>
void Node<T>::print_tree(std::stringstream &aux) const {
    if (parent != 0){
        aux << "\n node " << value;
        aux << " parent " << parent->value;
    }else
        aux << "\n root " << value;
    if (left != 0)
        aux << " left " << left->value;
    if (right != 0)
        aux << " right " << right->value;
    aux << "\n";
    if (left != 0) {
        left->print_tree(aux);
    }
    if (right != 0) {
        right->print_tree(aux);
    }
}

template <class T>
void Node<T>::preorder(std::stringstream &aux) const {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

template <class T>
void Node<T>::inorder(std::stringstream &aux) const {
    if (left != 0) {
        left->inorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
    if (right != 0) {
        right->inorder(aux);
    }
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* child) {
    Node<T> *parent = child->parent;
    
    if(parent->parent) {
        if(parent->parent->left == parent)
            parent->parent->left = child;
        else
            parent->parent->right = child;
    }
    
    child->parent = parent->parent;
    parent->parent = child;
    parent->left = child->right;
    if(child->right)
        child->right->parent = parent;
    child->right = parent;
    
    return child;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* child) {
    Node<T> *parent = child->parent;
    
    if(parent->parent) {
        if(parent->parent->left == parent)
            parent->parent->left = child;
        else
            parent->parent->right = child;
    }
    
    child->parent = parent->parent;
    parent->parent = child;
    parent->right = child->left;
    if(child->left)
        child->left->parent = parent;
    child->left = parent;
    
    return child;
}

template <class T>
Node<T>* Node<T>::succesor() {
    Node<T> *le, *ri;

    le = right;
    ri = right;

    if (right == 0) {
        return 0;
    }
    
    if (right->left == 0) {
        right = right->right;
        ri->right = 0;
        return ri;
    }

    while (le->left != 0) {
        ri = le;
        le = le->left;
    }
    
    ri->left = le->right;
    if(le->right)
        le->right->parent = ri;
    le->right = 0;
    
    return le;
}

template <class T>
class SplayTree {
private:
    Node<T> *root;
    
    void splay(Node<T>* node);

public:
    SplayTree() : root(0) {}
    ~SplayTree();
    bool empty() const;
    void add(T);
    bool find(T);
    void remove(T);
    void removeAll();
    std::string inorder() const;
    std::string preorder() const;
};

template <class T>
void SplayTree<T>::splay(Node<T>* node) {
    while(node->parent != 0) {
        Node<T>* parent = node->parent;
        Node<T>* grand = parent->parent;
        
        if(grand == 0) { // Zig step
            if(parent->left == node)
                root = node->rot_right(node);
            else
                root = node->rot_left(node);
        } else {
            if(grand->left == parent) {
                if(parent->left == node) { // Zig-zig step
                    node->rot_right(parent);
                    root = node->rot_right(node);
                } else { // Zig-zag step
                    node->rot_left(node);
                    root = node->rot_right(node);
                }
            } else {
                if(parent->right == node) { // Zig-zig step
                    node->rot_left(parent);
                    root = node->rot_left(node);
                } else { // Zig-zag step
                    node->rot_right(node);
                    root = node->rot_left(node);
                }
            }
        }
    }
    root = node;
}

template <class T>
bool SplayTree<T>::empty() const {
    return (root == 0);
}

template <class T>
void SplayTree<T>::add(T val) {
    if (root == 0) {
        root = new Node<T>(val);
        return;
    }
    
    Node<T> *curr = root;
    while(curr != 0) {
        if(val < curr->value) {
            if(curr->left == 0) {
                curr->left = new Node<T>(val);
                curr->left->parent = curr;
                splay(curr->left);
                return;
            }
            curr = curr->left;
        } else {
            if(curr->right == 0) {
                curr->right = new Node<T>(val);
                curr->right->parent = curr;
                splay(curr->right);
                return;
            }
            curr = curr->right;
        }
    }
}

template <class T>
bool SplayTree<T>::find(T val) {
    if (root == 0) {
        return false;
    }
    
    Node<T> *curr = root;
    while(curr != 0) {
        if(val == curr->value) {
            splay(curr);
            return true;
        }
        if(val < curr->value)
            curr = curr->left;
        else
            curr = curr->right;
    }
    return false;
}

template <class T>
void SplayTree<T>::remove(T val) {
    if (root == 0) {
        return;
    }
    
    if(!find(val)) {
        return;
    }
    
    Node<T> *succ;
    if(root->left == 0) {
        succ = root->right;
        delete root;
        if(succ)
            succ->parent = 0;
        root = succ;
    } else if(root->right == 0) {
        succ = root->left;
        delete root;
        if(succ)
            succ->parent = 0;
        root = succ;
    } else {
        Node<T> *leftTree = root->left;
        leftTree->parent = 0;
        Node<T> *rightTree = root->right;
        rightTree->parent = 0;
        delete root;
        
        root = leftTree;
        while(leftTree->right != 0)
            leftTree = leftTree->right;
        
        splay(leftTree);
        root->right = rightTree;
        rightTree->parent = root;
    }
}

template <class T>
void SplayTree<T>::removeAll() {
    if (root != 0) {
        delete root;
        root = 0;
    }
}

template <class T>
SplayTree<T>::~SplayTree() {
    removeAll();
}

template <class T>
std::string SplayTree<T>::inorder() const {
    std::stringstream aux;
    
    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string SplayTree<T>::preorder() const {
    std::stringstream aux;
    
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

#endif