#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include "Student.h"

class FileStorage 
{
public:
    static bool saveStudents(const Student students[], int count);
    static int loadStudents(Student students[], int maximumStudents);
};

#endif
