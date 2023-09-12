#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* next;
    Node* tail;

    Node () {}
    Node(int key) {
        this->key = key;
        this->next = NULL;
        this->tail = NULL;
    }
};

class Linkedlist {
public:
    int size;
    Node* head;

    Linkedlist() {
        size = 0;
        head = NULL;
    }

    void printLinkedList() {
        Node* temp = head;
        if (temp == NULL) {
            cout << "Empty linked list" <<endl;
            return;
        }

        for (int i=0; i<size; i++) {
            cout << temp->key << " ";
            temp = temp->next;
        }
    }

    Node* findNode(int index) {
        Node* temp = this->head;

        if (index >= this->size || index < 0) {
            cout << "index out of range" << endl;
            return NULL;
        }

        for (int i=0; i<index-1; i++) {
            temp = temp->next;
        }

        return temp;
    }

    void insertNode(int index, int key) {
        Node* newNode = new Node(key);

        if (index == 0) {
            newNode->next = head;
            head = newNode;
            size++;
        }
        else {
            Node* pre = findNode(index-1);
            newNode->next = pre->next;
            pre->next = newNode;
            size++;
        }
    }
};


int main()
{
    Linkedlist ll = Linkedlist();
    ll.insertNode(0, 1);
    ll.insertNode(1, 2);
    ll.printLinkedList();

    return 0;
}
