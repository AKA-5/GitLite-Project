#include "Nodes.h"
#include "Tree.h"
#include "FileManager.h"
template <typename T>
class RedBlackTree : public Tree<T> {
private:
    RBNode<T>* root;
    int count;

    void rotateLeft(RBNode<T>*& node) {
        RBNode<T>* child = node->descendants[1];
        node->descendants[1] = child->descendants[0];
        if (node->descendants[1] != nullptr)
            node->descendants[1]->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->descendants[0])
            node->parent->descendants[0] = child;
        else
            node->parent->descendants[1] = child;
        child->descendants[0] = node;
        node->parent = child;
    }

    void rotateRight(RBNode<T>*& node) {
        RBNode<T>* child = node->descendants[0];
        node->descendants[0] = child->descendants[1];
        if (node->descendants[0] != nullptr)
            node->descendants[0]->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->descendants[0])
            node->parent->descendants[0] = child;
        else
            node->parent->descendants[1] = child;
        child->descendants[1] = node;
        node->parent = child;
    }

    void fixAfterInsertion(RBNode<T>*& node) {
        RBNode<T>* parent = nullptr;
        RBNode<T>* grandparent = nullptr;

        while (node != root && node->color == 0 && node->parent->color == 0) { // 0: RED
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->descendants[0]) {
                RBNode<T>* uncle = grandparent->descendants[1];
                if (uncle != nullptr && uncle->color == 0) {
                    grandparent->setColor(0);
                    parent->setColor(1);
                    uncle->setColor(1);
                    node = grandparent;
                }
                else {
                    if (node == parent->descendants[1]) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                        node->updated = true;
                    }
                    rotateRight(grandparent);
                    if (parent->color != grandparent->color)
                    {
                        swap(parent->color, grandparent->color);
                        parent->updated = true;
                        grandparent->updated = true;
                    }
                    node = parent;
                }
            }
            else {
                RBNode<T>* uncle = grandparent->descendants[0];
                if (uncle != nullptr && uncle->color == 0) {
                    grandparent->setColor(0);
                    parent->setColor(1);
                    uncle->setColor(1);
                    node = grandparent;
                }
                else {
                    if (node == parent->descendants[0]) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                        node->updated = true;
                    }
                    rotateLeft(grandparent);
                    if (parent->color != grandparent->color)
                    {
                        swap(parent->color, grandparent->color);
                        parent->updated = true;
                        grandparent->updated = true;
                    }
                    node = parent;
                }
            }
        }
        if (root->color != 1)
            root->setColor(1); // 1: BLACK
    }

    void fixAfterDeletion(RBNode<T>*& node, RBNode<T>*& root) {
        while (node != root && (node == nullptr || node->color == 1)) { // 1: Black
            if (node == node->parent->descendants[0]) {
                RBNode<T>* sibling = node->parent->descendants[1];

                // Case 1: Sibling is red
                if (sibling->color == 0) {
                    sibling->setColor(1);
                    node->parent->setColor(0);
                    rotateLeft(node->parent);
                    sibling = node->parent->descendants[1];
                    node->parent->updated = true;
                }

                // Case 2: Both sibling's children are black
                if ((sibling->descendants[0] == nullptr || sibling->descendants[0]->color == 1) &&
                    (sibling->descendants[1] == nullptr || sibling->descendants[1]->color == 1)) {
                    sibling->setColor(0);
                    node = node->parent;
                }
                else {
                    // Case 3: Sibling's right child is black, left child is red
                    if (sibling->descendants[1] == nullptr || sibling->descendants[1]->color == 1) {
                        if (sibling->descendants[0] != nullptr) {
                            sibling->descendants[0]->setColor(1);
                        }
                        sibling->setColor(0);
                        rotateRight(sibling);
                        sibling = node->parent->descendants[1];
                        node->parent->updated = true;
                    }

                    // Case 4: Sibling's right child is red
                    sibling->setColor(node->parent->color);
                    node->parent->setColor(1);
                    if (sibling->descendants[1] != nullptr) {
                        sibling->descendants[1]->setColor(1);
                    }
                    rotateLeft(node->parent);
                    node = root;
                }
            }
            else { // Symmetric cases for the right child
                RBNode<T>* sibling = node->parent->descendants[0];

                // Case 1: Sibling is red
                if (sibling->color == 0) {
                    sibling->setColor(1);
                    node->parent->setColor(0);
                    rotateRight(node->parent);
                    sibling = node->parent->descendants[0];
                    node->parent->updated = true;
                }

                // Case 2: Both sibling's children are black
                if ((sibling->descendants[0] == nullptr || sibling->descendants[0]->color == 1) &&
                    (sibling->descendants[1] == nullptr || sibling->descendants[1]->color == 1)) {
                    sibling->setColor(0);
                    node = node->parent;
                }
                else {
                    // Case 3: Sibling's left child is black, right child is red
                    if (sibling->descendants[0] == nullptr || sibling->descendants[0]->color == 1) {
                        if (sibling->descendants[1] != nullptr) {
                            sibling->descendants[1]->setColor(1);
                        }
                        sibling->setColor(0);
                        rotateLeft(sibling);
                        sibling = node->parent->descendants[0];
                        node->parent->updated = true;
                    }

                    // Case 4: Sibling's left child is red
                    sibling->setColor(node->parent->color);
                    node->parent->setColor(1);
                    if (sibling->descendants[0] != nullptr) {
                        sibling->descendants[0]->setColor(1);
                    }
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }

        if (node != nullptr && node->color != 1) {
            node->setColor(1);
        }
    }

    RBNode<T>* findMinValueNode(RBNode<T>*& node) {
        RBNode<T>* current = node;
        while (current->descendants[0] != nullptr)
            current = current->descendants[0];
        return current;
    }

    void transplant(RBNode<T>*& root, RBNode<T>* u, RBNode<T>* v) {
        if (u->parent == nullptr) {
            root = v;
        }
        else if (u == u->parent->descendants[0]) {
            u->parent->descendants[0] = v;
            u->parent->updated = true;
        }
        else {
            u->parent->descendants[1] = v;
            u->parent->updated = true;
        }

        if (v != nullptr) {
            v->parent = u->parent;
            v->updated = true;
        }
    }

    void inorderHelper(RBNode<T>* node) const {
        if (node == nullptr) return;

        inorderHelper(node->descendants[0]);
        String sColor = (node->color == 0) ? "RED" : "BLACK";
        cout << node->key << " (" << sColor << ")" << endl;
        inorderHelper(node->descendants[1]);
    }


    void clearAll(RBNode<T>* node) {
        if (node != nullptr) {
            clearAll(node->descendants[0]);
            clearAll(node->descendants[1]);

            delete node;
        }
    }

public:

    RedBlackTree() : root(nullptr) {}

    ~RedBlackTree() { clearAll(root); }

    RedBlackTree(const RedBlackTree<T>& other) {
        root = copyTree(other.root);
        this->count = other.count;
    }

    //assignment operator
    RedBlackTree<T>& operator=(const RedBlackTree<T>& other) {
        if (this != &other) {
            deleteTree();
            root = copyTree(other.root);
            this->count = other.count;
        }
        return *this;
    }

    RBNode<T>* copyTree(const RBNode<T>* other) {
        if (other == nullptr) return nullptr;

        // Create a new node with the same key, data, and hash type
        RBNode<T>* newNode = new RBNode<T>(other->key, other->data, other->hashType, other->id);

        // Copy height
        newNode->color = other->color;

        // Recursively copy left and right descendants
        newNode->descendants[0] = copyTree(other->descendants[0]);
        newNode->descendants[1] = copyTree(other->descendants[1]);

        // Set parent pointers for copied descendants
        if (newNode->descendants[0])
            newNode->descendants[0]->parent = newNode;
        if (newNode->descendants[1])
            newNode->descendants[1]->parent = newNode;

        return newNode;
    }

    RedBlackTree<T>* clone() override {
        return new RedBlackTree<T>(*this);
    }

    void deleteTree() override {
        clearAll(root);
        root = nullptr;
    }


    void insert(T key, String data, int hashType) override {
        count++;
        RBNode<T>* node = new RBNode<T>(key, data, hashType, this->count);
        node->updated = true;
        RBNode<T>* parent = nullptr;
        RBNode<T>* current = root;

        while (current != nullptr) {
            parent = current;
            if (node->key < current->key)
                current = current->descendants[0];
            else
                current = current->descendants[1];
        }

        node->setParent(parent);

        if (parent == nullptr) {
            root = node;
        }
        else if (node->key < parent->key) {
            parent->descendants[0] = node;
            parent->updated = true;
        }
        else {
            parent->descendants[1] = node;
            parent->updated = true;
        }

        fixAfterInsertion(node);
    }

    void remove(T key, fs::path path) override {
        RBNode<T>* node = root;
        RBNode<T>* z = nullptr;
        RBNode<T>* x = nullptr;
        RBNode<T>* y = nullptr;

        while (node != nullptr) {
            if (node->key == key) {
                z = node;
            }

            if (node->key <= key) {
                node = node->descendants[1];
            }
            else {
                node = node->descendants[0];
            }
        }

        if (z == nullptr) {
            cout << "Key not found in the tree" << endl;
            return;
        }

        y = z;
        int yOriginalColor = y->color;

        // Case 1: Node to delete has no left child
        if (z->descendants[0] == nullptr) {
            x = z->descendants[1];
            transplant(root, z, z->descendants[1]);
        }
        // Case 2: Node to delete has no right child
        else if (z->descendants[1] == nullptr) {
            x = z->descendants[0];
            transplant(root, z, z->descendants[0]);
        }
        // Case 3: Node to delete has two children
        else {
            y = findMinValueNode(z->descendants[1]); // Find the successor
            yOriginalColor = y->color;
            x = y->descendants[1];
            if (y->parent == z) {
                if (x != nullptr)
                    x->setParent(y);
            }
            else {
                transplant(root, y, y->descendants[1]);
                y->descendants[1] = z->descendants[1];
                y->descendants[1]->setParent(y);
                y->updated = true;
            }
            transplant(root, z, y);
            y->descendants[0] = z->descendants[0];
            y->descendants[0]->setParent(y);
            y->setColor(z->color);
        }

        fs::path fileName = path / "Nodes" / z->nodeName;
		FileManager::deleteFile(fileName);
        delete z;

        // If the original color was black, fix the tree properties
        if (yOriginalColor == 1) {
            fixAfterDeletion(x, root);
        }
    }


    void inorder() const override {
        if (root == nullptr) {
            cout << "Tree is empty\n";
            return;
        }
        inorderHelper(root);
        cout << endl;
    }

    TreeNode<T>* getRoot() override {
        return root;

    }

    // rehashing:
    void rehashNode(RBNode<T>* node) {
        if (node == nullptr) return;
        this->rehashNode(node->descendants[0]);
        this->rehashNode(node->descendants[1]);

        if (node->updated || node->descendants[0]->updated || node->descendants[1]->updated)
        {
            if (node->isLeaf())
                generateHash(node->hashType, node->data, node->instructorHash, node->shaHash);
            else
                node->rehash();

            // Node's updation has been dealt, so now resetting the flag:
            node->updated = false;
        }
    }
};