#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string getLCS(string x, string y)
{
    string res;
    int r = 1;
    int **matrix = new int *[x.length() + 1];
    for (int i = 0; i < x.length() + 1; ++i)
    {
        matrix[i] = new int[y.length() + 1];
    }
    for (int i = 0; i <= x.length(); i++)
    {
        for (int j = 0; j <= y.length(); j++)
        {
            if (i == 0 || j == 0)
            {
                matrix[i][j] = 0;
                continue;
            }
            if (x[i - 1] == y[j - 1])
            {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
                if (r <= i){
                    res += x[i - 1];
                    r = i + 1;
                }
            } else
            {
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);
            }
        }
    }
    for (int i = 0; i < x.length() + 1; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return res;
}

int main()
{
    string x;
    string y;
    string res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, x);
        getline(fin, y);
        fin.close();
    }

    res = getLCS(x, y);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res;
    fout.close();

    return 0;
}