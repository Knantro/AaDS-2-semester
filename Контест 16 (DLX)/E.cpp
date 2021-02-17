#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool done;

bool ableStudentAt(int a, int b, int N, vector<string> &out)
{
    for (int i = 0; i < a; ++i)
    {
        if (out[i][b] == '1')
        {
            return false;
        }
    }

    for (int i = 1; i <= a && i <= b; ++i)
    {
        if (out[a - i][b - i] == '1')
        {
            return false;
        }
    }

    for (int i = 1; i <= a && b + i < N; i++)
    {
        if (out[a - i][b + i] == '1')
        {
            return false;
        }
    }

    return true;
}

void setStudent(int a, int N, vector<string> &out)
{
    if (a == N)
    {
        done = true;
        return;
    }

    for (int i = 0; i < N; ++i)
    {
        if (ableStudentAt(a, i, N, out))
        {
            out[a][i] = '1';
            setStudent(a + 1, N, out);
            if (done)
            {
                return;
            }
            out[a][i] = '0';
        }
    }
}

void getPlaces(int n, vector<string> &out)
{
    out = vector<string>(n, string(n, '0'));
    setStudent(0, n, out);
}

int main()
{
    int n;
    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        fin >> n;
        fin.close();
    }

    vector<string> res;
    getPlaces(n, res);

    fstream fout;
    fout.open("output.txt", ios::out);
    for (int i = 0; i < res.size() - 1; i++)
        fout << res[i] << endl;
    fout << res[res.size() - 1];
    fout.close();
    return 0;
}