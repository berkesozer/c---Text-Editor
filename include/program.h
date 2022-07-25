#ifndef  _PROGRAM_
#define  _PROGRAM_
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <conio.h>
#include "action.h"
#include "linked-list.h"
#include "stack.h"

using namespace std;

class Program
{
    public:
        int CurrentPage;
        int Open;

        Stack<Action *> History;

        LL<string> Book;

        Program()
        {
            Open = CurrentPage = 0;
        }

        void Start()
        {
            do
            {
                cout << "command > ";
                string command;
                getline(cin, command);
                if (command.compare("exit") == 0)
                {
                    break;
                }
                else
                {
                    CommandParser(command);
                }
            }
            while (1);

            cout << "Program closed." << endl;
        }

        void CommandParser(string & command)
        {
            if (command.compare(0, 4, "open") == 0)
            {
                OpenParser(command);
            }
            else if (command.compare(0, 4, "save") == 0)
            {
                SaveParser(command);   
            }
            else if (command.compare(0, 6, "insert") == 0)
            {
                InsertParser(command);
            }
            else if (command.compare(0, 6, "delete") == 0)
            {
                DeletParser(command);
            }
            else if (command.compare(0, 4, "move") == 0)
            {
                MoveParser(command);
            }
            else if (command.compare(0, 7, "replace") == 0)
            {
                ReplaceParser(command);
            }
            else if (command.compare(0, 4, "next") == 0)
            {
                NextCommand(1);
            }
            else if (command.compare(0, 4, "prev") == 0)
            {
                PrevCommand(1);
            }
            else if (command.compare(0, 4, "undo") == 0)
            {
                UndoCommand();
            }
            else
            {
                cout << "Uncorrect command '" << command << "'." << endl << "Please retry.\n";
            }
        }

        void OpenParser(string & command)
        {
            command.erase(0, 5);
            OpenCommand(1, command);
        }

        void SaveParser(string & command)
        {
            command.erase(0, 5);
            SaveCommand(1, command);
        }

        void InsertParser(string & command)
        {
            int n;
            command.erase(0, command.find(" ") + 1);
            n = GetInteger(command);
            command.erase(0, command.find(" ") + 1);
            InsertCommand(1, n, command);
        }

        void DeletParser(string & command)
        {
            int n;
            command.erase(0, command.find(" ") + 1);
            n = GetInteger(command);

            DeletCommand(1, n);
        }

        void MoveParser(string & command)
        {
            int n, m;
            command.erase(0, command.find(" ") + 1);
            n = GetInteger(command);
            command.erase(0, command.find(" ") + 1);
            m = GetInteger(command);
            MoveCommand(1, n, m);
        }

        void ReplaceParser(string & command)
        {
            int n;
            command.erase(0, command.find(" ") + 1);
            n = GetInteger(command);
            command.erase(0, command.find(" ") + 1);
            
            ReplaceCommand(1, n, command);
        }

        void OpenCommand(int add_history, string & file)
        {
            ifstream reader(file);
            if (reader.is_open())
            {
                Open = 1;
                int n = 0;
                string line;
                while (getline(reader, line))
                {
                    if (line.compare("") != 0)
                    {
                        Book.insert(line);
                        if (add_history)
                        {
                            History.push((Action *)(new Insert(n++)));
                        }
                    }
                }
                PrintBook();
            }
            else
            {
                cout << "File '" << file << "' couldn't find." << endl;
            }
        }

        void SaveCommand(int add_history, string & file)
        {
            if (Open)
            {
                fstream saver(file);
                if (saver.is_open())
                {
                    string whole_file((std::istreambuf_iterator<char>(saver)), std::istreambuf_iterator<char>());
                    Node<string> * r = Book.root;
                    
                    saver.clear();
                    saver.seekg(0);

                    while (r)
                    {
                        saver << r->data << endl;
                        r = r->next;
                    }
                    
                    if (add_history)
                    {
                        History.push((Action *)(new Save(file, whole_file)));
                    }
                }
                else
                {
                    cout << "File '" << file << "' couldn't find." << endl;
                }
            }
            else
            {
                cout << "You should first open a file to read" << endl;
            }
        }

        void InsertCommand(int add_history, int n, string & text)
        {
            if (Open)
            {
                if (n > 0)
                {
                    Book.insert(n, text, "");
                    if (add_history)
                    {
                        History.push((Action *)(new Insert(n)));
                    }
                    PrintBook();
                }
                else
                {
                    cout << "You can add line just nonnegative indexes" << endl;
                }
            }
            else
            {
                cout << "You should first open a file to read" << endl;
            }
        }

