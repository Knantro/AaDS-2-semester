#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solve(int N, vector<vector<int>> g, vector<int> &res)
{
    vector<int> degree(N);
    degree.assign(N, 0);
    vector<int> q;
    int VLeft = N;
    vector<bool> isCenter(N);
    isCenter.assign(N, true);

    for (int i = 0; i < N; ++i)
    {
        degree[i] = g[i].size();
    }

    while (VLeft > 2)
    {
        for (int i = 0; i < N; i++)
        {
            if (degree[i] == 1)
            {
                q.emplace_back(i);
            }
        }
        for (int j : q)
        {
            degree[j]--;
            isCenter[j] = false;
            auto it = find(g[g[j][0]].begin(), g[g[j][0]].end(), j);
            degree[g[j][0]]--;
            g[g[j][0]].erase(it);
            VLeft--;
        }
        q.clear();
    }

    for (int i = 0; i < N; ++i)
    {
        if (isCenter[i])
            res.emplace_back(i + 1);
    }
}

int main()
{
    int N;
    int a, b;
    ifstream ifin("input.txt", ios::in);
    ifin >> N;
    vector<vector<int>> g(N);
    vector<int> res;
    for (int i = 0; i < N - 1; ++i)
    {
        ifin >> a;
        ifin >> b;
        g[a - 1].emplace_back(b - 1);
        g[b - 1].emplace_back(a - 1);
    }
    ifin.close();
    solve(N, g, res);
    ofstream ofout("output.txt", ios::out);
    ofout << res.size() << endl;
    for (int j : res)
    {
        ofout << j << " ";
    }
    ofout.close();
    return 0;
}