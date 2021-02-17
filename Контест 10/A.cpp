#include <iostream>
#include <algorithm>
#include <queue>
#include "ReadWriter.cpp"

using namespace std;

//Можно добавлять любые методы для решения задачи.

bool comparator(const string &s1, const string &s2)
{
    for (int i = 0; i < min(s1.length(), s2.length()); ++i)
    {
        if (s1[i] != s2[i])
        {
            return s1[i] < s2[i];
        }
    }
    return s1.length() < s2.length();
}

void solve(vector<Node> &graph, int start, vector<string> &result)
{
    int nodesCurrentCount = 0;
    int nodesCount = 1;
    int nodesNextCount = 0;
    vector<string> v;
    queue<Node *> q;
    q.push(&graph[start]);
    result.emplace_back(graph[start].name);
    graph[start].visited = true;

    while (!q.empty())
    {
        Node *cur = q.front();
        nodesCurrentCount++;
        q.pop();
        for (Node *neighbor : cur->neighbours)
        {
            if (!neighbor->visited)
            {
                nodesNextCount++;
                v.emplace_back(neighbor->name);
                q.push(neighbor);
                neighbor->visited = true;
            }
        }
        if (nodesCurrentCount == nodesCount) {
            sort(v.begin(), v.end(), comparator);
            result.insert(result.end(), v.begin(), v.end());
            v.clear();
            nodesCount = nodesNextCount;
            nodesNextCount = 0;
            nodesCurrentCount = 0;
        }
    }
}

int main()
{
    vector<Node> graph;
    vector<string> result;
    int start;

    ReadWriter rw;
    rw.readGraph(graph, start);
    solve(graph, start, result);
    rw.writeAnswer(result);
    return 0;
}

//ИСПРАВЛЕНО В MAIN: Убрано явное указание namespace std, использовав соответствующий using.