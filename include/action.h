#ifndef  _ACTION_
#define  _ACTION_
#include <iostream>

using namespace std;

enum Type
{
    save,
    insert,
    delet,
    move,
    replace,
    next,
    prev
};

class Action
{
    protected:
        int type;
    public:
        ~Action() { }
        virtual int get_type() = 0;
};

class Save : public Action
{
    public:
        string filename;
        string lastversion;

        Save(string f, string l)
        {
            type = Type::save;
            filename = f;
            lastversion = l;
        }

        int get_type()
        {
            return type;
        }
};

class Insert : public Action
{
    public:
        int offset;

        Insert(int o)
        {
            type = insert;
            offset = o;
        }

        int get_type()
        {
            return type;
        }
};

class Delet : public Action
{
    public:
        int offset;
        string text;

        Delet(int o, string t)
        {
            type = Type::delet;
            offset = o;
            text = t;
        }

        int get_type()
        {
            return type;
        }
};

class Move : public Action
{
    public:
        int offset_x;
        int offset_y;

        Move(int x, int y)
        {
            type = Type::move;
            offset_x = x;
            offset_y = y;
        }

        int get_type()
        {
            return type;
        }
};

class Replace : public Action
{
    public:
        int offset;
        string prevtext;

        Replace(int o, string t)
        {
            type = Type::replace;
            offset = o;
            prevtext = t;
        }

        int get_type()
        {
            return type;
        }
};

class Next : public Action
{
    public:
        Next()
        {
            type = Type::next;
        }

        int get_type()
        {
            return type;
        }
};

class Prev : public Action
{
    public:
        Prev()
        {
            type = Type::prev;
        }

        int get_type()
        {
            return type;
        }
};

#endif