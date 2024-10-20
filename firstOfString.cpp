#include <vector>
#include <string>
#include <map>
#include "existeEpsilon.h"
#include "update.h"

using namespace std;
vector<char> firstOfString(string cadena, map<char, vector<char>> &firsts)
{

    vector<char> first;

    for (int i = 0; i < cadena.length(); i++)
    {

        if (!isupper(cadena[i]))
        {
            first.push_back(cadena[i]);
            break;
        }
        else
        {

            update(first, firsts[cadena[i]]);

            if (!existeEpsilon(firsts[cadena[i]]))
            {
                break;
            }

            if (i + 1 == cadena.length())
            {
                first.push_back('e');
            }
        }
    }

    return first;
}
