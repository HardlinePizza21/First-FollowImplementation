#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "construirProducciones.cpp"


using namespace std;

int main()
{
    int n;
    cin >> n; //Numero de casos

    int m;
    cin >> m; //Numero lineas de la gramatica 


	//Lectura de la gramatica y creacion del diccionario que representa los first

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

		//Implementacion del algoritmo para calcular los firsts


        bool changes = true;

        while (changes)
        {
            changes = false;

            for (const auto& par : gramatica) {

                cout << "No terminal: " << par.first << " Producciones: ";

                for (int i = 0; i < par.second.size(); i++)
                {



                     cout << par.second[i] << " ";
                }

				cout << endl;

            }
        }
    }
    return 0;
}
