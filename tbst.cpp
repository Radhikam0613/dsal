// Convert given binary tree into threaded binary tree. Analyze time and space complexity of the algorithm.
#include <iostream>
using namespace std;

struct Node {
    Node *left, *right;  // Pointers to left and right children
    int data;            // Data stored in the node
    int lthread, rthread; // Flags indicating whether left/right pointers are threads
};

class TBST {
public:
    Node* root = NULL; // Root node of the tree
    Node* inSucc(Node* ptr); // Function to find inorder successor of a node
    Node* inPred(Node* ptr); // Function to find inorder predecessor of a node
    void inorder(Node* root); // Function for inorder traversal of the tree
    Node* insert(Node* root, int key); // Function to insert a new key into the tree
    Node* caseA(Node* root, Node* par, Node* ptr); // Case when the node to be deleted has no children
    Node* caseB(Node* root, Node* par, Node* ptr); // Case when the node to be deleted has one child
    Node* caseC(Node* root, Node* par, Node* ptr); // Case when the node to be deleted has two children
    Node* del(Node* root, int key); // Function to delete a node from the threaded BST
};

Node* TBST::insert(Node* root, int key) {
    Node *ptr = root, *par = NULL;
    while (ptr) {
        par = ptr;
        if (key < ptr->data) {
            if (ptr->lthread) ptr = ptr->left; // If left thread exists, move to left child
            else break; // If no thread, exit loop (key not found)
        } else {
            if (ptr->rthread) ptr = ptr->right; // If right thread exists, move to right child
            else break; // If no thread, exit loop (key not found)
        }
    }
    Node* tmp = new Node{NULL, NULL, key, 0, 0}; 
    if (!par) root = tmp; // If tree is empty, new node becomes root
    else if (key < par->data) {
        tmp->left = par->left; // Set left child of new node
        tmp->right = par; // Set right child of new node to the parent
        par->lthread = 1; // Set parent's left thread
        par->left = tmp; // Update parent's left pointer to new node
    } else {
        tmp->left = par; // Set left child of new node to parent
        tmp->right = par->right; // Set right child of new node to parent's right
        par->rthread = 1; // Set parent's right thread
        par->right = tmp; // Update parent's right pointer to new node
    }
    return root; // Return updated root
}

Node* TBST::inSucc(Node* ptr) {
    if (ptr->rthread == 0) return ptr->right; // If there is no right thread, return the right child
    ptr = ptr->right;
    while (ptr->lthread == 1) ptr = ptr->left; // Traverse left if there are left threads
    return ptr;
}

void TBST::inorder(Node* root) {
    if (!root) {
        cout << "Tree is empty\n";
        return;
    }
    Node* ptr = root;
    while (ptr->lthread == 1) ptr = ptr->left; // Move to the leftmost node
    while (ptr) {
        cout << ptr->data << " "; // Print the node's data
        ptr = inSucc(ptr); // Move to the next node in inorder traversal
    }
}

Node* TBST::inPred(Node* ptr) {
    if (ptr->lthread == 0) return ptr->left; // If there is no left thread, return the left child
    ptr = ptr->left;
    while (ptr->rthread == 1) ptr = ptr->right; // Traverse right if there are right threads
    return ptr;
}

Node* TBST::caseA(Node* root, Node* par, Node* ptr) {
    if (!par) root = NULL; // If node to be deleted is root, set root to NULL
    else if (ptr == par->left) {
        par->lthread = 0; // Update parent's left thread
        par->left = ptr->left; // Set parent's left child to the left child of node to be deleted
    } else {
        par->rthread = 0; // Update parent's right thread
        par->right = ptr->right; // Set parent's right child to the right child of node to be deleted
    }
    delete ptr; // Free memory of the node
    return root; // Return updated root
}

Node* TBST::caseB(Node* root, Node* par, Node* ptr) {
    Node* child = (ptr->lthread == 1) ? ptr->left : ptr->right; // Find the child of the node to be deleted
    if (!par) root = child; // If parent is NULL (root), set root to the child
    else if (ptr == par->left) par->left = child; // If node is parent's left child, update parent's left child
    else par->right = child; // If node is parent's right child, update parent's right child
    Node* s = inSucc(ptr); // Find the successor
    Node* p = inPred(ptr); // Find the predecessor
    if (ptr->lthread == 1) p->right = s; // Update predecessor's right pointer if node has left thread
    if (ptr->rthread == 1) s->left = p; // Update successor's left pointer if node has right thread
    delete ptr; // Free memory of the node
    return root; // Return updated root
}

Node* TBST::caseC(Node* root, Node* par, Node* ptr) {
    Node *parsucc = ptr, *succ = ptr->right;
    while (succ->lthread == 1) {
        parsucc = succ;
        succ = succ->left; // Find the leftmost child of the successor
    }
    ptr->data = succ->data; // Copy successor's data to the current node
    if (succ->lthread == 0 && succ->rthread == 0) // If successor has no children
        root = caseA(root, parsucc, succ); // Use case A (no child) to delete successor
    else
        root = caseB(root, parsucc, succ); // Use case B (one child) to delete successor
    return root; // Return updated root
}

Node* TBST::del(Node* root, int dkey) {
    Node *par = NULL, *ptr = root;
    while (ptr) {
        if (dkey == ptr->data) break; // If key is found, exit loop
        par = ptr;
        ptr = (dkey < ptr->data && ptr->lthread) ? ptr->left : ptr->right; // Move based on key comparison
    }
    if (!ptr) {
        cout << "Key not found\n";
        return root; // If key not found, return root without modification
    }
    if (ptr->lthread && ptr->rthread) return caseC(root, par, ptr); // If node has two children, use case C
    else if (ptr->lthread) return caseB(root, par, ptr); // If node has one child (left), use case B
    else if (ptr->rthread) return caseB(root, par, ptr); // If node has one child (right), use case B
    else return caseA(root, par, ptr); // If node has no children, use case A
}

int main() {
    TBST t;
    Node* root = NULL;
    root = t.insert(root, 50);
    root = t.insert(root, 30);
    root = t.insert(root, 70);
    root = t.insert(root, 20);
    root = t.insert(root, 40);
    cout << "Inorder traversal: ";
    t.inorder(root);
    cout << "\n";
    root = t.del(root, 20);
    cout << "Inorder traversal after deletion: ";
    t.inorder(root);
    cout << "\n";
    return 0;
}
