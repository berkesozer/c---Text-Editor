#ifndef  _STACK_
#define  _STACK_
#include <iostream>
#include "node.h"

using namespace std;

template<typename T>
class Stack
{
    public:
        Node<T> * root;
        T nil;
        
        void push(T data)
        {
            Node<T> * add = new Node<T>(data);
            add->next = root;
            root = add;
        }

        void pop()
        {
            if (root)
            {
                Node<T> * r = root;
                root = root->next;
                delete r;
            }
        }

        T top()
        {
            if (root)
            {
                return root->data;
            }
            return NULL;
        }
};

#endif