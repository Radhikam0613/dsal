// Convert given binary tree into threaded binary tree. Analyze time and space
// complexity of the algorithm.
#include <iostream>
using namespace std;

struct Node {
    Node *left, *right;
    int data;
    int lthread, rthread; // 1 if thread exists, 0 if child exists
};

class TBST {
public:
    Node* root = NULL;
    void inorder(Node* root);
    Node* insert(Node* root, int ikey);
    Node* inorderSuccessor(Node* ptr);
    Node* inPred(Node* ptr);
    Node* caseA(Node* root, Node* par, Node* ptr); // Leaf node
    Node* caseB(Node* root, Node* par, Node* ptr); // One child
    Node* caseC(Node* root, Node* par, Node* ptr); // Two children
    Node* delThreadedBST(Node* root, int dkey);
};

Node* TBST::insert(Node* root, int ikey) {
    Node* ptr = root; // Start at the root of the tree
    Node* par = NULL;// Parent pointer to keep track of the node where we'll insert the new node
    while (ptr != NULL) {
        par = ptr;  // Set parent to current node
        if (ikey < ptr->data) { // If the key to insert is smaller than the current node's data
            if (ptr->lthread == 1) { // Check if there's a left thread (which means we can go left)
                ptr = ptr->left; // Move left
            } else {
                break; // No left child, stop here
            }
        } else { // If the key to insert is greater or equal
            if (ptr->rthread == 1) { // Check if there's a right thread (which means we can go right)
                ptr = ptr->right; // Move right
            } else {
                break; // No right child, stop here
            }
        }
    }
    Node* tmp = new Node;
    tmp->data = ikey;
    tmp->lthread = 0;
    tmp->rthread = 0;
    if (par == NULL) { // Case 1: Tree is empty — new node becomes the root
        tmp->left = NULL;
        tmp->right = NULL;
        root = tmp;
    } else if (ikey < par->data) { // Case 2: Insert to the left of parent
        tmp->left = par->left;   // New node inherits left thread from parent
        tmp->right = par;        // New node’s right thread points to parent
        par->lthread = 1;        // Parent now has a real left child
        par->left = tmp;         // Connect parent to new left child
    }
    else { // Case 3: Insert to the right of parent
        tmp->left = par;         // New node’s left thread points to parent
        tmp->right = par->right; // New node inherits right thread from parent
        par->rthread = 1;        // Parent now has a real right child
        par->right = tmp;        // Connect parent to new right child
    }
    return root;
}

Node* TBST::inorderSuccessor(Node* ptr) {
    // Case 1: If the right thread is not set (rthread == 0), this means the node has an actual right child.
    // In this case, the inorder successor will be the right child of the current node.
    if (ptr->rthread == 0) {
        return ptr->right; // The right thread points to the successor (actual right child)
    }

    // Case 2: If the right thread is set (rthread == 1), we need to find the leftmost node in the right subtree
    ptr = ptr->right; // Move to the node linked by the right thread

    // Traverse down the leftmost path in the right subtree by following the left threads
    while (ptr->lthread == 1) {
        ptr = ptr->left; // Move left along the left thread until there's no more left thread
    }

    // Return the leftmost node in the right subtree, which is the inorder successor
    return ptr;
}


// Return the inorder predecessor of a given node
Node* TBST::inPred(Node* ptr) {
    // Case 1: If the left thread is not set, it means the current node has an actual left child.
    // In this case, the inorder predecessor is simply the left child of the current node.
    if (ptr->lthread == 0) {
        return ptr->left; // The left child is the predecessor
    }

    // Case 2: If the left thread is set, we need to find the rightmost node in the left subtree
    ptr = ptr->left; // Move to the node linked by the left thread

    // Traverse up the rightmost path in the left subtree by following the right threads
    while (ptr->rthread == 1) {
        ptr = ptr->right; // Move right along the right thread until there's no more right thread
    }
    return ptr;
}

void TBST::inorder(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty"; // If the root is null, print message and return
        return;
    }
    // Start from the leftmost node in the tree
    Node* ptr = root;
    // Traverse down the leftmost path (following the left threads) to find the leftmost node
    while (ptr->lthread == 1) {
        ptr = ptr->left; // Keep moving left until there are no more left threads
    }
    // Now ptr is the leftmost node, we can start the inorder traversal
    while (ptr != NULL) {
        cout << ptr->data << " "; // Print the data of the current node
        ptr = inorderSuccessor(ptr); // Move to the inorder successor using the threaded links
    }
}

