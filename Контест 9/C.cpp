#include "ReadWriter.h"
#include <algorithm>
//vector, string, iostream, algorithm included in "ReadWriter.h"

using namespace std;

bool comparator(pair<int, int> a, pair<int, int> b)
{
    if ((double) a.first / a.second != (double) b.first / b.second)
    {
        return (double) a.first / a.second < (double) b.first / b.second;
    } else
    {
        return a.first > b.first;
    }
}

//Задача реализовать этот метод (жадный алгоритм)
//param N - количество предметов
//param W - ограничения на вес рюкзака
//param items - массив размера N, с предметами - first = вес, second = стоимость
//param res - вектор результатов (предметы, которые надо взять)
void solve(int N, int W, pair<int, int> *items, vector<pair<int, int>> &res)
{
    sort(items, items + N, comparator);
    int currWeight = 0;
    for (int i = 0; i < N && currWeight < W; ++i)
    {
        if (items[i].first + currWeight <= W)
        {
            currWeight += items[i].first;
            res.emplace_back(items[i]);
        }
    }
}

int main(int argc, const char *argv[])
{
    ReadWriter rw;
    int N = rw.readInt(); //количество предметов
    int W = rw.readInt(); //ограничения на вес рюкзака

    //структура массив pair выбрана, так как известно количество элементов, и у объекта всего 2 характеристики
    //first = вес(weight), second = стоимость (cost)
    //Можно переложить данные в любую другую удобную струтуру
    //Внимание(!) данные не упорядочены, но можно это сделать если вам требуется
    auto *arr = new pair<int, int>[N];
    rw.readArr(arr, N);

    //структура вектор pair выбрана, так как неизвестно количество элементов, и у объекта всего 2 характеристики
    //результат, также first = вес(weight), second = стоимость (cost)
    vector<pair<int, int>> res;
    solve(N, W, arr, res);

    int sumCost = 0, sumWeight = 0;
    for (auto &re : res)
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