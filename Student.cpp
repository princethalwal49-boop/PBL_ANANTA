#include "Student.h"
#include "FileStorage.h"
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

namespace {
void copyText(char* destination, const char* source, int size) 
{
    strncpy(destination, source ? source : "", size - 1);
    destination[size - 1] = '\0';
}
}

Student::Student() : id(0), semester(0), averageRating(0.0f), ratingCount(0), flagged(false), banned(false), manuallyBanned(false) 
{
    name[0] = branch[0] = username[0] = password[0] = teachSkill[0] = '\0';
}

Student::Student(int studentId, const char* studentName, const char* studentBranch,
                 int studentSemester, const char* user, const char* pass, const char* skill)
    : id(studentId), semester(studentSemester), averageRating(0.0f), ratingCount(0), flagged(false), banned(false), manuallyBanned(false) {
    copyText(name, studentName, 60);
    copyText(branch, studentBranch, 40);
    copyText(username, user, 30);
    copyText(password, pass, 30);
    copyText(teachSkill, skill, 50);
}

int Student::getId() const 
{ 
    return id; 
}
const char* Student::getName() const 
{ 
    return name; 
}
const char* Student::getBranch() const 
{ 
    return branch; 
}
int Student::getSemester() const 
{ 
    return semester; 
}
const char* Student::getUsername() const 
{ 
    return username; 
}
const char* Student::getPassword() const 
{ 
    return password; 
}
const char* Student::getTeachSkill() const 
{ 
    return teachSkill; 
}
bool Student::passwordMatches(const char* enteredPassword) const 
{
    return enteredPassword && strcmp(password, enteredPassword) == 0;
}
float Student::getAverageRating() const 
{ 
    return averageRating; 
}
int Student::getRatingCount() const 
{ 
    return ratingCount; 
}
bool Student::isFlagged() const 
{ 
    return flagged; 
}
bool Student::isBanned() const 
{ 
    return banned || manuallyBanned; 
}
bool Student::addRating(int score) 
{
    if (score < 1 || score > 5) return false;
    averageRating = ((averageRating * ratingCount) + score) / (ratingCount + 1);
    ++ratingCount;

    return true;
}
void Student::clearRatings() 
{ 
    averageRating = 0.0f; 
    ratingCount = 0; 
}
void Student::setFlagged(bool value) 
{ 
    flagged = value; 
}
void Student::setBanned(bool value) 
{ 
    banned = value; 
}
void Student::setManualBanned(bool value) 
{ 
    manuallyBanned = value; 
}
bool Student::isManuallyBanned() const 
{ 
    return manuallyBanned; 
}

void Student::displayProfile() const 
{
    cout << "\n========== STUDENT PROFILE ==========\n";
    cout << "Student ID : " << id << "\n";
    cout << "Name       : " << name << "\n";
    cout << "Branch     : " << branch << "\n";
    cout << "Semester   : " << semester << "\n";
    cout << "Username   : " << username << "\n";
    cout << "Can teach  : " << teachSkill << "\n";
    cout << "Rating     : " << fixed << setprecision(1) << averageRating << "/5.0\n";
}

StudentManager::StudentManager() : studentCount(0) {}

bool StudentManager::textIsValid(const char* text) const 
{
    return text && text[0] != '\0' && strchr(text, '|') == 0;
}

bool StudentManager::registerStudent(int id, const char* name, const char* branch, int semester,
                                     const char* username, const char* password, const char* teachSkill) {
    if (studentCount >= MAX_STUDENTS || id <= 0 || semester < 1 || semester > 8 ||
        !textIsValid(name) || !textIsValid(branch) || !textIsValid(username) || !textIsValid(password) || !textIsValid(teachSkill) ||
        findById(id) || findByUsername(username)) {
        return false;
    }
    students[studentCount++] = Student(id, name, branch, semester, username, password, teachSkill);
    return true;
}

Student* StudentManager::login(const char* username, const char* password) 
{
    Student* student = findByUsername(username);
    return student && student->passwordMatches(password) ? student : 0;
}

Student* StudentManager::findById(int id) 
{
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].getId() == id) return &students[i];
    }
    return 0;
}

Student* StudentManager::findByUsername(const char* username) 
{
    if (!username) return 0;
    for (int i = 0; i < studentCount; ++i) {
        if (strcmp(students[i].getUsername(), username) == 0) return &students[i];
    }
    return 0;
}

Student* StudentManager::getStudentAt(int index) 
{
    if (index < 0 || index >= studentCount) return 0;
    return &students[index];
}

bool StudentManager::removeById(int id) 
{
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].getId() == id) {
            for (int j = i; j < studentCount - 1; ++j) students[j] = students[j + 1];
            --studentCount;
            students[studentCount] = Student();
            return true;
        }
    }
    return false;
}

int StudentManager::getCount() const 
{ 
    return studentCount; 
}

bool StudentManager::loadFromFile() 
{
    studentCount = FileStorage::loadStudents(students, MAX_STUDENTS);
    return studentCount >= 0;
}

bool StudentManager::saveToFile() const 
{
    return FileStorage::saveStudents(students, studentCount);
}
