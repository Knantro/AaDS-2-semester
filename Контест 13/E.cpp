#include <algorithm>
#include <climits>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

#define INF 1000000

using namespace std;

class Edge
{
public:
    int A;
    int B;
    int W;
    int number;
};

class ReadWriter
{
private:

    std::fstream fin;
    std::fstream fout;

public:

    ~ReadWriter()
    {
        fin.close();
        fout.close();
    }

    ReadWriter()
    {
        fin.open("input.txt", std::ios::in);
        fout.open("output.txt", std::ios::out);
    }

    // read 2 int value and empty line
    void read2Ints(int &N, int &M)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        fin >> N;
        //empty line read
        std::string s;
        std::getline(fin, s);
        fin >> M;
        //empty line read
        std::getline(fin, s);
    }

    // read M edges, and fill vector
    void readEgdes(int M, std::vector<Edge> &edges)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");

        std::string s;
        for (int i = 0; i < M; i++)
        {
            Edge e{};
            fin >> e.A >> e.B >> e.W;
            edges.push_back(e);
            //empty line read
            std::getline(fin, s);
        }
    }

    // write all values
    void writeValues(std::vector<std::vector<int>> &result);
};

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

bool BellmanFord(int N, int M, vector<Edge> &edges, vector<int> &result)
{
    result = vector<int>(N, INF);
    result[N - 1] = 0;
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
    result.pop_back();
    return x == -1;
}

void Dijkstra(int N, vector<vector<pair<int, int>>> g, vector<vector<int>> &result, int s)
{
    vector<int> d(N, INF), p(N);
    d[s] = 0;
    priority_queue<pair<int, int>> q;
    q.push(make_pair(0, s));
    while (!q.empty())
    {
        int v = q.top().second, cur_d = -q.top().first;
        q.pop();
        if (cur_d > d[v])
            continue;

        for (size_t j = 0; j < g[v].size(); ++j)
        {
        int to = g[v][j].first,
            len = g[v][j].second;
            if (d[v] + len < d[to])
            {
                d[to] = d[v] + len;
                p[to] = v;
                q.push(make_pair(-d[to], to));
            }
        }
    }
    result[s] = d;
}

bool solve(int N, int M, vector<Edge> &edges, vector<vector<int>> &result)
{
    vector<vector<pair<int, int>>> g(N);
    vector<Edge> Edges{};
    vector<int> W;
    for (int j = 0; j < N; ++j)
    {
        Edge edge{};
        edge.A = N;
        edge.B = j;
        edge.W = 0;
        Edges.emplace_back(edge);
        result[j] = vector<int>(N);
    }
    for (int i = 0; i < M; ++i)
    {
        Edges.emplace_back(edges[i]);
    }
    if (!BellmanFord(N + 1, M + N, Edges, W))
    {
        return false;
    } else
    {
        for (int i = 0; i < M; ++i)
        {
            edges[i].W += W[edges[i].A] - W[edges[i].B];
            g[edges[i].A].emplace_back(make_pair(edges[i].B, edges[i].W));
        }
        for (int i = 0; i < N; ++i)
        {
            Dijkstra(N, g, result, i);
            for (int j = 0; j < N; ++j)
            {
                result[i][j] += W[j] - W[i];
            }
        }
    }
    return true;
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
    if (solve(N, M, edges, result))
    {
        rw.writeValues(result);
    }

    return 0;
}