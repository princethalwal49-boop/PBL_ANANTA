#ifndef REPORT_H
#define REPORT_H

const int MAX_REPORTS = 100;

struct PeerReport
{
    int id;
    int reporterId;
    int reportedId;
    char reason[100];
    PeerReport* next;
};

class ReportSystem
{
private:
    PeerReport* head;
    int nextId;
public:
    ReportSystem();
    ~ReportSystem();
    bool submit(int reporterId, int reportedId, const char* reason);
    int getAll(PeerReport results[], int maximum) const;
    void removeForStudent(int studentId);
    bool loadFromFile();
    bool saveToFile() const;
    void clear();
};

#endif
