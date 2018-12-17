#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
typedef struct
{
    char c;
    int n;
    int len;
    string bit;
} chart;
chart chartable[1000];
struct huff
{
    int weight;
    vector<int> node;
    bool operator<(const huff &a) const
    {
        return weight > a.weight; //大顶堆
    }
};
struct treenode
{
    int ischar;
    char thechar;
    treenode *leftchild;
    treenode *rightchild;
    int isleft;
    int isright;
    treenode()
    {
        isleft = 0;
        isright = 0;
        ischar = 0;
        thechar = 0;
    }
};
bool mylessc(const chart &t1, const chart &t2)
{
    return t1.n < t2.n;
}
unsigned int bin2dec(int *a)
{
    unsigned int n = 0;
    unsigned int j;

    for (int i = 0; i < 32; i++)
    {
        j = 0;
        j = j | a[i];
        j = j << i;
        n = n | j;
    }
    return n;
}
priority_queue<huff> huffman;
void compress()
{

    cout << "Please input source file name(size less than 4GB):";
    string sourcename;
    cin >> sourcename;
    cout << "Please input code file name:";
    string codename;
    cin >> codename;
    cout << "processing..." << endl;
    ifstream infile;
    ofstream outfile;
    infile.open(sourcename);
    char x;
    int mycount = -1;
    int charcount = 0;
    infile >> noskipws;
    while (infile >> x)
    {
        charcount++;
        int flag = 0;
        for (int i = 0; i <= mycount; i++)
        {
            if (x == chartable[i].c)
            {
                chartable[i].n++;
                flag = 1;
            }
        }
        if (flag == 0)
        {
            chartable[mycount + 1].c = x;
            chartable[mycount + 1].n = 1;
            chartable[mycount + 1].bit = "";
            chartable[mycount + 1].len = 0;
            mycount++;
        }
    }
    infile.close();
    sort(chartable, chartable + mycount + 1, mylessc);
    for (int i = 0; i <= mycount; i++)
    {
        huff temp;
        temp.weight = chartable[i].n;
        temp.node.push_back(i);
        huffman.push(temp);
    }
    while (huffman.size() > 1)
    {
        huff huf0 = huffman.top();
        huffman.pop();
        huff huf1 = huffman.top();
        for (int i = 0; i < huf0.node.size(); i++)
        {
            chartable[huf0.node[i]].bit = "0" + chartable[huf0.node[i]].bit;
            chartable[huf0.node[i]].len++;
        }
        for (int i = 0; i < huf1.node.size(); i++)
        {
            chartable[huf1.node[i]].bit = "1" + chartable[huf1.node[i]].bit;
            chartable[huf1.node[i]].len++;
        }
        for (int i = 0; i < huf0.node.size(); i++)
        {
            huf1.node.push_back(huf0.node[i]);
        }
        huf1.weight += huf0.weight;
        huffman.pop();
        huffman.push(huf1);
    }
    infile.open(sourcename);
    infile >> noskipws;
    outfile.open(codename, ios::binary);
    char tempchar;
    int a[33];
    int poa = 0;
    unsigned int multi = mycount + 1;
    outfile.write((char *)&multi, sizeof(int));
    outfile.write((char *)&charcount, sizeof(int));
    for (int i = 0; i <= mycount; i++)
    {
        unsigned int character = int(chartable[i].c);
        outfile.write((char *)&character, sizeof(int));
        unsigned int lenofa = chartable[i].len;
        outfile.write((char *)&lenofa, sizeof(int));
        for (int j = 0; j < chartable[i].bit.size(); j++)
        {
            if (chartable[i].bit[j] == '1')
            {
                a[poa] = 1;
                poa++;
            }
            else
            {
                a[poa] = 0;
                poa++;
            }
            if (poa == 32)
            {
                unsigned int no = bin2dec(a);
                outfile.write((char *)&no, sizeof(int));
                poa = 0;
            }
        }
        if (poa > 0)
        {
            unsigned int no = bin2dec(a);
            outfile.write((char *)&no, sizeof(int));
            poa = 0;
        }
    }
    while (infile >> tempchar)
    {
        int i;
        for (i = mycount; i >= 0; i--)
        {
            if (chartable[i].c == tempchar)
                break;
        }
        for (int j = 0; j < chartable[i].bit.size(); j++)
        {
            if (chartable[i].bit[j] == '1')
            {
                a[poa] = 1;
                poa++;
            }
            else
            {
                a[poa] = 0;
                poa++;
            }
            if (poa == 32)
            {
                unsigned int no = bin2dec(a);
                outfile.write((char *)&no, sizeof(int));
                poa = 0;
            }
        }
    }
    if (poa > 0)
    {
        unsigned int no = bin2dec(a);
        outfile.write((char *)&no, sizeof(int));
        poa = 0;
    }
    infile.close();
    outfile.close();
    cout << "processed!" << endl;
}
void decompress()
{
    cout << "please input code file name:";
    string codename;
    cin >> codename;
    cout << "please input target file name:";
    string targetname;
    cin >> targetname;
    cout << "processing..." << endl;
    treenode *ht = new treenode();
    ifstream infile;
    ofstream outfile;
    infile.open(codename, ios::binary);
    outfile.open(targetname);
    unsigned int dicnumber;
    infile.read((char *)&dicnumber, sizeof(int));
    unsigned int charnumber;
    infile.read((char *)&charnumber, sizeof(int));
    for (int i = 1; i <= dicnumber; i++)
    {
        unsigned int no;
        infile.read((char *)&no, sizeof(int));
        char tch = char(no);
        int langnumber;
        infile.read((char *)&no, sizeof(int));
        langnumber = no;
        treenode *hm = ht;
        while (langnumber > 0)
        {
            infile.read((char *)&no, sizeof(int));
            while (langnumber > 0)
            {
                int st = no % 2;
                langnumber--;
                no = no >> 1;
                if (st == 1)
                {
                    if (hm->isright == 1)
                        hm = hm->rightchild;
                    else
                    {
                        hm->isright = 1;
                        hm->rightchild = new treenode();
                        hm = hm->rightchild;
                    }
                }
                else
                {
                    if (hm->isleft == 0)
                    {
                        hm->isleft = 1;
                        hm->leftchild = new treenode();
                    }
                    hm = hm->leftchild;
                }
            }
        }
        hm->ischar = 1;
        hm->thechar = tch;
    }
    treenode *hr = ht;
    unsigned int nt;
    while (infile.read((char *)&nt, sizeof(int)))
    {
        for (int i = 1; i <= 32; i++)
        {
            int temp = nt % 2;
            nt = nt >> 1;
            if (temp == 1)
                hr = hr->rightchild;
            else
                hr = hr->leftchild;
            if (hr->thechar != 0)
            {
                outfile << hr->thechar;
                hr = ht;
                charnumber--;
                if (charnumber == 0)
                    break;
            }
        }
    }
    infile.close();
    outfile.close();
    cout << "processed!" << endl;
}
int main()
{
    while (1)
    {
        cout << "1.Huffman compress." << endl
             << "2.Huffman decompress." << endl
             << "3.Exit." << endl
             << "Please select:";
        int n;
        cin >> n;
        if (n == 1)
            compress();
        else if (n == 2)
            decompress();
        else
            break;
        cout << endl;
    }
    return 0;
}
