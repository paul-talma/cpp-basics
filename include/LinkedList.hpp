#include <cstddef>
#include <string>
class LinkedList {
  public:
    struct Node {
        int val;
        Node *next;
        Node(int v = 0, Node *node = nullptr);
    };

    Node *head;
    Node *tail;

    LinkedList();
    LinkedList(int n);
    LinkedList(int *arr, size_t n);
    ~LinkedList();
    void push_back(int n);

    void push_front(int n);

    void insert_at(size_t id, int n);

    void pop_front();

    void pop_back();

    void pop(size_t id);

    std::string show();

    int front() const;

    int back() const;

    bool empty() const;

    size_t len() const;

  private:
    size_t size{0};
};
