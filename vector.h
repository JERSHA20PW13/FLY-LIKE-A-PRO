#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <iostream>

template <class T>

class Vector
{
private:
    T* data;
    int size;
    int capacity;

    const int CAPACITY_INCREMENT = 10;

    void resize(int location)
    {
        if(size==capacity || location>=capacity)
        {
            T* temp = new T[capacity + CAPACITY_INCREMENT];

            for(int i=0; i<size; i++)
            {
                temp[i]= data[i];
            }
            delete[] data;
            data = temp;

            capacity = capacity+ CAPACITY_INCREMENT;
        }

        else if(size <capacity-CAPACITY_INCREMENT)
        {
            T* temp = new T[capacity-CAPACITY_INCREMENT];
            for(int i=0; i<size; i++)
            {
                temp[i] = data[i];
            }
            delete[] data;
            data = temp;

            capacity = capacity- CAPACITY_INCREMENT;
        }
    }

public:
    Vector();
    Vector(const Vector&);
    int getSize();
    int getCapacity();
    bool isEmpty();
    void pushBack(T);
    void ins(int, T);
    void shiftRight(int);
    void sortRange(int, int);
    void removeAt(int);
    bool validIndex(int);
    int getLength(int);
    void print();

    T& operator[](int);
    Vector& operator=(const Vector&);

    //~Vector();
};

template <class T>
Vector<T>::Vector()
{
    size = 0;
    capacity = CAPACITY_INCREMENT;
    data = new T[capacity];
}

template <class T>
Vector<T>::Vector(const Vector& toCopy)
{
    size = toCopy.size;
    capacity = toCopy.capacity;
    data = new T[size];

    for(int i=0; i<size; i++)
    {
        data[i] = toCopy.data[i];
    }
}

template <class T>
int Vector<T>::getSize()
{
    return size;
}

template <class T>
int Vector<T>::getCapacity()
{
    return capacity;
}

template <class T>
bool Vector<T>::isEmpty()
{
    if (size==0)
        return true;
    else
        return false;
}

template <class T>
void Vector<T>::pushBack(T value)
{
    resize(0);
    data[size] = value;
    size++;
}

template <class T>
void Vector<T>::ins(int location, T value)
{
    while(location>=capacity || size==capacity)
    {
        resize(location);
    }
    shiftRight(location);
    data[location]= value;
}

template <class T>
void Vector<T>::shiftRight(int location)
{
    for(int i= size-1; i>=location; i--)
    {
        data[i+1]= data[i];
    }
    size++;
}

template <class T>
void Vector<T>::sortRange(int start, int stop)
{
    for(int i=start; i<stop; i++)
    {
        for(int j=i+1; j<=stop; j++)
        {
            if(data[i]>data[j])
            {
                T temp = data[i];
                data[i]= data[j];
                data[j]= temp;
            }
        }
    }
}

template <class T>
void Vector<T>::removeAt(int location)
{
    if(validIndex(location))
    {
        for(int i= location; i<size-1; i++)
        {
            data[i]=data[i+1];
        }

        size--;
    }
}

template <class T>
bool Vector<T>::validIndex(int location)
{
    if(location>=0 && location< size)
        return true;
    else
    {
        std::cerr << "Vector index out of bounds\n";
        return false;
    }
}

template <class T>
T& Vector<T>::operator[](int location)
{
    if(validIndex(location))
    {
        return data[location];
    }
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& toCopy)
{
    delete[] data;
    size = toCopy.size;
    capacity = toCopy.capacity;

    data = new T[size];
    for(int i=0; i<size; i++)
    {
        data[i]= toCopy.data[i];
    }
    return *this;
}

template <class T>
int Vector<T>::getLength(int index)
{
    T number = data[index];
    int numDigits =0;

    if(number==0)
    {
        numDigits++;
    }
    while(number)
    {
        number /=10;
        numDigits++;
    }
    return numDigits;
}

template <class T>
void Vector<T>::print()
{
    for(int i=0; i<size; i++)
    {
        std::cout << "[" << i << "]: " << data[i] << "\n";
    }
}

// Destructor: deallocate memory for vectors

    /*
    template <class T>
    Vector<T>::~Vector()
    {
        delete[] data;
    }*/

#endif // VECTOR_H_INCLUDED
