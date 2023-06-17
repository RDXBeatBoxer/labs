#include <iostream>
#include <fstream>
#include <string>

void copyEvenLines(const std::string& inputFile, const std::string& outputFile) {
    std::ifstream input(inputFile);
    if (!input) {
        std::cerr << "Error opening input file: " << inputFile << std::endl;
        return;
    }

    std::ofstream output(outputFile);
    if (!output) {
        std::cerr << "Error opening output file: " << outputFile << std::endl;
        input.close();
        return;
    }

    std::string line;
    int lineNumber = 0;
    int evenLineNumber = 0;
    while (std::getline(input, line)) {
        lineNumber++;
        if (lineNumber % 2 == 0) {
            output << line << std::endl;
            evenLineNumber++;
        }
    }

    input.close();
    output.close();

    std::cout << "Copied " << evenLineNumber << " even lines from " << inputFile << " to " << outputFile << std::endl;
}

int getFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return -1;
    }

    int fileSize = file.tellg();
    file.close();

    return fileSize;
}

int main() {
    std::string inputFile = "F1.txt";
    std::string outputFile = "F2.txt";

    copyEvenLines(inputFile, outputFile);

    int fileSizeF1 = getFileSize(inputFile);
    int fileSizeF2 = getFileSize(outputFile);

    if (fileSizeF1 != -1) {
        std::cout << "File F1 size: " << fileSizeF1 << " bytes" << std::endl;
    }

    if (fileSizeF2 != -1) {
        std::cout << "File F2 size: " << fileSizeF2 << " bytes" << std::endl;
    }

    return 0;
}
