#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

int *brArray(string T)
{
    int i, n = T.length(), t;
    int *br = new int[n];
    br[0] = 0;
    for (i = 1; i < n; i++)
    {
        t = br[i - 1];
        while ((t > 0) && (T[i] != T[t]))
        {
            t = br[t - 1];
        }
        if (T[i] == T[t])
        {
            br[i] = t + 1;
        }
        else
        {
            br[i] = 0;
        }
    }
    return br;
}

//Основная задача - реализовать данный метод
//Можно изменить передачу параметров на ссылки (&)
//Можно добавлять любое количество любых вспомогательных методов, структур и классов
void getSubstrings(string &source, string &substring, vector<int> &res)
{
    int pozition = 0;
    int *br = brArray(substring);
    for (int i = 0; i < source.size(); i++)
    {
        while (pozition == substring.length() || (pozition > 0 && substring[pozition] != source[i]))
        {
            pozition = br[pozition - 1];
            if (substring.length() - pozition > source.length() - i)
            {
                break;
            }
        }
        if (source[i] == substring[pozition])
        {
            pozition++;
        }

        if (pozition == substring.length())
        {
            res.emplace_back(i - pozition + 1);
        }
    }
    res.shrink_to_fit();
}

//Не изменять метод main без крайней необходимости
//ОБЯЗАТЕЛЬНО добавить в комментариях подробные пояснения и причины побудившие вас изменить код этого метода.
int main()
{
    string t;
    string p;
    vector<int> res;

    ifstream fin;
    fin.open("input.txt");
    if (fin.is_open())
    {
        getline(fin, t);
        getline(fin, p);
        fin.close();
    }

    getSubstrings(t, p, res);

    fstream fout;
    fout.open("output.txt", ios::out);
    fout << res.size() << "\n";
    for (std::vector<int>::const_iterator i = res.begin(); i != res.end(); ++i)
        fout << *i << "\n";
    fout.close();

    return 0;
}
