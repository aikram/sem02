#include <iostream>

template<typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        Node(T val) : value(val), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int listSize;

public:
    LinkedList() : head(nullptr), tail(nullptr), listSize(0) {}

    T front() { 
        if (empty()) throw std::out_of_range("List is empty");
        return head->value;
    }

    T back() {
        if (empty()) throw std::out_of_range("List is empty");
        return tail->value;
    }

    void push_front(T val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        listSize++;
    }

    void push_back(T val) {
        Node* newNode = new Node(val);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        listSize++;
    }

    T pop_front() {
        if (empty()) throw std::out_of_range("List is empty");
        T value = head->value;
        Node* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        listSize--;
        return value;
    }

    T pop_back() {
        if (empty()) throw std::out_of_range("List is empty");
        T value = tail->value;
        Node* temp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete temp;
        listSize--;
        return value;
    }

    T operator[](int index) {
        if (index < 0 || index >= size()) throw std::out_of_range("Index out of range");
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->value;
    }

    bool empty() {
        return listSize == 0;
    }

    int size() {
        return listSize;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    void sort() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* sorted = nullptr;

    while (head != nullptr) {
        Node* current = head;
        head = head->next;

        if (sorted == nullptr || sorted->value >= current->value) {
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->value < current->value) {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
    }

    head = sorted; 

    tail = nullptr;
    Node* prev = nullptr;
    Node* curr = head;
    while (curr != nullptr) {
        curr->prev = prev;
        prev = curr;
        if (curr->next == nullptr) tail = curr;
        curr = curr->next;
    }
}

    void reverse() {
        Node* current = head;
        Node* temp = nullptr;
        while (current != nullptr) {
            temp = current->prev;
            current->prev = current->next;
            current->next = temp;
            current = current->prev;
        }
        temp = head;
        head = tail;
        tail = temp;
    }

    ~LinkedList() {
        clear();
    }
};

int main() {
    LinkedList<int> my_list;

    std::cout << "Is the list empty? " << (my_list.empty() ? "Yes" : "No") << std::endl;

    my_list.push_front(5);
    my_list.push_back(15);
    std::cout << "Front: " << my_list.front() << std::endl;
    std::cout << "Back: " << my_list.back() << std::endl;
    std::cout << "Size: " << my_list.size() << std::endl;

    my_list.push_front(3);
    my_list.push_back(20);

    std::cout << "Element at index 1: " << my_list[1] << std::endl;

    std::cout << "All elements: ";
    for (int i = 0; i < my_list.size(); ++i) {
        std::cout << my_list[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Removed from front: " << my_list.pop_front() << std::endl;
    std::cout << "Removed from back: " << my_list.pop_back() << std::endl;

    my_list.reverse();
    std::cout << "Reversed list: ";
    for (int i = 0; i < my_list.size(); ++i) {
        std::cout << my_list[i] << " ";
    }
    std::cout << std::endl;

    my_list.clear();
    std::cout << "List cleared. New size: " << my_list.size() << std::endl;

    std::cout << "Is the list empty? " << (my_list.empty() ? "Yes" : "No") << std::endl;

    return 0;
}
