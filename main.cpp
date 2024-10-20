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

    // Lectura de la gramatica y creacion del diccionario que representa los first

    for (int h = 0; h < n; h++)
    {

        int m;
        cin >> m; // Numero lineas de la gramatica

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
                                if (changes2)
                                {
                                    setsUnion(follows[par.second[i][j]], follows[par.first]);
                                }
                                else
                                {
                                    changes2 = setsUnion(follows[par.second[i][j]], follows[par.first]);
                                }
                                break;
                            }

                            vector<char> beta = firstOfString(par.second[i].substr(j + 1), firsts);

                            if (changes2)
                            {
                                update(follows[par.second[i][j]], beta);
                            }
                            else
                            {
                                changes2 = update(follows[par.second[i][j]], beta);
                            }

                            if (existeEpsilon(beta))
                            {

                                if (changes2)
                                {
                                    setsUnion(follows[par.second[i][j]], follows[par.first]);
                                }
                                else
                                {
                                    changes2 = setsUnion(follows[par.second[i][j]], follows[par.first]);
                                }
                            }
                        }
                    }
                }
            }
        }

        // Impresion de first

        for (const auto &par : firsts)
        {

            cout << "First(" << par.first << ") = {" << par.second[0];

            for (int i = 1; i < par.second.size(); i++)
            {
                cout << "," << par.second[i];
            }

            cout << "}" << endl;
        }

        // Impresion de follow

        for (const auto &par : follows)
        {

            cout << "Follow(" << par.first << ") = {" << par.second[0];

            for (int x = 1; x < par.second.size(); x++)
            {
                cout << "," << par.second[x];
            }

            cout << "}" << endl;
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

// 3
// 3
// S AB
// A aA a
// B bBc bc
// 6
// S AB ICF
// A nA mA e
// B BB p
// I [
// F ]
// C C;C n
// 4
// A aaA e
// B Bb e
// C cCd S e
// S ABC
