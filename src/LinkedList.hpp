#include <string>

template <typename T> class LinkedList {
  private:
    size_t size{0};

  public:
    struct Node {
        T val;
        Node *next;
        Node(T v = T(), Node *node = nullptr) : val(v), next(node) {}
    };

    Node *head;
    Node *tail;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {};
    LinkedList(T val) : LinkedList() { push_back(val); }
    LinkedList(T *arr, size_t n) : LinkedList() {
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

    void push_back(T val) {
        Node *node = new Node(val);
        size++;
        if (!tail) {
            head = tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }

    void push_front(T val) {
        Node *node = new Node(val);
        size++;
        if (!head) {
            head = tail = node;
            return;
        }
        node->next = head;
        head = node;
    }

    void insert_at(size_t id, T val) {
        if (id > size) {
            throw std::out_of_range("index out of bounds!");
        }
        Node *node = new Node(val);
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

    T front() const {
        if (!head) {
            throw std::out_of_range("front(): list is empty!");
        }
        return head->val;
    }

    T back() const {
        if (!tail) {
            throw std::out_of_range("back(): list is empty!");
        }
        return tail->val;
    }

    bool empty() const { return head == nullptr; }

    size_t len() const { return size; }
};
