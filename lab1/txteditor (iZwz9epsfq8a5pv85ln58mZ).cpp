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
    int n; //行数
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
                cout <<cur->n<<" "<< cur->sen << endl;
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
    cout << "h 显示帮助" << endl;
    cout << "v 显示当前文件内容" << endl;
    cout << "# 到第一行"<<endl;
    cout << "$ 到最后一行" << endl;
    cout << "p 到前一行" << endl;
    cout << "n 到后一行" << endl;
    cout << "j 到指定的某一行" << endl;
    cout << "i 插入上一行" << endl;
    cout << "d 删除一行" << endl;
    cout << "x 替换当前行" << endl;
    cout << "c 替换某个子串" << endl;
    cout << "s 查找某个子串" << endl;
    cout << "q 统计文件行数和字符数" << endl;
    cout << "r 重新读入文件" << endl;
    cout << "w 保存当前文件" << endl;
    cout << "exit 退出当前系统" << endl;
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
        cout<<"当前行："<<endl;
        cout<<cur->n<<" "<<cur->sen<<endl;
        cout<<"输入参数：";
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
                cout<<"没有前一行了！"<<endl;
                continue;
            }
            else
                cur = cur ->_prev;
        }
        else   if(arg == "n")
        {
            if(cur == mylist._tail)
            {
                cout<<"没有后一行了！"<<endl;
                continue;
            }
            else
                cur = cur ->_next;
        }
        else   if(arg == "j")
        {
            cout<<"请输入您想跳转到哪一行:";
            int nn;
            cin>>nn;
            if(nn<1 || nn > mylist._tail->n)
            {
                cout<<"您输入的行数越界了！"<<endl;
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
            cout<<"请输入您想将什么插入此行的上一行：";
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
            cout<<"请输入您想将什么替换到此行：";
            getchar();
            getline(cin, alter);
            cur->sen = alter;
        }
        else   if(arg == "c")
        {
            string b, a;
            cout<<"请输入您改正前的字符串：";
            getchar();
            getline(cin, b);
            cout<<endl;
            cout<<"请输入您改正后的字符串：";
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
            cout<<"请输入您想要查找的字符串：";
            getchar();
            getline(cin, b);
            Node* temp = mylist._head;
            while(temp->_next != NULL)
            {
                if(temp->sen.find(b) != temp->sen.npos)
                {
                    cur = temp;
                    break;
                }
                temp = temp->_next;
            }
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
            cout<<"文件一共有"<<line<<"行，一共有"<<te<<"个字符。"<<endl;
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
            cout<<"您输入了错误的参数， 请重新输入"<<endl;
        }
    }
}
int main()
{
    string a, b;
    cout << "请输入输入文件的文件名（已经存在）: ";
    cin >> a;
    cout << endl;
    cout << "请输入输出文件的文件名（并未存在）: ";
    cin >> b;
    cout << endl;
    start(a, b);
    return 0;
}
