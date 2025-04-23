// A book consists of chapters, chapters consist of sections and sections consist of subsections.
// Construct a tree and print the nodes. Find the time and space requirements of your method.
#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    Node *next, *child;
};

Node* book = NULL;

Node* create(string title) {
    Node* node = new Node;
    cout << "Enter " << title << " name: ";
    getline(cin, node->name);
    node->next = node->child = NULL;
    return node;
}

void insert(Node*& parent, string title) {
    Node* node = create(title);
    if (parent == NULL) {
        parent = node;
    } else {
        Node* temp = parent;
        while (temp->next != NULL) temp = temp->next;
        temp->next = node;
    }
}

Node* find(Node* head, string target) {
    while (head != NULL && head->name != target) head = head->next;
    return head;
}

void add_book() {
    if (book == NULL) book = create("book"), cout << "Book added!\n";
    else cout << "Book exists!\n";
}

void add_chapter() {
    if (book == NULL) cout << "Add book first\n";
    else insert(book->child, "chapter");
}

void add_section() {
    if (book == NULL || book->child == NULL) {
        cout << "No chapters!\n";
        return;
    }
    string ch;
    cout << "Enter chapter name: ";
    getline(cin, ch);
    Node* chap = find(book->child, ch);
    if (chap != NULL) insert(chap->child, "section");
    else cout << "Chapter not found\n";
}

void add_subsection() {
    if (book == NULL || book->child == NULL) {
        cout << "No chapters!\n";
        return;
    }
    string ch, sec;
    cout << "Enter chapter: "; getline(cin, ch);
    cout << "Enter section: "; getline(cin, sec);
    Node* chap = find(book->child, ch);
    if (chap != NULL) {
        Node* section = find(chap->child, sec);
        if (section != NULL) insert(section->child, "subsection");
        else cout << "Section not found\n";
    } else cout << "Chapter not found\n";
}

void display() {
    if (book == NULL) {
        cout << "Empty tree\n";
        return;
    }
    cout << "Book: " << book->name << endl;
    for (Node* ch = book->child; ch != NULL; ch = ch->next) {
        cout << "  Chapter: " << ch->name << endl;
        for (Node* sec = ch->child; sec != NULL; sec = sec->next) {
            cout << "    Section: " << sec->name << endl;
            for (Node* sub = sec->child; sub != NULL; sub = sub->next)
                cout << "      Subsection: " << sub->name << endl;
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
    cout << "Select a chapter and section to add sub section in :- \n";
    add_subsection();
    display();
    return 0;
}
