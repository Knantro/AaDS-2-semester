#include "ReadWriter.h"
//vector, string, iostream included in "ReadWriter.h"

using namespace std;

void findAns(int N, int W, int **matrix, vector<pair<int, int>>& res, pair<int, int>* items)
{
    if (matrix[N][W] == 0)
    {
        return;
    }
    if (matrix[N - 1][W] == matrix[N][W])
    {
        findAns(N - 1, W, matrix, res, items);
    } else
    {
        findAns(N - 1, W - items[N - 1].first, matrix, res, items);
        res.emplace_back(items[N - 1]);
    }
}
//Можно добавлять любые вспомогательные методы и классы для решения задачи.

//Задача реализовать этот метод
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int>* items, vector<pair<int, int>>& res)
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
            if (s >= items[k - 1].first)
            {
                matrix[k][s] = max(matrix[k - 1][s], matrix[k - 1][s - items[k - 1].first] + items[k - 1].second);
            } else
            {
                matrix[k][s] = matrix[k - 1][s];
            }
        }
    }
    findAns(N, W, matrix,res, items);
    for (int i = 0; i < N + 1; ++i)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main(int argc, const char * argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    auto* arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (auto & re : res)
    {
        sumWeight += re.first;
        sumCost += re.second;
    }
    //записываем ответ в файл
    rw.writeInt(sumCost);
    rw.writeInt(sumWeight);
    rw.writeInt(res.size());
    rw.writeVector(res);

    delete[] arr;
    return 0;
}