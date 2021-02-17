#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static void makeTransposition(vector<int> &args, int pivot, int N)
{
    args[pivot]++;
    while (find(args.begin(), args.end(), args[pivot]) != args.begin() + pivot || args[pivot] > N || distance(args.begin(), max_element(args.begin(), args.end())) != pivot)
    {
        if (args[pivot] > N)
        {
            args[pivot] = 0;
            makeTransposition(args, pivot - 1, N);
        }
        args[pivot]++;
    }
}

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get(int N, int K, int M)
{
    string res;
    vector<int> args(M);
    args[0] = 1;
    for (int k = 1; k < M; ++k)
    {
        args[k] = args[k - 1] + 1;
    }
    int pivot = M - 1;
    for (int j = 1; j < K; ++j)
    {
        makeTransposition(args, pivot, N);
    }
    for (int i = 0; i < M; ++i)
    {
        if (i != M - 1)
        {
            res += to_string(args[i]) + " ";
        } else
        {
            res += to_string(args[i]);
        }
    }
    return res;
}

int main(int argc, const char *argv[])
{
    int M, N, K;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        N = atoi(str.c_str());
        getline(fin, str);
        K = atoi(str.c_str());
        getline(fin, str);
        M = atoi(str.c_str());
        fout << get(N, K, M) << endl;

        fout.close();
        fin.close();
    }
    return 0;
}