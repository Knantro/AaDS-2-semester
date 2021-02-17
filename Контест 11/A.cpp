#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> g{}, gr{};
vector<bool> used;
vector<int> order, component;

bool comparatorString(const string &w1, const string &w2)
{
    for (int i = 0; i < min(w1.length(), w2.length()); ++i)
    {
        if (w1[i] != w2[i])
        {
            return w1[i] < w2[i];
        }
    }
    return w1.length() < w2.length();
}

bool comparatorVector(const vector<string> &w1, const vector<string> &w2)
{
    return comparatorString(w1[0], w2.back());
}

void dfs1(int v)
{
    used[v] = true;
    for (int i : g[v])
    {
        if (!used[i])
        {
            dfs1(i);
        }
    }
    order.push_back(v);
}

void dfs2(int v)
{
    used[v] = true;
    component.push_back(v);
    for (int i : gr[v])
    {
        if (!used[i])
        {
            dfs2(i);
        }
    }
}

int main()
{
    vector<string> names = vector<string>();
    vector<vector<string>> result;

    //setlocale(LC_ALL, "ru_RU.UTF-8");

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        string str;
        getline(fin, str);

        while (str != "#")
        {
            names.emplace_back(str.substr(str.find(' ') + 1));
            getline(fin, str);
        }

        for (int i = 0; i < names.size(); i++)
        {
            vector<int> ge;
            g.emplace_back(ge);
            gr.emplace_back(ge);
        }

        getline(fin, str);

        while (fin)
        {
            int a = stoi(str.substr(0, str.find(' '))) - 1;
            int b = stoi(str.substr(str.find(' '))) - 1;
            g[a].emplace_back(b);
            gr[b].emplace_back(a);
            getline(fin, str);
        }

        used.assign(names.size(), false);
        for (int i = 0; i < names.size(); ++i)
        {
            if (!used[i])
            {
                dfs1(i);
            }
        }
        used.assign(names.size(), false);
        for (int i = 0; i < names.size(); ++i)
        {
            int v = order[names.size() - 1 - i];
            if (!used[v])
            {
                dfs2(v);
                for (int j = 0; j < component.size(); ++j)
                {
                    if (j == 0)
                    {
                        vector<string> vec;
                        result.emplace_back(vec);
                    }
                    result.back().emplace_back(names[component[j]]);
                }
                sort(result.back().begin(), result.back().end(), comparatorString);
                component.clear();
            }
        }
        sort(result.begin(), result.end(), comparatorVector);
        fin.close();
        ofstream fout;
        fout.open("output.txt", ios::out);
        for (int i = 0; i < result.size(); ++i)
        {
            for (const auto & j : result[i])
            {
                fout << j << "\n";
            }
            if (i != result.size() - 1)
            {
                fout << "\n";
            }
        }
        fout.close();
    }
    return 0;
}