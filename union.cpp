#include "union.h"
#include <algorithm>  // Para std::find
#include <vector>

//Actualiza el vector2 con todos lo elementos del vector1 que no tenga

bool setsUnion(std::vector<char>& vector2, std::vector<char>& vector1) 
{
    bool changes = false;
    
    for (const char& elem : vector1) 
    {
        if (std::find(vector2.begin(), vector2.end(), elem) == vector2.end()) {
            vector2.push_back(elem);
            changes = true;
        }
    }

    return changes;
}
