#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include "construirProducciones.cpp"
#include "update.cpp"
#include "existeEpsilon.cpp"

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

        for (int j = 0; j < m; j++)
        {

            string noTerminal;
            cin >> noTerminal;

            string producciones;
            getline(cin, producciones);

            vector<string> producciones_ = construirProducciones(producciones);

            gramatica[noTerminal[0]] = producciones_;
            firsts[noTerminal[0]] = vector<char>();
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
                            if (std::find(firsts[par.first].begin(), firsts[par.first].end(), par.second[i][j]) == firsts[par.first].end())
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
                                    if (std::find(firsts[par.first].begin(), firsts[par.first].end(), 'e') == firsts[par.first].end())
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

        // Impresion de los cambios

        for (const auto &par : firsts)
        {

            cout << "first(" << par.first << "): { ";

            for (int i = 0; i < par.second.size(); i++)
            {
                cout << par.second[i] << " ";
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