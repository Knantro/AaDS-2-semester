#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <string>

using namespace std;

//Необходимо реализовать метод
//об алгоритме можно прочитать в источниках указанных в программе курса, или на странице курса в ЛМС или в презентациях к семинару.
int Wagner_Fischer(string &s, string &t)
{
    int s_len = s.length();
    int t_len = t.length();

    int matrix[s_len + 1][t_len + 1];

    for (int i = 0; i <= s_len; i += 1)
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
        }
    int res = matrix[s_len][t_len];
    return res;
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
        int n = atoi(N.c_str());
        for (int i = 0; i < n; i++)
        {
            string s;
            string t;
            getline(fin, s);
            getline(fin, t);
            fout << Wagner_Fischer(s, t) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        fin.close();
    }
    return 0;
}