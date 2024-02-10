#include <iostream>
using namespace std;
#include <random>
#include <ctime>
#define ui unsigned int
#define max 4294967295
#define x 200000006
ui arr[x];
ui copy_[x];

void random_(ui a[], int n)
{
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<ui> dist(0, max);
    for (int i = 0; i < n; i++)
    {
        a[i] = dist(rng);
    }
}
void insertionsort(ui a[], int n)
{
    ui temp = 0;
    int i, j;
    for (i = 0; i < n; i++)
    {
        temp = a[i];
        for (j = i - 1; j >= 0; j--)
        {
            if (a[j] <= temp)
                break;
            a[j + 1] = a[j];
        }
        a[j + 1] = temp;
    }
}
void shellsort(ui a[], int n)
{
    for (int step = n / 2; step > 0; step /= 2)
    {
        for (int i = step; i < n; i++)
        {
            int j = i;
            int current = a[i];
            while (j - step >= 0 && current < a[j - step])
            {
                a[j] = a[j - step];
                j = j - step;
            }
            a[j] = current;
        }
    }
}
void Merge(ui a[], ui b[], int startIndex, int midIndex, int endIndex)
{
    int i = startIndex, j = midIndex + 1, k = startIndex;
    while (i != midIndex + 1 && j != endIndex + 1)
    {
        if (a[i] > a[j])
            b[k++] = a[j++];
        else
            b[k++] = a[i++];
    }
    while (i != midIndex + 1)
        b[k++] = a[i++];
    while (j != endIndex + 1)
        b[k++] = a[j++];
    for (i = startIndex; i <= endIndex; i++)
        a[i] = b[i];
}

void MergeSort(ui a[], ui b[], int startIndex, int endIndex)
{
    int midIndex;
    if (startIndex < endIndex)
    {
        midIndex = startIndex + (endIndex - startIndex) / 2; // 避免溢出int
        MergeSort(a, b, startIndex, midIndex);
        MergeSort(a, b, midIndex + 1, endIndex);
        Merge(a, b, startIndex, midIndex, endIndex);
    }
}
void mergesort(ui a[], int l, int r)
{
    ui *temp = new ui[r - l + 1];
    MergeSort(a, temp, l, r);
    return;
}

ui Pivot(ui a[], int l, int r)
{
    ui pivot = a[l];
    while (l < r)
    {
        while (l < r && a[r] >= pivot)
        {
            --r;
        }
        a[l] = a[r];
        while (l < r && pivot >= a[l])
        {
            ++l;
        }
        a[r] = a[l];
    }
    a[l] = pivot;
    return l;
}

void quicksort(ui a[], int l, int r)
{
    if (l < r)
    {
        int pivot = Pivot(a, l, r);
        quicksort(a, l, pivot - 1);
        quicksort(a, pivot + 1, r);
    }
    return;
}

void radixsort(ui A[], int n)
{
    int d = 10;
    ui *tmp = new ui[n];
    int count[10];
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++)
    {
        for (j = 0; j < 10; j++)
            count[j] = 0;
        for (j = 0; j < n; j++)
        {
            k = (A[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j];
        for (j = n - 1; j >= 0; j--)
        {
            k = (A[j] / radix) % 10;
            tmp[count[k] - 1] = A[j];
            count[k]--;
        }
        for (j = 0; j < n; j++)
            A[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
}

int main()
{
    srand((unsigned)time(NULL));
    int n;
    cin >> n;
    random_(arr, n);
    int len = sizeof(arr) / sizeof(arr[0]);
    memcpy(copy_, arr, len * sizeof(ui));
    clock_t start, end;
    if (n <= 1000000)
    {
        start = clock();
        insertionsort(copy_, n);
        end = clock();
        cout << "runtime of insertion sort is " << end - start << "ms" << endl;
    }

    memcpy(copy_, arr, len * sizeof(ui));
    start = clock();
    shellsort(copy_, n);
    end = clock();
    cout << "runtime of shell sort is " << end - start << "ms" << endl;

    memcpy(copy_, arr, len * sizeof(ui));
    start = clock();
    mergesort(copy_, 0, n - 1);
    end = clock();
    cout << "runtime of merge sort is " << end - start << "ms" << endl;
    memcpy(copy_, arr, len * sizeof(ui));
    clock_t start1, end1;
    start1 = clock();
    quicksort(copy_, 0, n - 1);
    end1 = clock();
    cout << "runtime of quick sort is " << end1 - start1 << "ms" << endl;
    memcpy(copy_, arr, len * sizeof(ui));
    start = clock();
    radixsort(copy_, n);
    end = clock();
    cout << "runtime of radix sort is " << end - start << "ms" << endl;
    return 0;
}