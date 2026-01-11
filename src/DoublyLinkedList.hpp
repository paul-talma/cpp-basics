#include "../include/DoublyLinkedList.hpp"
#include <cstddef>
#include <initializer_list>
#include <ostream>

template <typename T> struct Node {
    T val;
    Node *next;
    Node *prev;
    Node(T v) : val(v), next(nullptr), prev(nullptr) {}
};
template <typename T> class DoublyLinkedList {
  private:
    Node<T> *_head;
    Node<T> *_tail;
    size_t _size;

  public:
    DoublyLinkedList() : _size(0), _head(nullptr), _tail(nullptr) {};
    DoublyLinkedList(T val) : DoublyLinkedList() { push_back(val); }
    DoublyLinkedList(T *arr, size_t n) : DoublyLinkedList() {
        for (size_t i = 0; i < n; i++) {
            push_back(arr[i]);
        }
    }
    DoublyLinkedList(std::initializer_list<T> &list)
        : DoublyLinkedList(), _size(list.size()) {
        for (const T &elem : list) {
            push_back(elem);
        }
    }

    // copy semantics
    DoublyLinkedList(const DoublyLinkedList &other) {
        *this = other;
        // _size = other._size;
        // Node<T> *curr = other.head();
        // while (curr) {
        //     push_back(curr->val);
        //     curr = curr->next;
        // }
    }

    DoublyLinkedList &operator=(const DoublyLinkedList &other) {
        if (this != &other) {
            this.~DoublyLinkedList();
            _size = other.size();
            Node<T> *curr = other.head();
            while (curr) {
                push_back(curr->val);
                curr = curr->next;
            }
        }
        return *this;
    }

    // move semantics
    DoublyLinkedList(const DoublyLinkedList &&other) {
        this.~DoublyLinkedList();
        _size = other.size();
        _head = other.head();
        _tail = other.tail();

        other._size = 0;
        other._head = nullptr;
        other._tail = nullptr;
    }
    DoublyLinkedList &operator=(const DoublyLinkedList &&other) {
        if (this != other) {
            this.~DoublyLinkedList();
            _size = other.size();
            _head = other.head();
            _tail = other.tail();

            other._size = 0;
            other._head = nullptr;
            other._tail = nullptr;
        }
        return *this;
    }

    ~DoublyLinkedList() {
        Node<T> *curr = _head;
        while (curr) {
            Node<T> *temp = curr;
            curr = curr->next;
            delete temp;
        }
        _head = nullptr;
        _tail = nullptr;
        _size = 0;
    }

    void push_back(T val) {
        Node<T> *node = new Node<T>(val);
        _size++;
        if (!_tail) {
            _head = _tail = node;
            return;
        }
        _tail->next = node;
        node->prev = _tail;
        _tail = node;
    }

    void push_front(T val) {
        Node<T> *node = new Node<T>(val);
        _size++;
        if (!_head) {
            _head = _tail = node;
            return;
        }
        node->next = _head;
        _head->prev = node;
        _head = node;
    }

    void insert_at(size_t id, T val) {
        if (id > _size) {
            throw std::out_of_range("index out of bounds!");
        }
        Node<T> *node = new Node<T>(val);
        if (!_head) {
            _head = node;
            _tail = node;
        } else if (id == 0) {
            node->next = _head;
            _head->prev = node;
            _head = node;
            return;
        } else if (id == _size) {
            _tail->next = node;
            node->prev = _tail;
            _tail = node;
            return;
        } else {
            Node<T> *curr = _head;
            for (size_t i = 0; i < id - 1; i++) {
                curr = curr->next;
            }
            node->next = curr->next;
            node->next->prev = node;
            curr->next = node;
            node->prev = curr;
        }
        _size++;
    }

    void pop_front() {
        if (!_head) {
            throw std::out_of_range("List empty, nothing to pop!");
        }
        Node<T> *tmp = _head;
        _head = _head->next;
        if (_head) {
            _head->prev = nullptr;
        }
        delete tmp;
        _size--;
    }

    void pop_back() {
        if (!_tail) {
            throw std::out_of_range("List empty, nothing to pop!");
        }
        Node<T> *tmp = _tail;
        if (_tail == _head) {
            _tail = _head = nullptr;
        } else {
            _tail = _tail->prev;
            _tail->next = nullptr;
        }
        delete tmp;
        _size--;
    }

    void pop(size_t id) {
        if (id >= _size) {
            throw std::out_of_range("Index out of bounds!");
        }
        if (id == 0) {
            pop_front();
            return;
        }
        if (id == _size - 1) {
            pop_back();
            return;
        }

        Node<T> *curr = _head;
        for (size_t i = 0; i < id - 1; i++) {
            curr = curr->next;
        }
        Node<T> *tmp = curr->next;
        curr->next = tmp->next;
        curr->next->prev = curr;
        delete tmp;
        _size--;
    }

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

    void reverse() {
        Node<T> *curr = _head;
        Node<T> *nxt, *prv;
        while (curr) {
            prv = curr->prev;
            nxt = curr->next;
            curr->next = prv;
            curr->prev = nxt;
            curr = nxt;
        }
        Node<T> *tmp = _tail;
        _tail = _head;
        _head = tmp;
    }

    Node<T> *head() const { return _head; }
    Node<T> *tail() const { return _tail; }

    bool empty() const { return _head == nullptr; }

    size_t size() const { return _size; }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const DoublyLinkedList<T> &ll) {
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
