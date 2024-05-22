// Lucas Martin Garcia

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib> // Necesario para std::rand() y std::srand()
#include <algorithm>
#include <random>


using namespace std;

//Se codifica como matriz de adyacencia, triangular, sin repetidos

vector<int> indices_desordenados(int N) {
	// Crear un vector de N indices
	vector<int> indices(N);
	for (int i = 0; i < N; ++i) {
		indices[i] = i;
	}

	// Semilla para el generador de numeros aleatorios
	random_device rd;
	mt19937 g(rd());

	// Desordenar el vector de indices
	shuffle(indices.begin(), indices.end(), g);
	return indices;
}




void generar_par_bueno_malo() {
	int numCases, N, maxM, option;
	string name;
	cout << "Introduce the number of cases to generate:\n";
	cin >> numCases;
	cout << "Introduce the number of nodes:\n";
	cin >> N;
	cout << "Introduce the name of the file:\n";
	cin >> name;

	srand(static_cast<unsigned int>(std::time(nullptr)));

	ofstream dataFile(name + "Comas.csv");
	ofstream dataFileWC(name + "Spaces.csv");
	int M, peso, valor;
	for (int i = 0; i < numCases; i++) {
		dataFile << N ;
		dataFileWC << N ;

		vector<vector<bool>> matriz_ad(N,vector<bool>(N,false));
		for (int j = 0; j < N; j++) { //Rellenar matriz adyacencia
			for (int k = j+1; k < N; k++) {
				matriz_ad[j][k]= rand() % 2;
				matriz_ad[k][j] = matriz_ad[j][k];

				dataFile << "," << matriz_ad[j][k] ;
				dataFileWC << " " << matriz_ad[j][k];
			}
		}

		int valorAct[2];
		vector<vector<bool>> sin_cubrir; //aristas sin cubrir
		vector<vector<bool> > instancias(2, vector<bool>(N, false));
		for (int k = 0; k < 2; k++) {
			valorAct[k] = 0;
			sin_cubrir = matriz_ad;
			vector<int> indices = indices_desordenados(N); //Para que no coja siempre objetos del principio
			for (int j = 0; j < N ; j++) {
				instancias[k][indices[j]] = rand() % 2;
				if (instancias[k][indices[j]]) {
					for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
						sin_cubrir[g][indices[j]] = false;
						sin_cubrir[indices[j]][g] = false;
					}
					valorAct[k]++;
				}
			}
			for (int j = 0; j < N; j++) { //Anadir nodos de las aristas sin cubrir
				for (int m = j + 1; m < N; m++) {
					if (sin_cubrir[j][m]) { //si hay una arista sin cubrir anades ese vertice
						if (rand() % 2) {
							instancias[k][j] = true;
							for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
								sin_cubrir[g][j] = false;
								sin_cubrir[j][g] = false;
							}
						}
						else {
							instancias[k][m] = true;
							for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
								sin_cubrir[g][m] = false;
								sin_cubrir[m][g] = false;
							}
						}
						valorAct[k]++;
					}
				}
			}
		}

		if (valorAct[0] >= valorAct[1])
			for (int k = 0; k < 2; k++) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		else
			for (int k = 1; k >= 0; k--) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		dataFile << endl;
		dataFileWC << endl;
	}
	dataFile.close();

}


