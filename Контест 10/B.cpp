#include "ReadWriter.cpp"
#include <queue>
#include <algorithm>

using namespace std;

bool comparator(Node *n1, Node *&n2)
{
    string s1 = n1->name;
    string s2 = n2->name;
    for (int i = 0; i < min(s1.length(), s2.length()); ++i)
    {
        if (s1[i] != s2[i])
        {
            return s1[i] < s2[i];
        }
    }
    return s1.length() < s2.length();
}

void dfs(vector<Node> &graph, Node *node, vector<string> &result)
{
    result.emplace_back(node->name);
    node->visited = true;
    sort(node->neighbours.begin(), node->neighbours.end(), comparator);
    for (auto i : node->neighbours)
    {
        if (!i->visited)
        {
            dfs(graph, i, result);
        }
    }
}

void solve(vector<Node> &graph, int start, vector<string> &result)
{
    dfs(graph, &graph[start], result);
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

//ИСПРАВЛЕНО: подключено пространство имён std.
