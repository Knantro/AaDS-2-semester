#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class ShannonFano
{
public:
    vector<int> probabilityList;
    vector<string> resultList;

    ShannonFano() = default;

    void Shannon_Fano(int *arr, const string& code, int length)
    {
        if (length == 1)
        {
            resultList.emplace_back(code);
            return;
        }

        int sum1 = 0;
        int sum2 = 0;
        int l = 0;
        int r = 0;
        vector<int> leftGroup;
        vector<int> rightGroup;

        for (int i = 0; i < length; ++i)
        {
            if (sum2 <= sum1)
            {
                rightGroup.emplace_back(arr[length - r - 1]);
                sum2 += arr[length - r - 1];
                r++;
            }
            else
            {
                leftGroup.emplace_back(arr[l]);
                sum1 += arr[l];
                l++;
            }
        }

        reverse(begin(rightGroup), end(rightGroup));

        Shannon_Fano(leftGroup.data(), code + "0", leftGroup.size());
        Shannon_Fano(rightGroup.data(), code + "1", rightGroup.size());
    }

    void build()
    {
        Shannon_Fano(probabilityList.data(), "", probabilityList.size());
    }

    void addChance(int chance)
    {
        probabilityList.emplace_back(chance);
    }

    string get(int i)
    {
        return resultList[i];
    }
};

int main()
{
    int n;
    ShannonFano *shf = new ShannonFano();

    fstream fin;
    fin.open("input.txt", ios::in);
    if (fin.is_open())
    {
        fin >> n;
        for (int i = 0; i < n; i++)
        {
            int x;
            fin >> x;
            shf->addChance(x);
        }

        fin.close();

        shf->build();
        fstream fout;
        fout.open("output.txt", ios::out);
        for (int i = 0; i < n; i++)
        {
            fout << shf->get(i) << (i == n - 1 ? "" : " ");
        }
        fout.close();
        delete shf;
    }
    return 0;
}