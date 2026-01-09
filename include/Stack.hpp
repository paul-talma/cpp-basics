#include "Array.hpp"
#include <cstddef>
class Stack {
  public:
    // constructors
    Stack();
    Stack(size_t n);
    Stack(int *arr, size_t n);
    // copy constructors
    Stack(const Stack &other);
    Stack &operator=(const Stack &other);
    // move constructors
    Stack(const Stack &&other);
    Stack &operator=(const Stack &&other);

    // class methods
    void push(int n);
    int pop();
    int top() const;
    bool empty() const;
    size_t size() const;

  private:
    Array data;
};
