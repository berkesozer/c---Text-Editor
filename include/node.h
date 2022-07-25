#ifndef  _NODE_
#define  _NODE_
#include <iostream>

using namespace std;

template<typename T>
class Node
{
    public:
        Node * next;

        T data;

        Node(T d)
        {
            next = NULL;
            data = d;
        }

        Node(T d, Node * n)
        {
            next = n;
            data = d;
        }
};

#endif