#include "Graph.h"
#include <iostream>
using namespace std;
StudentGraph::StudentGraph():count(0){for(int i=0;i<MAX_GRAPH_STUDENTS;i++)links[i]=0;}
StudentGraph::~StudentGraph(){for(int i=0;i<count;i++)clear(links[i]);}
int StudentGraph::indexOf(int id)const{for(int i=0;i<count;i++)if(ids[i]==id)return i;return -1;}
void StudentGraph::clear(GraphNode* n){while(n){GraphNode* d=n;n=n->next;delete d;}}
bool StudentGraph::addStudent(int id){if(id<=0||indexOf(id)!=-1||count>=MAX_GRAPH_STUDENTS)return false;ids[count]=id;links[count]=0;count++;return true;}
bool StudentGraph::connect(int a,int b){int x=indexOf(a),y=indexOf(b);if(x<0||y<0||a==b)return false;GraphNode* n=links[x];while(n){if(n->id==b)return true;n=n->next;}n=new GraphNode;n->id=b;n->next=links[x];links[x]=n;n=new GraphNode;n->id=a;n->next=links[y];links[y]=n;return true;}
void StudentGraph::display(int id)const{int x=indexOf(id);if(x<0||!links[x]){cout<<"No connections.\n";return;}cout<<"Connected student IDs: ";for(GraphNode* n=links[x];n;n=n->next)cout<<n->id<<" ";cout<<"\n";}
