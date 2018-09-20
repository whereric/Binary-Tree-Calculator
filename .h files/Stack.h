#ifndef STACK_H
#define STACK_H

#include <iostream>
#include "List.h"
using namespace std;

template <class Arbitrary>
class Stack : private List<Arbitrary> {
public:
        using List<Arbitrary> :: IsEmpty;
        using List<Arbitrary> :: getOccupancy;
        using List<Arbitrary> :: Write;

        Arbitrary * Pop (void);
        Arbitrary * Push (Arbitrary *);
        Arbitrary * Top (void) const;
};

#include "Stack.c"

#endif
