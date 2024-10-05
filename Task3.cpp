#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node *prev, *next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
    Node *head, *tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void insertAtBeginning(int val) {
        Node *newNode = new Node(val);
        if (!head) head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        printList();
    }

    void insertAtEnd(int val) {
        Node *newNode = new Node(val);
        if (!head) head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        printList();
    }

    void insertAtPosition(int pos, int val) {
        if (pos <= 0 || (pos == 1 && !head)) return insertAtBeginning(val);

        Node *temp = head;
        for (int i = 1; temp && i < pos - 1; i++) temp = temp->next;
        if (!temp) return;

        Node *newNode = new Node(val);
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) temp->next->prev = newNode;
        else tail = newNode;
        temp->next = newNode;
    }

    void deleteFromBeginning() {
        if (!head) return;
        Node *temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
    }

    void deleteFromEnd() {
        if (!tail) return;
        Node *temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
    }

    void deleteFromPosition(int pos) {
        if (pos <= 0 || !head) return;
        if (pos == 1) return deleteFromBeginning();

        Node *temp = head;
        for (int i = 1; temp && i < pos; i++) temp = temp->next;
        if (!temp) return;

        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        if (temp == tail) tail = temp->prev;
        delete temp;
    }

    void deleteAllNodes() {
        while (head) deleteFromBeginning();
        cout << "All nodes deleted.\n";
    }

    void printList() {
        if (!head) cout << "List is empty.\n";
        else for (Node *temp = head; temp; temp = temp->next) cout << temp->data << " ";
        cout << endl;
    }
};

int main() {
    DoublyLinkedList dll;

    cout << "Test 1: Deleting from an empty list\n";
    dll.deleteFromBeginning();
    dll.deleteFromEnd();
    dll.deleteFromPosition(1);

    cout << "\nInserting elements:\n";
    dll.insertAtBeginning(10);
    dll.insertAtEnd(20);
    dll.insertAtEnd(30);

    cout << "Test 2: Inserting at a position greater than the length of the list\n";
    dll.insertAtPosition(5, 25);

    cout << "Test 3: Deleting all nodes one by one\n";
    dll.deleteAllNodes();
    dll.deleteFromBeginning();
    dll.deleteFromEnd();
    dll.deleteFromPosition(1);

    return 0;
}
