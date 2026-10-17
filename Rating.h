#ifndef RATING_H
#define RATING_H

#include "Student.h"
#include "RequestQueue.h"

struct RatingRecord 
{ 
    int raterId; 
    int ratedId; 
    int score; 
    RatingRecord* next; 
};

class RatingSystem {
private:
    RatingRecord* head;
    bool alreadyRated(int raterId, int ratedId) const;
public:
    RatingSystem();
    ~RatingSystem();
    bool submit(int raterId, Student& ratedStudent, int score, const RequestQueue& requests);
    int getAll(RatingRecord results[], int maximum) const;
    void removeForStudent(int studentId);
    void recalculate(StudentManager& manager) const;
    bool loadFromFile();
    bool saveToFile() const;
    void clear();
};

#endif
