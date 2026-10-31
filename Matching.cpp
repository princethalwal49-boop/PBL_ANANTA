#include "Matching.h"
#include <cstring>
#include <cctype>
#include <cstdlib>

namespace {
bool sameText(const char* first, const char* second)
{
    if (!first || !second) return false;
    while (*first && *second) {
        if (std::tolower(static_cast<unsigned char>(*first)) != std::tolower(static_cast<unsigned char>(*second))) return false;
        ++first; ++second;
    }
    return *first == '\0' && *second == '\0';
}
}
MatchingSystem::MatchingSystem() : indexCount(0), indexedRevision(-1)
{
    for(int i=0;i<HASH_BUCKETS;++i)buckets[i]=-1;
}
unsigned int MatchingSystem::hash(const char* skill)const
{
    unsigned int value=2166136261u;
    for(;*skill;++skill) value=(value^static_cast<unsigned char>(*skill))*16777619u;
    return value%HASH_BUCKETS;
}
void MatchingSystem::normalizeSkill(const char* source,char destination[])const
{
    if(!source) { destination[0]='\0'; return; }
    while(*source&&isspace(static_cast<unsigned char>(*source)))++source;
    int length=0;
    while(*source&&length<49)
    {
        destination[length++]=static_cast<char>(tolower(static_cast<unsigned char>(*source++)));
    }
    while(length>0&&isspace(static_cast<unsigned char>(destination[length-1])))--length;
    destination[length]='\0';
}
void MatchingSystem::buildIndex(StudentManager& students)
{
    for(int i=0;i<HASH_BUCKETS;++i)buckets[i]=-1;
    indexCount=0;
    for(int studentIndex=0;studentIndex<students.getCount();++studentIndex)
    {
        Student* student=students.getStudentAt(studentIndex);
        char listed[50];
        strncpy(listed,student->getTeachSkill(),49); listed[49]='\0';
        for(char* token=strtok(listed,",");token&&indexCount<MAX_INDEX_ENTRIES;token=strtok(0,","))
        {
            char normalized[50]; normalizeSkill(token,normalized);
            if(!normalized[0])continue;
            unsigned int bucket=hash(normalized);
            strncpy(index[indexCount].skill,normalized,49); index[indexCount].skill[49]='\0';
            index[indexCount].studentIndex=studentIndex;
            index[indexCount].next=buckets[bucket];
            buckets[bucket]=indexCount++;
        }
    }
    indexedRevision=students.getRevision();
}
int MatchingSystem::scoreCandidate(const Student& learner,const Student& candidate)const
{
    int rating=candidate.getRatingCount() ? static_cast<int>(candidate.getAverageRating()*10.0f+0.5f) : 30;
    int semesterGap=abs(learner.getSemester()-candidate.getSemester());
    return 100+rating+(sameText(learner.getBranch(),candidate.getBranch())?15:0)+(semesterGap<5?(5-semesterGap)*2:0);
}
void MatchingSystem::insertSorted(Recommendation results[],int& count,int maximum,const Recommendation& item)const
{
    int position=count;
    while(position>0&&(results[position-1].score<item.score ||
          (results[position-1].score==item.score && results[position-1].student->getId()>item.student->getId())))
    {
        if(position<maximum)results[position]=results[position-1];
        --position;
    }
    if(position<maximum)results[position]=item;
    if(count<maximum)++count;
}
int MatchingSystem::findMatches(Student* learner,StudentManager& students,const char* skill,Recommendation results[],int maximum)
{
    if(!learner||!skill||!skill[0]||!results||maximum<=0)return 0;
    if(indexedRevision!=students.getRevision())buildIndex(students);
    char requested[50]; normalizeSkill(skill,requested);
    if(!requested[0])return 0;
    int count=0;
    for(int entry=buckets[hash(requested)];entry!=-1;entry=index[entry].next)
    {
        if(strcmp(index[entry].skill,requested)!=0)continue;
        Student* candidate=students.getStudentAt(index[entry].studentIndex);
        if(candidate!=learner&&!candidate->isBanned())
        {
            Recommendation item={candidate,scoreCandidate(*learner,*candidate)};
            insertSorted(results,count,maximum,item);
        }
    }
    return count;
}
