/*
 * quadratic.h
 *      Angelo Segura Ibarra A01711723
 */

#ifndef QUADRATIC_H_
#define QUADRATIC_H_

#include <string>
#include <sstream>
#include <stdexcept>


class OutOfMemory : public std::exception 
{
    public:
        const char* what() const noexcept override 
        {
            return "Out of memory";
        }
};


class NoSuchElement : public std::exception 
{
    public:
        const char* what() const noexcept override 
        {
            return "No such element";
        }
};


class Overflow : public std::exception 
{
    public:
        const char* what() const noexcept override 
        {
            return "Overflow: Hash table is full";
        }
};

template <class Key, class Value>
class Quadratic 
{
    private:
        unsigned int (*func) (const Key);
        unsigned int size;
        unsigned int count;

        Key *keys;
        Key initialValue;
        Value *values;

        long indexOf(const Key) const;

    public:
        Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
        ~Quadratic();
        bool full() const;
        bool put(Key, Value);
        bool contains(const Key) const;
        Value get(const Key) const;
        void clear();
        std::string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key)) 
{
	size = sze;
	count = 0;
	initialValue = init;
	func = f;

	keys = new Key[size];
	if (keys == NULL) 
    {
		throw OutOfMemory();
	}

	values = new Value[size];
	if (values == NULL) 
    {
		throw OutOfMemory();
	}

	for (unsigned int i = 0; i < size; i++) 
    {
		keys[i] = initialValue;
		values[i] = 0;
	}
}


template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() 
{
	delete[] keys;
	delete[] values;
}


template <class Key, class Value>
bool Quadratic<Key, Value>::full() const 
{
	return count == size;
}


template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const 
{
	long index = func(k) % size; 
	unsigned int i = 0;

	while (keys[index] != initialValue) 
    {
		if (keys[index] == k) 
        {
			return index;
		}
		i++;
		index = (func(k) + i * i) % size; 

		if (i >= size) 
        {
			return -1; 
		}
	}
	return -1;
}

template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) 
{
	if (full()) 
    {
		throw Overflow();
	}

	long index = func(k) % size;
	unsigned int i = 0;

	while (keys[index] != initialValue && keys[index] != k) 
    {
		i++;
		index = (func(k) + i * i) % size; 
		if (i >= size) 
        {
			return false; 
		}
	}

	if (keys[index] == k) 
    {
		values[index] = v; 
	} 
    else 
    {
		keys[index] = k;
		values[index] = v;
		count++;
	}
	return true;
}


template <class Key, class Value>
bool Quadratic<Key, Value>::contains(const Key k) const 
{
	long index = func(k) % size;
	unsigned int i = 0;

	while (keys[index] != initialValue) 
    {
		if (keys[index] == k) 
        {
			return true;
		}
		i++;
		index = (func(k) + i * i) % size; 
		if (i >= size) 
        {
			return false;
		}
	}
	return false;
}


template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) const 
{
	long index = func(k) % size;
	unsigned int i = 0;

	while (keys[index] != initialValue) 
    {
		if (keys[index] == k) 
        {
			return values[index];
		}
		i++;
		index = (func(k) + i * i) % size; 
		if (i >= size) 
        {

			throw NoSuchElement();
		}
	}
	throw NoSuchElement();
}

template <class Key, class Value>
void Quadratic<Key, Value>::clear() 
{
	for (unsigned int i = 0; i < size; i++) 
    {
		keys[i] = initialValue;
		values[i] = 0;
	}
	count = 0;
}

template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const 
{
    std::stringstream aux;

    for (unsigned int i = 0; i < size; i++) 
    {
        if (keys[i] != initialValue) 
        {
            aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
        }
    }
    return aux.str();
}

#endif /* QUADRATIC_H_ */