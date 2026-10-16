#include "FileStorage.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

namespace {
const char* STUDENT_FILE = "students.txt";
}

bool FileStorage::saveStudents(const Student students[], int count) {
    ofstream file(STUDENT_FILE);
    if (!file) return false;

    for (int i = 0; i < count; ++i) {
        file << students[i].getId() << '|'
             << students[i].getName() << '|'
             << students[i].getBranch() << '|'
             << students[i].getSemester() << '|'
             << students[i].getUsername() << '|'
             << students[i].getPassword() << '|'
             << students[i].getTeachSkill() << '|'
             << students[i].isManuallyBanned() << '\n';
    }
    return file.good();
}

int FileStorage::loadStudents(Student students[], int maximumStudents) {
    ifstream file(STUDENT_FILE);
    if (!file) return 0;

    int count = 0;
    char line[300];
    while (file.getline(line, 300) && count < maximumStudents) {
        char* idText = strtok(line, "|");
        char* name = strtok(0, "|");
        char* branch = strtok(0, "|");
        char* semesterText = strtok(0, "|");
        char* username = strtok(0, "|");
        char* password = strtok(0, "|");
        char* teachSkill = strtok(0, "|");
        char* manualBan = strtok(0, "|");

        if (!idText || !name || !branch || !semesterText || !username || !password) continue;
        int id = atoi(idText);
        int semester = atoi(semesterText);
        if (id <= 0 || semester < 1 || semester > 8) continue;

        students[count] = Student(id, name, branch, semester, username, password, teachSkill ? teachSkill : "");
        if (manualBan && atoi(manualBan) != 0) students[count].setManualBanned(true);
        ++count;
    }
    return count;
}
