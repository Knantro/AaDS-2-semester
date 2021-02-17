#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

class Huffman
{
public:
    struct Node
    {
        int freq;
        Node *left, *right;
    };

    int binarySearch(Node **arr, int l, int r, int x)
    {
        if (r >= l)
        {
            int mid = l + (r - l) / 2;

            if (arr[mid]->freq < x && arr[mid - 1]->freq >= x)
                return mid;

            if (arr[mid]->freq >= x)
                return binarySearch(arr, mid + 1, r, x);

            return binarySearch(arr, l, mid - 1, x);
        }
        return -1;
    }


    Node *getNode(int freq, Node *left, Node *right)
    {
        Node *node = new Node();

        node->freq = freq;
        node->left = left;
        node->right = right;

        return node;
    }

    void encode(Node *root, const string &code, vector<pair<Node *, string>> &huffmanCode)
    {
        if (root == nullptr)
        {
            return;
        }

        if (!root->left && !root->right)
        {
            for (auto &i : huffmanCode)
            {
                if (i.first == root)
                {
                    i.second = code;
                    break;
                }
            }
        }

        encode(root->left, code + "0", huffmanCode);
        encode(root->right, code + "1", huffmanCode);
    }

    vector<int> probabilityList;
    vector<pair<Node *, string>> huffmanCode;

    Huffman() = default;

    void build()
    {
        vector<Node *> v;
        for (auto freq: probabilityList)
        {
            v.emplace_back(getNode(freq, nullptr, nullptr));
            huffmanCode.emplace_back(make_pair(v.back(), ""));
        }

        while (v.size() != 1)
        {
            Node *left = v.back();
            v.pop_back();
            Node *right = v.back();
            v.pop_back();
            int sum = left->freq + right->freq;
            if (v[0]->freq < sum)
            {
                v.insert(v.begin() + 0, getNode(sum, left, right));
            } else if (v[v.size() - 1]->freq >= sum)
            {
                v.insert(v.begin() + v.size(), getNode(sum, left, right));
            } else
            {
                v.insert(v.begin() + binarySearch(v.data(), 0, v.size(), sum), getNode(sum, left, right));
            }
        }

        Node *root = v.back();

        encode(root, "", huffmanCode);
    }

    void addChance(int chance)
    {
        probabilityList.emplace_back(chance);
    }

    string get(int i)
    {
        return huffmanCode[i].second;
    }
};

int main()
{
    int n;
    Huffman *huff = new Huffman();
    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            fin >> x;
            huff->addChance(x);
        }

        fin.close();

        huff->build();
        fstream fout;
        fout.open("output.txt", ios::out);
        for (int i = 0; i < n; i++)
        {
            fout << huff->get(i) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        delete huff;

    }
    return 0;
}