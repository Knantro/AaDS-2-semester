#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void generate(int last, int sum, int n, vector<int> &a)
{
    if (sum == n)
    {
        if (a[0] <= 12)
            for (int i = 0; i <= last; ++i)
            {
                if (i != last)
                {
                    cout << a[i] << " ";
                } else
                {
                    cout << a[i] << endl;
                }
            }
    } else
        for (int j = 1; j <= min(a[last], n - sum); ++j)
        {
            last++;
            a[last] = j;
            generate(last, sum + j, n, a);
            last--;
        }
}


int main()
{
    unsigned long long int M, N, K;
    int n;
    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        string str;
        getline(fin, str);
        n = stoi(str);
        fin.close();
    }
    vector<int> a(n, 0);
    for (int j = 1; j < n; ++j)
    {
        a[0] = j;
        generate(0, j, n, a);
    }
    if (a[0] <= 12)
        cout << n;
    return 0;
}