#include "Rating.h"
#include <fstream>

using namespace std;

RatingSystem::RatingSystem() : head(0) {}
RatingSystem::~RatingSystem() 
{ 
    clear(); 
}
bool RatingSystem::alreadyRated(int raterId, int ratedId) const 
{ 
    RatingRecord* current = head; 
    while (current) 
    { 
        if (current->raterId == raterId && current->ratedId == ratedId) return true; 
        current = current->next; 
    } 
    return false; 
}
bool RatingSystem::submit(int raterId, Student& ratedStudent, int score, const RequestQueue& requests, const StudentGraph& graph) 
{
    if (score < 1 || score > 5 || raterId == ratedStudent.getId() || alreadyRated(raterId, ratedStudent.getId()) ||
        !requests.hasAcceptedPair(raterId, ratedStudent.getId()) || !graph.areConnected(raterId, ratedStudent.getId())) return false;
    RatingRecord* node = new RatingRecord; 
    node->raterId = raterId; 
    node->ratedId = ratedStudent.getId(); 
    node->score = score; 
    node->next = head; 
    head = node;
    ratedStudent.addRating(score); 
    
    return true;
}
int RatingSystem::getAll(RatingRecord results[], int maximum) const 
{ 
    int count = 0; 
    RatingRecord* current = head; 
    while (current && count < maximum) 
    { 
        results[count] = *current; 
        results[count++].next = 0; 
        current = current->next; 
    } 
    return count; 
}
void RatingSystem::removeForStudent(int studentId) 
{ 
    RatingRecord* current = head; 
    RatingRecord* previous = 0; 
    while (current) 
    { 
        if (current->raterId == studentId || current->ratedId == studentId) 
        { 
            RatingRecord* deleted = current; 
            current = current->next; 
            if (previous) previous->next = current; 
            else head = current; 
            delete deleted;
        } else 
        { 
            previous = current; 
            current = current->next; 
        } 
    } 
}
void RatingSystem::recalculate(StudentManager& manager) const 
{
    for (int i = 0; i < manager.getCount(); ++i) manager.getStudentAt(i)->clearRatings();
    RatingRecord* current = head; 
    while (current) 
    { 
        Student* student = manager.findById(current->ratedId); 
        if (student) student->addRating(current->score); 
        current = current->next; 
    }
    for (int i = 0; i < manager.getCount(); ++i) 
    { 
        Student* student = manager.getStudentAt(i); 
        // A student is warned before an automatic ban can occur.
        student->setFlagged(student->getRatingCount() >= 2 && student->getAverageRating() <= 2.5f); 
        student->setBanned(student->getRatingCount() >= 4 && student->getAverageRating() <= 1.5f); 
    }
}
bool RatingSystem::saveToFile() const 
{ 
    ofstream file("ratings.txt"); 
    if (!file) return false; 
    RatingRecord* current = head; 
    while (current) 
    { 
        file << current->raterId << '|' << current->ratedId << '|' << current->score << '\n'; current = current->next; 
    } 
    return file.good(); 
}
bool RatingSystem::loadFromFile() 
{ 
    clear();
    ifstream file("ratings.txt"); 
    if (!file) return true; 
    int rater, rated, score; 
    char firstDivider, secondDivider; 
    while (file >> rater >> firstDivider >> rated >> secondDivider >> score) 
    { 
        if (firstDivider != '|' || secondDivider != '|' || rater <= 0 || rated <= 0 || rater == rated || score < 1 || score > 5 || alreadyRated(rater, rated)) continue;
        RatingRecord* node = new RatingRecord; 
        node->raterId = rater; 
        node->ratedId = rated; 
        node->score = score; 
        node->next = head; 
        head = node; 
    } 
    return true; 
}
void RatingSystem::clear() 
{ 
    while (head) 
    { 
        RatingRecord* deleted = head; 
        head = head->next; 
        delete deleted; 
    } 
}
