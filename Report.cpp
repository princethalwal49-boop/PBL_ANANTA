#include "Report.h"
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

ReportSystem::ReportSystem() : head(0), nextId(1) {}
ReportSystem::~ReportSystem() { clear(); }

bool ReportSystem::submit(int reporterId, int reportedId, const char* reason)
{
    if (reporterId <= 0 || reportedId <= 0 || reporterId == reportedId || !reason || !reason[0] || strchr(reason, '|')) return false;
    for (PeerReport* current = head; current; current = current->next)
        if (current->reporterId == reporterId && current->reportedId == reportedId) return false;
    PeerReport* report = new PeerReport;
    report->id = nextId++;
    report->reporterId = reporterId;
    report->reportedId = reportedId;
    strncpy(report->reason, reason, 99);
    report->reason[99] = '\0';
    report->next = head;
    head = report;
    return true;
}

int ReportSystem::getAll(PeerReport results[], int maximum) const
{
    int count = 0;
    for (PeerReport* current = head; current && count < maximum; current = current->next)
    {
        results[count] = *current;
        results[count++].next = 0;
    }
    return count;
}

void ReportSystem::removeForStudent(int studentId)
{
    PeerReport* current = head;
    PeerReport* previous = 0;
    while (current)
    {
        if (current->reporterId == studentId || current->reportedId == studentId)
        {
            PeerReport* deleted = current;
            current = current->next;
            if (previous) previous->next = current;
            else head = current;
            delete deleted;
        }
        else { previous = current; current = current->next; }
    }
}

bool ReportSystem::loadFromFile()
{
    clear();
    nextId = 1;
    ifstream file("reports.txt");
    if (!file) return true;
    char line[250];
    while (file.getline(line, sizeof(line)))
    {
        char* id = strtok(line, "|");
        char* reporter = strtok(0, "|");
        char* reported = strtok(0, "|");
        char* reason = strtok(0, "|");
        if (!id || !reporter || !reported || !reason || !reason[0]) continue;
        int reportId = atoi(id), reporterId = atoi(reporter), reportedId = atoi(reported);
        if (reportId <= 0 || reporterId <= 0 || reportedId <= 0 || reporterId == reportedId) continue;
        PeerReport* report = new PeerReport;
        report->id = reportId; report->reporterId = reporterId; report->reportedId = reportedId;
        strncpy(report->reason, reason, 99); report->reason[99] = '\0';
        report->next = head; head = report;
        if (reportId >= nextId) nextId = reportId + 1;
    }
    return !file.bad();
}

bool ReportSystem::saveToFile() const
{
    ofstream file("reports.txt");
    if (!file) return false;
    for (PeerReport* current = head; current; current = current->next)
        file << current->id << '|' << current->reporterId << '|' << current->reportedId << '|' << current->reason << '\n';
    return file.good();
}

void ReportSystem::clear()
{
    while (head) { PeerReport* deleted = head; head = head->next; delete deleted; }
}
