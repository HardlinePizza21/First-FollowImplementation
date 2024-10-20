#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "update.cpp"
#include "construirProducciones.cpp"
#include "existeEpsilon.cpp"
#include "firstOfString.cpp"
#include "union.cpp"

using namespace std;

int main()
{

    int n;
    cin >> n; // Numero de casos

    int m;
    cin >> m; // Numero lineas de la gramatica

    // Lectura de la gramatica y creacion del diccionario que representa los first

    for (int i = 0; i < n; i++)
    {
        map<char, vector<string>> gramatica;
        map<char, vector<char>> firsts;
        map<char, vector<char>> follows;

        for (int j = 0; j < m; j++)
        {

            string noTerminal;
            cin >> noTerminal;

            string producciones;
            getline(cin, producciones);

            vector<string> producciones_ = construirProducciones(producciones);

            gramatica[noTerminal[0]] = producciones_;
            firsts[noTerminal[0]] = vector<char>();
            follows[noTerminal[0]] = vector<char>();
        }

        // Implementacion del algoritmo para calcular los firsts

        bool changes = true;

        while (changes)
        {
            changes = false;

            for (const auto &par : gramatica)
            {

                for (int i = 0; i < par.second.size(); i++)
                {

                    for (int j = 0; j < par.second[i].length(); j++)
                    {

                        if (!isupper(par.second[i][j]))
                        {
                            if (find(firsts[par.first].begin(), firsts[par.first].end(), par.second[i][j]) == firsts[par.first].end())
                            {
                                // Solo agregar el carácter si no está ya presente
                                firsts[par.first].push_back(par.second[i][j]);
                                changes = true;
                            }

                            break;
                        }
                        else
                        {
                            if (changes)
                            {
                                update(firsts[par.first], firsts[par.second[i][j]]);
                            }
                            else
                            {
                                changes = update(firsts[par.first], firsts[par.second[i][j]]);
                            }

                            if (!existeEpsilon(firsts[par.second[i][j]]))
                            {
                                break;
                            }
                            else
                            {

                                if (j + 1 == par.second[i].length())
                                {
                                    if (find(firsts[par.first].begin(), firsts[par.first].end(), 'e') == firsts[par.first].end())
                                    {
                                        firsts[par.first].push_back('e');
                                        changes = true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Calculando el first de cada producción

        for (const auto &par : gramatica)
        {
            for (int j = 0; j < par.second.size(); j++)
            {

                vector<char> firstOfTheString = firstOfString(par.second[j], firsts);

                cout << "firstString(" << par.second[j] << ") = {";

                for (int y = 0; y < firstOfTheString.size(); y++)
                {
                    cout << " " << firstOfTheString[y];
                }

                cout << "}" << endl;
            }
        }

        // Implementacion del algoritmo para calcular los follows

        bool changes2 = true;

        follows['S'].push_back('$');

        while (changes2)
        {
            changes2 = false;

            for (const auto &par : gramatica)
            {
                for (int i = 0; i < par.second.size(); i++)
                {
                    for (int j = 0; j < par.second[i].length(); j++)
                    {
                        if (isupper(par.second[i][j]))
                        {

                            if (j + 1 == par.second[i].length())
                            {

                                changes2 = setsUnion(follows[par.second[i][j]], follows[par.first]);
                                break;
                            }

                            vector<char> beta = firstOfString(par.second[i].substr(j + 1), firsts);

                            changes2 = update(follows[par.second[i][j]], beta);

                            if (existeEpsilon(beta))
                            {
                                changes2 = setsUnion(follows[par.second[i][j]], follows[par.first]);
                            }
                        }
                    }
                }
            }
        }

        // Impresion de first

        for (const auto &par : firsts)
        {

            cout << "first(" << par.first << "): {";

            for (int i = 0; i < par.second.size(); i++)
            {
                cout << " " << par.second[i];
            }

            cout << " }" << endl;
        }

        // Impresion de follow

        for (const auto &par : follows)
        {

            cout << "Follow(" << par.first << "): { ";

            for (int x = 0; x < par.second.size(); x++)
            {
                cout << par.second[x] << " ";
            }

            cout << " }" << endl;
        }
    }
    return 0;
}

// 1
// 4
// A aaA e
// B Bb e
// C cCd S e
// S ABC

// 1
// 6
// S AB ICF
// A nA mA e
// B BB p
// I [
// F ]
// C C;C n

// 1
// 3
// S AB
// A aA a
// B bBc bc
