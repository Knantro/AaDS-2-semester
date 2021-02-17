#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>

#define INF INT32_MAX

using namespace std;

// iPair ==> Integer Pair
typedef pair<int, int> iPair;

struct Node
{
    int A;
    int B;
    int W;
    bool used = false;

public:
    Node(int A, int B, int W)
    {
        this->A = A;
        this->B = B;
        this->W = W;
    }
};

// To add an edge
void addEdge(vector<pair<int, int>> adj[], int u, int v, int wt)
{
    adj[u].emplace_back(v, wt);
    adj[v].emplace_back(u, wt);
}

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
    void readAll(int &N, vector<iPair> adj[], vector<Node> &nodes)
    {
        if (!fin.is_open())
            throw std::ios_base::failure("file not open");
        std::string s;
        for (int i = 0; i < N; ++i)
        {
            int a;
            fin >> a;
            addEdge(adj, N, i, a);
            nodes.emplace_back(N, i, a);
        }
        std::getline(fin, s);
        for (int i = 0; i < N - 1; ++i)
        {
            int b;
            fin >> b;
            addEdge(adj, i, i + 1, b);
            nodes.emplace_back(i, i + 1, b);
        }
    }

    void writeAnswer(unsigned long long int result);

    void readN(int &N);
};

// write all values
void ReadWriter::writeAnswer(unsigned long long int res)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");
    fout << res;
}

void ReadWriter::readN(int &N)
{
    if (!fin.is_open())
        throw std::ios_base::failure("file not open");

    fin >> N;
    //empty line read
    std::string s;
    std::getline(fin, s);
}

unsigned long long int MST(vector<Node> &E, vector<pair<int, int> > adj[], int N)
{
    unsigned long long int res = 0;
    priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
    int src = 0;
    vector<int> key(N, INF);
    vector<int> parent(N, -1);
    vector<bool> inMST(N, false);
    pq.push(make_pair(0, src));
    key[src] = 0;
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;
        for (auto x : adj[u])
        {
            int v = x.first;
            int weight = x.second;
            if (inMST[v] == false && key[v] > weight)
            {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }
    for (auto &item : E)
        if (item.A == parent[item.B] || item.B == parent[item.A])
            res += item.W;

    return res;
}

int main()
{
    ReadWriter rw;

    int N;
    rw.readN(N);

    vector<iPair> adj[N + 1];
    vector<Node> nodes;

    rw.readAll(N, adj, nodes);

    rw.writeAnswer(MST(nodes, adj, N + 1));

    return 0;
}