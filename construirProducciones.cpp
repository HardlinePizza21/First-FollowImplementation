#include <vector>
#include <string>

using namespace std;

vector<string> construirProducciones(string producciones)
{

	int corte = 1;

	vector<string> producciones_;

	for (int i = 1; i < producciones.length(); i++)
	{

		if (producciones[i] == ' ')
		{
			int longitudProduccion = i - corte;
			producciones_.push_back(producciones.substr(corte, longitudProduccion));

			corte = i + 1;

		}

		if (i == producciones.length() - 1)
		{
			int longitudProduccion = i - corte;
			producciones_.push_back(producciones.substr(corte, longitudProduccion + 1));
		}
	}

	return producciones_;
}
