#include<iostream>
#include<cstring>
#include<string>
#include<stack>
#include<algorithm>
#include<cstdio>
#include<fstream>
using namespace std;
struct Node
{
    int n;//行数
    string sen;
    Node *_prev, *_next;
    Node(string x): _next(NULL), _prev(NULL), sen(x), n(0)
    {}
};

class List
{
public:
    List(): _head(NULL), _tail(NULL)
    {}

    List(const List& l): _head(NULL), _tail(NULL)
    {
        Copy(l);
    }

    ~List()
    {
        Destory();
    }

    List& operator=(List l)
    {
        swap(_head, l._head);
        swap(_tail, l._tail);
        return *this;
    }

    void number()
    {
        int linenumber = 1;
        Node* cur = _head;
        while(cur != _tail)
            {
                cur -> n = linenumber++;
                cur = cur -> _next;
            }
        cur -> n = linenumber;
    }

    void Insert(Node* pos, string x)//前插
    {
        if (_head == pos)
            {
                Node* tmp = new Node(x);
                tmp->_next = pos;
                pos->_prev = tmp;
                _head = tmp;
            }
        else
            {
                Node* tmp = new Node(x);
                Node* prev = pos->_prev;
                Node* next = pos;

                prev->_next = tmp;
                tmp->_next = next;
                next->_prev = tmp;
                tmp->_prev = prev;
            }
    }

    void Erase(Node* pos)
    {
        //1.1个 2.头删 3.尾删 4.中间
        //分头删尾删因为next和prev指向两端时候为空，空没有_next和_prev
        Node* next = pos->_next;
        Node* prev = pos->_prev;
        if (_head == _tail)
            {
                _head = _tail = NULL;
            }
        else if (next == NULL)
            {
                _tail = prev;
                prev->_next = NULL;
            }
        else if (prev == NULL)
            {
                _head = next;
                next->_prev = NULL;
            }
        else
            {
                prev->_next = next;
                next->_prev = prev;
            }
        delete pos;
    }

    void Destory()
    {
        Node* cur = _head;
        while (cur)
            {
                Node* del = cur;
                cur = cur->_next;
                delete del;
            }
        _head = _tail = NULL;
    }

    void Copy(const List& l)
    {
        Node* cur = l._head;
        while (cur)
            {
                PushBack(cur->sen);
                cur = cur->_next;
            }
        //PushBack已经把_head和_tail处理了，此处不用管了
    }

    Node* Find(string x)
    {
        Node* cur = _head;
        while (cur)
            {
                if (cur->sen == x)
                    {
                        return cur;
                    }
                cur = cur->_next;
            }
        return NULL;
    }

    void Print()
    {
        Node* cur = _head;
        cout<<"================================================================="<<endl;
        while (cur)
            {
                printf("%-5d", cur->n);
                cout<<cur->sen<<endl;
                cur = cur->_next;
            }
        cout << endl;
        cout<<"================================================================="<<endl;
    }

    void Writetofile()
    {
        Node* cur = _head;
        if(cur == NULL)
            cout<<"cur == null"<<endl;
        while (cur)
            {
                cout << cur->sen << endl;
                cur = cur->_next;
            }
        cout << endl;
    }

    void PushBack(string x)//插到尾部
    {
        //1.空 2.非空
        if (_head == NULL)
            {
                _head = _tail = new Node(x);
            }
        else
            {
                Node* tmp = new Node(x);
                _tail->_next = tmp;
                tmp->_prev = _tail;
                _tail = tmp;
            }
    }

    void PushFront(string x)	//插到头部
    {
        //Insert判定不为空链才进去，所以要分类讨论
        //1.空 2.非空
        if (_head == NULL)
            {
                _head = _tail = new Node(x);
            }
        else
            {
                Insert(_head, x);
            }
    }

    void PopBack()
    {
        Erase(_tail);
    }

