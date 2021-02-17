#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 31;

int countMinSum(int seconds, vector<int> &values)
{
    long sum = 0;
    auto *money = new long long int[N];

    for (unsigned int i = 0; i < N; i++)
    {
        money[i] = values[i];
    }
    for (unsigned int i = 1; i < N; i++)
    {
        if (2 * money[i - 1] > money[i])
        {
            money[i] = 2 * money[i - 1];
        }
    }
    for (int i = N - 1; i >= 0; i--)
    {
        if (seconds >= money[i])
        {
            sum += pow(2, i);
            seconds -= money[i];
        }
    }
    if (seconds > 0)
    {
        ++sum;
    }
    delete[] money;
    return sum;
}

int main()
{
    vector<int> values;
    int value = 0, seconds = 0;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> seconds;
        for (int i = 0; i < N; i++)
        {
            fin >> value;
            values.push_back(value);
        }
        fin.close();
    }

    int res = countMinSum(seconds, values);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}