void generar_par_bueno_malo_Matriz_Completa() {
	int numCases, N, maxM, option;
	string name;
	cout << "Introduce the number of cases to generate:\n";
	cin >> numCases;
	cout << "Introduce the number of nodes:\n";
	cin >> N;
	cout << "Introduce the name of the file:\n";
	cin >> name;

	srand(static_cast<unsigned int>(std::time(nullptr)));

	ofstream dataFile(name + "Comas.csv");
	ofstream dataFileWC(name + "Spaces.csv");
	int M, peso, valor;
	for (int i = 0; i < numCases; i++) {
		dataFile << N;
		dataFileWC << N;

		vector<vector<bool>> matriz_ad(N, vector<bool>(N, false));
		for (int j = 0; j < N; j++) { //Rellenar matriz adyacencia
			for (int k = j + 1; k < N; k++) {
				matriz_ad[j][k] = rand() % 2;
				matriz_ad[k][j] = matriz_ad[j][k];

			}
		}
		for (int j = 0; j < N; j++) { //Rellenar matriz adyacencia
			for (int k = 0; k < N; k++) {
				dataFile << "," << matriz_ad[j][k];
				dataFileWC << " " << matriz_ad[j][k];
			}
		}
		int valorAct[2];
		vector<vector<bool>> sin_cubrir; //aristas sin cubrir
		vector<vector<bool> > instancias(2, vector<bool>(N, false));
		for (int k = 0; k < 2; k++) {
			valorAct[k] = 0;
			sin_cubrir = matriz_ad;
			vector<int> indices = indices_desordenados(N); //Para que no coja siempre objetos del principio
			for (int j = 0; j < N; j++) {
				instancias[k][indices[j]] = rand() % 2;
				if (instancias[k][indices[j]]) {
					for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
						sin_cubrir[g][indices[j]] = false;
						sin_cubrir[indices[j]][g] = false;
					}
					valorAct[k]++;
				}
			}
			for (int j = 0; j < N; j++) { //Anadir nodos de las aristas sin cubrir
				for (int m = j + 1; m < N; m++) {
					if (sin_cubrir[j][m]) { //si hay una arista sin cubrir anades ese vertice
						if (rand() % 2) {
							instancias[k][j] = true;
							for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
								sin_cubrir[g][j] = false;
								sin_cubrir[j][g] = false;
							}
						}
						else {
							instancias[k][m] = true;
							for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
								sin_cubrir[g][m] = false;
								sin_cubrir[m][g] = false;
							}
						}
						valorAct[k]++;
					}
				}
			}
		}

		if (valorAct[0] >= valorAct[1])
			for (int k = 0; k < 2; k++) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		else
			for (int k = 1; k >= 0; k--) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		dataFile << endl;
		dataFileWC << endl;
	}
	dataFile.close();

}



// Algoritmo para resolver el Vertex Cover utilizando maximal matching
vector<bool> vertex_cover_approximation(const vector<vector<bool>>&matriz_ad) {
	int N = matriz_ad.size();
	vector<bool> matched_vertices(N, false);
	vector<bool> vertex_cover(N, false);

	for (int u = 0; u < N; ++u) {
		if (!matched_vertices[u]) {
			for (int v = u + 1; v < N; ++v) {
				if (matriz_ad[u][v] && !matched_vertices[v]) {
					vertex_cover[u] = true;
					vertex_cover[v] = true;
					matched_vertices[u] = true;
					matched_vertices[v] = true;
					break;
				}
			}
		}
	}
	return vertex_cover;
}


// Función para verificar si una solución propuesta es factible para el problema de Vertex Cover
bool esSolucionFactible(const vector<vector<bool>>& matriz_ad, const vector<bool>& solucion) {
	int N = matriz_ad.size(); // Número de vértices en el grafo
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if (matriz_ad[i][j]) { // Existe un arista entre el vértice i y el vértice j
				if (!solucion[i] && !solucion[j]) {
					// Ninguno de los dos vértices que conecta la arista está en la solución propuesta
					return false; // La solución no es factible
				}
			}
		}
	}
	return true; // Todos los lados están cubiertos por al menos un vértice en la solución
}