Node* TBST::caseA(Node* root, Node* par, Node* ptr) { // The node to be deleted is a leaf node
    if (par == NULL) {// If the node to be deleted is the root, the tree becomes empty
        root = NULL;
    } else if (ptr == par->left) {// If the node is the left child of its parent, update the parent's left pointer
        par->lthread = 0;  // Child exists
        par->left = ptr->left;  // Link the parent to the left child (or NULL)
    } else {// If the node is the right child of its parent, update the parent's right pointer
        par->rthread = 0;  // Child exists
        par->right = ptr->right;  // Link the parent to the right child (or NULL)
    }
    free(ptr);  // Deallocate the memory for the deleted node
    return root;  // Return the root (it could be NULL if the tree is empty)
}

Node* TBST::caseB(Node* root, Node* par, Node* ptr) { // Case B: Node to be deleted has one child
    // Determine the child of the node to be deleted (left or right)
    Node* child;
    if (ptr->lthread == 1) {
        child = ptr->left;  // If left thread exists, use the left pointer (inorder predecessor).
    } else {
        child = ptr->right; // Otherwise, use the right pointer (right child).
    }
    
    // If 'par' is NULL, 'ptr' is the root; so we update the root to the child
    if (par == NULL) {
        root = child;  // Root becomes the child of the deleted node
    } 
    // Otherwise, adjust the parent's pointer to bypass 'ptr' and point to 'child'
    else if (ptr == par->left) {
        par->left = child;  // Parent's left pointer points to the child
    } else {
        par->right = child;  // Parent's right pointer points to the child
    }

    // Update the threads of predecessor and successor
    Node* s = inorderSuccessor(ptr);  // Get the inorder successor of 'ptr'
    Node* p = inPred(ptr);  // Get the inorder predecessor of 'ptr'

    // If 'ptr' has a left thread, we link the predecessor's right pointer to the successor
    if (ptr->lthread) {
        p->right = s;  // Predecessor's right points to successor
    } 
    // If 'ptr' has a right thread, we link the successor's left pointer to the predecessor
    else if (ptr->rthread) {
        s->left = p;  // Successor's left points to predecessor
    }

    // Free the memory of the deleted node
    free(ptr);  // Deallocate the node

    // Return the updated root of the tree
    return root;
}


// Case C: Node to be deleted has two children
Node* TBST::caseC(Node* root, Node* par, Node* ptr) {
    Node* parsucc = ptr;
    Node* succ = ptr->right;

    // Find inorder successor and its parent
    while (succ->lthread) {
        parsucc = succ;
        succ = succ->left;
    }

    ptr->data = succ->data; // Copy successor’s data

    // Now delete the successor node
    if (!succ->lthread && !succ->rthread)
        root = caseA(root, parsucc, succ);
    else
        root = caseB(root, parsucc, succ);

    return root;
}

// Delete a node with key dkey from TBST
Node* TBST::delThreadedBST(Node* root, int dkey) {
    Node* ptr = root;
    Node* par = NULL;
    int found = 0;

    // Search for node to delete
    while (ptr) {
        if (dkey == ptr->data) {
            found = 1;
            break;
        }
        par = ptr;
        if (dkey < ptr->data) {
            if (ptr->lthread) ptr = ptr->left;
            else break;
        } else {
            if (ptr->rthread) ptr = ptr->right;
            else break;
        }
    }

    if (!found) {
        cout << "Key " << dkey << " not present in tree\n";
        return root;
    }

    // Handle deletion cases
    if (ptr->lthread && ptr->rthread) // Two children
        root = caseC(root, par, ptr);
    else if (ptr->lthread) // Only left child
        root = caseB(root, par, ptr);
    else if (ptr->rthread) // Only right child
        root = caseB(root, par, ptr);
    else // Leaf
        root = caseA(root, par, ptr);

    return root;
}

// Main function to test TBST
int main() {
    TBST t;
    Node* root = NULL;

    // Insert nodes
    root = t.insert(root, 50);
    root = t.insert(root, 30);
    root = t.insert(root, 70);
    root = t.insert(root, 20);
    root = t.insert(root, 40);
    root = t.insert(root, 60);
    root = t.insert(root, 80);

    // Inorder traversal
    cout << "Inorder: ";
    t.inorder(root);
    cout << "\n";

    // Delete nodes
    root = t.delThreadedBST(root, 30);
    root = t.delThreadedBST(root, 70);

    // Inorder after deletion
    cout << "Inorder after Deletion: ";
    t.inorder(root);
    cout << "\n";

    return 0;
}
