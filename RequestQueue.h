#ifndef REQUESTQUEUE_H
#define REQUESTQUEUE_H

const int MAX_REQUESTS = 100;

enum RequestStatus { PENDING, ACCEPTED, REJECTED };

struct LearningRequest 
{
    int id;
    int senderId;
    int receiverId;
    char topic[50];
    RequestStatus status;
    LearningRequest* next;
};

class RequestQueue {
private:
    LearningRequest* front;
    LearningRequest* rear;
    int nextId;
public:
    RequestQueue();
    ~RequestQueue();
    bool send(int senderId, int receiverId, const char* topic);
    bool respond(int requestId, int receiverId, bool accept);
    int getForReceiver(int receiverId, LearningRequest results[], int maximum, bool pendingOnly) const;
    int getAll(LearningRequest results[], int maximum) const;
    bool hasAcceptedPair(int firstId, int secondId) const;
    void removeForStudent(int studentId);
    bool loadFromFile();
    bool saveToFile() const;
    void clear();
};

#endif
