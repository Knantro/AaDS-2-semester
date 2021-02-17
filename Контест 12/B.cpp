#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

Edge find(vector<Edge> &edges, int A, int B)
{
    for (auto & edge : edges)
    {
        if ((edge.A == A && edge.B == B) || (edge.A == B && edge.B == A))
            return edge;
    }
}

void solve(int N, int M, vector<Edge> &edges, vector<Edge> &result)
{
    const int INF = INT32_MAX;
    vector<bool> used(N);
    vector<vector<int>> g(N);
    for (int k = 0; k < N; ++k)
    {
        g[k].assign(N, INF);
    }
    for (int i = 0; i < M; ++i)
    {
        g[edges[i].A][edges[i].B] = edges[i].W;
        g[edges[i].B][edges[i].A] = edges[i].W;
    }
    vector<int> min_e(N, INF), sel_e(N, -1);
    min_e[0] = 0;
    for (int i = 0; i < N; ++i)
    {
        int v = -1;
        for (int j = 0; j < N; ++j)
            if (!used[j] && (v == -1 || min_e[j] < min_e[v]))
                v = j;

        used[v] = true;
        if (sel_e[v] != -1)
            result.emplace_back(find(edges, sel_e[v], v));

        for (int to = 0; to < N; ++to)
            if (g[v][to] < min_e[to])
            {
                min_e[to] = g[v][to];
                sel_e[to] = v;
            }
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

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    //(а предложенные алгоритмы работают итеративно, увеличивая количество ребер входящих в решение на каждом шаге)
    vector<Edge> result;

    //Алгоритм решения задачи
    //В решение должны входить ребра из первоначального набора!
    solve(N, M, edges, result);

    //Выводим результаты
    rw.writeInt(result.size());
    rw.writeEdges(result);

    return 0;
}