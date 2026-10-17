#include "Admin.h"
#include <cstring>

using namespace std;

bool Admin::login(const char* username, const char* password) const 
{
    return username && password && strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0;
}
