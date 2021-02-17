#include "ReadWriter.h"
//iostream, fstream, string included in ReadWriter.h

//Можно создавать любые классы и методы для решения задачи
//Советую разделить решение на логические блоки


//Основной метод решения задачи, параметры:
//n - размер векторов условия
//up - доп. условия сверху, содержит буквы латинского алфавита и пробелы
//down - доп. условия снизу, содержит буквы латинского алфавита и пробелы
//left - доп. условия слева, содержит буквы латинского алфавита и пробелы
//up - доп. условия справа, содержит буквы латинского алфавита и пробелы
///Выходные параметры:
//result - матрица ограничений для задачи, содержит символы '0' и '1', других не содержит.
//передается по ссылке, чтобы потом можно было прочитать значение из main
//rows - количество строк в матрице результата
//cols - количество столбцов в матрице результата
void createMatrix(char *up, char *down, char *left, char *right, int n, char **&result, int &rows, int &cols)
{
    rows = n * n * n;
    cols = 3 * n * n;
    int o = 0;
    for (int i = 0; i < n; ++i)
    {
        if (up[i] != ' ')
        {
            o++;
        }
        if (down[i] != ' ')
        {
            o++;
        }
        if (left[i] != ' ')
        {
            o++;
        }
        if (right[i] != ' ')
        {
            o++;
        }
    }
    o *= 2;
    cols += o;
    result = new char *[rows];
    for (int j = 0; j < rows; ++j)
    {
        result[j] = new char[cols];
        for (int i = 0; i < cols; ++i)
        {
            result[j][i] = '0';
        }
    }
    for (int i = 0; i < rows; ++i)
    {
        result[i][i % n + i / (n * n) * n] = '1';
        result[i][i % (n * n) + n * n] = '1';
        result[i][i / n + (2 * n * n) + o] = '1';
    }
    int range;
    int col = n * n * 2;
    for (int i = 0; i < n; ++i)
    {
        if (up[i] != ' ')
        {
            range = up[i] - 'A';
            result[n * (i + 1) - 1][col] = '1';
            result[range + n * i][col] = '1';
            result[range + n * i][col + 1] = '1';
            result[range + n * i + n * n][col + 1] = '1';
            col += 2;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (left[i] != ' ')
        {
            range = left[i] - 'A';
            result[n + n * n * i - 1][col] = '1';
            result[range + n * n * i][col] = '1';
            result[range + n * n * i][col + 1] = '1';
            result[range + n + n * n * i][col + 1] = '1';
            col += 2;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (down[i] != ' ')
        {
            range = down[i] - 'A';
            result[rows - (n * (n - i - 1) + 1)][col] = '1';
            result[rows - (-range + n * (n - i))][col] = '1';
            result[rows - (-range + n * (n - i))][col + 1] = '1';
            result[rows - (-range + n * (n - i)) - n * n][col + 1] = '1';
            col += 2;
        }
    }
    for (int i = 0; i < n; ++i)
    {
        if (right[i] != ' ')
        {
            range = right[i] - 'A';
            result[rows - n * n * (n - i - 1) - 1][col] = '1';
            result[rows + range - n * n * (n - i - 1) - n][col] = '1';
            result[rows + range - n * n * (n - i - 1) - n][col + 1] = '1';
            result[rows + range - n * n * (n - i - 1) - 2 * n][col + 1] = '1';
            col += 2;
        }
    }
}


int main()
{
    ReadWriter rw;
    //читаем параметры
    int n = rw.readInt();

    char *up = new char[n];
    char *down = new char[n];
    char *left = new char[n];
    char *right = new char[n];

    rw.readData(up, down, left, right, n);

    //Память здесь не выделяется, так как размер неизвестен
    char **result = nullptr;
    //Основной алгоритм, возвращает результат как матрицу
    int rows = 0, cols = 0;
    createMatrix(up, down, left, right, n, result, rows, cols);

    //выводим результат в файл
    rw.writeInts(rows, cols);
    rw.writeMatrix(result, rows, cols);

    //освобождаем память
    delete[] up;
    delete[] down;
    delete[] left;
    delete[] right;

    for (int i = 0; i < rows; i++)
        delete[] result[i];
    delete[] result;

    return 0;
}