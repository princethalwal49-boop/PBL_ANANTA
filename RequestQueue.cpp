#include "RequestQueue.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

RequestQueue::RequestQueue() : front(0), rear(0), nextId(1) {}
RequestQueue::~RequestQueue() 
{ 
    clear(); 
}

bool RequestQueue::send(int senderId, int receiverId, const char* topic) 
{
    if (senderId <= 0 || receiverId <= 0 || senderId == receiverId || !topic || topic[0] == '\0' || strchr(topic, '|')) return false;
    LearningRequest* node = new LearningRequest;
    node->id = nextId++; 
    node->senderId = senderId; 
    node->receiverId = receiverId;
    strncpy(node->topic, topic, 49); 
    node->topic[49] = '\0';
    node->status = PENDING; 
    node->next = 0;
    if (!rear) front = rear = node; 
    else 
    { 
        rear->next = node; 
        rear = node; 
    }
    return true;
}

bool RequestQueue::respond(int requestId, int receiverId, bool accept) 
{
    LearningRequest* current = front;
    while (current) 
    {
        if (current->id == requestId && current->receiverId == receiverId && current->status == PENDING) 
        {
            current->status = accept ? ACCEPTED : REJECTED; 
            return true;
        }
        current = current->next;
    }
    return false;
}

int RequestQueue::getForReceiver(int receiverId, LearningRequest results[], int maximum, bool pendingOnly) const {
    int count = 0; 
    LearningRequest* current = front;
    while (current && count < maximum) 
    {
        if (current->receiverId == receiverId && (!pendingOnly || current->status == PENDING)) 
        {
            results[count] = *current; 
            results[count++].next = 0;
        }
        current = current->next;
    }
    return count;
}

int RequestQueue::getAll(LearningRequest results[], int maximum) const 
{
    int count = 0; 
    LearningRequest* current = front;
    while (current && count < maximum) 
    { 
        results[count] = *current;
        results[count++].next = 0; 
        current = current->next; 
    }
    return count;
}

bool RequestQueue::hasAcceptedPair(int firstId, int secondId) const 
{
    LearningRequest* current = front;
    while (current) 
    {
        if (current->status == ACCEPTED && ((current->senderId == firstId && current->receiverId == secondId) || (current->senderId == secondId && current->receiverId == firstId))) return true;
        current = current->next;
    }
    return false;
}

void RequestQueue::removeForStudent(int studentId) 
{
    LearningRequest* current = front; 
    LearningRequest* previous = 0;
    while (current) 
    {
        if (current->senderId == studentId || current->receiverId == studentId) 
        {
            LearningRequest* deleted = current; 
            current = current->next;
            if (previous) previous->next = current; 
            else front = current;
            if (deleted == rear) rear = previous; 
            delete deleted;
        } else 
        {
            previous = current; 
            current = current->next; 
        }
    }
}

bool RequestQueue::saveToFile() const 
{
    ofstream file("requests.txt"); 
    if (!file) return false;
    LearningRequest* current = front;
    while (current) 
    { 
        file << current->id << '|' << current->senderId << '|' << current->receiverId << '|' << current->topic << '|' << current->status << '\n'; 
        current = current->next; 
    }
    return file.good();
}

bool RequestQueue::loadFromFile() 
{
    ifstream file("requests.txt"); 
    if (!file) return true;
    char line[200];
    while (file.getline(line, 200)) 
    {
        char* id = strtok(line, "|"); 
        char* sender = strtok(0, "|"); 
        char* receiver = strtok(0, "|"); 
        char* topic = strtok(0, "|"); 
        char* status = strtok(0, "|");
        if (!id || !sender || !receiver || !topic || !status) continue;
        LearningRequest* node = new LearningRequest;
        node->id = atoi(id); 
        node->senderId = atoi(sender); 
        node->receiverId = atoi(receiver); 
        strncpy(node->topic, topic, 49); 
        node->topic[49] = '\0'; 
        node->status = (RequestStatus)atoi(status); 
        node->next = 0;
        if (!rear) front = rear = node; 
        else 
        { 
            rear->next = node; rear = node; 
        }
        if (node->id >= nextId) nextId = node->id + 1;
    }
    return true;
}

void RequestQueue::clear() 
{ 
    while (front) 
    { 
        LearningRequest* deleted = front; 
        front = front->next; 
        delete deleted; 
    } 
    rear = 0; 
}
