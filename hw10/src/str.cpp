#include <iostream>
#include <cstring>
#include <windows.h>
#define max 10000004
int bmGs[max];
int bmBc[max];
int osuff[max];
using namespace std;
void bf(string pattern, string text)
{
    int len_t = text.length();
    int len_p = pattern.length();
    for (int i = 0; i < len_t - len_p + 1; i++)
    {
        for (int j = 0; j < len_p; j++)
        {
            if (pattern[j] != text[i + j])
            {
                break;
            }
            else if (j == len_p - 1)
            {
                cout << "brute force match at text position " << i + 1 << endl;
            }
        }
    }
}

void compute_prefix_function(int *p, int m, string pattern)
{
    p[0] = 0;
    int k = 0;
    for (int q = 1; q < m; q++)
    {
        while (k > 0 && pattern[k] != pattern[q])
        {
            k = p[k - 1];
        }
        if (pattern[k] == pattern[q])
        {
            k++;
        }
        p[q] = k;
    }
}

void kmp(string pattern, string text)
{
    int n = text.length();
    int m = pattern.length();
    int p[m];
    compute_prefix_function(p, m, pattern);
    int q = 0;
    for (int i = 0; i < n; i++)
    {
        while (q > 0 && pattern[q] != text[i])
        {
            q = p[q - 1];
        }
        if (pattern[q] == text[i])
        {
            q++;
        }
        if (q == m)
        {
            cout << "kmp match at text position " << i - m + 2 << endl;
            q = p[q - 1];
        }
    }
}

void compute_BMBC(string pattern, int m)
{
    for (int i = 0; i < 128; i++)
    {
        bmBc[i] = m;
    }
    for (int i = 1; i < m; i++)
    {
        bmBc[pattern[i]] = m - i;
    }
}
void compute_osuff(string pattern, int m)
{
    int k;
    osuff[m] = m;
    for (int i = m; i > 0; i--)
    {
        for (k = 0; k <= i; k++)
        {
            if (pattern[i - k] != pattern[m - k])
            {
                break;
            }
        }
        osuff[i] = k;
    }
}
void compute_BMGS(string pattern, int m)
{
    compute_osuff(pattern, m);
    for (int i = 1; i <= m; i++)
    {
        bmGs[i] = m;
    }
    int j = 1;
    for (int i = m - 1; i > 0; i--)
    {
        if (osuff[i] == i)
        {
            while (j <= m - i)
            {
                if (bmGs[j] == m)
                    bmGs[j] = m - i;
                j++;
            }
        }
    }
    for (int i = 1; i < m; i++)
    {
        bmGs[m - osuff[i]] = m - i;
    }
}

void bm(string pattern, string text)
{
    int n = text.length();
    int m = pattern.length();
    pattern = " " + pattern;
    text = " " + text;
    compute_BMBC(pattern, m);
    compute_BMGS(pattern, m);
    int s = 0;
    while (s <= n - m)
    {
        int i = m;
        while (pattern[i] == text[s + i])
        {
            if (i == 1)
            {
                cout << "bm match at text position " << s + i << endl;
                break;
            }
            else
                i--;
        }
        if (bmGs[i] > bmBc[text[s + i]] - m + i)
            s = s + bmGs[i];
        else
            s = s + bmBc[text[s + i]] - m + i;
    }
}
int main()
{
    string method;
    cout << "Choose the method of input and output. 'manual' for typing yourself and 'auto' for reading from existing sample." << endl;
    cin >> method;
    // method="auto";
    string pattern;
    string text;
    if (method == "manual")
    {
        cout << "please type the pattern and the text" << endl;
        cin >> pattern >> text;
        LARGE_INTEGER freq;
        LARGE_INTEGER start, end;
        double t[3];
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
        bf(pattern, text);
        QueryPerformanceCounter(&end);
        t[0] = 1e3 * (end.QuadPart - start.QuadPart) / freq.QuadPart;
        QueryPerformanceCounter(&start);
        kmp(pattern, text);
        QueryPerformanceCounter(&end);
        t[1] = 1e3 * (end.QuadPart - start.QuadPart) / freq.QuadPart;
        QueryPerformanceCounter(&start);
        bm(pattern, text);
        QueryPerformanceCounter(&end);
        t[2] = 1e3 * (end.QuadPart - start.QuadPart) / freq.QuadPart;
        // cout<<pattern<<endl;
        cout << "brute force time " << t[0] << "ms" << endl;
        cout << "kmp time " << t[1] << "ms" << endl;
        cout << "bm time " << t[2] << "ms" << endl;
    }
    else if (method == "auto")
    {
        freopen("input.txt", "r", stdin);
        cin >> text >> pattern;
        LARGE_INTEGER freq;
        LARGE_INTEGER start, end;
        double t[3];
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);
        bf(pattern, text);
        QueryPerformanceCounter(&end);
        t[0] = 1e3 * (end.QuadPart - start.QuadPart) / freq.QuadPart;
        QueryPerformanceCounter(&start);
        kmp(pattern, text);
        QueryPerformanceCounter(&end);
        t[1] = 1e3 * (end.QuadPart - start.QuadPart) / freq.QuadPart;
        QueryPerformanceCounter(&start);
        bm(pattern, text);
        QueryPerformanceCounter(&end);
        t[2] = 1e3 * (end.QuadPart - start.QuadPart) / freq.QuadPart;
        // cout<<pattern<<endl;
        cout << "brute force time " << t[0] << "ms" << endl;
        cout << "kmp time " << t[1] << "ms" << endl;
        cout << "bm time " << t[2] << "ms" << endl;
    }
}