#include <iostream>

using namespace std;

void Towers(int ring, int start, int end, int buffer)
{


    if (ring != 0)
    {
        Towers(ring - 1, start, buffer, end);
        cout << start << " -> " << end << endl;
        Towers(ring - 1, buffer, end, start);
    }
}
int main()
{
    int rings = 5;

    Towers(rings, 1, 3, 2);

    cout << "\n  ";

    return 0;
}