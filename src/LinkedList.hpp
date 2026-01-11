#include <ostream>
#include <string>

template <typename T> struct Node {
    T val;
    Node *next;
    Node *prev;
    Node(T v) : val(v), next(nullptr), prev(nullptr) {}
};

template <typename T> class LinkedList {
  private:
    size_t size{0};

  public:
    Node<T> *_head;
    Node<T> *_tail;

    LinkedList() : _head(nullptr), _tail(nullptr), size(0) {};
    LinkedList(T val) : LinkedList() { push_back(val); }
    LinkedList(T *arr, size_t n) : LinkedList() {
        for (size_t i = 0; i < n; i++) {
            push_back(arr[i]);
        }
    }

    ~LinkedList() {
        Node<T> *curr = _head;
        while (curr) {
            Node<T> *temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    void push_back(T val) {
        Node<T> *node = new Node<T>(val);
        size++;
        if (!_tail) {
            _head = _tail = node;
            return;
        }
        _tail->next = node;
        _tail = node;
    }

    void push_front(T val) {
        Node<T> *node = new Node<T>(val);
        size++;
        if (!_head) {
            _head = _tail = node;
            return;
        }
        node->next = _head;
        _head = node;
    }

    void insert_at(size_t id, T val) {
        if (id > size) {
            throw std::out_of_range("index out of bounds!");
        }
        Node<T> *node = new Node<T>(val);
        if (!_head) {
            _head = node;
            _tail = node;
        } else if (id == 0) {
            node->next = _head;
            _head = node;
            return;
        } else if (id == size) {
            _tail->next = node;
            _tail = node;
            return;
        } else {
            Node<T> *curr = _head;
            for (size_t i = 0; i < id - 1; i++) {
                curr = curr->next;
            }
            node->next = curr->next;
            curr->next = node;
        }
        size++;
    }

    void pop_front() {
        if (!_head) {
            throw std::out_of_range("List empty, nothing to pop!");
        }
        Node<T> *old = _head;
        _head = _head->next;
        delete old;
        size--;
    }

    void pop_back() {
        if (!_head) {
            throw std::out_of_range("List empty, nothing to pop!");
        }
        if (size == 1) {
            delete _head;
            _head = _tail = nullptr;
        } else {
            Node<T> *curr = _head;
            Node<T> *prev;
            while (curr->next) {
                prev = curr;
                curr = curr->next;
            }
            delete curr;
            _tail = prev;
            _tail->next = nullptr;
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

        Node<T> *curr = _head;
        for (size_t i = 0; i < id - 1; i++) {
            curr = curr->next;
        }
        Node<T> *tmp = curr->next;
        curr->next = tmp->next;
        delete tmp;
        size--;
    }

    Node<T> *head() const { return _head; }
    Node<T> *tail() const { return _tail; }

    T front() const {
        if (!_head) {
            throw std::out_of_range("front(): list is empty!");
        }
        return _head->val;
    }

    T back() const {
        if (!_tail) {
            throw std::out_of_range("back(): list is empty!");
        }
        return _tail->val;
    }

    bool empty() const { return _head == nullptr; }

    size_t len() const { return size; }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const LinkedList<T> &ll) {
    os << "[";
    Node<T> *curr = ll.head();
    while (curr) {
        os << curr->val;
        if (curr->next) {
            os << " <-> ";
        }
        curr = curr->next;
    }
    os << "]";
    return os;
}
