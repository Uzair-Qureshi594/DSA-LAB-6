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
        if (pos == 1) return insertAtBeginning(val);
        Node *temp = head;
        for (int i = 1; temp && i < pos - 1; i++) temp = temp->next;
        if (!temp) return;

        Node *newNode = new Node(val);
        newNode->next = temp->next;
        if (temp->next) temp->next->prev = newNode;
        temp->next = newNode;
        newNode->prev = temp;
        if (!newNode->next) tail = newNode;
        printList();
    }

    void deleteFromBeginning() {
        if (!head) return;
        Node *temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        printList();
    }

    void deleteFromEnd() {
        if (!head) return;
        Node *temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        printList();
    }

    void deleteFromPosition(int pos) {
        if (pos == 1) return deleteFromBeginning();
        Node *temp = head;
        for (int i = 1; temp && i < pos; i++) temp = temp->next;
        if (!temp) return;

        if (temp->prev) temp->prev->next = temp->next;
        if (temp->next) temp->next->prev = temp->prev;
        if (temp == tail) tail = temp->prev;
        delete temp;
        printList();
    }

    void printList() {
        for (Node *temp = head; temp; temp = temp->next)
            cout << temp->data << " ";
        cout << endl;
    }
};

int main() {
    DoublyLinkedList list;
    list.insertAtBeginning(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.insertAtPosition(2, 15);
    list.insertAtPosition(5, 35);
    list.deleteFromBeginning();
    list.deleteFromEnd();
    list.deleteFromPosition(2);

    return 0;
}
