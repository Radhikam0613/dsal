// A Dictionary stores keywords and its meanings. Provide facility for adding new
// keywords, deleting keywords, updating values of any entry. Provide facility to
// display whole data sorted in ascending/ Descending order. Also find how many
// maximum comparisons may require for finding any keyword. Use Height balance
// tree and find the complexity for finding a keyword
#include <iostream>
using namespace std;

struct Node {
    string key, value;
    Node *left = nullptr, *right = nullptr;
    int height = 1;

    Node(string k, string v) : key(k), value(v) {}
};

int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

Node* getMin(Node* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* remove(Node* root, string key) {
    if (root == NULL)
        return nullptr;
    if (key < root->key) {
        root->left = remove(root->left, key);
    } else if (key > root->key) {
        root->right = remove(root->right, key);
    } else {
        if (root->left == NULL || root->right == NULL) { // one child
            Node* temp = root->left ? root->left : root->right;
            delete root;
            return temp;
        }
        Node* temp = getMin(root->right); // two child
        root->key = temp->key;
        root->value = temp->value;
        root->right = remove(root->right, temp->key);
    } // balance heights after deletion
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0) return rotateRight(root);
    if (balance < -1 && getBalance(root->right) <= 0) return rotateLeft(root);
    if (balance > 1 && getBalance(root->left) < 0) return root->left = rotateLeft(root->left), rotateRight(root);
    if (balance < -1 && getBalance(root->right) > 0) return root->right = rotateRight(root->right), rotateLeft(root);
    return root;
}

Node* insert(Node* root, string key, string value) {
    if (root == NULL) 
        return new Node(key, value);
    if (key < root->key) {
        root->left = insert(root->left, key, value);
    } else if (key > root->key) {
        root->right = insert(root->right, key, value);
    } else {
        root->value = value; // key exists so update the value
        return root;
    }
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balance = getBalance(root);
    if (balance > 1 && key < root->left->key) return rotateRight(root);
    if (balance < -1 && key > root->right->key) return rotateLeft(root);
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

bool search(Node* root, string key) {
    if (root == NULL) 
        return false;
    if (key == root->key) 
        return true;
    if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

void displayAscending(Node* root) {
    if (root == NULL) return;
    displayAscending(root->left);
    cout << root->key << ": " << root->value << endl;
    displayAscending(root->right);
}

int main() {
    Node* root = nullptr;
    root = insert(root, "zdate", "A fruit");
    root = insert(root, "cbanana", "A yellow fruit");
    root = insert(root, "acherry", "A red fruit");
    cout << "\nDictionary in ascending order (in-order traversal):\n";
    displayAscending(root);
    string term = "banana";
    cout << "\nSearching for the term '" << term << "'...\n";
    cout << "'" << term << "' " << (search(root, term) ? "found" : "not found") << " in dictionary.\n";
    cout << "\nRemoving 'cherry' from the dictionary...\n";
    root = remove(root, "cherry");
    cout << "\nDictionary after deleting 'cherry':\n";
    displayAscending(root);
    return 0;
}