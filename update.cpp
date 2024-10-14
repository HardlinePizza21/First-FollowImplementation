#include <algorithm>  // Para std::find
#include <vector>


bool update(std::vector<char>& vector2, std::vector<char>& vector1) 
{
    bool changes = false;
    
    for (const char& elem : vector1) 
    {
        if (std::find(vector2.begin(), vector2.end(), elem) == vector2.end() && elem != 'e') {
            vector2.push_back(elem);
            changes = true;
        }
    }

    return changes;
}
