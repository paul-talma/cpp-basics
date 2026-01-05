#include <iostream>
#include <string>

class LinkedList {
  public:
    struct Node {
        int val;
        struct Node *next;
        Node(int v = 0, Node *node = nullptr) : val(v), next(node) {}
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
            head = node;
            return;
        } else if (id == size) {
            tail->next = node;
            tail = node;
            return;
        } else {
            Node *curr = head;
            for (size_t i = 0; i < id - 1; i++) {
                curr = curr->next;
            }
            node->next = curr->next;
            curr->next = node;
        }
        size++;
    }

    void pop_front() {
        if (!head) {
            throw std::out_of_range("List empty, nothing to pop!");
        }
        Node *old = head;
        head = head->next;
        delete old;
        size--;
    }

    void pop_back() {
        if (!head) {
            throw std::out_of_range("List empty, nothing to pop!");
        }
        if (size == 1) {
            delete head;
            head = tail = nullptr;
        } else {
            Node *curr = head;
            Node *prev;
            while (curr->next) {
                prev = curr;
                curr = curr->next;
            }
            delete curr;
            tail = prev;
            tail->next = nullptr;
        }
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

        // size_t pos{0};
        Node *curr = head;
        for (size_t i = 0; i < id - 1; i++) {
            curr = curr->next;
        }
        Node *tmp = curr->next;
        curr->next = tmp->next;
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
                nodeString.append(" -> ");
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

    bool empty() const { return head == nullptr; }

    size_t len() const { return size; }

  private:
    size_t size{0};
};

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    LinkedList list(arr, 5);
    list.insert_at(2, 7);
    list.pop(4);

    std::cout << list.show() << std::endl;
    std::cout << "len: " << list.len() << std::endl;
    std::cout << "head: " << list.head->val << std::endl;
    std::cout << "tail: " << list.tail->val << std::endl;

    return 0;
}
