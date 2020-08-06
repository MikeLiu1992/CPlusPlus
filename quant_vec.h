#include <immintrin.h>
#include <vector>
#include <exception>

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
    size_t size()
    {
        return _arr_size;
    }

    size_t capacity()
    {
        return _capacity;
    }
    
    quant_vector()
    {
        _arr_value = nullptr;
        _arr_size = 0;
        _capacity = 0;
    }

    quant_vector(const std::vector<T> &other)
    {
        _arr_size = other.size();
        _capacity = _arr_size;
        _arr_value = new double[_arr_size];
        for (size_t i = 0; i < _arr_size; i ++)
        {
            _arr_value[i] = (double)other[i];
        }
    }
    
    void push_back(T k)
    {
        if (_arr_size == 0)
        {
            _capacity = 2;
            _arr_size = 1;
            _arr_value = new double[_capacity];
            _arr_value[0] =  (double)k;
        }
        else
        {
            if (_arr_size == _capacity)
            {
               increase_capacity();
            }
            _arr_value[_arr_size] = (double)k;
            _arr_size += 1;         
        }       
    }

    T operator[](size_t i)
    {
        if (i >= _arr_size)
        {
            throw overflow_ex;
        }
        else
        {
            return (T)_arr_value[i]; 
        }
    }

    ~quant_vector()
    {
        _arr_size = 0;
        delete[] _arr_value;
    }

private:
    double * _arr_value;
    size_t _arr_size;
    size_t _capacity; 

    void increase_capacity()
    {
        _capacity *= 2;
        double *new_arr = new double[_capacity];
        const size_t aligendN = _arr_size - _arr_size % 4;
        for (size_t i = 0; i < aligendN; i+=4) 
        {
            _mm_storeu_pd(new_arr, _mm_loadu_pd(&_arr_value[i]));
        }
        for (size_t i = aligendN; i < _arr_size; ++i) {
            new_arr[i] = _arr_value[i];
        } 
        delete[] _arr_value;
        _arr_value = new_arr;
    }
};


