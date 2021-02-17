#include "ReadWriter.h"
//string, iostream included in "ReadWriter.h"

using namespace std;

long long **matrix;

long long lazySolve(int N, int M, int rows, int columns)
{
    if (N < 0 || M < 0 || N >= rows || M >= columns)
    {
        return 0;
    }
    if (matrix[N][M] != -1)
    {
        return matrix[N][M];
    }
    matrix[N][M] =
            lazySolve(N - 2, M - 1, rows, columns) + lazySolve(N - 2, M + 1, rows, columns) +
            lazySolve(N - 1, M - 2, rows, columns) + lazySolve(N + 1, M - 2, rows, columns);
    return matrix[N][M];
}

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

//Задача реализовать этот метод
//param N - количество строк (rows) доски
//param M - количество столбцов (columns) доски
//return - количество способов попасть в правый нижний угол доски (клетка N-1, M-1, если считать что первая клетка 0,0)
long long solve(int N, int M)
{
    long long res;
    if (N == 1 && M == 1)
    {
        return 1;
    }
    if (N <= 2 && M <= 2)
    {
        return 0;
    }
    matrix = new long long *[N];
    for (int i = 0; i < N; ++i)
    {
        matrix[i] = new long long[M];
        for (int j = 0; j < M; ++j)
        {
            matrix[i][j] = -1;
        }
    }
    matrix[0][0] = 1;
    res = lazySolve(N - 1, M - 1, N, M);
    for (int i = 0; i < N; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
    return res;
}

int main(int argc, const char *argv[])
{
    ReadWriter rw;

    int N = rw.readInt(); //количество строк (rows)
    int M = rw.readInt(); //количество столбцов (columns)
    //решение
    long long res = solve(N, M);
    //результат в файл
    rw.writeLongLong(res);

    return 0;
}