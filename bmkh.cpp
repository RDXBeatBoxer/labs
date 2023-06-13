#include <iostream>
#include<string>
using namespace std;
struct element
{
    int* sdvigy;
    char* znaky;
    void sozdanie(int n, string B)
    {
        reverse(B.begin(), B.end());
        sdvigy = new int[n];
        for (int i = 0; i < n; i++)
            sdvigy[i] = n;
        znaky = new char[n];
        for (int i = 0; i < n; i++)
            znaky[i] = '0';
        for (int i = 0; i < n; i++)
        {
            int j = 0;
            while (znaky[j] != '0' && B[i] != znaky[j])
            {
                j++;
            }
            if (znaky[j] == '0')
            {
                znaky[j] = B[i];
                if (i != 0)
                    sdvigy[j] = i;
            }
            else if (B[i] == znaky[j])
                if (sdvigy[j] > i)
                    sdvigy[j] = i;
        }
    }
    int sdvig_po_znaku(char z, int n)
    {
        for (int i = 0; i < n; i++)
            if (znaky[i] == z)
                return sdvigy[i];
        return n + 1;
    }
};

int search(string A, string B, int aLen, int bLen, element M)
{
    int a = bLen - 1, b, i;
    while (a < aLen)
    {
        b = bLen - 1;
        i = 0;
        while (A[a - i] == B[b - i])
        {
            i++;
            if (i == bLen)
            {
                cout << "\nThe substring was found and is located from " << a - i + 2 << " to " << a + 1 << " element.\n";
                return 1;
            }
        }
        a += M.sdvig_po_znaku(A[a], bLen);
    }
    cout << "\nSubstring not found!\n";
    return 0;
}

int main()
{
    system("chcp 1251");
    setlocale(0, "");
    int aLen, bLen;
    string A;
    string B;
    cout << "Enter the main string in which you want to search: ";
    getline(cin, A);
    cout << "Type the substring you want to search for: ";
    getline(cin, B);
    aLen = A.length();
    bLen = B.length();
    if (aLen == 0 || bLen == 0 || aLen < bLen)
    {
        cout << "\nerror!\n";
        return 0;
    }
    element M;
    M.sozdanie(bLen, B);
    search(A, B, aLen, bLen, M);
}
