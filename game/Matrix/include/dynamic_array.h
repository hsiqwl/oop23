#ifndef LAB3_MATRIX_H
#define LAB3_MATRIX_H
#include <cstddef>
#include <type_traits>
#include <iterator>
#include <initializer_list>
#include <limits>
#include <utility>
#include <algorithm>
#include <concepts>
    template<std::default_initializable T>
    class dynamic_array;

    template<typename T, bool is_const>
    class array_iterator;


    template<typename T, bool is_const>
    class array_iterator {
    private:
        array_iterator(T *ptr) : ptr(ptr) {}

        friend dynamic_array<T>;
        friend array_iterator<T, !is_const>;
        typedef std::conditional_t<is_const, const T, T> *node_ptr_t;
        node_ptr_t ptr;
    public:
        typedef ptrdiff_t difference_type;
        typedef T value_type;
        typedef std::conditional_t<is_const, const T, T> *pointer;
        typedef std::conditional_t<is_const, const T, T> &reference;
        typedef std::contiguous_iterator_tag iterator_category;

        array_iterator() : ptr(nullptr) {}

        template<bool other_const>
        array_iterator(array_iterator<T, other_const> &&other) noexcept
        requires(is_const >= other_const) : ptr(
                other.ptr) {
            other.ptr = nullptr;
        }

        template<bool other_const>
        array_iterator(const array_iterator<T, other_const> &other) noexcept
        requires(is_const >= other_const): ptr(
                other.ptr) {}

        template<bool other_const>
        array_iterator &operator=(array_iterator<T, other_const> &&other) noexcept
                requires(is_const >= other_const) {
            ptr = other.ptr;
            other.ptr = nullptr;
        }

        template<bool other_const>
        array_iterator &
        operator=(const array_iterator<T, other_const> &other) noexcept
                requires(is_const >= other_const) {
            ptr = other.ptr;
        }

        array_iterator &operator++() noexcept {
            ++ptr;
            return *this;
        }

        array_iterator operator++(int) noexcept {
            array_iterator iter(ptr);
            ++ptr;
            return iter;
        }

        array_iterator &operator--() noexcept {
            --ptr;
            return *this;
        }

        array_iterator operator--(int) noexcept {
            array_iterator iter(ptr);
            --ptr;
            return iter;
        }

        reference operator*() noexcept {
            return *ptr;
        }

        std::add_const_t<reference> operator*() const noexcept {
            return *ptr;
        }

        template<bool other_const>
        bool operator==(const array_iterator<T, other_const> &other) const noexcept {
            return ptr == other.ptr;
        }

        array_iterator &operator+=(difference_type n) noexcept {
            ptr += n;
            return *this;
        }

       array_iterator &operator-=(difference_type n) noexcept {
            ptr -= n;
            return *this;
        }

        array_iterator operator+(difference_type n) const noexcept {
            array_iterator iter(ptr + n);
            return iter;
        }

        array_iterator operator-(difference_type n) const noexcept {
            array_iterator iter(ptr - n);
            return iter;
        }

        reference operator[](difference_type n) noexcept {
            return *(ptr + n);
        }

        std::add_const_t<reference> operator[](difference_type n) const noexcept {
            return *(ptr + n);
        }

        template<bool other_const>
        bool operator<=(const array_iterator<T, other_const> &other) const noexcept {
            return *ptr <= *other.ptr;
        }

        template<bool other_const>
        bool operator>(const array_iterator<T, other_const> &other) const noexcept {
            return *ptr > *other.ptr;
        }

        template<bool other_const>
        bool operator>=(const array_iterator<T, other_const> &other) const noexcept {
            return *ptr >= *other.ptr;
        }

        template<bool other_const>
        bool operator<(const array_iterator<T, other_const> &other) const noexcept {
            return *ptr < *other.ptr;
        }

        template<bool other_const>
        difference_type operator-(const array_iterator<T, other_const> &other) const noexcept {
            return ptr - other.ptr;
        }

        pointer operator->() const noexcept {
            return ptr;
        }

    public:
        friend array_iterator operator+(difference_type n, const array_iterator &iter) noexcept {
            array_iterator new_iter(iter.ptr + n);
            return new_iter;
        }
    };


    template<std::default_initializable T>
    class dynamic_array {
    private:
        T *data;
        size_t array_size;

        T *realloc(T *old_data, size_t old_size, size_t new_size) {
            T *new_data = new T[new_size];
            std::copy(old_data, old_data + old_size, new_data);
            delete[] old_data;
            return new_data;
        }

    public:
        typedef T value_type;
        typedef T &reference;
        typedef const T &const_reference;
        typedef array_iterator<T, true> const_iterator;
        typedef array_iterator<T, false> iterator;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

        dynamic_array() : data(nullptr), array_size(0) {}

        dynamic_array(size_type n) : data(new T[n]), array_size(n) {}

        dynamic_array(const dynamic_array &other) noexcept(std::copy_constructible<T>) {
            array_size = other.array_size;
            std::copy(other.data, other.data + array_size, data);
        }

        dynamic_array(dynamic_array &&other) noexcept(std::is_nothrow_move_constructible_v<T>) {
            data = std::exchange(other.data, nullptr);
            array_size = std::exchange(other.array_size, 0);
        }

        dynamic_array(size_type size, const T &value) noexcept(std::copy_constructible<T>)
                : data(new T[size]{value}), array_size(size) {};

        dynamic_array(const std::initializer_list<T> &v) noexcept(std::copy_constructible<T>) {
            data = new T[v.size()];
            array_size = v.size();
            int pos = 0;
            for (auto &i: v) {
                data[pos] = i;
                ++pos;
            }
        }

        ~dynamic_array() noexcept { delete[] data; array_size = 0;}

        dynamic_array &operator=(const std::initializer_list<T> &v) noexcept(std::copy_constructible<T>) {
            T *new_data = new T[v.size()];
            delete[] data;
            std::copy(v, v + v.size(), new_data);
            array_size = v.size();
            data = new_data;
            return *this;
        }

        dynamic_array &operator=(const dynamic_array &other) noexcept(std::copy_constructible<T>) {
            if (this == &other)
                return *this;
            T *new_data = new T[other.array_size];
            delete[] data;
            std::copy(other.data, other.data + other.array_size, new_data);
            array_size = other.array_size;
            data = new_data;
            return *this;
        }

        dynamic_array &operator=(dynamic_array &&other) noexcept {
            delete[] data;
            data = std::exchange(other.data, nullptr);
            array_size = std::exchange(other.array_size, 0);
            return *this;
        }

        bool operator==(const dynamic_array &other) const noexcept {
            bool equal_sizes = array_size == other.array_size;
            if (equal_sizes) {
                for (int i = 0; i < std::min(array_size, other.array_size); ++i) {
                    if (data[i] != other.data[i])
                        return false;
                }
                return true;
            } else
                return false;
        }

        reference operator[](size_t n) {
            return data[n];
        }

        const_reference operator[](size_t n) const {
            return data[n];
        }

        size_type size() const noexcept {
            return array_size;
        }

        size_type max_size() const noexcept {
            return std::numeric_limits<size_type>::max();
        }

        bool empty() const noexcept {
            return array_size == 0;
        }

        void swap(dynamic_array &other) noexcept {
            std::swap(data, other.data);
            std::swap(array_size, other.array_size);
        }

        iterator begin() noexcept {
            return iterator(data);
        }

        iterator end() noexcept {
            return iterator(data + array_size);
        }

        const_iterator cbegin() noexcept {
            return const_iterator(data);
        }

        const_iterator cend() noexcept {
            return const_iterator(data + array_size);
        }

        iterator erase(const_iterator q) noexcept {
            if (q.ptr == nullptr)
                return iterator(nullptr);
            for (auto i = q.ptr; i != data + array_size - 1; ++i)
                *i = *(i + 1);
            --array_size;
            data = realloc(data, array_size + 1, array_size);
            return iterator(const_cast<T *>(q.ptr));
        }

        iterator erase(const_iterator q1, const_iterator q2) noexcept {
            while (q1 != q2) {
                q1 = erase(q1);
            }
            return iterator(const_cast<T *>(q2.ptr));
        }

        template<typename ... Args>
        iterator emplace(const_iterator p, Args &&... args)requires(std::constructible_from<T, Args...>) {
            size_type pack_size = sizeof...(args);
            data = realloc(data, array_size, array_size + pack_size);
            array_size += pack_size;
            for (auto i = data + array_size - 1; i != p.ptr + pack_size - 1; --i)
                *i = *(i - pack_size);
            int count = 0;
            dynamic_array v({value_type(args)...});
            for (auto i = p.ptr; i != p.ptr + pack_size; ++i) {
                *i = v.data[count];
                ++count;
            }
            return iterator(p.ptr);
        }

        iterator insert(const_iterator p, const T &t) noexcept(std::copy_constructible<T>) {
            return emplace(p, t);
        }

        iterator insert(const_iterator p, T &&t) noexcept(std::move_constructible<T>) {
            return emplace(p, std::move(t));
        }

        iterator insert(const_iterator p, size_t n, const T &t) noexcept(std::copy_constructible<T>) {
            if (n == 0)
                return iterator(const_cast<T *>(p.ptr));
            else {
                iterator before_p(p.ptr - 1);
                try {
                    for (int i = 0; i < n; i++)
                        insert(p, t);
                } catch (...) {
                    erase(++before_p, p);
                    throw;
                }
                return ++before_p;
            }
        }

        template<std::input_iterator It>
        iterator insert(const_iterator p, It i, It j)requires(std::copy_constructible<T>) {
            if (i == j)
                return iterator(const_cast<T *>(p.ptr));
            else {
                iterator before_p(p.ptr - 1);
                try {
                    for (; i != j; ++i)
                        insert(p, *i);
                } catch (...) {
                    erase(++before_p, p);
                }
                return ++before_p;
            }
        }

        iterator insert(const_iterator p, std::initializer_list<T> il)requires(std::move_constructible<T>) {
            return insert(p, std::move_iterator(il.begin()), std::move_iterator(il.end()));
        }

        void clear() noexcept {
            erase(begin(), end());
        }

        template<std::forward_iterator It>
        void assign(It i, It j) {
            if (empty()) {
                insert(end(), i, j);
            } else {
                auto first = cbegin();
                auto last = --cend();
                insert(end(), i, j);
                erase(first, ++last);
            }
        }

        void assign(std::initializer_list<T> il)requires(std::copy_constructible<T>) {
            if (empty()) {
                insert(end(), std::move(il));
            } else {
                auto first = cbegin();
                auto last = --cend();
                insert(end(), std::move(il));
                erase(first, ++last);
            }
        }

        void assign(size_t n, const T &t)requires(std::copy_constructible<T>) {
            if (empty()) {
                insert(end(), n, t);
            } else {
                auto first = cbegin();
                auto last = --cend();
                insert(end(), n, t);
                erase(first, ++last);
            }

        }

        reference front() {
            return *begin();
        }

        const_reference front() const {
            return *begin();
        }

        reference back() {
            return *(--end());
        }

        const_reference back() const {
            return *(--end());
        }

        template<typename ... Args>
        void emplace_front(Args &&... args)requires(std::constructible_from<T, Args...>) {
            emplace(++begin(), args...);
        }

        template<typename ... Args>
        void emplace_back(Args &&... args)requires(std::constructible_from<T, Args...>) {
            emplace(end(), args...);
        }

        void push_front(const T &t)requires(std::copy_constructible<T>) {
            insert(++begin(), t);
        }

        void push_front(T &&t)requires(std::move_constructible<T>) {
            insert(++begin(), t);
        }

        void push_back(const T &t)requires(std::copy_constructible<T>) {
            insert(end(), t);
        }

        void push_back(T &&t)requires(std::move_constructible<T>) {
            insert(end(), t);
        }

        void pop_front() noexcept {
            if (empty())
                erase(begin());
        }

        void pop_back() noexcept {
            if (empty())
                erase(--end());
        }

        reference at(size_t n) {
            if (n >= array_size)
                throw std::out_of_range("out of range");
            else
                return data[n];
        }

        const_reference at(size_t n) const {
            if (n >= array_size)
                throw std::out_of_range("out of range");
            else
                return data[n];
        }
    };
#endif //LAB3_MATRIX_H
