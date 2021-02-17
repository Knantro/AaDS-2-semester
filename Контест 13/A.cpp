#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h
#include <algorithm>
#include <climits>

using namespace std;

// write all values
void ReadWriter::writeValues(std::vector<std::vector<int>> &result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");
    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < result.size(); ++j)
        {
            if (i != j)
            {
                fout << i << " " << j << " ";
                if (result[i][j] != 1000000)
                {
                    fout << result[i][j] << '\n';
                } else
                {
                    fout << -1 << '\n';
                }
            }
        }
    }
    //Можно сюда передать матрицу и здесь вычислять какие значения выводить в файл.
    //Можно заранее сформировать ответ и здесь его просто выводить построчно. Как вам удобнее.
    //Работать с файлом вот так:
    //fout<< value1 << value2 << value3;
}

void shortestPaths(vector<vector<int>> &matrix, vector<vector<int>> &w)
{
    int i, j, k;
    int N = matrix.size();
    int INF = 1000000;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i != j)
            {
                for (k = 0; k < N; k++)
                {
                    if (matrix[i][k] != INF && w[k][j] != INF)
                    {
                        matrix[i][j] = min(matrix[i][j], matrix[i][k] + w[k][j]);
                    }
                }
            }
        }
    }
}

void solve(int N, int M, vector<Edge> &edges, vector<vector<int>> &result)
{
    const int INF = 1000000;
    vector<vector<int>> W = vector<vector<int>>(N);
    result = vector<vector<int>>(N);
    for (int l = 0; l < N; ++l)
    {
        result[l] = vector<int>(N, INF);
        W[l] = vector<int>(N, INF);
    }
    for (int m = 0; m < M; ++m)
    {
        result[edges[m].A][edges[m].B] = edges[m].W;
        W[edges[m].A][edges[m].B] = edges[m].W;
    }
    int m = 1;
    while (m < N)
    {
        m *= 2;
        shortestPaths(result, result);
    }
}

int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    vector<vector<int>> result(N);

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    rw.writeValues(result);

    return 0;
}