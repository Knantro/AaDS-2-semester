#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int Wagner_Fischer(string &s, string &t, int D)
{
    int s_len = s.length();
    int t_len = t.length();

    if (abs(s_len - t_len) > D)
    {
        return D + 1;
    }

    int matrix[s_len + 1][t_len + 1];

    for (int i = 0; i <= s_len; i += 1)
    {
        for (int j = 0; j <= t_len; j += 1)
        {
            if (i == 0)
            {
                matrix[i][j] = j;
            }
            else if (j == 0)
            {
                matrix[i][j] = i;
            }
            else if (s[i - 1] == t[j - 1])
            {
                matrix[i][j] = matrix[i - 1][j - 1];
            }
            else
            {
                matrix[i][j] = 1 + min(min(matrix[i - 1][j], matrix[i][j - 1]), matrix[i - 1][j - 1]);
            }
            if (matrix[i][j] > 11)
            {
                return D + 1;
            }
        }
    }
    int res = matrix[s_len][t_len];
    return res;
}

int *getAllEdits(string *args1, string *args2, int N, int D, int K)
{
    int *res = new int[K];
    for (int k = 0; k < K; ++k)
    {
        res[k] = 0;
    }
    for (int i = 0; i < K; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (Wagner_Fischer(args2[i], args1[j], D) <= D)
            {
                res[i]++;
            }
        }
    }
    return res;
}

int main()
{
    int N;
    int K;
    int D;
    string *args1; // Массив строк, к которым подбираются строки из args2
    string *args2; // Массив строк, которые подбираются к строкам из args1
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string line;
        getline(fin, line);
        N = stoi(line);
        args1 = new string[N];
        for (int i = 0; i < N; i++)
        {
            string s;
            getline(fin, s);
            args1[i] = s;
        }
        getline(fin, line);
        D = stoi(line);
        getline(fin, line);
        K = stoi(line);
        args2 = new string[K];
        for (int i = 0; i < K; i++)
        {
            string s;
            getline(fin, s);
            args2[i] = s;
        }
        int *res = getAllEdits(args1, args2, N, D, K); // Получить ответ
        for (int j = 0; j < K; ++j)
        {
            fout << res[j] << "\n";
        }
        fout.close();
        fin.close();
    }
    return 0;
}
