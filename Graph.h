#ifndef GRAPH_H
#define GRAPH_H

const int MAX_GRAPH_STUDENTS = 100;
struct GraphNode { int id; GraphNode* next; };
class StudentGraph {
private:
    int ids[MAX_GRAPH_STUDENTS];
    GraphNode* links[MAX_GRAPH_STUDENTS];
    int count;
    int indexOf(int id) const;
    void clear(GraphNode* node);
public:
    StudentGraph();
    ~StudentGraph();
    bool addStudent(int id);
    bool connect(int firstId,int secondId);
    void display(int id) const;
};

#endif
