#include <iostream>
using namespace std;

struct Node {
    string key, value;
    Node *left = 0, *right = 0;
    int height = 1;
    Node(string key, string value) : key(key), value(value) {}
};

int getHeight(Node* node) { return node ? node->height : 0; }
int getBalance(Node* node) { return node ? getHeight(node->left) - getHeight(node->right) : 0; }

Node* rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* insert(Node* node, string key, string value) {
    if (!node) {
    return new Node(key, value);
    }
    if (key < node->key) {
        node->left = insert(node->left, key, value);
    } else if (key > node->key) {
        node->right = insert(node->right, key, value);
    } else {
        node->value = value; // no duplicates
        return node;
    }    
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalance(node);

    if (balance < -1 && key > node->right->key) 
        return rotateLeft(node);

    if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

    if (balance > 1 && key < node->left->key) 
        return rotateRight(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

Node* getMinValueNode(Node* node) {
    while (node->left) node = node->left;
    return node;
}

Node* remove(Node* node, string key) {
    if (!node) return nullptr;
    if (key < node->key) node->left = remove(node->left, key);
    else if (key > node->key) node->right = remove(node->right, key);
    else {
        if (node->left == nullptr || node->right == nullptr){// No or one child
            Node* temp = node->left ? node->left : node->right;// this makes temp the existing child in onr child case
            delete node;
            return temp;
        }
        Node* temp = getMinValueNode(node->right);// min value in right subtree
        node->key = temp->key;
        node->value = temp->value;
        node->right = remove(node->right, temp->key);// delete temp after storing it in curr to be deleted node
    }
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balance = getBalance(node);
    if (balance < -1 && getBalance(node->right) <= 0) return rotateLeft(node);
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    if (balance > 1 && getBalance(node->left) >= 0) return rotateRight(node);
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    return node;
}

bool search(Node* node, string key) {
    if (!node) return false;
    if (key == node->key) return true;
    if (key < node->key) {
        return search(node->left, key);
    } else {
        return search(node->right, key);
    }
}

void inorder(Node* node) {
    if (node){
    inorder(node->left);
    cout << node->key << ": " << node->value << endl;
    inorder(node->right);
    }
}

int main() {
    Node* root = nullptr;
    root = insert(root, "zebra", "A animal");
    root = insert(root, "banana", "A yellow fruit");
    root = insert(root, "truck", "A vehicle");
    cout << "\nIn-order (Ascending):\n";
    inorder(root);
    string term = "banana";
    cout << "\nSearching '" << term << "': " << (search(root, term) ? "Found" : "Not Found") << "\n";
    cout << "\nDeleting 'apple'...\n";
    root = remove(root, "apple");
    cout << "\nAfter Deletion:\n";
    inorder(root);
}