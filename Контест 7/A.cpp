#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Node
{
    int offset;
    int length;
    char next;
};

Node *makeNode(int offset, int length, char next)
{
    Node *node = new Node();
    node->offset = offset;
    node->length = length;
    node->next = next;
    return node;
}

vector<Node *> res;
string buffer;
const int bufferPreviewLength = 1024;
const int bufferBackstoryLength = 3072;
int position = 0;
int border = 0;
int offset = 0;
int length = 0;

int *brArray(string T)
{
    int i, n = T.length(), t;
    int *br = new int[n];
    br[0] = 0;
    for (i = 1; i < n; i++)
    {
        t = br[i - 1];
        while ((t > 0) && (T[i] != T[t]))
        {
            t = br[t - 1];
        }
        if (T[i] == T[t])
        {
            br[i] = t + 1;
        } else
        {
            br[i] = 0;
        }
    }
    return br;
}

void getSubstrings(const string &source, const string &substring)
{
    int pozition = 0;
    length = 0;
    offset = 0;
    int *br = brArray(substring);
    for (int i = 0; i < source.size(); i++)
    {
        while (pozition == substring.length() || (pozition > 0 && substring[pozition] != source[i]))
        {
            pozition = br[pozition - 1];
            if (substring.length() - pozition > source.length() - i)
            {
                break;
            }
        }
        if (source[i] == substring[pozition])
        {
            pozition++;
        }

        if (pozition > length && i - pozition + 1 < position - border)
        {
            length = pozition;
            offset = position - border - i + pozition - 1;
        }
    }
    delete br;
}

void encode()
{
    while (buffer.size() > position)
    {
        getSubstrings(buffer.substr(border, bufferPreviewLength + position - border),
                      buffer.substr(position, bufferPreviewLength));
        position += length + 1;
        if (position > bufferBackstoryLength)
        {
            border = position - bufferBackstoryLength;
        }
        res.emplace_back(makeNode(offset, length, buffer[position - 1]));
    }
}

int main()
{
    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        getline(fin, buffer);
        fin.close();
        encode();
        fstream fout;
        fout.open("output.txt", ios::out);
        fout << res.size() << endl;
        for (auto &re : res)
        {
            fout << re->offset << " " << re->length << " " << re->next << " ";
        }
        fout.close();
    }
    return 0;
}