void generar_par_bueno_malo_menos_unos() { //Generar conjunto con ambas soluciones aleatorias
	int numCases, N, maxM, option;
	string name;
	cout << "Introduce the number of cases to generate:\n";
	cin >> numCases;
	cout << "Introduce the number of nodes:\n";
	cin >> N;
	cout << "Introduce the name of the file:\n";
	cin >> name;

	srand(static_cast<unsigned int>(std::time(nullptr)));

	ofstream dataFile(name + "Comas.csv");
	ofstream dataFileWC(name + "Spaces.csv");
	int M, peso, valor;
	for (int i = 0; i < numCases; i++) {
		dataFile << N;
		dataFileWC << N;

		vector<vector<bool>> matriz_ad(N, vector<bool>(N, false));
		for (int j = 0; j < N; j++) { //Rellenar matriz adyacencia
			for (int k = j + 1; k < N; k++) {
				if (rand() % 2 && rand() % 2) {//así cada arista tiene un 12,5% de probabilidad de que conecte a los dos nodos
					matriz_ad[j][k] = rand() % 2;
					matriz_ad[k][j] = matriz_ad[j][k];
				}

				dataFile << "," << matriz_ad[j][k];
				dataFileWC << " " << matriz_ad[j][k];
			}
		}

		int valorAct[2];
		vector<vector<bool>> sin_cubrir; //aristas sin cubrir
		vector<vector<bool> > instancias(2, vector<bool>(N, false));
		for (int k = 0; k < 2; k++) {
			valorAct[k] = 0;
			sin_cubrir = matriz_ad;
			vector<int> indices = indices_desordenados(N); //Para que no coja siempre objetos del principio
			for (int j = 0; j < N; j++) {
				instancias[k][indices[j]] = rand() % 2;
				if (instancias[k][indices[j]]) {
					for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
						sin_cubrir[g][indices[j]] = false;
						sin_cubrir[indices[j]][g] = false;
					}
					valorAct[k]++;
				}
			}
			for (int j = 0; j < N; j++) { //Anadir nodos de las aristas sin cubrir
				for (int m = j + 1; m < N; m++) {
					if (sin_cubrir[j][m]) { //si hay una arista sin cubrir anades ese vertice
						if (rand() % 2) {
							instancias[k][j] = true;
							for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
								sin_cubrir[g][j] = false;
								sin_cubrir[j][g] = false;
							}
						}
						else {
							instancias[k][m] = true;
							for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
								sin_cubrir[g][m] = false;
								sin_cubrir[m][g] = false;
							}
						}
						valorAct[k]++;
					}
				}
			}
		}

		if (valorAct[0] >= valorAct[1])
			for (int k = 0; k < 2; k++) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		else
			for (int k = 1; k >= 0; k--) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		dataFile << endl;
		dataFileWC << endl;
	}
	dataFile.close();

}



