#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

//Можно добавлять любые вспомогательные методы и классы для решения задачи.

void findAns(int N, int W, int **matrix, vector<int> *res, int *stones)
{
    if (matrix[N][W] == 0)
    {
        return;
    }
    if (matrix[N - 1][W] == matrix[N][W])
    {
        findAns(N - 1, W, matrix, res, stones);
    } else
    {
        findAns(N - 1, W - stones[N - 1], matrix, res, stones);
        res->emplace_back(stones[N - 1]);
    }
}

//Задача реализовать этот метод
//param N - количество камней
//param M - ограничения на вес
//param stones - массив размера N, с весами камней
//param res - вектор результатов (вес камней, которые надо взять)
void solve(int N, int W, int *stones, vector<int> &res)
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
            if (s >= stones[k - 1])
            {
                matrix[k][s] = max(matrix[k - 1][s], matrix[k - 1][s - stones[k - 1]] + stones[k - 1]);
            } else
            {
                matrix[k][s] = matrix[k - 1][s];
            }
        }
    }
    findAns(N, W, matrix, &res, stones);
    for (int i = 0; i < N + 1; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main(int argc, const char *argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //камни
    int W = rw.readInt(); //ограничения на вес
    int *arr = new int[N]; //имеющиеся камни
    rw.readArr(arr, N);

    //основной структурой выбран вектор, так как заранее неизвестно какое количество камней будет взято
    vector<int> res;
    //решаем задачу
    solve(N, W, arr, res);
    int sum = 0;
    for (int re : res)
        sum += re;

    //записываем ответ в файл
    rw.writeInt(sum); //итоговый вес
    rw.writeInt(res.size()); //количество взятых камней
    rw.writeVector(res); //сами камни

    delete[] arr;
    return 0;
}