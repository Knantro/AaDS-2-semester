#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

void quickSort(int* arr, int low, int high)
{
    int i = low;
    int j = high;
    int pivot = arr[high];

    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            swap(arr[i],arr[j]);
            i++;
            j--;
        }
    };

    if (low < j)
        quickSort(arr, low, j);
    if (i < high)
        quickSort(arr, i, high);
}

void quickSort(int *numbers, int array_size)
{
    quickSort(numbers, 0, array_size - 1);
}

int main()
{
    int *brr;
    int n;

    fstream fin;
    fin.open("input.txt",ios::in);
    if (fin.is_open())
    {
        fin >> n;
        brr = new int[n];
        for (int i = 0; i < n; i++)
            fin >> brr[i];

        fin.close();
    }
    quickSort(brr, n);
    fstream fout;
    fout.open("output.txt",ios::out);
    for (int i = 0; i < n; i++)
        fout << brr[i] << " ";

    fout.close();
    delete[] brr;
    return 0;
}