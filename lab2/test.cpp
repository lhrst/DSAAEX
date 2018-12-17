#include<iostream>
#include<stack>
#include<string>
using namespace std;
stack<char> mystack;//操作符
stack<double > outope;//操作数
bool judge(string s)
{
​stack<char> temp;
​for(int i=0;i<s.length();i++)​​//如果出现字母或者非法符号，返回false
​{
​​if(s[i]==' ')
{
​​​continue;
​​}
​​if(s[i]>='0'&&s[i]<='9')
​​{
​​​continue;
​​}
​​if(s[i]=='('||s[i]==')'||s[i]=='*'||s[i]=='/'||s[i]=='-'||s[i]=='+')
​​{
​​​continue;
​​}
​​return false;
​}
​for(int i=0;i<s.length();i++)    ​//如果括号不成对或者不合法，返回false
​{
​​if(s[i]=='(')
    ​​temp.push(s[i]);
​​else if(s[i]==')')
    ​​{
    ​​​if(temp.top()=='(')
        ​​​temp.pop();
    ​​}
​}
​if(temp.empty())
    ​​return true;
​return false;
}
int prelevel(char s)
{
​if(s=='(' )return 0;
​if(s=='+'||s=='-') return 2;
​if(s=='*'||s=='/') return 4;
​if(s==')') return 6;
}
double cal();
bool isdata(char a)​​//如果是数字，返回true
{
​if(a<='9'&&a>='0') return true;
​return false;
}
double getpost(string s)
{
​if(!judge(s))​​​//判断计算式是否合法，不合法就退出
​{
​​cout<<"wrong input!"<<endl;
​​return 0;
​}
​stack <char> sigh;
​sigh.push('0');
​double num=0;
​int flag=1;
​for(int i=0;i<s.length();i++)
​{
​​if(s[i]==' ')
​​{
​​​continue;
​​}
​​if(s[i]=='-'&&isdata(s[i+1]))​​​//如果是'-'，判断是负号还是减号
​​{
​​​flag=-1;
​​​continue;
​​}
​​if(isdata(s[i])) {
​​​if(i==s.length()-1)​​​​
​​​{
​​​​num=flag*(10*num+(int)s[i]-48);
​​​​outope.push(num);
​​​​num=0;
​​​​flag=1;
​​​}
​​​else if(!isdata(s[i+1]))
​​​{
​​​​num=flag*(10*num+(int)s[i]-48);
​​​​outope.push(num);
​​​​num=0;
​​​​flag=1;
​​​}
​​​else
​​​{
​​​​num=10*num+(int)s[i]-48；
​​​}
​​}
​​else{
​​​if(sigh.top()=='0')
​​​{
​​​​sigh.push(s[i]);
​​​}
​​​else if(s[i]=='(')
    ​​​{
    ​​​​sigh.push(s[i]);
    ​​​}
​​​else if(s[i]==')')
    ​​​{
    ​​​​while(sigh.top()!='(')
        ​​​​{
        ​​​​​mystack.push(sigh.top());
        ​​​​
        ​​​​​outope.push(cal());
        ​​​​​
        ​​​​​sigh.pop();
        ​​​​}
    ​​​​sigh.pop();
    ​​​}
​​​else if(prelevel(s[i])>prelevel(sigh.top()))
    ​​​{
    ​​​​sigh.push(s[i]);
    ​​​}
​​​else
    ​​​{
    ​​​​while(sigh.top()!='('&&sigh.top()!='0'&&prelevel(sigh.top())>=prelevel(s[i]))
        ​​​​{
        ​​​​​mystack.push(sigh.top());
        ​​​​​outope.push(cal());
        ​​​​​sigh.pop();
        ​​​​}
    ​​​​sigh.push(s[i]);
    ​​​}​​​
        ​​}
​}
​while(sigh.top()!='0')
    ​{
    ​​mystack.push(sigh.top());
    ​​outope.push(cal());
    ​
    ​​sigh.pop();
    ​}
​cout<<s<<"="<<" ";
​cout<<outope.top()<<endl;
}
double cal(  )
{
​double a=outope.top();
​outope.pop();
​double b=outope.top();
​outope.pop();
​char s=mystack.top();
​mystack.pop();
​if(s=='+')
    ​{
    ​​cout<<a<<"+"<<b<<"="<<a+b<<endl;
    ​​return a+b;
    ​}
​else if(s=='-')
    ​{
    ​​cout<<b<<"-"<<a<<"="<<b-a<<endl;
    ​​return b-a;
    ​}
​else if(s=='/')
    ​{
    ​​cout<<b<<"/"<<a<<"="<<b/a<<endl;
    ​​return b/a;
    ​}
​else if(s=='*')
    ​{
    ​​cout<<a<<"*"<<b<<"="<<a*b<<endl;
    ​​return a*b;
    ​}
​
}
int main()
{
​
​string s;
​getline(cin,s);
​getpost(s);
}')}')}')')}')')}}}')')}')')}')')}}
