#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <cassert>
#include <iterator>
#include <limits>


    template <class Type>
    class Vector;

    template <class val_type, bool is_const>
    class Vector_iterator
    {
    private:
        typedef std::conditional_t<is_const, const val_type, val_type>* elem_ptr;

        elem_ptr ptr;

        Vector_iterator(elem_ptr ptr): ptr(ptr){};

        template <class Type>
        friend class Vector;

        friend Vector_iterator<val_type, !is_const>;

    public:
        typedef ptrdiff_t difference_type;
        typedef val_type value_type;
        typedef std::conditional_t<is_const, const val_type, val_type>* pointer;
        typedef std::conditional_t<is_const, const val_type, val_type>& reference;
        typedef std::random_access_iterator_tag iterator_category;

        constexpr Vector_iterator () noexcept;

        template <bool other_const>
        Vector_iterator(const Vector_iterator<val_type, other_const>& it) noexcept
        requires (is_const >= other_const);

        template <bool other_const>
        Vector_iterator(Vector_iterator<val_type, other_const>&& it) noexcept
        requires (is_const >= other_const);

        template <bool other_const>
        Vector_iterator& operator = (const Vector_iterator<val_type, other_const>& it) noexcept
        requires (is_const >= other_const);

        template <bool other_const>
        Vector_iterator& operator = (Vector_iterator<val_type, other_const>&& it) noexcept
        requires (is_const >= other_const);

        reference operator * () const noexcept;
        //pointer operator -> () const noexcept;

        template <bool other_const>
        bool operator == (const Vector_iterator<val_type, other_const>& it) const noexcept;
        template<bool other_const>
        bool operator != (const Vector_iterator<val_type, other_const>& it) const noexcept;
        template<bool other_const>
        bool operator < (const Vector_iterator<val_type, other_const>& it) const noexcept;
        template<bool other_const>
        bool operator > (const Vector_iterator<val_type, other_const>& it) const noexcept;
        template<bool other_const>
        bool operator <= (const Vector_iterator<val_type, other_const>& it) const noexcept;
        template<bool other_const>
        bool operator >= (const Vector_iterator<val_type, other_const>& it) const noexcept;

        Vector_iterator& operator ++ () noexcept;
        Vector_iterator operator ++ (int) noexcept;
        Vector_iterator& operator -- () noexcept;
        Vector_iterator operator -- (int) noexcept;

        Vector_iterator operator +(difference_type n) const noexcept;
        Vector_iterator operator -(difference_type n) const noexcept;
        template<bool other_const>
        difference_type operator -(const Vector_iterator<val_type, other_const>& it) const;

        template<class n_type, bool is_const_n>
        friend Vector_iterator operator +(difference_type n, const Vector_iterator<n_type, is_const_n>& it);

        reference operator [](difference_type n) const;
        Vector_iterator& operator += (difference_type n);
        Vector_iterator& operator -= (difference_type n);

    };

    template <class Type>
    class Vector
    {
    private:

        size_t size;
        size_t capacity;

        Type* arr;
    public:

        typedef Type value_type;
        typedef Type& reference;
        typedef const Type& const_reference;
        typedef Vector_iterator<Type, false> iterator;
        typedef Vector_iterator<Type, true> const_iterator;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;

        constexpr iterator begin() noexcept;
        constexpr iterator end() noexcept;

        constexpr const_iterator begin() const noexcept;
        constexpr const_iterator end() const noexcept;
        constexpr const_iterator cbegin() const noexcept;
        constexpr const_iterator cend() const noexcept;

        constexpr Vector (): size(0), capacity(0), arr(nullptr) {};
        constexpr explicit Vector (size_type size);
        constexpr explicit Vector (size_type size, const_reference val)
        requires std::copy_constructible<Type>;
        constexpr Vector (const std::initializer_list<Type>& il);

        constexpr Vector (Vector const& v);
        constexpr Vector (Vector&& v) noexcept;

        constexpr Vector& operator = (const Vector& v);
        constexpr Vector& operator = (Vector&& v) noexcept;
        constexpr Vector& operator = (const std::initializer_list<Type>& il);
        constexpr bool operator == (Vector const& v) const;
        constexpr reference operator [](size_type pos);
        constexpr const_reference operator [](size_type pos) const;

        [[nodiscard]] constexpr size_type get_size() const noexcept;
        [[nodiscard]] constexpr size_type get_capacity() const noexcept;
        [[nodiscard]] constexpr size_type max_size() const noexcept;
        [[nodiscard]] constexpr bool empty() const noexcept;

        constexpr void reserve(size_type new_capacity)
        requires std::move_constructible<Type>;
        constexpr void shrink_to_fit()
        requires std::move_constructible<Type>;

        constexpr reference at(size_type pos);
        constexpr const_reference at(size_type pos) const;
        constexpr reference front();
        constexpr const_reference front() const;
        constexpr reference back();
        constexpr const_reference back() const;
        constexpr Type* data() noexcept;
        constexpr const Type* data() const noexcept;

        constexpr void assign (size_type size, const Type& val);
        constexpr void push_back (const Type& val);
        constexpr void pop_back();
        constexpr iterator insert(const_iterator position, const Type& val);
        constexpr iterator erase(iterator position);
        constexpr void clear();
        constexpr void resize(size_type size);

        ~Vector() {delete[] this->arr; };
    };

    static_assert(std::random_access_iterator <Vector_iterator <int, false>>);
    static_assert(std::random_access_iterator <Vector_iterator <int, true>>);

    template <class val_type, bool is_const>
    constexpr Vector_iterator <val_type, is_const>::Vector_iterator () noexcept: ptr(nullptr) {}

    template <class val_type, bool is_const>
    template <bool other_const>
    Vector_iterator <val_type, is_const>::Vector_iterator(const Vector_iterator<val_type, other_const>& it) noexcept
    requires (is_const >= other_const)
            : ptr(it.ptr) {}

    template <class val_type, bool is_const>
    template <bool other_const>
    Vector_iterator <val_type, is_const>::Vector_iterator(Vector_iterator<val_type, other_const>&& it) noexcept
    requires (is_const >= other_const)
            : ptr(it.ptr)
    {
        it.ptr = nullptr;
    }

    template <class val_type, bool is_const>
    template <bool other_const>
    Vector_iterator <val_type, is_const>& Vector_iterator <val_type, is_const>::operator = (const Vector_iterator<val_type, other_const>& it) noexcept
    requires (is_const >= other_const)
    {
        ptr = it.ptr;
        return *this;
    }

    template <class val_type, bool is_const>
    template <bool other_const>
    Vector_iterator <val_type, is_const>& Vector_iterator <val_type, is_const>::operator = (Vector_iterator<val_type, other_const>&& it) noexcept
    requires (is_const >= other_const)
    {
        this->ptr = it.ptr;
        it.ptr = nullptr;
    }

    template <class val_type, bool is_const>
    typename Vector_iterator <val_type, is_const>::reference Vector_iterator <val_type, is_const>::operator * () const noexcept
    {
        return *(this->ptr);
    }

   /* template <class val_type, bool is_const>
    typename Vector_iterator <val_type, is_const>::pointer Vector_iterator <val_type, is_const>::operator -> () const noexcept
    {
        return &this->ptr;
    }*/

    template <class val_type, bool is_const>
    template <bool other_const>
    bool Vector_iterator <val_type, is_const>::operator == (const Vector_iterator<val_type, other_const>& it) const noexcept
    {
        return this->ptr == it.ptr;
    }

    template <class val_type, bool is_const>
    template<bool other_const>
    bool Vector_iterator <val_type, is_const>::operator != (const Vector_iterator<val_type, other_const>& it) const noexcept
    {
        return this->ptr != it.ptr;
    }

    template <class val_type, bool is_const>
    template<bool other_const>
    bool Vector_iterator <val_type, is_const>::operator < (const Vector_iterator<val_type, other_const>& it) const noexcept
    {
        return this->ptr < it.ptr;
    }

    template <class val_type, bool is_const>
    template<bool other_const>
    bool Vector_iterator <val_type, is_const>::operator > (const Vector_iterator<val_type, other_const>& it) const noexcept
    {
        return this->ptr > it.ptr;
    }

    template <class val_type, bool is_const>
    template<bool other_const>
    bool Vector_iterator <val_type, is_const>::operator <= (const Vector_iterator<val_type, other_const>& it) const noexcept
    {
        return this->ptr <= it.ptr;
    }

    template <class val_type, bool is_const>
    template<bool other_const>
    bool Vector_iterator <val_type, is_const>::operator >= (const Vector_iterator<val_type, other_const>& it) const noexcept
    {
        return this->ptr >= it.ptr;
    }

    template <class val_type, bool is_const>
    Vector_iterator<val_type, is_const>& Vector_iterator <val_type, is_const>::operator ++ () noexcept
    {
        (*this).ptr++;
        return *this;
    }

    template <class val_type, bool is_const>
    Vector_iterator <val_type, is_const> Vector_iterator <val_type, is_const>::operator ++ (int) noexcept
    {
        Vector_iterator<val_type, is_const> old(*this);
        (*this).ptr++;
        return old;
    }

    template <class val_type, bool is_const>
    Vector_iterator <val_type, is_const>& Vector_iterator <val_type, is_const>::operator -- () noexcept
    {
        (*this).ptr--;
        return *this;
    }

    template <class val_type, bool is_const>
    Vector_iterator <val_type, is_const> Vector_iterator <val_type, is_const>::operator -- (int) noexcept
    {
        Vector_iterator<val_type, is_const> old(*this);
        (*this).ptr--;
        return old;
    }

    template <class val_type, bool is_const>
    Vector_iterator<val_type, is_const> Vector_iterator<val_type, is_const>::operator +(difference_type n) const noexcept
    {
        Vector_iterator<val_type,is_const> iter(this->ptr + n);
        return iter;
    }

    template <class val_type, bool is_const>
    Vector_iterator<val_type, is_const>  Vector_iterator<val_type, is_const>::operator -(difference_type n) const noexcept
    {
        Vector_iterator<val_type, is_const> iter(this->ptr - n);
        return iter;
    }

    template <class val_type, bool is_const>
    template<bool other_const>
    typename Vector_iterator <val_type, is_const>::difference_type Vector_iterator<val_type, is_const>::operator -(const Vector_iterator<val_type, other_const>& it) const
    {
        return ptr - it.ptr;
    }

    template <class val_type, bool is_const>
    Vector_iterator <val_type, is_const> operator +(typename Vector_iterator <val_type, is_const>::difference_type n, const Vector_iterator <val_type, is_const>& it)
    {
        it.ptr += n;
        return it;
    }

    template <class val_type, bool is_const>
    typename Vector_iterator <val_type, is_const>::reference Vector_iterator <val_type, is_const>::operator [](difference_type n) const
    {
        auto tmp = this->ptr;
        tmp += n;
        return *tmp;
    }

    template <class val_type, bool is_const>
    Vector_iterator <val_type, is_const>& Vector_iterator <val_type, is_const>::operator += (difference_type n)
    {
        this->ptr += n;
        return *this;
    }

    template <class val_type, bool is_const>
    Vector_iterator <val_type, is_const>& Vector_iterator <val_type, is_const>::operator -= (difference_type n)
    {
        this->ptr -= n;
        return *this;
    }

    template <class Type>
    constexpr typename Vector<Type>::iterator Vector<Type>::begin() noexcept
    {
        return iterator(this->arr);
    }

    template <class Type>
    constexpr typename Vector<Type>::iterator Vector<Type>::end() noexcept
    {
        return iterator(this->arr + this->size);
    }

    template <class Type>
    constexpr typename Vector<Type>::const_iterator Vector<Type>::begin() const noexcept
    {
        return const_iterator(this->arr);
    }

    template <class Type>
    constexpr typename Vector<Type>::const_iterator Vector<Type>::end() const noexcept
    {
        return const_iterator(this->arr + this->size);
    }

    template <class Type>
    constexpr typename Vector<Type>::const_iterator Vector<Type>::cbegin() const noexcept
    {
        return const_iterator(this->arr);
    }

    template <class Type>
    constexpr typename Vector<Type>::const_iterator Vector<Type>::cend() const noexcept
    {
        return const_iterator(this->arr + this->size);
    }

    template <class Type>
    constexpr Vector<Type>::Vector (size_type size)
    {
        this->arr = new Type[size];

        if (this->arr == nullptr)
        {
            throw std::bad_alloc();
        }

        this->size = size;
        this->capacity = size;
    }

    template <class Type>
    constexpr Vector<Type>::Vector (size_type size, const_reference val)
    requires std::copy_constructible<Type>
    {
        this->arr = new Type[size];

        if (this->arr == nullptr)
        {
            throw std::bad_alloc();
        }

        for (size_t i = 0; i < size; i++)
        {
            this->arr[i] = val;
        }

        this->size = size;
        this->capacity = size;
    }

    template<class Type>
    constexpr Vector<Type>::Vector(const std::initializer_list<Type> &il)
    {
        this->arr = new Type[il.size()];
        if(this->arr == nullptr)
        {
            throw std::bad_alloc();
        }

        for(size_t i = 0; i < il.size(); ++i){
            this->arr[i] = *(il.begin() + i);
        }
        this->size = il.size();
        this->capacity = il.size();
    }

    template <class Type>
    constexpr Vector<Type>::Vector (Vector const& v)
    {
        this->arr = new Type[v.size];

        if (this->arr == nullptr)
        {
            throw std::bad_alloc();
        }
        std::copy(v.arr, v.arr + v.size, this->arr);
        this->size = this->capacity = v.size;
    }

    template <class Type>
    constexpr Vector<Type>::Vector (Vector&& v) noexcept :
            size(v.size), capacity(v.capacity), arr(v.arr)
    {
        v.size = 0;
        v.capacity = 0;
        v.arr = nullptr;
    }

    template <class Type>
    constexpr Vector<Type>& Vector<Type>::operator = (const Vector& v)
    {
        if(this == &v)
            return *this;
        Type* new_data = new Type[v.size];
        if(new_data == nullptr)
            throw std::bad_alloc();
        for(int i = 0; i < v.size; ++i){
            new_data[i] = v[i];
        }
        delete[] this->arr;
        this->arr = new_data;
        this->size = v.size;
        this->capacity = v.size;
        return *this;
    }

    template <class Type>
    constexpr Vector<Type>& Vector<Type>::operator = (Vector<Type>&& v) noexcept
    {
        delete [] this->arr;
        this->size = v.size;
        this->capacity = v.capacity;
        this->arr = v.arr;

        v.size = 0;
        v.capacity = 0;
        v.arr = nullptr;
        return *this;
    }

    template<class Type>
    constexpr Vector<Type>& Vector<Type>::operator = (const std::initializer_list<Type> &il) {
        Type* new_data = new Type[il.size()];
        if(new_data == nullptr)
            throw std::bad_alloc();
        for(int i = 0 ; i < il.size(); ++i){
            new_data[i] = *(il.begin() + i);
        }
        delete[] this->arr;
        this->arr = new_data;
        this->size = il.size();
        this->capacity = il.size();
        return *this;
    }

    template <class Type>
    constexpr bool Vector<Type>::operator == (Vector const& v) const
    {
        if (this->size != v.size)
        {
            return false;
        }

        for (size_t i = 0; i < this->size; i++)
        {
            if (this->arr[i] != v[i])
            {
                return false;
            }
        }

        return true;
    }

    template <class Type>
    constexpr typename Vector<Type>::reference Vector<Type>::operator [] (size_type pos)
    {
        return this->arr[pos];
    }

    template <class Type>
    constexpr typename Vector<Type>::const_reference Vector<Type>::operator [] (size_type pos) const
    {
        return this->arr[pos];
    }

    template <class Type>
    constexpr typename Vector<Type>::size_type Vector<Type>::get_size () const noexcept
    {
        return this->size;
    }

    template <class Type>
    constexpr typename Vector<Type>::size_type Vector<Type>::get_capacity () const noexcept
    {
        return this->capacity;
    }

    template <class Type>
    constexpr typename Vector<Type>::size_type Vector<Type>::max_size () const noexcept
    {
        return std::numeric_limits<size_type>::max();
    }

    template <class Type>
    [[nodiscard]] constexpr bool Vector<Type>::empty () const noexcept
    {
        return this->size == 0;
    }

    template <class Type>
    constexpr void Vector<Type>::reserve (typename Vector<Type>::size_type new_capacity)
    requires std::move_constructible<Type>
    {
        if (new_capacity < this->capacity)
        {
            return;
        }

        Type* buf_arr = new Type[new_capacity];
        Type* ptr = buf_arr, *src = arr;
        for (size_t i = 0; i < this->size; i++, ptr++, src++)
        {
            new(static_cast<void*>(ptr)) Type{std::move(*src)};
        }

        delete [] arr;
        this->arr = buf_arr;
        this->capacity = new_capacity;
    }

    template <class Type>
    constexpr void Vector<Type>::shrink_to_fit ()
    requires std::move_constructible<Type>
    {
        if (this->capacity == this->size)
        {
            return;
        }

        Type* buf_arr = new Type[this->size];
        Type* ptr = buf_arr, *src = arr;
        for (size_t i = 0; i < this->size; i++, ptr++, src++)
        {;
            new(static_cast<void*>(ptr)) Type{std::move(*src)};
        }

        delete [] arr;
        this->arr = buf_arr;
        this->capacity = this->size;
    }

    template <class Type>
    constexpr typename Vector<Type>::reference Vector<Type>::at (size_type pos)
    {
        if (pos >= this->size)
        {
            throw std::out_of_range("bad pos");
        }
        else
        {
            return this->arr[pos];
        }
    }

    template <class Type>
    constexpr typename Vector<Type>::const_reference Vector<Type>::at (size_type pos) const
    {
        if (pos >= this->size)
        {
            throw std::out_of_range("bad pos");
        }
        else
        {
            return this->arr[pos];
        }
    }

    template <class Type>
    constexpr typename Vector<Type>::reference Vector<Type>::front ()
    {
        return this->arr[0];
    }

    template <class Type>
    constexpr typename Vector<Type>::const_reference Vector<Type>::front () const
    {
        return this->arr[0];
    }

    template <class Type>
    constexpr typename Vector<Type>::reference Vector<Type>::back ()
    {
        return this->arr[this->size-1];
    }

    template <class Type>
    constexpr typename Vector<Type>::const_reference Vector<Type>::back () const
    {
        return this->arr[this->size-1];
    }

    template <class Type>
    constexpr Type* Vector<Type>::data () noexcept
    {
        return this->arr;
    }

    template <class Type>
    constexpr const Type* Vector<Type>::data () const noexcept
    {
        return this->arr;
    }

    template <class Type>
    constexpr void Vector<Type>::assign (typename Vector<Type>::size_type size, const Type& val)
    {
        Type* new_data = new Type[size]{val};
        if(new_data == nullptr)
            throw std::bad_alloc();
        delete[] this->arr;
        this->arr = new_data;
        this->size = size;
        this->capacity = size;
    }

    template <class Type>
    constexpr void Vector<Type>::push_back (const Type& val)
    {
        this->insert(this->end(), val);
    }

    template <class Type>
    constexpr void Vector<Type>::pop_back ()
    {
        this->erase(this->end() - 1);
    }

    template <class Type>
    constexpr typename Vector<Type>::iterator Vector<Type>::insert (Vector<Type>::const_iterator position, const Type& val)
    {
        if (this->size == this->capacity)
        {
            if (this->size == 0)
            {
                this->capacity = 1;
            }
            else
            {
                this->capacity *= 2;
            }

            Type* buf_arr = new Type[this->capacity];
            Type* ptr = buf_arr, *src = arr;

            Vector<Type>::iterator it;
            for (it = this->begin(); it != position; it++, ptr++, src++)
            {
                new(static_cast<void*>(ptr)) Type{std::move(*src)};
            }

            Vector<Type>::iterator return_iter(ptr);
            *ptr = val;
            ++ptr;

            for ( ; it != this->end(); it++, ptr++, src++)
            {
                new(static_cast<void*>(ptr)) Type{std::move(*src)};
            }

            delete [] arr;
            this->arr = buf_arr;
            ++this->size;
            return return_iter;
        }
        else
        {
            Vector<Type>::iterator it;
            for (it = this->end(); it != position; --it)
            {
                *it = *(it-1);
            }
            *it = val;
            ++this->size;
            return it;
        }
    }

    template <class Type>
    constexpr typename Vector<Type>::iterator Vector<Type>::erase(Vector<Type>::iterator position)
    {
        size_t diff = position - begin();
        for (iterator it = position + 1; it != this->end(); it++)
        {
            *(it-1) = *(it);
        }
        if (this->size - 1 == this->capacity / 2)
        {
            this->capacity /= 2;

            Type* buf_arr = new Type[this->capacity];
            Type* ptr = buf_arr, *src = arr;
            for (size_t i = 0; i < this->size-1; i++, ptr++, src++)
            {
                new(static_cast<void*>(ptr)) Type{std::move(*src)};
            }

            delete [] arr;
            this->arr = buf_arr;
            this->size--;
        }
        else
        {
            this->size--;
        }
        return iterator(this->arr + diff);
    }

    template <class Type>
    constexpr void Vector<Type>::clear()
    {
        for (Type* ptr = this->arr; ptr != this->arr + this->size; ptr++)
        {
            ptr->~Type();
        }

        this->size = 0;
    }

    template <class Type>
    constexpr void Vector<Type>::resize (size_type size)
    {
        if (this->size == size)
        {
            return;
        }

        size_t copy_size;
        if (this->size < size)
        {
            copy_size = this->size;
        }

        if (this->size > size)
        {
            copy_size = size;
        }
        Type* buf_arr = new Type[size];
        Type* ptr = buf_arr, *src = arr;
        for (size_t i = 0; i < copy_size; i++, ptr++, src++)
        {
            new(static_cast<void*>(ptr)) Type{std::move(*src)};
        }
        delete [] arr;
        this->arr = buf_arr;
        this->capacity = size;
        this->size = size;
    }

#endif // VECTOR_H