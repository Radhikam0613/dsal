// Beginning with an empty binary search tree, Construct binary search tree by
// inserting the values in the order given. After constructing a binary tree -
// i. Insert new node, 
// ii. Find number of nodes in longest path from root,
// iii. Minimum data value found in the tree, 
// iv. Change a tree so that the roles of the left and right pointers are swapped at every node, 
// v. Search a value
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

class BST {
public:
    Node* insert(Node* root, int data) {
        if (!root)
            return new Node(data);
        if (data < root->data) {
            root->left = insert(root->left, data);
        } else {
            root->right = insert(root->right, data);
        }
        return root;
    }

    int longestPath(Node* root) {
        if (root) {
            int leftPath = longestPath(root->left);
            int rightPath = longestPath(root->right);
            return 1 + max(leftPath, rightPath);
        } else return 0;
    }

    int findMin(Node* root) {
        while (root && root->left) {
            root = root->left;
        }
        if (root) {// Check again if root is not null for empty tree case
            return root->data;
        } else return -1;
    }

    Node* swapChildren(Node* root) {
        if (root) {
            Node* temp = root->left;
            root->left = root->right;
            root->right = temp;
            swapChildren(root->left);
            swapChildren(root->right);
        }
        return root;
    }
    
    bool search(Node* root, int key) {
        if (!root) return false;
        if (root->data == key) return true;
        if (key < root -> data) return search(root->left, key);
        else return search(root->right, key);
    }

    void inorder(Node* root) {
        if (root) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }
};

int main() {
    BST tree;
    Node* root = nullptr;
    root = tree.insert(root, 50);
    root = tree.insert(root, 40);
    root = tree.insert(root, 20);
    root = tree.insert(root, 80);
    cout << "Inorder Traversal:- "; 
    tree.inorder(root);
    cout << endl;
    cout << "Longest path:- " << tree.longestPath(root) << endl;
    cout << "Min value:- " << tree.findMin(root) << endl;
    root = tree.swapChildren(root);
    cout << "After swapping children: "; tree.inorder(root); cout << endl;
    bool found = tree.search(root, 40);
    cout << "Is 40 present" << (found ? " Yes" : " No") << endl;
    return 0;
}