void generar_par_bueno_malo_menos_unos_algor() { //Generar conjunto con una solucion aleatoria y la otra con algoritmo de aproximación
	int numCases, N, maxM, option; 
	string name;
	cout << "Introduce the number of cases to generate:\n";
	cin >> numCases;
	cout << "Introduce the number of nodes:\n";
	cin >> N;
	cout << "Introduce the name of the file:\n";
	cin >> name;

	srand(static_cast<unsigned int>(std::time(nullptr)));

	ofstream dataFile(name + "Comas.csv");
	ofstream dataFileWC(name + "Spaces.csv");
	int M, peso, valor;
	int contAux = 0;
	for (int i = 0; i < numCases; i++) {
		dataFile << N;
		dataFileWC << N;

		vector<vector<bool>> matriz_ad(N, vector<bool>(N, false));
		for (int j = 0; j < N; j++) { //Rellenar matriz adyacencia
			for (int k = j + 1; k < N; k++) {
				switch (i%5)
				{
				case 0: // 50%
					matriz_ad[j][k] = rand() % 2 ;
					break;
				case 1: // 25%
					matriz_ad[j][k] = rand() % 2 && rand() % 2;
					break;
				case 2: // 12,5%
					matriz_ad[j][k] = rand() % 2 && rand() % 2 && rand() % 2;
					break;
				case 3: // 6,25%
					matriz_ad[j][k] = rand() % 2 && rand() % 2 && rand() % 2 && rand() % 2;
					break;
				case 4: // 3,125%
					matriz_ad[j][k] = rand() % 2 && rand() % 2 && rand() % 2 && rand() % 2 && rand() % 2;
					break;
				}

				matriz_ad[k][j] = matriz_ad[j][k];

				dataFile << "," << matriz_ad[j][k];
				dataFileWC << " " << matriz_ad[j][k];
			}
		}


		//for (int j = 0; j < N; j++) { //Rellenar matriz adyacencia
		//	for (int k = 0; k < N; k++) {
		//		cout << matriz_ad[j][k] << " ";
		//	}
		//	cout << endl;
		//}
		//cout << endl;

		int valorAct[2];
		vector<vector<bool>> instancias(2, vector<bool>(N, false));

		// Generar solucion aleatoria
		vector<vector<bool>> sin_cubrir; //aristas sin cubrir
		valorAct[0] = 0;
		sin_cubrir = matriz_ad;
		vector<int> indices = indices_desordenados(N); //Para que no coja siempre objetos del principio
		for (int j = 0; j < N; j++) {
			instancias[0][indices[j]] = rand() % 2;
			if (instancias[0][indices[j]]) {
				for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
					sin_cubrir[g][indices[j]] = false;
					sin_cubrir[indices[j]][g] = false;
				}
				valorAct[0]++;
			}
		}
		for (int j = 0; j < N; j++) { //Anadir nodos de las aristas sin cubrir
			for (int m = j + 1; m < N; m++) {
				if (sin_cubrir[j][m]) { //si hay una arista sin cubrir introduce ese vertice
					if (rand() % 2) {
						instancias[0][j] = true;
						for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
							sin_cubrir[g][j] = false;
							sin_cubrir[j][g] = false;
						}
					}
					else {
						instancias[0][m] = true;
						for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
							sin_cubrir[g][m] = false;
							sin_cubrir[m][g] = false;
						}
					}
					valorAct[0]++;
				}
			}
		}

		// Generar solución aproximada
		instancias[1] = vertex_cover_approximation(matriz_ad);
		valorAct[1] = 0;
		for (int j = 0; j < N; j++) {
			if (instancias[1][j])
				valorAct[1]++;
		}



		for (int j = 0; j < 2; j++) {
			if (!esSolucionFactible(matriz_ad, instancias[j]))
				cout << "No es factible la solucion: " << j << '\n';
		}

		/*for (int k = 0; k < 2; k++) {
			cout << "Solucion: " << k << ": ";
			for (int j = 0; j < N; j++) {
				cout << "," << instancias[k][j];
			}
			cout << endl;
			cout << "Valor: " << valorAct[k];
			cout << endl;
		}
		cout << endl;*/



		if (valorAct[0] >= valorAct[1])
			for (int k = 0; k < 2; k++) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		else {
			contAux++;
			for (int k = 1; k >= 0; k--) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		}
		dataFile << endl;
		dataFileWC << endl;
	}
	dataFile.close();
}





























