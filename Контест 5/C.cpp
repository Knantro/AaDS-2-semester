#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//Необходимо реализовать метод
//об алгоритме можно прочитать в источниках указанных в программе курса, или на странице курса в ЛМС или в презентациях к семинару.
int Wagner_Fischer_for_Damerau_Levenshtein(string &s, string &t)
{
    int s_len = s.length();
    int t_len = t.length();
    int d[s_len + 1][t_len + 1];

    int i;
    int j;
    int cost;

    for (i = 0; i <= s_len; i++)
    {
        d[i][0] = i;
    }
    for (j = 0; j <= t_len; j++)
    {
        d[0][j] = j;
    }
    for (i = 1; i <= s_len; i++)
    {
        for (j = 1; j <= t_len; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                cost = 0;
            } else
            {
                cost = 1;
            }
            d[i][j] = min(d[i - 1][j] + 1, min(d[i][j - 1] + 1, d[i - 1][j - 1] + cost));
            if ((i > 1) && (j > 1) && (s[i - 1] == t[j - 2]) && s[i - 2] == t[j - 1])
            {
                d[i][j] = min(d[i][j], d[i - 2][j - 2] + cost);
            }
        }
    }
    return d[s_len][t_len];
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main(int argc, const char *argv[])
{
    int n;
    fstream fin;
    fstream fout;
    fin.open("input.txt", ios::in);
    fout.open("output.txt", ios::out);
    if (fin.is_open())
    {
        string N;
        getline(fin, N);
        n = atoi(N.c_str());
        for (int i = 0; i < n; i++)
        {
            string s;
            string t;
            getline(fin, s);
            getline(fin, t);
            fout << Wagner_Fischer_for_Damerau_Levenshtein(s, t) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}