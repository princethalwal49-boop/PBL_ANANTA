#ifndef MATCHING_H
#define MATCHING_H
#include "Student.h"
struct Recommendation 
{ 
    Student* student; 
    int score; 
};
class MatchingSystem 
{
private:
    static const int HASH_BUCKETS = 257;
    static const int MAX_INDEX_ENTRIES = MAX_STUDENTS * 10;
    struct SkillIndexEntry { char skill[50]; int studentIndex; int next; };
    SkillIndexEntry index[MAX_INDEX_ENTRIES];
    int buckets[HASH_BUCKETS];
    int indexCount;
    int indexedRevision;

    unsigned int hash(const char* skill) const;
    void normalizeSkill(const char* source, char destination[]) const;
    void buildIndex(StudentManager& students);
    int scoreCandidate(const Student& learner, const Student& candidate) const;
    void insertSorted(Recommendation results[], int& count, int maximum, const Recommendation& item) const;
public:
    MatchingSystem();
    int findMatches(Student* learner,StudentManager& students,const char* skill,Recommendation results[],int maximum);
};
#endif
