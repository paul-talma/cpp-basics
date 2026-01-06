#include <cstddef>
#include <stdexcept>
#include <string>
class Array {
  public:
    Array() : size(0), capacity(8) { data = new int[capacity]; }
    Array(size_t n) : size(n), capacity(8) {
        if (size > capacity) {
            capacity = size;
        }
        data = new int[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = 0;
        }
    }
    Array(int *arr, size_t n) : size(n), capacity(8) {
        if (size > capacity) {
            capacity = size;
        }
        data = new int[capacity];
        for (size_t i = 0; i < size; i++) {
            data[i] = arr[i];
        }
    }
    ~Array() { delete[] data; }

    void push(int n) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = n;
    }

    int pop_back() {
        if (size == 0) {
            throw std::out_of_range("empty array");
        }
        size--;
        int val = data[size];
        if (size < capacity / 2) {
            resize(capacity / 2);
        }
        return val;
    }

    void insert_at(size_t id, int n) {
        if (id > size) {
            throw std::out_of_range("invalid index");
        }
        if (size == capacity) {
            resize(capacity * 2);
        }
        for (size_t i = size; i > id; i--) {
            data[i] = data[i - 1];
        }
        data[id] = n;
        size++;
    }

    void erase(size_t id) {
        if (id >= size) {
            throw std::out_of_range("invalid index");
        }
        size--;
        for (size_t i = id; i < size; i++) {
            data[i] = data[i + 1];
        }
        if (size < capacity / 2) {
            resize(capacity / 2);
        }
    }

    int &operator[](size_t id) { return data[id]; }
    const int &operator[](size_t id) const { return data[id]; }

    int &at(size_t id) {
        if (id >= size) {
            throw std::out_of_range("invalid index");
        }
        return data[id];
    }
    const int &at(size_t id) const {
        if (id >= size) {
            throw std::out_of_range("invalid index");
        }
        return data[id];
    }

    std::string show() {
        std::string arr_str = "[";
        for (size_t i = 0; i < size; i++) {
            arr_str.append(std::to_string(data[i]));
            if (i < size - 1) {
                arr_str.append(" ");
            }
        }
        return arr_str.append("]");
    }

    size_t len() const { return size; }
    size_t cap() const { return capacity; }

  private:
    int *data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity) {
        int *new_data = new int[new_capacity];
        for (size_t i = 0; i < size; i++) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }
};

int main() {
    int input[] = {1, 2, 3, 4, 5, 6, 7};
    Array arr(input, 7);

    arr.push(8);
    arr.push(9);
    arr.push(10);

    return 0;
}
