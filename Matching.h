#ifndef MATCHING_H
#define MATCHING_H
#include "Student.h"
struct Recommendation { Student* student; int score; };
class MatchingSystem {
private:
    void sort(Recommendation results[],int count) const;
public:
    int findMatches(Student* learner,StudentManager& students,const char* skill,Recommendation results[],int maximum) const;
};
#endif
