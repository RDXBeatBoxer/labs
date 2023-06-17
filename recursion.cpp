#include <iostream>
using namespace std;
int n, f = 1, temp, c;

int rec(int n, int f)
{
    c = f + temp;
    temp = c - temp;
    f = c;
    if (n != 0)
    {
    cout « f « endl;
    return rec(n-1, f);
    }
    else
        return 0;
}

void main()
{
    cin » n;
    rec(n, f);
}