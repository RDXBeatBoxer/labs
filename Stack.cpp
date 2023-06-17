#include <iostream>
#include <string>
using namespace std;

struct Node {
    string data;
    Node* next;
};

Node* top = NULL;

void push(string key) {
    Node* temp = new Node;
    temp->data = key;
    temp->next = top;
    top = temp;
}

void pop(string data) {
    Node* temp = top;
    Node* prev = NULL;
    while (temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        cout << "Key not found" << endl;
        return;
    }
    if (prev == NULL) {
        top = top->next;
    }
    else {
        prev->next = temp->next;
    }
    delete temp;
}

void printStack() {
    Node* temp = top;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int main() {
    push("One");
    push("Two");
    push("Three");
    printStack();
    pop("Two");
    printStack();

    return 0;
}