#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int sum = 0;

void findAns(int N, int W, int **matrix, vector<int> m, vector<int> c)
{
    if (matrix[N][W] == 0)
    {
        return;
    }
    if (matrix[N - 1][W] == matrix[N][W])
    {
        findAns(N - 1, W, matrix, m, c);
    } else
    {
        findAns(N - 1, W - m[N - 1], matrix, m, c);
        sum += c[N - 1];
    }
}

void solve(int N, int W, vector<int> m, vector<int> c)
{
    int **matrix = new int *[N + 1];
    for (int i = 0; i < N + 1; ++i)
    {
        matrix[i] = new int[W + 1];
    }
    for (int k = 0; k <= N; ++k)
    {
        for (int s = 0; s <= W; ++s)
        {
            if (k == 0 || s == 0)
            {
                matrix[k][s] = 0;
                continue;
            }
            if (s >= m[k - 1])
            {
                matrix[k][s] = max(matrix[k - 1][s], matrix[k - 1][s - m[k - 1]] + c[k - 1]);
            } else
            {
                matrix[k][s] = matrix[k - 1][s];
            }
        }
    }
    findAns(N, W, matrix, m, c);
    for (int i = 0; i < N + 1; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main()
{
    int N;
    int M;
    vector<int> m;
    vector<int> c;
    ifstream fin("input.txt", ios::in);
    fin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        int k;
        fin >> k;
        m.emplace_back(k);
    }
    for (int i = 0; i < N; ++i)
    {
        int k;
        fin >> k;
        c.emplace_back(k);
    }
    fin.close();
    solve(N, M, m, c);
    ofstream fout("output.txt", ios::out);
    fout << sum;
    return 0;
}