#include <vector>

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