        void DeletCommand(int add_history, int n)
        {
            if (Open)
            {
                if (n > 0 && n <= Book.size)
                {
                    string line = (Book.get_item(n - 1))->data;
                    Book.delet(n);
                    if (add_history)
                    {
                        History.push((Action *)(new Delet(n, line)));
                    }
                    PrintBook();
                }
                else
                {
                    cout << "You can delete only range line" << endl;
                }
            }
            else
            {
                cout << "You should first open a file to read" << endl;
            }
        }

        void MoveCommand(int add_history, int n, int m)
        {
            if (Open)
            {
                if ( n && m && n != m && n <= Book.size && m <= Book.size)
                {
                    Book.move(n, m);
                    if (add_history)
                    {
                        History.push((Action *)(new Move(n, m)));
                    }
                    PrintBook();
                }
                else
                {
                    cout << "Indexes can just in range and different number" << endl;
                }
            }
            else
            {
                cout << "You should first open a file to read" << endl;
            }   
        }

        void ReplaceCommand(int add_history, int n, string & text)
        {
            if (Open)
            {
                if (n > 0 && n <= Book.size)
                {
                    string line = (Book.get_item(n - 1))->data;
                    Book.replace(n, text);
                    if (add_history)
                    {
                        History.push((Action *)(new Replace(n, line)));
                    }
                    PrintBook();
                }
                else
                {
                    cout << "You can replace only range line" << endl;
                }
            }
            else
            {
                cout << "You should first open a file to read" << endl;
            }
        }

        void NextCommand(int add_history)
        {
            if (Open)
            {
                if ((CurrentPage + 1) * 10 < Book.size)
                {
                    CurrentPage++;
                    if (add_history)
                    {
                        History.push((Action *)(new Next()));
                    }
                    PrintBook();
                }
                else
                {
                    cout << "There is no next page" << endl;
                }
            }
            else
            {
                cout << "You should first open a file to read" << endl;
            }
        }

        void PrevCommand(int add_history)
        {
            if (Open)
            {
                if (CurrentPage > 0)
                {
                    CurrentPage--;
                    if (add_history)
                    {
                        History.push((Action *)(new Next()));
                    }
                    PrintBook();
                }
                else
                {
                    cout << "You can get just nonnegative pages" << endl;
                }
            }
            else
            {
                cout << "You should first open a file to read" << endl;
            }
        }

        void UndoCommand()
        {
            if (Open)
            {
                Action * last = NULL;
                if ((last = History.top()))
                {
                    int type = last->get_type();

                    if (type == Type::save)
                    {
                        Save * p = (Save *)last;
                        ofstream typer(p->filename);
                        typer << p->lastversion;
                    }
                    else if (type == Type::insert)
                    {
                        Insert * p = (Insert *)last;
                        DeletCommand(0, p->offset);
                    }
                    else if (type == Type::delet)
                    {
                        Delet * p = (Delet *)last;
                        InsertCommand(0, p->offset, p->text);
                    }
                    else if (type == Type::move)
                    {
                        Move * p = (Move *)last;
                        MoveCommand(0, p->offset_y, p->offset_x);
                    }
                    else if (type == Type::replace)
                    {
                        Replace * p = (Replace *)last;
                        ReplaceCommand(0, p->offset, p->prevtext);
                    }
                    else if (type == Type::next)
                    {
                        PrevCommand(0);
                    }
                    else if (type == Type::prev)
                    {
                        NextCommand(0);
                    }
                    else
                    {
                        cout << "Unexpected Action" << endl;
                    }
                    History.pop();
                }
                else
                {
                    cout << "History list is empty" << endl;
                }
            }
            else
            {
                cout << "There is nothing to revert back" << endl;
            }
        }

        void PrintBook()
        {
            system("cls");
            Node<string> * r = Book.get_item(CurrentPage * 10);

            for (int i = 0; i < 10 && r; ++i, r=r->next)
            {
                cout << CurrentPage * 10 + 1 + i << ") " << r->data << endl;
            }

            cout << endl << "---PAGE " << CurrentPage + 1 << "---" << endl << endl;
        }

        int GetInteger(string & command)
        {
            int integer = 0;
            string number = command.substr(0, command.find(" "));

            for (int i = 0, length = number.length(); i < length; ++i)
            {
                integer += (number[i] - 48) * pow(10, length - i - 1);
            }

            return integer;
        }
};

#endif