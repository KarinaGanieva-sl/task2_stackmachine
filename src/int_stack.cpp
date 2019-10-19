////////////////////////////////////////////////////////////////////////////////
// Module Name:  int_stack.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////


#include "int_stack.h"

// TODO: add necessary headers here
// #include <...
#include <iostream>

namespace xi {
    IntStack::IntStack(size_t sz)
    {
        _stack = new int[sz];
        _ssize = sz;
        _head = -1;
    }
    IntStack::~IntStack()
    {
        delete[] _stack;
    }
    void IntStack::push(int el)
    {
        if(_ssize == _head + 1)
            throw std::logic_error("Stack is overflow!!!");

        _stack[++_head] = el;
    }
    int IntStack::pop()
    {
        if(_head == -1)
            throw std::logic_error("Stack is empty!");

        return _stack[_head--];
    }
    int IntStack::top()
    {
        if(_head == -1)
            throw std::logic_error("Stack is empty!");

        return _stack[_head];
    }
    void IntStack::clear()
    {
        _head = -1;
    }
    bool IntStack::isEmpty() const
    {
        return _head == -1;
    }
    bool IntStack::isFull() const
    {
        return _head + 1 == _ssize;
    }

} // namespace xi

