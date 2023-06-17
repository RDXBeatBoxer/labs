#include <iostream>
#include <fstream>
#include <string>

struct Applicant {
    std::string lastName;
    std::string firstName;
    std::string patronymic;
    int birthYear;
    int examScores[3];
    float averageGrade;
};

void printApplicants(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    Applicant applicant;
    while (file.read(reinterpret_cast<char*>(&applicant), sizeof(Applicant))) {
        std::cout << "Last Name: " << applicant.lastName << std::endl;
        std::cout << "First Name: " << applicant.firstName << std::endl;
        std::cout << "Patronymic: " << applicant.patronymic << std::endl;
        std::cout << "Birth Year: " << applicant.birthYear << std::endl;
        std::cout << "Exam Scores: ";
        for (int i = 0; i < 3; ++i) {
            std::cout << applicant.examScores[i] << " ";
        }
        std::cout << std::endl;
        std::cout << "Average Grade: " << applicant.averageGrade << std::endl;
        std::cout << "------------------------" << std::endl;
    }

    file.close();
}

void deleteApplicant(const std::string& filename, int position) {
    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::ofstream tempFile("temp.bin", std::ios::binary);
    if (!tempFile) {
        std::cerr << "Error creating temporary file." << std::endl;
        inputFile.close();
        return;
    }

    Applicant applicant;
    int currentPosition = 0;
    while (inputFile.read(reinterpret_cast<char*>(&applicant), sizeof(Applicant))) {
        if (currentPosition != position) {
            tempFile.write(reinterpret_cast<const char*>(&applicant), sizeof(Applicant));
        }
        ++currentPosition;
    }

    inputFile.close();
    tempFile.close();

    if (remove(filename.c_str()) != 0) {
        std::cerr << "Error deleting file: " << filename << std::endl;
        return;
    }

    if (rename("temp.bin", filename.c_str()) != 0) {
        std::cerr << "Error renaming file." << std::endl;
        return;
    }

    std::cout << "Applicant at position " << position << " has been deleted." << std::endl;
}

void addApplicant(const std::string& filename, const std::string& lastName) {
    std::ifstream inputFile(filename, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::ofstream tempFile("temp.bin", std::ios::binary);
    if (!tempFile) {
        std::cerr << "Error creating temporary file." << std::endl;
        inputFile.close();
        return;
    }

    Applicant applicant;
    bool added = false;
    while (inputFile.read(reinterpret_cast<char*>(&applicant), sizeof(Applicant))) {
        tempFile.write(reinterpret_cast<const char*>(&applicant), sizeof(Applicant));

        if (applicant.lastName == lastName && !added) {
            Applicant newApplicant;
            newApplicant.lastName = "New";
            newApplicant.firstName = "Applicant";
            newApplicant.patronymic = "Added";
            newApplicant.birthYear = 2000;
            newApplicant.examScores[0] = 90;
            newApplicant.examScores[1] = 80;
            newApplicant.examScores[2] = 85;
            newApplicant.averageGrade = 85.0f;

            tempFile.write(reinterpret_cast<const char*>(&newApplicant), sizeof(Applicant));
            added = true;
        }
    }

    inputFile.close();
    tempFile.close();

    if (remove(filename.c_str()) != 0) {
        std::cerr << "Error deleting file: " << filename << std::endl;
        return;
    }

    if (rename("temp.bin", filename.c_str()) != 0) {
        std::cerr << "Error renaming file." << std::endl;
        return;
    }

    if (added) {
        std::cout << "New applicant has been added after the applicant with last name: " << lastName << std::endl;
    } else {
        std::cout << "No applicant found with last name: " << lastName << std::endl;
    }
}

int main() {
    const std::string filename = "applicants.bin";

    std::ofstream outputFile(filename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error creating file: " << filename << std::endl;
        return 1;
    }

    Applicant applicant1;
    applicant1.lastName = "Smith";
    applicant1.firstName = "John";
    applicant1.patronymic = "Robert";
    applicant1.birthYear = 2002;
    applicant1.examScores[0] = 80;
    applicant1.examScores[1] = 85;
    applicant1.examScores[2] = 90;
    applicant1.averageGrade = 85.0f;

    Applicant applicant2;
    applicant2.lastName = "Johnson";
    applicant2.firstName = "Emily";
    applicant2.patronymic = "Anne";
    applicant2.birthYear = 2001;
    applicant2.examScores[0] = 75;
    applicant2.examScores[1] = 90;
    applicant2.examScores[2] = 85;
    applicant2.averageGrade = 83.3f;

    outputFile.write(reinterpret_cast<const char*>(&applicant1), sizeof(Applicant));
    outputFile.write(reinterpret_cast<const char*>(&applicant2), sizeof(Applicant));

    outputFile.close();

    std::cout << "Contents of the file:" << std::endl;
    printApplicants(filename);
    std::cout << std::endl;

    int positionToDelete = 1;
    deleteApplicant(filename, positionToDelete);
    std::cout << std::endl;

    std::string lastNameToAddAfter = "Smith";
    addApplicant(filename, lastNameToAddAfter);
    std::cout << std::endl;

    std::cout << "Contents of the file after deletion and addition:" << std::endl;
    printApplicants(filename);

    return 0;
}