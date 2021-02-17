#include "BigIntegerAlgorithms.hh"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

static bool NextPermutation(int N, vector<int> &a)
{
    for (int i = N - 2; i >= 0; i--)
    {
        if (a[i] < a[i + 1])
        {
            int min_val = a[i + 1], min_id = i + 1;
            for (int j = i + 2; j < N; j++)
                if (a[j] > a[i] && a[j] < min_val)
                {
                    min_val = a[j];
                    min_id = j;
                }
            swap(a[i], a[min_id]);
            sort(a.begin() + i + 1, a.end());
            return true;
        }
    }
    return false;
}

//Необходимо реализовать данный метод
//Вся информация о задаче доступна в тексте задачи и в слайдах презентации к семинару(в ЛМС)
static string get_day(int N, int k)
{
    string res;
    vector<int> a(N);
    a[0] = 1;
    for (int i = 1; i < N; ++i)
    {
        a[i] = a[i - 1] + 1;
    }
    for (int j = 1; j < k; ++j)
    {
        NextPermutation(N, a);
    }
    for (int l = 0; l < N; ++l)
    {
        if (l != N - 1)
        {
            res += to_string(a[l]) + " ";
        } else
        {
            res += to_string(a[l]);
        }
    }
    return res;
}

int main(int argc, const char *argv[])
{

    int N, K;
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
        fout << get_day(N, K) << endl;

        fout.close();
        fin.close();
    }

    return 0;
}
