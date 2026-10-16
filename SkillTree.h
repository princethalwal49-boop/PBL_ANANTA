#ifndef SKILLTREE_H
#define SKILLTREE_H

struct SkillNode { char name[50]; SkillNode* child; SkillNode* sibling; };

class SkillTree {
private:
    SkillNode* root;
    SkillNode* create(const char* name);
    SkillNode* find(SkillNode* node, const char* name) const;
    void show(SkillNode* node, int level) const;
    void destroy(SkillNode* node);
public:
    SkillTree();
    ~SkillTree();
    void loadDefaultSkills();
    bool add(const char* parent, const char* name);
    bool contains(const char* name) const;
    void display() const;
};

#endif
