#include<iostream>
#include<string>
using namespace std;

int straightFind(string A, string B)
{
    int i = 0, h;
    while (i < A.length())
    {
        h = 0;
        int j = 0, k = i;
        while ((A[k] == B[j]) && (h < B.length()) && (k < A.length()))
        {
            k++;
            j++;
            h++;
        }
        if (h == B.length())
        {
            cout << "\nthe substring found from " << i + 1 << " to " << i + B.length() << " element.\n";
            return 1;
        }
        i++;
    }
    cout << "\nthe substring not found!\n";
    return 0;
}

int main()
{
    setlocale(0, "");
    string A;
    string B;
    cout << "Enter the main string in which you want to search: ";
    getline(cin, A);
    cout << "Type the substring you want to search for: ";
    getline(cin, B);
    if (A.length() == 0 || B.length() == 0 || A.length() < B.length())
    {
        cout << "\nerror!\n";
        return 0;
    }
    straightFind(A, B);
}