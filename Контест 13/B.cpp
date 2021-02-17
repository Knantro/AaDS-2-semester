#include <algorithm>
#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
//Результат также в виде вектора кратчайших расстояний из 0-й вершины во все остальные начиная с 1-й, то есть N-1 значение должно быть
void solve(int N, int M, vector<Edge> &edges, vector<int> &result)
{
    int INF = 1000000;
    result = vector<int>(N, INF);
    result[0] = 0;
    vector<int> p(N, -1);
    int x;
    for (int i = 0; i < N; ++i)
    {
        x = -1;
        for (int j = 0; j < M; ++j)
            if (result[edges[j].A] < INF)
                if (result[edges[j].B] > result[edges[j].A] + edges[j].W)
                {
                    result[edges[j].B] = max(-INF, result[edges[j].A] + edges[j].W);
                    p[edges[j].B] = edges[j].A;
                    x = edges[j].B;
                }
    }
    result.erase(result.begin());
    if (x != -1)
        result.clear();
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

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<int> result;

    //Алгоритм решения задачи
    solve(N, M, edges, result);

    //Выводим результаты
    if (!result.empty())
        rw.writeInt(result.size());
    rw.writeIntValues(result);

    return 0;
}