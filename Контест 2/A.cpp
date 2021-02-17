#include "ReadWriter.h"
#include "MergeSort.h"
//iostream, fstream включены в ReadWriter.h

//Не рекомендуется добавлять собственные вспомогательные классы и методы.
//Необходимо использовать уже имеющиеся классы и методы, добавив реализацию, соответствующую описанию.
using namespace std;

//Описание методов на английском языке имеется в классе MergeSort, в файле MergeSort.h
void MergeSort::sort(int *arr, int length)
{
    divide_and_merge(arr, 0, length - 1);
}

void MergeSort::merge(int *arr, int first, int second, int end)
{
    int i1 = 0;
    int i2 = 0;
    int flength = second - first + 1;
    int slength = end - second;
    int F[flength], S[slength];

    for (i1 = 0; i1 < flength; i1++)
    {
        F[i1] = arr[first + i1];
    }

    for (i2 = 0; i2 < slength; i2++)
    {
        S[i2] = arr[second + 1 + i2];
    }

    int k = first;
    i1 = 0;
    i2 = 0;

    while (i1 < flength && i2 < slength)
    {
        if (F[i1] <= S[i2])
        {
            arr[k] = F[i1];
            i1++;
        } else
        {
            arr[k] = S[i2];
            i2++;
        }
        k++;
    }

    while (i1 < flength)
    {
        arr[k] = F[i1];
        i1++;
        k++;
    }

    while (i2 < slength)
    {
        arr[k] = S[i2];
        i2++;
        k++;
    }
}

void MergeSort::divide_and_merge(int *arr, int left, int right)
{
    if (left < right)
    {
        int m = left + (right - left) / 2;

        divide_and_merge(arr, left, m);
        divide_and_merge(arr, m + 1, right);

        merge(arr, left, m, right);
    }
}

int main()
{
    ReadWriter rw;

    int *brr = nullptr;
    int length;

    //Read data from file
    length = rw.readInt();

    brr = new int[length];
    rw.readArray(brr, length);

    //Start sorting
    MergeSort s;

    s.sort(brr, length);

    //Write answer to file
    rw.writeArray(brr, length);

    delete[] brr;

    return 0;
}
