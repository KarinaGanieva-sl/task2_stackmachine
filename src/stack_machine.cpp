////////////////////////////////////////////////////////////////////////////////
// Module Name:  stack_machine.h/cpp
// Authors:      Sergey Shershakov
// Version:      0.2.0
// Date:         23.01.2017
//
// This is a part of the course "Algorithms and Data Structures" 
// provided by  the School of Software Engineering of the Faculty 
// of Computer Science at the Higher School of Economics.
////////////////////////////////////////////////////////////////////////////////

#include "stack_machine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>
namespace xi {

//==============================================================================
// Free functions -- helpers
//==============================================================================

// TODO: if you need any free functions, add their definitions here.
std::pair<int, bool> getInt(char* string)
{
    return std::make_pair(atoi(string), atoi(string));
}

//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(char op, int a, int b, int /*c*/) // < just commented unused argument. This does not affect the code anyhow.
{
    if(op != '+')
        throw std::logic_error("Operation other than Plus (+) are not supported");

    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const
{
    return arDue;
}

//AssignOp class
int AssignOp::operation(char op, int a, int /*b*/, int /*c*/)
{
    if(op != '=')
        throw std::logic_error("Operation other than Assign (=) are not supported");

    return a;
}
IOperation::Arity AssignOp::getArity() const
{
    return arUno;
}

//SigChangeOp class
int SigChangeOp::operation(char op, int a, int /*b*/, int /*c*/)
{
    if(op != '!')
        throw std::logic_error("Operation other than Sign Change (!) are not supported");

    return -a;
}
IOperation::Arity SigChangeOp::getArity() const
{
    return arUno;
}

//SigChangeOp class
int OrOp::operation(char op, int a, int b, int /*c*/)
{
    if(op != '|')
        throw std::logic_error("Operation other than Or (|) are not supported");

    return a | b;
}
IOperation::Arity OrOp::getArity() const
{
    return arDue;
}

//==============================================================================
// class StackMachine
//==============================================================================


// TODO: put StackMachine methods implementation here

void StackMachine::registerOperation(char symb, IOperation* oper)
{
    SymbolToOperMapConstIter it = _opers.find(symb);
    if(it != _opers.end())
        throw std::logic_error("An operation is already registered!");

    StackMachine::_opers[symb] = oper;
}

IOperation* StackMachine::getOperation(char symb)
{
    SymbolToOperMapConstIter it = _opers.find(symb);
    if(it == _opers.end())
        return nullptr;

    return it -> second;
}

void StackMachine::doOperation(IOperation* oper, char* token)
{
    switch (oper->getArity())
    {
        case IOperation::arUno:
            _s.push(oper->operation(token[0], _s.pop()));
            break;
        case IOperation::arDue:
            _s.push(oper->operation(token[0], _s.pop(), _s.pop()));
            break;
        case IOperation::arTre:
            _s.push(oper->operation(token[0], _s.pop(), _s.pop(), _s.pop()));
            break;
    }
}

int StackMachine::calculate(const std::string& expr, bool clearStack)
{
    char* tokens = new char[expr.length()+1];
    std::pair<int, bool> pair;
    IOperation* oper = nullptr;
    strcpy(tokens, expr.c_str());
    char* token = strtok(tokens, " ");
    if(clearStack)
        _s.clear();
    while(token)
    {
        pair = getInt(token);
        if(pair.second)
        {
            _s.push(pair.first);
            token = strtok(0, " ");
            continue;
        }
        oper = getOperation(token[0]);
        if(strlen(token) != 1 || oper == nullptr)
            throw std::logic_error("Invalid expression!");

        doOperation(oper, token);
        token = strtok(0, " ");
    }
    delete[] tokens;
    delete[] token;
    return _s.top();
}
} // namespace xi
