#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

int min(int left, int right)
{
    return left > right ? right : left;
}

vector<int> findPolym(string &s)
{
    int n = s.length();
    vector<int> res(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; ++i)
    {
        int k = i > r ? 1 : min(res[l + r - i], r - i + 1);
        while (i + k < n && i - k >= 0 && s[i + k] == s[i - k])
        {
            ++k;
        }
        res[i] = k;
        if (i + k - 1 > r)
        {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    return res;
}

int main()
{
    string t;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        fin.close();
    }

    res = findPolym(t);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i * 2 - 1 << " ";
    fout.close();

    return 0;
}
