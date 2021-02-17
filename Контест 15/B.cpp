#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

static void makeTransposition(vector<unsigned long long int> &args, unsigned long long int N, unsigned long long int K)
{
    vector<unsigned long long int> v;
    unsigned long long int a;
    int base = N;
    while (K > 0)
    {
        a = K % base;
        K /= base;
        v.emplace_back(a);
        base--;
    }
    for (unsigned long long int i = 0; i < v.size(); ++i)
    {
        args[args.size() - 1 - i] = v[i];
    }
}

static string get(unsigned long long int N, unsigned long long int K)
{
    stringstream res;
    vector<unsigned long long int> args(N, 0);
    makeTransposition(args, N, K - 1);
    for (unsigned long long int i = 0; i < N; ++i)
    {
        if (i != N - 1)
        {
            res << args[i] + 1;
            res << " ";
        } else
        {
            res << args[i] + 1;
        }
    }
    return res.str();
}

int main()
{
    unsigned long long int N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = stoll(str);
        getline(fin, str);
        K = stoll(str);
        fout << get(N, K) << endl;

        fout.close();
        fin.close();
    }
    return 0;
}