    void PopFront()
    {
        Erase(_head);
    }
    Node* _head;
    Node* _tail;
};
List read(string in)
{
    List mylist;
    ifstream fin;
    char cpy[100];
    strcpy(cpy, in.c_str());
    fin.open(cpy);
    string str;
    while (!fin.eof())

        {
            getline(fin, str);
            mylist.PushBack(str);
        }
    mylist.number();
    fin.close();
    return mylist;
}
void write(string out, List mylist)
{
    char cpy[100];
    strcpy(cpy, out.c_str());
    freopen(cpy,"w",stdout);
    mylist.Writetofile();
    freopen("CON", "w", stdout);
}
void help()
{
    cout <<"---------------------------------------"<<endl;
    cout << "h(help)" << endl;
    cout << "v(iew)" << endl;
    cout << "# (jump to the first line)"<<endl;
    cout << "$ (jump to the last line)" << endl;
    cout << "p(revious)" << endl;
    cout << "n(ext)" << endl;
    cout << "j(ump)" << endl;
    cout << "i(nsert)" << endl;
    cout << "d(elete)" << endl;
    cout << "x (Replace current line)" << endl;
    cout << "c (Replace a substring)" << endl;
    cout << "s(earch)" << endl;
    cout << "q (Statistics file lines and characters)" << endl;
    cout << "r(ead)" << endl;
    cout << "w(rite)" << endl;
    cout << "exit" << endl;
    cout <<"---------------------------------------"<<endl;
}
void start(string in, string out)
{
    help();
    List mylist = read(in);
    Node* cur = mylist._head;
    mylist.Print();
    while(1)
        {
            cout<<"Current line:"<<endl;
            printf("%-5d", cur->n);
            cout<<cur->sen<<endl;
            cout<<"Input parameters:";
            string arg;
            cin>>arg;
            if(arg == "h")
                {
                    help();
                }
            else   if(arg == "v")
                {
                    mylist.Print();
                }
            else   if(arg == "#")
                {
                    cur = mylist._head;
                }
            else   if(arg == "$")
                {
                    cur = mylist._tail;
                }
            else   if(arg == "p")
                {
                    if(cur == mylist._head)
                        {
                            cout<<"There is no previous line!"<<endl;
                            continue;
                        }
                    else
                        cur = cur ->_prev;
                }
            else   if(arg == "n")
                {
                    if(cur == mylist._tail)
                        {
                            cout<<"There is no next line!"<<endl;
                            continue;
                        }
                    else
                        cur = cur ->_next;
                }
            else   if(arg == "j")
                {
                    cout<<"Please enter which line you want to jump to:";
                    int nn;
                    cin>>nn;
                    if(nn<1 || nn > mylist._tail->n)
                        {
                            cout<<"The number of lines you entered is out of bounds!"<<endl;
                            continue;
                        }
                    else
                        {
                            Node* temp = mylist._head;
                            while(temp->n != nn)
                                temp = temp->_next;
                            cur = temp;
                        }
                }
            else   if(arg == "i")
                {
                    string inserts;
                    cout<<"Please enter what you want to insert into the previous line of this line:";
                    getchar();
                    getline(cin, inserts);
                    mylist.Insert(cur, inserts);
                    mylist.number();
                }
            else   if(arg == "d")
                {
                    Node* temp = cur;
                    if(cur == mylist._tail)
                        cur = cur->_prev;
                    else
                        cur = cur->_next;
                    mylist.Erase(temp);
                    mylist.number();
                }
            else   if(arg == "x")
                {
                    string alter;
                    cout<<"Please enter what you want to replace with this line:";
                    getchar();
                    getline(cin, alter);
                    cur->sen = alter;
                }
            else   if(arg == "c")
                {
                    string b, a;
                    cout<<"Please enter the string before your correction:";
                    getchar();
                    getline(cin, b);
                    cout<<endl;
                    cout<<"Please enter your corrected string:";
                    getline(cin, a);
                    Node* temp = mylist._head;
                    while(temp->_next != NULL)
                        {
                            while(temp->sen.find(b) != temp->sen.npos)
                                {
                                    int pos = temp->sen.find(b);
                                    temp->sen.replace(pos, b.size(), a);
                                }
                            temp = temp->_next;
                        }
                }
            else   if(arg == "s")
                {
                    string b;
                    cout<<"Please enter the string you want to find:";
                    getchar();
                    getline(cin, b);
                    Node* temp = mylist._head;
                    while(temp != NULL)
                        {
                            if(temp->sen.find(b) != temp->sen.npos)
                                {
                                    cur = temp;
                                    break;
                                }
                            temp = temp->_next;
                        }
                    temp = mylist._head;
                    int c = 0;
                    while(temp != NULL)
                        {
                            if(temp->sen.find(b) != temp->sen.npos)
                                {
                                    c++;
                                }
                            temp = temp->_next;
                        }
                    temp = mylist._head;
                    cout<<"already found "<<c<<" lines which contains your string:"<<endl;
                    cout<<"---"<<endl;
                    while(temp != NULL)
                        {
                            if(temp->sen.find(b) != temp->sen.npos)
                                {
                                    printf("%-5d", temp->n);
                                    cout<<temp->sen<<endl;
                                }
                            temp = temp->_next;
                        }
                    cout<<"---"<<endl;
                }
            else   if(arg == "q")
                {
                    Node* temp = mylist._head;
                    int te = 0;
                    int line = 0;
                    while(temp != NULL)
                        {
                            te += temp->sen.size();
                            line++;
                            temp = temp->_next;
                        }
                    cout<<"There are "<<line<<" lines, and there are "<<te<<" characters"<<endl;
                }
            else   if(arg == "r")
                {
                    mylist = read(in);
                    cur = mylist._head;
                }
            else   if(arg == "w")
                {
                    write(out, mylist);
                }
            else   if(arg == "exit")
                {
                    break;
                }
            else
                {
                    cout<<"Incorrect parameters, please re-enter"<<endl;
                }
        }
}
int main()
{
    string a, b;
    cout << "Please enter the file name of the input file (already exists) ";
    cin >> a;
    cout << endl;
    cout << "Please enter the file name of the output file: ";
    cin >> b;
    cout << endl;
    start(a, b);
    return 0;
}
