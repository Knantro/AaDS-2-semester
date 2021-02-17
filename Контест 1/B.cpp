#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h

using namespace std;

// Получение максимального значения из массива
int getMax(int *numbers, int array_size)
{
    int max = -1;
    for (int i = 0; i < array_size; ++i)
    {
        if (max < numbers[i])
        {
            max = numbers[i];
        }
    }
    return max;
}

// Функция сортировки подсчётом для цифровой сортировки
void countingSort(int *numbers, int array_size, int exp)
{
    int *B = nullptr;
    int *C = nullptr;
    int max = 256;
    B = new int[array_size];
    C = new int[max];
    for (int i = 0; i < max; ++i)
    {
        C[i] = 0;
    }
    for (int i = 0; i < array_size; ++i)
    {
        C[(numbers[i] / exp) % max]++;
    }
    for (int i = 1; i < max; ++i)
    {
        C[i] += C[i - 1];
    }
    for (int i = array_size - 1; i >= 0; --i)
    {
        B[C[(numbers[i] / exp) % max] - 1] = numbers[i];
        C[(numbers[i] / exp) % max]--;
    }
    for (int i = 0; i < array_size; ++i)
    {
        numbers[i] = B[i];
    }
    delete[] C;
    delete[] B;
}

// Функция цифровой сортировки
void radixSort(int *numbers, int array_size)
{
    int max = getMax(numbers, array_size);
    for (int exp = 1; max / exp > 0; exp *= 256)
    {
        countingSort(numbers, array_size, exp);
    }
}

//Не удалять и не изменять метод main без крайней необходимости.
//Необходимо добавить комментарии, если все же пришлось изменить метод main.
int main()
{
    //Объект для работы с файлами
    ReadWriter rw;

    int *brr = nullptr;
    int n;

    //Ввод из файла
    n = rw.readInt();

    brr = new int[n];
    rw.readArray(brr, n);

    //Запуск сортировки, ответ в том же массиве (brr)
    radixSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}

