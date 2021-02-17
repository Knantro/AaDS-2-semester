#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Основная задача - реализовать данный метод
int countMaxCross(string &riverMap)
{
    int left = 0;
    int right = 1;
    for (char i : riverMap)
    {
        if (i == 'L')
        {
            left++;
        }
        if (i == 'R')
        {
            right++;
        }
        if (i == 'B')
        {
            left++;
            right++;
        }
        if (left + 1 < right)
        {
            right--;
        }
        if (right < left - 1)
        {
            left--;
        }
    }
    return right;
}

int main()
{
    string riverMap;
    int res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, riverMap);
        fin.close();
    }

    res = countMaxCross(riverMap);
    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();
    return 0;
}