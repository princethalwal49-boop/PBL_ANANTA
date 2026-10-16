#ifndef STUDENT_H
#define STUDENT_H

const int MAX_STUDENTS = 100;

class Student {
private:
    int id;
    char name[60];
    char branch[40];
    int semester;
    char username[30];
    char password[30];
    char teachSkill[50];
    float averageRating;
    int ratingCount;
    bool flagged;
    bool banned;
    bool manuallyBanned;

public:
    Student();
    Student(int studentId, const char* studentName, const char* studentBranch,
            int studentSemester, const char* user, const char* pass, const char* skill = "");

    int getId() const;
    const char* getName() const;
    const char* getBranch() const;
    int getSemester() const;
    const char* getUsername() const;
    const char* getPassword() const;
    const char* getTeachSkill() const;
    bool passwordMatches(const char* enteredPassword) const;
    float getAverageRating() const;
    int getRatingCount() const;
    bool isFlagged() const;
    bool isBanned() const;
    bool addRating(int score);
    void clearRatings();
    void setFlagged(bool value);
    void setBanned(bool value);
    void setManualBanned(bool value);
    bool isManuallyBanned() const;
    void displayProfile() const;
};

class StudentManager {
private:
    Student students[MAX_STUDENTS];
    int studentCount;

    bool textIsValid(const char* text) const;

public:
    StudentManager();

    bool registerStudent(int id, const char* name, const char* branch, int semester,
                         const char* username, const char* password, const char* teachSkill = "");
    Student* login(const char* username, const char* password);
    Student* findById(int id);
    Student* findByUsername(const char* username);
    Student* getStudentAt(int index);
    bool removeById(int id);
    int getCount() const;

    bool loadFromFile();
    bool saveToFile() const;
};

#endif
