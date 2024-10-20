#include "existeEpsilon.h"
#include <vector>

// Verifica si un vector de caracteres esta epsilon(e)

using namespace std;

bool existeEpsilon(vector<char>& first)
{

    for(int i = 0; i < first.size(); i++)
    {
        if(first[i] == 'e')
        {
            return true;
        }
    }

    return false;

}
