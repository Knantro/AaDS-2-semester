#include <iostream>

using namespace std;

int Search_BinaryL(int *arr, int left, int right, int key)
{
    int midd = 0;
    int length = right;
    if (arr[right - 1] <= key) return 0;
    if (arr[0] > key) return right;
    while (true)
    {
        midd = (left + right) / 2;

        if (key < arr[midd] && key < arr[midd - 1])
            right = midd - 1;
        else if (key >= arr[midd] && key >= arr[midd - 1])
            left = midd + 1;
        else
            return length - midd;
    }
}

int Search_BinaryR(int *arr, int left, int right, int key)
{
    int midd = 0;
    if (arr[0] >= key) return 0;
    if (arr[right - 1] < key) return right;
    while (true)
    {
        midd = (left + right) / 2;

        if (key <= arr[midd] && key <= arr[midd - 1])
            right = midd - 1;
        else if (key > arr[midd] && key > arr[midd - 1])
            left = midd + 1;
        else
            return midd;
    }
}

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

void sort(int *args, int length)
{
    for (int i = length / 2 - 1; i >= 0; i--)
    {
        heapify(args, length, i);
    }

    for (int i = length - 1; i >= 0; i--)
    {
        swap(args[0], args[i]);
        heapify(args, i, 0);
    }
}

int main()
{
    int N;
    int x, y;
    int K;
    int Z;

    cin >> N;

    int *argsL = nullptr;
    int *argsR = nullptr;
    argsL = new int[N];
    argsR = new int[N];

    for (int i = 0; i < N; ++i)
    {
        cin >> x;
        cin >> y;
        argsL[i] = x;
        argsR[i] = y;
    }

    sort(argsL, N);
    sort(argsR, N);

    cin >> K;

    for (int i = 0; i < K; ++i)
    {
        cin >> Z;
        cout << N - Search_BinaryL(argsL, 0, N, Z) - Search_BinaryR(argsR, 0, N, Z) << '\n';
    }

    delete[] argsL;
    delete[] argsR;
    return 0;
}