#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int N;
int A;
int B;
int C;

void solve(int currentFloor, int *floors)
{
    if (currentFloor < N && floors[currentFloor] != 1)
    {
        floors[currentFloor] = 1;
        solve(currentFloor + A, floors);
        solve(currentFloor + B, floors);
        solve(currentFloor + C, floors);
    }
    return;
}

int main()
{
    int res = 0;
    ifstream fin("input.txt", ios::in);
    fin >> N >> A >> B >> C;
    int floors[N];
    for (int i = 0; i < N; ++i)
    {
        floors[i] = 0;
    }
    fin.close();
    solve(0, floors);
    ofstream fout("output.txt", ios::out);
    for (int i = 0; i < N; ++i)
    {
        res += floors[i];
    }
    fout << res;
    return 0;
}