void generar_par_bueno_malo_menos_unos_Matriz_Completa() {
	int numCases, N, maxM, option;
	string name;
	cout << "Introduce the number of cases to generate:\n";
	cin >> numCases;
	cout << "Introduce the number of nodes:\n";
	cin >> N;
	cout << "Introduce the name of the file:\n";
	cin >> name;

	srand(static_cast<unsigned int>(std::time(nullptr)));

	ofstream dataFile(name + "Comas.csv");
	ofstream dataFileWC(name + "Spaces.csv");
	int M, peso, valor;
	for (int i = 0; i < numCases; i++) {
		dataFile << N;
		dataFileWC << N;

		vector<vector<bool>> matriz_ad(N, vector<bool>(N, false));
		for (int j = 0; j < N; j++) { //Rellenar matriz adyacencia
			for (int k = j + 1; k < N; k++) {
				if (rand() % 2 && rand() % 2) {//así cada arista tiene un 12,5% de probabilidad de que conecte a los dos nodos
					matriz_ad[j][k] = rand() % 2;
					matriz_ad[k][j] = matriz_ad[j][k];
				}
			}
		}
		for (int j = 0; j < N; j++) { //Rellenar matriz adyacencia
			for (int k = 0; k < N; k++) {
				dataFile << "," << matriz_ad[j][k];
				dataFileWC << " " << matriz_ad[j][k];
			}
		}

		int valorAct[2];
		vector<vector<bool>> sin_cubrir; //aristas sin cubrir
		vector<vector<bool> > instancias(2, vector<bool>(N, false));
		for (int k = 0; k < 2; k++) {
			valorAct[k] = 0;
			sin_cubrir = matriz_ad;
			vector<int> indices = indices_desordenados(N); //Para que no coja siempre objetos del principio
			for (int j = 0; j < N; j++) {
				instancias[k][indices[j]] = rand() % 2;
				if (instancias[k][indices[j]]) {
					for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
						sin_cubrir[g][indices[j]] = false;
						sin_cubrir[indices[j]][g] = false;
					}
					valorAct[k]++;
				}
			}
			for (int j = 0; j < N; j++) { //Anadir nodos de las aristas sin cubrir
				for (int m = j + 1; m < N; m++) {
					if (sin_cubrir[j][m]) { //si hay una arista sin cubrir anades ese vertice
						if (rand() % 2) {
							instancias[k][j] = true;
							for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
								sin_cubrir[g][j] = false;
								sin_cubrir[j][g] = false;
							}
						}
						else {
							instancias[k][m] = true;
							for (int g = 0; g < N; ++g) { //eliminar aristas cubiertas por el nodo anadido
								sin_cubrir[g][m] = false;
								sin_cubrir[m][g] = false;
							}
						}
						valorAct[k]++;
					}
				}
			}
		}

		if (valorAct[0] >= valorAct[1])
			for (int k = 0; k < 2; k++) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		else
			for (int k = 1; k >= 0; k--) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
				}
			}
		dataFile << endl;
		dataFileWC << endl;
	}
	dataFile.close();

}



void generar_solo_caso() {
	int numCases, N, maxM, option;
	string name;
	cout << "Introduce the number of cases to generate:\n";
	cin >> numCases;
	cout << "Introduce the number of items per case:\n";
	cin >> N;
	cout << "Introduce the maximum number of available space in the bag:\n";
	cin >> maxM;
	cout << "Introduce the name of the file:\n";
	cin >> name;

	srand(static_cast<unsigned int>(std::time(nullptr)));

	ofstream dataFile(name + "Comas.csv");
	ofstream dataFileWC(name + "Spaces.csv");
	int M, peso, valor;
	for (int i = 0; i < numCases; i++) {
		//M
		M = rand() % maxM + 1;
		dataFile << N << "," << M << ",";
		dataFileWC << N << " " << M << " ";

		for (int j = 0; j < N; j++) {
			peso = rand() % (M + 1) + 1; //peso y valor aleatorios
			valor = rand() % 100 + 1;
			dataFile << peso << "," << valor;
			dataFileWC << peso << " " << valor;
			if (j < N - 1) {
				dataFile << ",";
				dataFileWC << " ";
			}
		}
		dataFile << endl;
		dataFileWC << endl;
	}
	dataFile.close();
}




int main() {
	int opcion;
	cout << "Generar: Caso - Solucion optima (0)\nGenerar: Caso - Solucion optima con Menos aristas(1)\nGenerar: Caso - Solucion optima con Menos aristas con Matriz de adyacencia Completa(2)\nGenerar: Caso - Solucion peor - Solucion mejor (aleatorio y aproximado) (3) (utilizado en el TFG)\n"; //\nGenerar: Caso - (2)\n
	cin >> opcion;
	if (opcion == 0) {
		generar_par_bueno_malo();
	}
	else if (opcion == 1) {
		generar_par_bueno_malo_menos_unos();
	}
	else if (opcion == 2) {
		generar_par_bueno_malo_menos_unos_Matriz_Completa();
	}
	else if (opcion == 3) {
		generar_par_bueno_malo_menos_unos_algor();
	}
	return 0;
}