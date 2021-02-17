#include "ReadWriter.h"
//iostream, fstream включены в ReadWriter.h
using namespace std;

void heapify(int *args, int n, int i)
{
    int max = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && args[l] > args[max])
        max = l;

    if (r < n && args[r] > args[max])
        max = r;

    if (max != i)
    {
        swap(args[i], args[max]);
        heapify(args, n, max);
    }
}

//Можно создавать любое количество любых вспомогательных классов, структур и методов для решения задачи.

//Функция сортировки на куче
//Необходимо реализовать данную функцию.
//Результат должен быть в массиве numbers.
void heapSort(int *numbers, int array_size)
{
    for (int i = array_size / 2 - 1; i >= 0; i--)
    {
        heapify(numbers, array_size, i);
    }

    for (int i = array_size - 1; i >= 0; i--)
    {
        swap(numbers[0], numbers[i]);
        heapify(numbers, i, 0);
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
    heapSort(brr, n);

    //Запись в файл
    rw.writeArray(brr, n);

    //освобождаем память
    delete[] brr;

    return 0;
}