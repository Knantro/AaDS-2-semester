#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

static void makeTransposition(vector<unsigned long long int> &args, unsigned long long int N, unsigned long long int K)
{
    unsigned long long int M = args.size();
    unsigned long long int index = 0;
    int counter = 0;
    for (unsigned long long int i = 0; i < K; ++i)
    {
        if ((counter + index + 1) >= M)
        {
            index = M - 2;
            while (args[index] == 0)
            {
                index--;
            }
            args[index + 1] = 1 + args[M - 1];
            args[index]--;
            if (index + 1 != M - 1)
            {
                args[M - 1] = 0;
                index++;
                continue;
            }
            index++;
            if (counter + index >= M - 1)
            {
                counter = 0;
            }
            continue;
        }
        if (index == M - 1)
        {
            index = M - 2;
            while (args[index] == 0)
            {
                index--;
            }
            args[index]--;
            args[index + 1] = 1 + args[M - 1];
            if (index + 1 != M - 1)
            {
                args[M - 1] = 0;
            }
            continue;
        }
        if (counter + index >= M - 1)
        {
            counter = 0;
        }
        args[counter + index]--;
        args[counter + index + 1]++;
        counter++;
    }
}

static string get(unsigned long long int N, unsigned long long int K, unsigned long long int M)
{
    stringstream res;
    vector<unsigned long long int> args(M, 0);
    args[0] += N;
    makeTransposition(args, N, K - 1);
    for (unsigned long long int i = 0; i < M; ++i)
    {
        if (i != M - 1)
        {
            res << args[i];
            res << " ";
        } else
        {
            res << args[i];
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