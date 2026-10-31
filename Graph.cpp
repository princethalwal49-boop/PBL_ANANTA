#include "Graph.h"
#include <iostream>
#include <fstream>
using namespace std;
StudentGraph::StudentGraph():count(0)
{
    for(int i=0;i<MAX_GRAPH_STUDENTS;i++)
    links[i]=0;
}
StudentGraph::~StudentGraph()
{
    for(int i=0;i<count;i++)clear(links[i]);
}
int StudentGraph::indexOf(int id)const
{
    for(int i=0;i<count;i++)
        if(ids[i]==id)return i;
    return -1;
}
void StudentGraph::clear(GraphNode* n)
{
    while(n)
    {
        GraphNode* d=n;n=n->next;
        delete d;
    }
}
bool StudentGraph::addStudent(int id)
{
    if(id<=0||indexOf(id)!=-1||count>=MAX_GRAPH_STUDENTS)return false;
    ids[count]=id;
    links[count]=0;
    count++;
    return true;
}
bool StudentGraph::removeStudent(int id)
{
    int index=indexOf(id);
    if(index<0)return false;
    clear(links[index]);
    links[index]=0;
    for(int i=0;i<count;i++)
    {
        GraphNode* current=links[i];
        GraphNode* previous=0;
        while(current)
        {
            if(current->id==id)
            {
                GraphNode* deleted=current;
                current=current->next;
                if(previous)previous->next=current;
                else links[i]=current;
                delete deleted;
            }
            else { previous=current; current=current->next; }
        }
    }
    for(int i=index;i<count-1;i++) { ids[i]=ids[i+1]; links[i]=links[i+1]; }
    --count;
    links[count]=0;
    return true;
}
bool StudentGraph::areConnected(int a,int b)const
{
    int x=indexOf(a);
    if(x<0)return false;
    for(GraphNode* n=links[x];n;n=n->next)if(n->id==b)return true;
    return false;
}
bool StudentGraph::connect(int a,int b)
{
    int x=indexOf(a),y=indexOf(b);
    if(x<0||y<0||a==b)return false;
    if(areConnected(a,b))return true;
    GraphNode* n;
    n=new GraphNode;
    n->id=b;
    n->next=links[x];
    links[x]=n;
    n=new GraphNode;
    n->id=a;
    n->next=links[y];
    links[y]=n;
    
    return true;
}
void StudentGraph::display(int id)const
{
    int x=indexOf(id);
    if(x<0||!links[x])
    {
        cout<<"No connections.\n";
        return;
    }
    cout<<"Connected student IDs: ";
    for(GraphNode* n=links[x];n;n=n->next)
        cout<<n->id<<" ";
    cout<<"\n";
    }
bool StudentGraph::saveToFile()const
{
    ofstream file("connections.txt");
    if(!file)return false;
    for(int i=0;i<count;i++)
        for(GraphNode* n=links[i];n;n=n->next)
            if(ids[i]<n->id)file<<ids[i]<<'|'<<n->id<<'\n';
    return file.good();
}
bool StudentGraph::loadFromFile()
{
    ifstream file("connections.txt");
    if(!file)return true;
    int first,second; char divider;
    while(file>>first>>divider>>second)
        if(divider=='|')connect(first,second);
    return !file.bad();
}
