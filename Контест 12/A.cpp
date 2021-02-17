#include "ReadWriter.h"
//string, fstream, iostream, vector, algorithm, Edge.h - included in ReadWriter.h

using namespace std;

struct Component
{
public:
    vector<int> V;
    Edge minEdge;
};

struct Vertice
{
public:
    int V;
    unsigned int compNum;
};

vector<Component> components;
vector<Vertice> vert;
vector<bool> used;
vector<vector<int>> g;

void dfs(int v)
{
    used[v] = true;
    components.back().V.emplace_back(v);
    vert[v].V = v;
    vert[v].compNum = components.size() - 1;
    for (int to : g[v])
    {
        if (!used[to])
            dfs(to);
    }
}

void find_comps(int n)
{
    components.clear();
    vert.clear();
    used.assign(n, false);
    for (int i = 0; i < n; ++i)
        if (!used[i])
        {
            components.emplace_back();
            components.back().minEdge.W = 30001;
            dfs(i);
        }
}

void minEdges(int M, vector<Edge> &edges)
{
    for (int i = 0; i < M; ++i)
    {
        int first = vert[edges[i].A].compNum;
        int second = vert[edges[i].B].compNum;
        if (first != second)
        {
            if (components[first].minEdge.W > edges[i].W)
            {
                components[first].minEdge = edges[i];
            }
            if (components[second].minEdge.W > edges[i].W)
            {
                components[second].minEdge = edges[i];
            }
        }
    }
}

void solve(int N, int M, vector<Edge> &edges, vector<Edge> &result)
{
    vector<bool> edgesUsed(N);
    edgesUsed.assign(M, false);
    vert = vector<Vertice>(N);
    g = vector<vector<int>>(N);
    while (result.size() < N - 1)
    {
        find_comps(N);
        minEdges(M, edges);
        for (auto &component : components)
        {
            if (!edgesUsed[component.minEdge.number] && component.minEdge.W != INT32_MAX)
            {
                result.emplace_back(component.minEdge);
                edgesUsed[component.minEdge.number] = true;
                g[component.minEdge.A].emplace_back(component.minEdge.B);
                g[component.minEdge.B].emplace_back(component.minEdge.A);
            }
        }
    }
}

int main()
{
    ReadWriter rw;
    int N, M;
    rw.read2Ints(N, M);
    vector<Edge> edges;
    rw.readEgdes(M, edges);
    vector<Edge> result;
    solve(N, M, edges, result);
    rw.writeInt(result.size());
    rw.writeEdges(result);
    return 0;
}