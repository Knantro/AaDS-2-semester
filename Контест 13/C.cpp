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
    const int INF = 10000000;
    vector<vector<pair<int, int>>> g(N);
    for (int i = 0; i < M; ++i)
    {
        g[edges[i].A].emplace_back(make_pair(edges[i].B, edges[i].W));
    }
    int s = 0;
    result = vector<int>(N, INF);
    vector<int> p(N);
    result[s] = 0;
    vector<bool> u(N);
    for (int i = 0; i < N; ++i)
    {
        int v = -1;
        for (int j = 0; j < N; ++j)
            if (!u[j] && (v == -1 || result[j] < result[v]))
                v = j;
        if (result[v] == INF)
            break;
        u[v] = true;

        for (size_t j = 0; j < g[v].size(); ++j)
        {
            int to = g[v][j].first,
                    len = g[v][j].second;
            if (result[v] + len < result[to])
            {
                result[to] = result[v] + len;
                p[to] = v;
            }
        }
    }
    result.erase(result.begin());
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
    rw.writeInt(result.size());
    rw.writeIntValues(result);

    return 0;
}