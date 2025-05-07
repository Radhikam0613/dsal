#include <iostream>     
#include <string>       
using namespace std;

struct Node {
    string name;        
    Node *next, *child; 
};

Node* book = NULL;      // Pointer to root book node (initially null)

Node* create(string title) {
    Node* node = new Node;                      // Allocate memory for new node
    cout << "Enter " << title << " name: ";     // Ask user to enter name
    getline(cin, node->name);                   // Read full line as name
    node->next = node->child = NULL;            // Initialize pointers
    return node;                                // Return newly created node
}
// Node*& is reference to a pointer allowing to modify the original pointer ex book->child
void insert(Node*& parent, string title) {      
    Node* node = create(title);                 // Create new node of given title
    if (!parent) {                       // If parent has no children yet
        parent = node;                          // Set as first child
    } else {
        Node* temp = parent;                    // Traverse to end of sibling list
        while (temp->next) temp = temp->next;
        temp->next = node;                      // Append at end
    }
}

Node* find(Node* head, string target) {
    while (head && head->name != target) head = head->next; // Traverse until match or end
    return head;                                // Return matched node or NULL
}

void add_book() {
    if (!book) {
        book = create("book");
        cout << "Book added!\n";
    } else cout << "Book exists!\n";
}

void add_chapter() {
    if (!book) 
        cout << "Add book first\n";
    else 
        insert(book->child, "chapter");
}

void add_section() {
    if (!book || !book->child) {
        cout << "No chapters!\n";
        return;
    }
    string ch;
    cout << "Enter chapter name: ";              // Ask for chapter name
    getline(cin, ch);
    Node* chap = find(book->child, ch);          // Find chapter node
    if (chap) 
        insert(chap->child, "section");          // Insert section into chapter's child list
    else 
        cout << "Chapter not found\n";           // Invalid chapter name
}

void add_subsection() {
    if (!book || !book->child ) {
        cout << "No chapters!\n";                // Ensure chapters exist
        return;
    }
    string ch, sec;
    cout << "Enter chapter: "; getline(cin, ch); 
    cout << "Enter section: "; getline(cin, sec);
    Node* chap = find(book->child, ch);          // Find chapter
    if (chap) {
        Node* section = find(chap->child, sec);  // Find section under chapter
        if (section) 
            insert(section->child, "subsection");// Insert subsection under section
        else 
            cout << "Section not found\n";       // Invalid section name
    } else 
        cout << "Chapter not found\n";           // Invalid chapter name
}

void display() {
    if (!book) {
        cout << "Empty tree\n";
        return;
    }
    cout << "Book: " << book->name << endl;
    for (Node* ch = book->child; ch ; ch = ch->next) {
        cout << "   Chapter: " << ch->name << endl;
        for (Node* sec = ch->child; sec; sec = sec->next) { 
            cout << "       Section: " << sec->name << endl;
            for (Node* sub = sec->child; sub; sub = sub->next)
                cout << "           Subsection: " << sub->name << endl;
        }
    }
}

int main() {
    add_book();                                  
    cout << "Now add two chapters :- ";
    add_chapter();
    add_chapter();
    cout << "Select a chapter to add section in :- \n";
    add_section();
    add_section();
    cout << "Select a chapter and section to add sub section in :- \n";
    add_subsection();
    display();
    return 0;
}