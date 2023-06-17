#include <iostream>
#include <string>

using namespace std;

void printWords(const string& input) {
    const int lineLength = 60;
    string output;
    int currentLength = 0;

    for (int i = 0; i < input.length(); i++) {
        if (input[i] != '0') {
            output += input[i];
            currentLength++;

            if (currentLength == lineLength) {
                cout << "(" << output << ")";
                output.clear();
                currentLength = 0;
            }
            else {
                output += ",";
                currentLength++;
            }
        }
        else {
            if (!output.empty()) {
                cout << "(" << output << ")";
                output.clear();
                currentLength = 0;
            }
        }
    }

    if (!output.empty()) {
        cout << "(" << output << ")";
    }
}

int main() {
    string words[3] = {
        "123023402303450",
        "234450234567010",
        "234455677670450"
    };

    for (int i = 0; i < 3; i++) {
        cout << "Result for line " << i + 1 << ": ";
        printWords(words[i]);
        cout << endl;
    }

    return 0;
}
