#include <cstddef>
#include <iostream>
#include <string>

class LinkedList {
  public:
    struct Node {
        int val;
        Node *next;
        Node *prev;
        Node(int v = 0) : val(v), next(nullptr), prev(nullptr) {}
    };

    Node *head;
    Node *tail;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {};
    LinkedList(int n) : LinkedList() { push_back(n); }
    LinkedList(int *arr, size_t n) : LinkedList() {
        for (size_t i = 0; i < n; i++) {
            push_back(arr[i]);
        }
    }

    ~LinkedList() {
        Node *curr = head;
        while (curr) {
            Node *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void push_back(int n) {
        Node *node = new Node(n);
        size++;
        if (!tail) {
            head = tail = node;
            return;
        }
        tail->next = node;
        node->prev = tail;
        tail = node;
    }

    void push_front(int n) {
        Node *node = new Node(n);
        size++;
        if (!head) {
            head = tail = node;
            return;
        }
        node->next = head;
        head->prev = node;
        head = node;
    }

    void insert_at(size_t id, int n) {
        if (id > size) {
            throw std::out_of_range("index out of bounds!");
        }
        Node *node = new Node(n);
        if (!head) {
            head = node;
            tail = node;
        } else if (id == 0) {
            node->next = head;
            head->prev = node;
            head = node;
            return;
        } else if (id == size) {
            tail->next = node;
            node->prev = tail;
            tail = node;
            return;
        } else {
            Node *curr = head;
            for (size_t i = 0; i < id - 1; i++) {
                curr = curr->next;
            }
            node->next = curr->next;
            node->next->prev = node;
            curr->next = node;
            node->prev = curr;
        }
        size++;
    }

    void pop_front() {
        if (!head) {
            throw std::out_of_range("List empty, nothing to pop!");
        }
        Node *tmp = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        }
        delete tmp;
        size--;
    }

    void pop_back() {
        if (!tail) {
            throw std::out_of_range("List empty, nothing to pop!");
        }
        Node *tmp = tail;
        if (tail == head) {
            tail = head = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete tmp;
        size--;
    }

    void pop(size_t id) {
        if (id >= size) {
            throw std::out_of_range("Index out of bounds!");
        }
        if (id == 0) {
            pop_front();
            return;
        }
        if (id == size - 1) {
            pop_back();
            return;
        }

        Node *curr = head;
        for (size_t i = 0; i < id - 1; i++) {
            curr = curr->next;
        }
        Node *tmp = curr->next;
        curr->next = tmp->next;
        curr->next->prev = curr;
        delete tmp;
        size--;
    }

    std::string show() {
        if (!head) {
            return "show(): no nodes!";
        }

        std::string nodeString;
        Node *curr = head;
        while (curr) {
            nodeString.append(std::to_string(curr->val));
            if (curr->next) {
                nodeString.append(" <-> ");
            }
            curr = curr->next;
        }
        return nodeString;
    }

    int front() const {
        if (!head) {
            throw std::out_of_range("front(): list is empty!");
        }
        return head->val;
    }

    int back() const {
        if (!tail) {
            throw std::out_of_range("back(): list is empty!");
        }
        return tail->val;
    }

    void reverse() {
        Node *curr = head;
        Node *nxt, *prv;
        while (curr) {
            prv = curr->prev;
            nxt = curr->next;
            curr->next = prv;
            curr->prev = nxt;
            curr = nxt;
        }
        Node *tmp = tail;
        tail = head;
        head = tmp;
    }

    bool empty() const { return head == nullptr; }

    size_t len() const { return size; }

  private:
    size_t size{0};
};

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    LinkedList list(arr, 5);
    list.reverse();

    std::cout << list.show() << std::endl;
    std::cout << "len: " << list.len() << std::endl;
    std::cout << "head: " << list.head->val << std::endl;
    std::cout << "tail: " << list.tail->val << std::endl;

    return 0;
}
