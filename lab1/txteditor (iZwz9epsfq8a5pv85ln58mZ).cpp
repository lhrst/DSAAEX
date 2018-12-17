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
    int n; //����
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

        void Insert(Node* pos, string x)//ǰ��
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
            //1.1�� 2.ͷɾ 3.βɾ 4.�м�
            //��ͷɾβɾ��Ϊnext��prevָ������ʱ��Ϊ�գ���û��_next��_prev
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
            //PushBack�Ѿ���_head��_tail�����ˣ��˴����ù���
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

        void PushBack(string x)//�嵽β��
        {
            //1.�� 2.�ǿ�
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

        void PushFront(string x)	//�嵽ͷ��
        {
            //Insert�ж���Ϊ�����Ž�ȥ������Ҫ��������
            //1.�� 2.�ǿ�
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
    cout << "h ��ʾ����" << endl;
    cout << "v ��ʾ��ǰ�ļ�����" << endl;
    cout << "# ����һ��"<<endl;
    cout << "$ �����һ��" << endl;
    cout << "p ��ǰһ��" << endl;
    cout << "n ����һ��" << endl;
    cout << "j ��ָ����ĳһ��" << endl;
    cout << "i ������һ��" << endl;
    cout << "d ɾ��һ��" << endl;
    cout << "x �滻��ǰ��" << endl;
    cout << "c �滻ĳ���Ӵ�" << endl;
    cout << "s ����ĳ���Ӵ�" << endl;
    cout << "q ͳ���ļ��������ַ���" << endl;
    cout << "r ���¶����ļ�" << endl;
    cout << "w ���浱ǰ�ļ�" << endl;
    cout << "exit �˳���ǰϵͳ" << endl;
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
        cout<<"��ǰ�У�"<<endl;
        cout<<cur->n<<" "<<cur->sen<<endl;
        cout<<"���������";
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
                cout<<"û��ǰһ���ˣ�"<<endl;
                continue;
            }
            else
                cur = cur ->_prev;
        }
        else   if(arg == "n")
        {
            if(cur == mylist._tail)
            {
                cout<<"û�к�һ���ˣ�"<<endl;
                continue;
            }
            else
                cur = cur ->_next;
        }
        else   if(arg == "j")
        {
            cout<<"������������ת����һ��:";
            int nn;
            cin>>nn;
            if(nn<1 || nn > mylist._tail->n)
            {
                cout<<"�����������Խ���ˣ�"<<endl;
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
            cout<<"���������뽫ʲô������е���һ�У�";
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
            cout<<"���������뽫ʲô�滻�����У�";
            getchar();
            getline(cin, alter);
            cur->sen = alter;
        }
        else   if(arg == "c")
        {
            string b, a;
            cout<<"������������ǰ���ַ�����";
            getchar();
            getline(cin, b);
            cout<<endl;
            cout<<"����������������ַ�����";
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
            cout<<"����������Ҫ���ҵ��ַ�����";
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
            cout<<"�ļ�һ����"<<line<<"�У�һ����"<<te<<"���ַ���"<<endl;
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
            cout<<"�������˴���Ĳ����� ����������"<<endl;
        }
    }
}
int main()
{
    string a, b;
    cout << "�����������ļ����ļ������Ѿ����ڣ�: ";
    cin >> a;
    cout << endl;
    cout << "����������ļ����ļ�������δ���ڣ�: ";
    cin >> b;
    cout << endl;
    start(a, b);
    return 0;
}
