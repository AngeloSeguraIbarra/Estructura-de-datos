/**
 * Angelo segura ibarra
 * A01711723
 * BST
 */
#ifndef BST_H_
#define BST_H_

#include <string>
#include <sstream>
#include <vector>

template <class T> class BST;

template <class T>
class TreeNode {
private:
    T value;
    TreeNode *left, *right;

public:
    TreeNode(T);
    void add(T);
    bool find(T);
    void inorder(std::stringstream&) const;
    void preorder(std::stringstream&) const;
    void postorder(std::stringstream&) const;
    int height() const;
    bool ancestors(T, std::stringstream&) const;
    int whatlevelamI(T, int level) const;

    friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0) {}

template <class T>
void TreeNode<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            left->add(val);
        } else {
            left = new TreeNode<T>(val);
        }
    } else {
        if (right != 0) {
            right->add(val);
        } else {
            right = new TreeNode<T>(val);
        }
    }
}

template <class T>
bool TreeNode<T>::find(T val) {
    if (val == value) {
        return true;
    } else if (val < value) {
        return (left != 0 && left->find(val));
    } else {
        return (right != 0 && right->find(val));
    }
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
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
void TreeNode<T>::preorder(std::stringstream &aux) const {
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
void TreeNode<T>::postorder(std::stringstream &aux) const {
    if (left != 0) {
        left->postorder(aux);
    }
    if (right != 0) {
        right->postorder(aux);
    }
    if (aux.tellp() != 1) {
        aux << " ";
    }
    aux << value;
}

template <class T>
int TreeNode<T>::height() const {
    int leftHeight = (left != 0) ? left->height() : 0;
    int rightHeight = (right != 0) ? right->height() : 0;
    return 1 + std::max(leftHeight, rightHeight);
}

template <class T>
bool TreeNode<T>::ancestors(T val, std::stringstream &aux) const {
    std::vector<T> nodes;  // Vector para almacenar los nodos padres
    bool found = false;
    const TreeNode* current = this;

    while (current != 0) {
        if (val == current->value) {
            found = true;  
            break;
        }
        nodes.push_back(current->value);  

        if (val < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (found) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (i > 0) {
                aux << " ";  
            }
            aux << nodes[i];
        }
        return true;
    }

    return false;
}


template <class T>
int TreeNode<T>::whatlevelamI(T val, int level) const {
    if (val == value) {
        return level;
    } else if (val < value && left != 0) {
        return left->whatlevelamI(val, level + 1);
    } else if (val > value && right != 0) {
        return right->whatlevelamI(val, level + 1);
    }
    return -1; // Not found
}

template <class T>
class BST {
private:
    TreeNode<T> *root;

public:
    BST();
    ~BST();
    bool empty() const;
    void add(T);
    bool find(T) const;
    std::string inorder() const;
    std::string preorder() const;
    std::string postorder() const;
    std::string visit() const;
    int height() const;
    std::string ancestors(T) const;
    int whatlevelamI(T) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
}

template <class T>
bool BST<T>::empty() const {
    return root == 0;
}

template <class T>
void BST<T>::add(T val) {
    if (root != 0) {
        if (!root->find(val)) {
            root->add(val);
        }
    } else {
        root = new TreeNode<T>(val);
    }
}

template <class T>
bool BST<T>::find(T val) const {
    if (root != 0) {
        return root->find(val);
    } else {
        return false;
    }
}

template <class T>
std::string BST<T>::inorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->inorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::preorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->preorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::postorder() const {
    std::stringstream aux;
    aux << "[";
    if (!empty()) {
        root->postorder(aux);
    }
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::visit() const {
    std::stringstream aux;
    aux << preorder() << "\n" << inorder() << "\n" << postorder() << "\n" << preorder();
    return aux.str();
}

template <class T>
int BST<T>::height() const {
    return (root != 0) ? root->height() : 0;
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
    aux << "[";  
    if (root != 0 && root->find(val)) {  
        std::stringstream temp;
        root->ancestors(val, temp);
        std::string ancestorsList = temp.str();
        if (!ancestorsList.empty()) {
            aux << ancestorsList;  
        }
    }
    aux << "]";  
    return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    if (root != 0) {
        return root->whatlevelamI(val, 1);
    }
    return -1;
}

#endif /* BST_H_ */