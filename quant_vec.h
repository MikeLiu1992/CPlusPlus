#include <immintrin.h>
#include <vector>
#include <exception>
#include <initializer_list>

class quant_vector_overflow_exception: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Quant vector overflow!";
  }
} overflow_ex;

template <class T>
class quant_vector {
public:

    size_t size() const;
    size_t capacity() const;
    void fast_copy(double *dest_arr, double *orig_arr, size_t i);
    quant_vector();
    quant_vector(const quant_vector &other);
    quant_vector(T other[], size_t arr_size);
    ~quant_vector();
    void push_back(T k);
    template <class K> quant_vector(const std::vector<K> &other) {list_initializer(other);}
       
    T operator[](size_t i) const
    {
        if (i >= _arr_size)
        {
            throw overflow_ex;
        }
        else
        {
            return _arr_value[i]; 
        }
    }
    template<class K>
    void list_initializer(const K &other)
    {
        _arr_size = other.size();
        _capacity = _arr_size;
        _arr_value = new T[_arr_size];
        for (size_t i = 0; i < _arr_size; i ++)
        {
            _arr_value[i] = (T)other[i];
        }
    }

protected:
    T * _arr_value;
    size_t _arr_size;
    size_t _capacity;   
};

class quant_double: public quant_vector<double>
{
public:
    quant_double():quant_vector<double>(){}  
    template <class K>
    quant_double(const std::vector<K> &other):quant_vector<double>(other) {} 
    template <class K>
    quant_double(K other[], size_t arr_size):quant_vector<double>(other, arr_size) {}  
    quant_double(const quant_double &other):quant_vector<double>(other) {} 
};

template <class T>
size_t quant_vector<T>::size() const
{
    return _arr_size;
}
template <class T>
size_t quant_vector<T>::capacity() const
{
    return _capacity;
}
template <class T>
void quant_vector<T>::fast_copy(double *dest_arr, double *orig_arr, size_t i)
{
    _mm256_storeu_pd(dest_arr + i * sizeof(double), _mm256_loadu_pd(orig_arr + i * sizeof(double)));
}
template <class T>
quant_vector<T>::quant_vector()
{
    _arr_value = nullptr;
    _arr_size = 0;
    _capacity = 0;
}
template <class T>
quant_vector<T>::quant_vector(const quant_vector &other) 
{
    list_initializer(other);
} 
template <class T>
quant_vector<T>::quant_vector(T other[], size_t arr_size)
{
    _arr_size = arr_size;
    _capacity = _arr_size;
    _arr_value = new T[_arr_size];
    int data_size = 32 / sizeof(T);
    const size_t aligendN = _arr_size - _arr_size % data_size;
    size_t i = 0;
    while (i < aligendN) 
    {
        fast_copy(_arr_value, other, i);
        i+=data_size;
    }
    while (i < _arr_size) 
    {
        _arr_value[i] = other[i];
        i ++;
    }
}
template <class T>
void quant_vector<T>::push_back(T k)
{
    if (_arr_size == 0)
    {
        _capacity = 2;
        _arr_size = 1;
        _arr_value = new T[_capacity];
        _arr_value[0] =  k;
    }
    else
    {
        if (_arr_size == _capacity)
        {
            _capacity *= 2;
            double *new_arr = new double[_capacity];
            int data_size = 32 / sizeof(T);
            const size_t aligendN = _arr_size - _arr_size % data_size;
            size_t i = 0;
            while (i < aligendN) 
            {
                fast_copy(new_arr, _arr_value, i);
                i+=data_size;
            }
            while (i < _arr_size) 
            {
                new_arr[i] = _arr_value[i];
                i ++;
            } 
    delete[] _arr_value;
    _arr_value = new_arr;
        }
        _arr_value[_arr_size] = k;
        _arr_size += 1;         
    }       
}
template <class T>
quant_vector<T>::~quant_vector()
{
    _arr_size = 0;
    delete[] _arr_value;
}