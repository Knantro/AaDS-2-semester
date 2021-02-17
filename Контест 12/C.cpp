#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

Edge find(vector<Edge> &edges, int A, int B)
{
    for (auto &edge : edges)
    {
        if ((edge.A == A && edge.B == B) || (edge.A == B && edge.B == A))
            return edge;
    }
}

void solve(int N, int M, vector<Edge> &edges, vector<Edge> &result)
{
    int cost = 0;
    sort(edges.begin(), edges.end(), [](const Edge &ed1, const Edge &ed2)
    {
        return ed1.W < ed2.W;
    });
    vector<int> tree_id(N);
    for (int i = 0; i < N; ++i)
        tree_id[i] = i;
    for (int i = 0; i < M; ++i)
    {
        int a = edges[i].A, b = edges[i].B, l = edges[i].W;
        if (tree_id[a] != tree_id[b])
        {
            cost += l;
            result.emplace_back(find(edges, a, b));
            //res.push_back(make_pair(a, b));
            int old_id = tree_id[b], new_id = tree_id[a];
            for (int j = 0; j < N; ++j)
                if (tree_id[j] == old_id)
                    tree_id[j] = new_id;
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