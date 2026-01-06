#include <cstddef>
#include <string>
class Array {
  public:
    // constructors
    Array();
    Array(size_t n);
    Array(int *arr, size_t n);

    // copy constructors
    Array(const Array &other);
    Array &operator=(const Array &other);

    // destructor
    ~Array();

    void push(int n);

    int pop_back();

    void insert_at(size_t id, int n);

    void erase(size_t id);

    int &operator[](size_t id);
    const int &operator[](size_t id) const;

    int &at(size_t id);
    const int &at(size_t id) const;

    std::string show();

    size_t len() const;
    size_t cap() const;

  private:
    int *data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity);
};
