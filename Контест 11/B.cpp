#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> items;
vector<vector<int>> g;
vector<bool> visited;
vector<string> res;
vector<int> start;

bool comparator(const int &v1, const int &v2)
{
    string w1 = items[v1];
    string w2 = items[v2];
    for (int i = 0; i < min(w1.length(), w2.length()); ++i)
    {
        if (w1[i] != w2[i])
        {
            return w1[i] < w2[i];
        }
    }
    return w1.length() < w2.length();
}

void dfs(int v)
{
    visited[v] = true;
    for (int to : g[v])
    {
        if (!visited[to])
        {
            dfs(to);
        }
    }
    res.emplace_back(items[v]);
}

void topological_sort()
{
    res.clear();
    for (int i : start)
    {
        if (!visited[i])
        {
            dfs(i);
        }
    }
    reverse(res.begin(), res.end());
}

int main()
{
    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        int i = 0;
        while (str != "#")
        {
            items.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
            start.emplace_back(i);
            i++;
        }
        getline(fin, str);
        g = vector<vector<int>>(items.size());
        while (fin)
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            g[a].emplace_back(b);
            getline(fin, str);
        }
        fin.close();
    }
    vector<int>::iterator it;
    for (int i = 0; i < items.size(); ++i)
    {
        for (int j : g[i])
        {
            it = find(start.begin(), start.end(), j);
            if (it != start.end())
            {
                start.erase(it);
            }
        }
        sort(g[i].begin(), g[i].end(), comparator);
    }
    sort(start.begin(), start.end(), comparator);
    visited = vector<bool>(items.size());
    visited.assign(items.size(), false);
    topological_sort();
    fstream fout;
    fout.open("output.txt", ios::out);
    for (const auto &re : res)
    {
        fout << re << "\n";
    }
    fout.close();
    return 0;

}