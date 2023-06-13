#include <iostream>
#include<string>
using namespace std;

void zap_mas(int* mas, string B, int bLen)
{
    mas[0] = 0;
    int j = 0, i = 1;
    while (i <= bLen)
    {
        if (B[j] == B[i])
        {
            mas[i] = j + 1;
            i++;
            j++;
        }
        else if (j == 0)
        {
            mas[i] = 0;
            i++;
        }
        else
            j = mas[j - 1];
    }
}

int search(string A, string B, int aLen, int bLen, int* mas)
{
    int i = 0, j = 0;
    while (i < aLen)
    {
        if (A[i] == B[j])
        {
            i++;
            j++;
            if (j == bLen)
            {
                cout << "\nthe substring found from " << i - bLen + 1 << " to " << i << " element.\n";
                return 1;
            }
        }
        else if (j == 0)
        {
            i++;
            if (i == aLen)
            {
                cout << "\nthe substring not found!\n";
                return 0;
            }
        }
        else
            j = mas[j - 1];
    }
    cout << "\nsearch error!\n";
    return -1;
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
    int* mas = new int[bLen];
    zap_mas(mas, B, bLen);
    search(A, B, aLen, bLen, mas);
    return 0;
}
