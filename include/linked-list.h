#ifndef  LINKED_LIST
#define  LINKED_LIST
#include <iostream>
#include "node.h"

using namespace std;

template<typename T>
class LL
{
    public:
        int size;

        Node<T> * root;

        LL()
        {
            size = 0;
            root = NULL;
        }

        void insert(int n, T data, T nil)
        {
            Node<T> ** r = & root;
            int i = 1;

            while ((i++) < n)
            {
                if (!(* r)->next)
                {
                    (* r)->next = new Node<T>(nil);
                }
                r = & ((* r)->next);
            }

            * r = new Node<T>(data, (* r));
            
            size = (size < n) ? n : size + 1;
        }

        void insert(T data)
        {
            Node<T> ** r = & root;

            while (* r)
            {
                r = & ((* r)->next);
            }

            Node<T> * new_node = new Node<T>(data, (* r));
            * r = new_node;
            size++;
        }

        void delet(int n)
        {
            Node<T> ** r = & root;
            int i = 1;

            while ((i++) < n)
            {
                r = & ((* r)->next);
            }

            Node<T> * temp = * r;
            (* r) = (* r)->next;

            delete temp;
            size--;
        }

        void swap(Node<T> * x, Node<T> * y)
        {
            T tempnry = x -> data;
            x -> data = y -> data;
            y -> data = tempnry;
        }

        void move(int n, int m)
        {
            Node<T> * N = get_item(n - 1);
            Node<T> * M = get_item(m - 1);
            swap(N, M);
        }

        void replace(int n, T data)
        {
            Node<T> ** r = & root;
            int i = 1;

            while ((i ++) < n)
            {
                r = & ((* r)->next);
            }

            (* r)->data = data;
        }

        Node<T> * get_item(int n)
        {
            int o = 0;
            Node<T> * r = root;
            while (o++ < n)
            {
                if (!(r->next))
                {
                    return NULL;
                }
                r = r->next;
            }
            return r;
        }
};

#endif