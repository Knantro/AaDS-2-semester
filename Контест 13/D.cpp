#include <omp.h>
#include "ReadWriter.h"
//string, fstream, iostream, vector, Edge.h - included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи

using namespace std;

//Так как здесь есть несколько способов вывода ответа, то я предлагаю вам самим реализовать метод вывода,
//определенный в классе ReadWriter.
//Можно прямо сюда закинуть матрицу, и потом вычислять какие значения записывать в файл,
//или сначала сформировать вывод в каком-то вспомогательном методе и затем здесь только отправлять в файл.
void ReadWriter::writeValues(std::vector<std::vector<int>> result)
{
    if (!fout.is_open())
        throw std::ios_base::failure("file not open");
    for (int i = 0; i < result.size(); ++i)
    {
        for (int j = 0; j < result.size(); ++j)
        {
            if (i != j)
            {
                fout << i << " " << j << " ";
                if (result[i][j] != 1000000)
                {
                    fout << result[i][j] << '\n';
                } else
                {
                    fout << -1 << '\n';
                }
            }
        }
    }

    //Для записи в файл используйте конструкции:
    //fout << value1 << value2 << value3;

}


//Основной метод решения задачи, параметры:
//N - количество вершин, M - количество ребер в графе
//edges - вектор ориентированных ребер, каждое ребро представлено 3-мя числами (А, В, W),
// где A и B - номера вершин, которые оно соединяет (Путь строго из А в В), и W - вес ребра
//передается по ссылке (&), чтобы не копировать, изменять вектор и его значения можно.
void solve(int N, int M, vector<Edge> &edges, vector<vector<int>> &matrix)
{
    const int INF = 1000000;
    matrix = vector<vector<int>>(N);
    for (int l = 0; l < N; ++l)
    {
        matrix[l] = vector<int>(N, INF);
    }
    for (int m = 0; m < M; ++m)
    {
        matrix[edges[m].A][edges[m].B] = edges[m].W;
    }
    int i, j, k;
    for (k = 0; k < N; k++)
    {
        for (i = 0; i < N; i++)
        {
            if (matrix[i][k] != INF && i != k)
            {
                for (j = 0; j < N; j++)
                {
                    if (matrix[k][j] != INF && j != i && j != k)
                    {
                        int temp = matrix[i][k] + matrix[k][j];
                        if (matrix[i][j] == INF || temp < matrix[i][j])
                        {
                            matrix[i][j] = temp;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    ReadWriter rw;
    //Входные параметры
    //N - количество вершин, M - количество ребер в графе
    int N, M;
    rw.read2Ints(N, M);

    //Вектор ребер, каждое ребро представлено 3-мя числами (А, В, W), где A и B - номера вершин, которые оно соединяет, и W - вес ребра
    //Основной структурой выбран вектор, так как из него проще добавлять и удалять элементы (а такие операции могут понадобиться).
    vector<Edge> edges;
    rw.readEgdes(M, edges);

    //Основной структурой для ответа выбран вектор, так как в него проще добавлять новые элементы.
    vector<vector<int>> result(N);

    //Алгоритм решения задачи
    solve(N, M, edges, result);
    //Здесь можно вызвать ещё какой-то метод, если вам требуется.

    rw.writeValues(result);
    return 0;
}