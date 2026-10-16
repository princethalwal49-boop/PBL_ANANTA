#include "SkillTree.h"
#include <iostream>
#include <cstring>
using namespace std;
SkillTree::SkillTree():root(0){}
SkillTree::~SkillTree(){destroy(root);}
SkillNode* SkillTree::create(const char* name){if(!name||!name[0])return 0;SkillNode* n=new SkillNode;strncpy(n->name,name,49);n->name[49]='\0';n->child=0;n->sibling=0;return n;}
SkillNode* SkillTree::find(SkillNode* n,const char* name)const{if(!n)return 0;if(strcmp(n->name,name)==0)return n;SkillNode* x=find(n->child,name);return x?x:find(n->sibling,name);}
void SkillTree::show(SkillNode* n,int level)const{while(n){for(int i=0;i<level;i++)cout<<"  ";cout<<n->name<<"\n";show(n->child,level+1);n=n->sibling;}}
void SkillTree::destroy(SkillNode* n){if(!n)return;destroy(n->child);destroy(n->sibling);delete n;}
bool SkillTree::add(const char* parent,const char* name){if(!name||!name[0]||contains(name))return false;if(!root){if(parent&&parent[0])return false;root=create(name);return root!=0;}SkillNode* p=find(root,parent);if(!p)return false;SkillNode* n=create(name);if(!p->child)p->child=n;else{SkillNode* x=p->child;while(x->sibling)x=x->sibling;x->sibling=n;}return true;}
bool SkillTree::contains(const char* name)const{return find(root,name)!=0;}
void SkillTree::display()const{if(!root)cout<<"No skills.\n";else show(root,0);}
void SkillTree::loadDefaultSkills(){if(root)return;add("","Computer Science");add("Computer Science","Programming");add("Programming","C++");add("Programming","Python");add("Computer Science","Data Structures");add("Data Structures","Array");add("Data Structures","Linked List");add("Data Structures","Queue");}
