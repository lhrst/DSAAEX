#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<fstream>
#include<vector>
using namespace std;
typedef struct
{
    char c;
    int n;
    string bit = "";
} chart;
chart chartable[1000];
typedef struct
{
    int weight;
    vector<int> node;
} huff;
bool myless(const huff &t1, const huff &t2)
{
    return t1.weight < t2.weight;
}
bool mylessc(const chart &t1, const chart &t2)
{
    return t1.n < t2.n;
}
unsigned int bin2dec(int *a)
{
    unsigned int n = 0;
    unsigned int j = 1;
    for(int i = 0; i < 32; i++)
        {
            n += a[i]*j;
            j = j* 2;
        }
    return n;
}
vector<huff> huffman;
void compress()
{

    cout<<"Please input source file name(size less than 4GB):";
    string sourcename;
    cin>>sourcename;
    cout<<"Please input code file name:";
    string codename;
    cin>>codename;
    cout<<"Please input result file name:";
    string resultname;
    cin>>resultname;
    ifstream infile;
    infile.open(sourcename);
    char x;
    int mycount = -1;
    infile>>noskipws;
    while(infile>>x)
        {
            int flag = 0;
            for(int i = 0; i <= mycount; i++)
                {
                    if(x == chartable[i].c)
                        {
                            chartable[i].n++;
                            flag = 1;
                        }
                }
            if(flag == 0)
                {
                    chartable[mycount+1].c = x;
                    chartable[mycount+1].n = 1;
                    chartable[mycount+1].bit = "";
                    mycount++;
                }
        }
    infile.close();
    cout<<"processing..."<<endl;
    sort(chartable, chartable+mycount+1, mylessc);
//    for(int i = 0; i <= mycount; i++)
//        cout<<chartable[i].c<<" "<<chartable[i].n<<endl;
    for(int i = 0; i <= mycount; i++)
        {
            huff temp;
            temp.weight = chartable[i].n;
            temp.node.push_back(i);
            huffman.push_back(temp);
        }
    while(huffman.size() > 1)
        {
            sort(huffman.begin(), huffman.end(), myless);


            for(int i = 0; i < huffman[0].node.size(); i++)

                chartable[huffman[0].node[i]].bit = "0" + chartable[huffman[0].node[i]].bit;
            for(int i = 0; i < huffman[1].node.size(); i++)
                chartable[huffman[1].node[i]].bit = "1" + chartable[huffman[1].node[i]].bit;
            for(int i = 0; i < huffman[0].node.size(); i++)
                {
                    huffman[1].node.push_back(huffman[0].node[i]);
                }
            huffman[1].weight += huffman[0].weight;
            huffman.erase(huffman.begin());
        }
//    for(int i = 0; i <= mycount; i++)
//        cout<<chartable[i].c<<" "<<chartable[i].n<<" "<<chartable[i].bit<<endl;
    ofstream outfile;
    outfile.open(codename);
    for(int i = 0; i <= mycount; i++)
        outfile<<chartable[i].c<<" "<<chartable[i].bit<<endl;
    outfile.close();
    infile.open(sourcename);
    infile>>noskipws;
    outfile.open(resultname);
    char tempchar;
    while(infile>>tempchar)
        {
            int i;
            for(i = 0; i <= mycount; i++)
                {
                    if(chartable[i].c == tempchar)
                        break;
                }
            outfile<<chartable[i].bit;
        }
    infile.close();
    outfile.close();
    cout<<"processed!"<<endl;
}
void decompress()
{
    cout<<"Please input code file name:";
    string codename;
    cin>>codename;
    cout<<"Please input target file name:";
    string targetname;
    cin>>targetname;
    cout<<"Please input result file name:";
    string resultname;
    cin>>resultname;
    char huffmantree[8192];
    for(int i = 0; i <= 8192; i++)
        huffmantree[i] = 0;
    ifstream infile;
    ofstream outfile;
    cout<<"processing..."<<endl;
    infile.open(codename);
    infile>>noskipws;
    char x;
    string bit;
    char temp;
    while(infile>>x)
        {
            infile>>temp;
            infile>>bit;
            int s = 0;
            for(int i = 0; i < bit.size(); i++)
                {
                    if(bit[i] == '0')
                        s = s*2+1;
                    else
                        s = s*2+2;
                }
            huffmantree[s] = x;
            infile>>temp;
        }
    infile.close();
    infile.open(targetname);
    outfile.open(resultname);
    int ss = 0;
    char xv;
    while(infile>>xv)
        {
            //cout<<xv;
            if(xv == '0')
                ss = ss*2+1;
            else
                ss = ss*2+2;
            if(huffmantree[ss] != 0)
                {
                    outfile<<huffmantree[ss];
                    //cout<<" "<<huffmantree[ss]<<endl;
                    ss = 0;
                }
        }
    infile.close();
    outfile.close();
    cout<<"processed!"<<endl;
}
int main()
{
    while(1)
        {
            cout<<"1.Huffman compress."<<endl<<"2.Huffman decompress."<<endl<<"3.Exit."<<endl<<"Please select:";
            int n;
            cin>>n;
            if(n == 1)
                compress();
            else if(n == 2)
                decompress();
            else
                break;
            cout<<endl;
        }
    return 0;
}
