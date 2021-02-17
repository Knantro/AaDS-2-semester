#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
    int offset;
    int length;
    char ch;
};

Node *makeNode(int offset, int length, char ch)
{
    Node *node = new Node();
    node->offset = offset;
    node->length = length;
    node->ch = ch;
    return node;
}

vector<Node *> nodes;
string res;
const int bufferPreviewLength = 1024;
const int bufferBackstoryLength = 3072;
int count;

void decode()
{
    for (int i = 0; i < nodes.size();i++)
    {
        if (nodes[i]->offset == 0)
        {
            res +=  nodes[i]->ch;
        } else
        {
            for (int j = 0; j < nodes[i]->length; ++j)
            {
                res += res[res.length() - nodes[i]->offset];
            }
            res += nodes[i]->ch;
        }
    }
}

int main()
{
    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        string line;
        fin >> count;
        int offset;
        int index;
        char ch;
        for (int i = 0; i < count; ++i)
        {
            fin >> offset;
            fin >> index;
            fin >> ch;
            nodes.emplace_back(makeNode(offset, index, ch));
        }
        fin.close();
        decode();
        fstream fout;
        fout.open("output.txt", ios::out);
        fout << res;
        fout.close();
    }
    return 0;
}