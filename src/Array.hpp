#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <stdexcept>

template <typename T> class Array {
  private:
    T *_data;
    size_t _size;
    size_t _capacity;
    static constexpr size_t _min_capacity = 8;
    void _resize(size_t new_capacity) {
        new_capacity = std::max(new_capacity, _min_capacity);
        T *new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

  public:
    // constructors
    // default constructor
    Array() : _size(0), _capacity(_min_capacity) { _data = new T[_capacity]{}; }

    // initialize with given size
    Array(size_t n) : _size(n), _capacity(std::max(n, _min_capacity)) {

        _data = new T[_capacity]{};
    }

    // initialize from array
    Array(const T *arr, size_t n)
        : _size(n), _capacity(std::max(n, _min_capacity)) {
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
            _data[i] = arr[i];
        }
    }

    // initializer list
    Array(std::initializer_list<T> list)
        : _size(list.size()), _capacity(std::max(_size, _min_capacity)) {
        _data = new T[_capacity];
        size_t i{0};
        for (const T &elem : list) {
            _data[i++] = std::move(elem);
        }
    }

    // copy semantics
    Array(const Array &other) {
        std::cout << "calling copy constructor. copying from " << other
                  << std::endl;
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    };
    Array<T> &operator=(const Array &other) {
        std::cout << "calling copy assignment operator. copying from " << other
                  << std::endl;
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            T *new_data = new T[_capacity];
            for (size_t i = 0; i < _size; i++) {
                new_data[i] = other._data[i];
            }
            delete[] _data;
            _data = new_data;
        }
        return *this;
    }

    // move semantics
    Array(Array &&other) {
        std::cout << "calling move constructor. moving " << other << std::endl;
        _data = other._data;
        _size = other._size;
        _capacity = other._capacity;

        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }

    Array<T> &operator=(Array &&other) {
        std::cout << "calling move assignment operator. moving " << other
                  << std::endl;
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;

            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // destructor
    ~Array() { delete[] _data; }

    // member methods
    void push_back(const T &value) {
        if (_size == _capacity) {
            _resize(_capacity * 2);
        }
        _data[_size++] = value;
    }
    void push_back(T &&value) {
        if (_size == _capacity) {
            _resize(_capacity * 2);
        }
        _data[_size++] = std::move(value);
    }

    T pop_back() {
        if (_size == 0) {
            throw std::out_of_range("empty array");
        }
        _size--;
        T val = _data[_size];
        _data[_size].~T();
        if (_size < _capacity / 2 && _capacity / 2 > _min_capacity) {
            _resize(_capacity / 2);
        }
        return val;
    }

    void insert_at(size_t id, const T &value) {
        if (id > _size) {
            throw std::out_of_range("invalid index");
        }
        if (_size == _capacity) {
            _resize(_capacity * 2);
        }
        std::move_backward(_data + id, _data + _size, _data + _size + 1);
        _data[id] = value;
        _size++;
    }

    void erase(size_t id) {
        if (id >= _size) {
            throw std::out_of_range("invalid index");
        }
        std::move(_data + id + 1, _data + _size + 1, _data + id);
        _size--;
        _data[_size].~T();
        if (_size < _capacity / 2 && _capacity / 2 > _min_capacity) {
            _resize(_capacity / 2);
        }
    }

    void clear() { _size = 0; }

    T &operator[](size_t id) { return _data[id]; }
    const T &operator[](size_t id) const { return _data[id]; }

    T &at(size_t id) {
        if (id >= _size) {
            throw std::out_of_range("invalid index");
        }
        return _data[id];
    }
    const T &at(size_t id) const {
        if (id >= _size) {
            throw std::out_of_range("invalid index");
        }
        return _data[id];
    }

    size_t size() const { return _size; }
    size_t cap() const { return _capacity; }
    bool empty() const { return _size == 0; }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Array<T> &arr) {
    os << "[";
    size_t s{arr.size()};
    for (size_t i = 0; i < s; i++) {
        os << arr[i];
        if (i + 1 < s) {
            os << " ";
        }
    }
    os << "]";
    return os;
}
