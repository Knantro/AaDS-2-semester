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
    while (K > 0)
    {
        a = K % N;
        K /= N;
        v.emplace_back(a);
    }
    for (unsigned long long int i = 0; i < v.size(); ++i)
    {
        args[args.size() - 1 - i] = v[i];
    }
}

static string get(unsigned long long int N, unsigned long long int K, unsigned long long int M)
{
    stringstream res;
    vector<unsigned long long int> args(M, 0);
    makeTransposition(args, N, K - 1);
    for (unsigned long long int i = 0; i < M; ++i)
    {
        if (i != M - 1)
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
    unsigned long long int M, N, K;
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
        M = stoll(str);
        getline(fin, str);
        K = stoll(str);
        fout << get(N, K, M) << endl;

        fout.close();
        fin.close();
    }
    return 0;
}