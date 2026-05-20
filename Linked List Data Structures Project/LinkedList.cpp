#include <stdexcept>
#include "LinkedList.h"

// TODO(student): implement a linked list

//Constructor logic
LinkedList::LinkedList() : head(nullptr){}

LinkedList::LinkedList(const LinkedList& other) : head(nullptr) {
    if (other.head != nullptr){
        head = new Node(other.head->value);
        Node* currnode = head;
        Node* other_currnode = other.head->next;
        while (other_currnode != nullptr) {
            currnode->next = new Node(other_currnode->value);
            currnode = currnode->next;
            other_currnode = other_currnode->next;
        }
    }
}

LinkedList::~LinkedList() {
    Node* currnode = head;
    while (currnode != nullptr) {
        Node* tmp = currnode;
        currnode = currnode->next;
        delete tmp;
    }
    head = nullptr;
} // destructor

LinkedList& LinkedList::operator=(const LinkedList& other) {
            if (this != &other) {
                this->~LinkedList(); // Delete current list
                if (other.head == nullptr) {
                    head = nullptr;
                    return *this;
                }
                head = new Node(other.head->value);
                Node* currnode = head;
                Node* other_currnode = other.head->next;
                while (other_currnode != nullptr) {
                    currnode->next = new Node(other_currnode->value);
                    currnode = currnode->next;
                    other_currnode = other_currnode->next;
                }
            }
            return *this;
        } // copy assignment operator

bool LinkedList::empty() const{
    if (head == nullptr){
        return true;
    }

    return false;
}

unsigned LinkedList::size() const{
    Node* current = head;
    unsigned x = 0;
    while (current != nullptr) {
        x++;
        current = current->next; 
    }

    return x;

}

int LinkedList::at(unsigned index) const{

    if (index >= size()){
        throw std::out_of_range("Index is out of range");
    }

    Node* current = head;
    unsigned x = 0;
    while (current != nullptr) {
        if (x == index){
            return current->value;
        }
        current = current->next; 
        x++;
    }

    //Only throw if index is not found after iteration
    throw std::out_of_range("Index is out of range");

    return 0;

}

int LinkedList::front() const{
    if (empty()){
        throw std::out_of_range("");
    }

    return head->value;
}

void LinkedList::add(int value, unsigned index) {

    if (index > size()){
        throw std::out_of_range("Index is out of range");
    }

    Node* newnode = new Node(value);

    if (index == 0){
        newnode->next = head;
        head = newnode;
        return;
    }

    unsigned x = 0;
    Node* current = head;

    while (current != nullptr){
        if (x==index-1){
            break;
        }
        current = current -> next;
        x++;
    }

    newnode->next = current->next;
    current->next = newnode;

}

void LinkedList::remove(unsigned index){
    if (index >= size()){
        throw std::out_of_range("Index is out of range");
    }

    if (index == 0){
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    unsigned x = 0;
    Node* current = head;

    while (current != nullptr){
        if (x==index-1){
            break;
        }
        current = current -> next;
        x++;
    }

    Node* temp = current->next;
    current->next = temp->next;
    delete temp;
}

void LinkedList::clear(){

    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;



}

