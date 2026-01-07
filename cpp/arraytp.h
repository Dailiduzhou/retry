#ifndef ARRAYTP_H_
#define ARRAYTP_H_

#include<iostream>
#include<cstdlib>

template <class T, int n>
class ArrayTP
{
    private:
        T ar[n];
    public:
        ArrayTP() {};
        explicit ArrayTP(const T & v);
        virtual T & operator[](int i);
        virtual const T & operator[](int i) const;
};


#endif