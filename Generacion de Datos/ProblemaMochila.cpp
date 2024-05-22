//Lucas martin Garcia

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib> // Necesario para std::rand() y std::srand()
#include <algorithm>
#include <random>
#include <chrono>


using namespace std;



// Solución de fuerza bruta comprobando todos los posibles casos
int solucion_param(const vector<int>& listaPesos, const vector<int>& listaValores, vector<bool>& mejorLista, int n, int m) {
	vector<bool> actualLista(n + 1, false);
	int mejorValor = -1, actualValor, actualPeso, contSumar;

	while (!actualLista[n]) {
		actualPeso = 0;
		actualValor = 0;
		for (int i = 0; i < n && actualPeso <= m; i++) { //comprobar factible
			if (actualLista[i])
				actualPeso += listaPesos[i];
		}
		if (actualPeso <= m) { //comprobar factible
			for (int i = 0; i < n; i++) {
				if (actualLista[i])
					actualValor += listaValores[i];
			}
			if (actualValor > mejorValor) { //comprobar mejor solucion
				mejorValor = actualValor;
				mejorLista = actualLista;
			}
		}



		//sumar uno en binario al vector
		contSumar = 0;
		while (actualLista[contSumar]) {
			actualLista[contSumar] = false;
			contSumar++;
		}
		actualLista[contSumar] = true;
	}
	return mejorValor;
}

// Solucion de programacion dinamica generando la matriz de objetos respecto tamaño maximo de la mochila
int solucion_dinamica_costes(const vector<int>& listaPesos, const vector<int>& listaValores, vector<bool>& mejorLista, int M) {
	int n = listaValores.size();
	mejorLista = vector<bool>(n + 1, false);
	vector<vector<int>> dp(n+1,vector<int>(M + 1, 0));
	for (int i = 1; i <= n; ++i) {
		for (int j = M; j >= 1; --j) {
			if(j < listaPesos[i - 1])
				dp[i][j] = dp[i - 1][j];
			else dp[i][j] = max(dp[i-1][j], dp[i - 1][j - listaPesos[i-1]] + listaValores[i-1]);
		}
	}
	int tamRes = M;
	for (int i = n; i > 0; --i) {
		if (listaPesos[i-1] <= tamRes && dp[i][tamRes] != dp[i - 1][tamRes]){
			mejorLista[i-1] = true;
			tamRes -= listaPesos[i-1];
		}
	}
	return dp[n][M];
}

// Solucion de programacion dinamica generando la matriz de objetos respecto tamaño cota superior de valor optimo
int solucion_dinamica_valores(const vector<int>& listaPesos, const vector<int>& listaValores, vector<bool>& mejorLista, int M, int P = -1) {
	int n = listaValores.size();
	mejorLista = vector<bool>(n + 1, false);
	if (P < 0) {
		//Calcular maximo valor
		P = listaValores[0];
		for (int i = 1; i < n; ++i) {
			if (P < listaValores[i]) {
				P = listaValores[i];
			}
		}
	}
	vector<vector<int>> dp(n + 1, vector<int>(n * P + 1, n*M));
	dp[0][0] = 0;

	for (int i = 1; i <= n; ++i) {
		for (int j = n * P; j >= 0; --j) {
			if (j < listaValores[i - 1])
				dp[i][j] = dp[i - 1][j];
			else dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - listaValores[i - 1]] + listaPesos[i - 1]);
		}
	}
	int sol = n * P;
	while (dp[n][sol] > M) {
		sol--;
	}

	int valRes = sol;
	for (int i = n; i > 0; --i) {
		if (listaValores[i - 1] <= valRes && dp[i][valRes] != dp[i - 1][valRes]) {
			mejorLista[i - 1] = true;
			valRes -= listaValores[i - 1];
		}
	}
	return sol;
}


int solucion_FPTAS(const vector<int>& listaPesos, const vector<int>& listaValores, vector<bool>& mejorLista, int M, float eps) {
	int n = listaValores.size();
	vector<int> listaValoresModificada(n);

	//Calcular maximo valor
	int P = listaValores[0];
	for (int i = 1; i < n; ++i) {
		if (P < listaValores[i]) {
			P = listaValores[i];
		}
	}

	float K = eps * P / n;
	for (int i = 0; i < n; ++i) {
		listaValoresModificada[i] = floor(listaValores[i] / K);
	}
	solucion_dinamica_valores(listaPesos, listaValoresModificada, mejorLista, M);
	int sol = 0;

	for (int i = 0; i < n; ++i) {
		if(mejorLista[i])
			sol+= listaValores[i];
	}
	return sol;
}


void generar_con_mejor_solucion() {
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
	cout << "Add solution at the end (1) dont (0):\n";
	cin >> option;

	srand(static_cast<unsigned int>(std::time(nullptr)));

	ofstream dataFile(name + "Comas.csv");
	ofstream dataFileWC(name + "Spaces.csv");
	int M, peso, valor;
	for (int i = 0; i < numCases; i++) {
		//M
		M = rand() % maxM + 1;
		dataFile << N << "," << M << ",";
		dataFileWC << N << " " << M << " ";

		vector<int> listaPesos(N), listaValores(N);
		for (int j = 0; j < N; j++) {
			peso = rand() % (M + 1) + 1; //peso y valor aleatorios
			valor = rand() % 100 + 1;
			dataFile << peso << "," <<valor ;
			dataFileWC << peso << " " << valor;
			if (j < N - 1) {
				dataFile << ",";
				dataFileWC << " ";
			}
			listaPesos[j] = peso;
			listaValores[j] = valor;
		}
		if (option) { //calcular mejor solucion
			vector<bool> mejorLista;
			int sol;
			sol = solucion_param(listaPesos, listaValores, mejorLista, N, M);
			for (int j = 0; j < N; j++) {
				dataFile << "," << mejorLista[j];
				dataFileWC << " " << mejorLista[j];
			}
			dataFile << "," << sol;
			dataFileWC << " " << sol;
		}
		dataFile << endl;
		dataFileWC << endl;
	}
	dataFile.close();

}


// Solución de fuerza bruta comprobando todos los posibles casos
int solucion(vector<bool> & mejorLista) {
	int n, m;
	cout << "Introduce n:\n";
	cin >> n ;
	cout << "Introduce m:\n";
	cin >> m;

	cout << "Introduce los " << n <<" pares de Peso-Valor:\n";
	vector<int> listaPesos(n), listaValores(n);
	vector<bool> actualLista(n+1, false);
	for (int i = 0; i < n; i++) {
		cin >> listaPesos[i] >> listaValores[i];
	}
	int mejorValor = -1, actualValor, actualPeso, contSumar;

	while (!actualLista[n]) {
		actualPeso = 0;
		actualValor = 0;
		for (int i = 0; i < n && actualPeso <= m; i++) {
			if (actualLista[i])
				actualPeso += listaPesos[i];
		}
		if(actualPeso <= m){
			for (int i = 0; i < n; i++) {
				if (actualLista[i])
					actualValor += listaValores[i];
			}
			if (actualValor > mejorValor) {
				mejorValor = actualValor;
				mejorLista = actualLista;
			}
		}



		//sumar uno en binario al vector
		contSumar = 0;
		while (actualLista[contSumar]) {
			actualLista[contSumar] = false;
			contSumar++;
		}
		actualLista[contSumar] = true;
	}
	return mejorValor;
}



vector<int> indices_desordenados(int N) {
	// Crear un vector de N �ndices
	vector<int> indices(N);
	for (int i = 0; i < N; ++i) {
		indices[i] = i;
	}

	// Semilla para el generador de n�meros aleatorios
	random_device rd;
	mt19937 g(rd());

	// Desordenar el vector de �ndices
	shuffle(indices.begin(), indices.end(), g);
	return indices;
}



// generación de conjunto de datos con solucion buena y mala aleatorias
void generar_par_bueno_malo() {
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

		vector<int> listaPesos(N), listaValores(N);
		for (int j = 0; j < N; j++) {
			peso = rand() % (M + 1) + 1; //peso y valor aleatorios
			valor = rand() % 100 + 1;
			dataFile << peso << "," << valor;
			dataFileWC << peso << " " << valor;
			if (j < N - 1) {
				dataFile << ",";
				dataFileWC << " ";
			}
			listaPesos[j] = peso;
			listaValores[j] = valor;
		}
		vector<vector<bool> > instancias(2, vector<bool>(N, false));
		int valorAct[2];
		for (int k = 0; k < 2; k++) {
			vector<int> indices = indices_desordenados(N); //Para que no coja siempre objetos del principio
			int pesoAct = 0;
			valorAct[k] = 0;
			for (int j = 0; j < N && pesoAct <M ; j++) { //Decido no generar casos no plausibles aunque el modelo pueda generarlos
				if (pesoAct + listaPesos[indices[j]] <= M) {
					instancias[k][indices[j]] = rand() % 2; //Toma el objeto o no
					if (instancias[k][indices[j]]) {
						pesoAct += listaPesos[indices[j]];
						valorAct[k] += listaValores[indices[j]];
					}
				}
			}
			//Rellenar hasta que no quepan más objetos
			indices = indices_desordenados(N); //Para que no coja siempre objetos del principio
			
			for (int j = 0; j < N && pesoAct <M ; j++) { //Decido no generar casos no plausibles aunque el modelo pueda generarlos
				if ( !instancias[k][indices[j]] && pesoAct + listaPesos[indices[j]] <= M) {
					instancias[k][indices[j]] = 1; //Toma el objeto
					pesoAct += listaPesos[indices[j]];
					valorAct[k] += listaValores[indices[j]];
				}
			}
		}
		if(valorAct[0] <= valorAct[1])
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


// generación de conjunto de datos con solucion aleatoria y fptas evualuando la mejor y peor
void generar_par_bueno_malo_aleatorio_fptas() {
	int numCases, N, maxM, option, maxV;
	string name;
	cout << "Introduce the number of cases to generate:\n";
	cin >> numCases;
	cout << "Introduce the number of items per case:\n";
	cin >> N;
	cout << "Introduce the maximum number of available space in the bag:\n";
	cin >> maxM;
	cout << "Introduce the maximum number of values of the items:\n";
	cin >> maxV;
	cout << "Introduce the name of the file:\n";
	cin >> name;


	// Crea el generador de números aleatorios
	random_device rd;
	mt19937 gen(rd());  // Utiliza random_device para obtener una semilla

	// Define el rango de números aleatorios
	uniform_int_distribution<> distrib(1, max(maxV, maxM));


	ofstream dataFile(name + "Comas.csv");
	ofstream dataFileWC(name + "Spaces.csv");
	int M, peso, valor;
	for (int i = 0; i < numCases; i++) {
		//M
		//cout << endl;
		M = distrib(gen) % maxM + 1;
		dataFile << N << "," << M << ",";
		dataFileWC << N << " " << M << " ";
		//cout << N << " " << M << " ";

		vector<int> listaPesos(N), listaValores(N);
		for (int j = 0; j < N; j++) {
			peso = distrib(gen) % (M + 1) + 1; //peso y valor aleatorios
			valor = distrib(gen) % maxV + 1;
			dataFile << peso << "," << valor;
			dataFileWC << peso << " " << valor;
			//cout << peso << " " << valor << " ";
			if (j < N - 1) {
				dataFile << ",";
				dataFileWC << " ";
			}
			listaPesos[j] = peso;
			listaValores[j] = valor;
		}
		vector<vector<bool> > instancias(2, vector<bool>(N, false));
		int valorAct[2];
		vector<int> indices = indices_desordenados(N); //Para que no coja siempre objetos del principio

		// Generar solucion aleatoria
		int pesoAct = 0;
		valorAct[0] = 0;
		for (int j = 0; j < N && pesoAct < M; j++) { //Decido no generar casos no plausibles aunque el modelo pueda generarlos
			if (pesoAct + listaPesos[indices[j]] <= M) {
				instancias[0][indices[j]] = rand() % 2; //Toma el objeto o no
				if (instancias[0][indices[j]]) {
					pesoAct += listaPesos[indices[j]];
					valorAct[0] += listaValores[indices[j]];
				}
			}
		}
		//Rellenar hasta que no quepan más objetos
		indices = indices_desordenados(N); //Para que no coja siempre objetos del principio

		for (int j = 0; j < N && pesoAct < M; j++) { //Decido no generar casos no plausibles aunque el modelo pueda generarlos
			if (!instancias[0][indices[j]] && pesoAct + listaPesos[indices[j]] <= M) {
				instancias[0][indices[j]] = 1; //Toma el objeto
				pesoAct += listaPesos[indices[j]];
				valorAct[0] += listaValores[indices[j]];
			}
		}
		// Generar solucion fptas
		double eps = 0.5;
		valorAct[1] = solucion_FPTAS(listaPesos, listaValores, instancias[1], M, eps);

		if (valorAct[0] <= valorAct[1])
			for (int k = 0; k < 2; k++) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
					//cout << " " << instancias[k][j];
				}
				//cout << " k=" << k << " " << valorAct[k];
			}
		else
			for (int k = 1; k >= 0; k--) {
				for (int j = 0; j < N; j++) {
					dataFile << "," << instancias[k][j];
					dataFileWC << " " << instancias[k][j];
					//cout << " " << instancias[k][j];
				}
				//cout << " k=" << k << " " << valorAct[k];
			}
		dataFile << endl;
		dataFileWC << endl;
	}
	dataFile.close();

}




// generación de conjunto de datos con solo la instancia del problema sin soluciones
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
	cout << "Calcular solucion de un caso (0)\nGenerar: Caso - Solucion optima (1)\nGenerar: Caso - Solucion peor - Solucion mejor (Aleatorias) (2)\nGenerar: Solo instancia (3)\nGenerar: Caso - Solucion Aleatorio - Solucion FPTAS (4) (utilizado en el TFG)\n";
	cin >> opcion;
	if (opcion == 1) {
		generar_con_mejor_solucion();
	}
	else if (opcion == 2) {
		generar_par_bueno_malo();
	}
	else if (opcion == 3) {
		generar_solo_caso();
	}
	else if (opcion == 0) {
		int c, sol;
		cout << "Introduce numero de casos\n";
		cin >> c;
		vector<bool> mejorLista;
		for (int i = 0; i < c; i++) {
			sol = solucion(mejorLista);
			if (sol != -1) {
				cout <<"Valor Solucion: " << sol << "\n" << "Vector solucion: ";
				for (int j = 0; j < mejorLista.size() - 1; j++) {
					cout << mejorLista[j] << " ";
				}
				cout << "\n";
			}
			else cout << "IMPOSIBLE\n";

		}
	}
	else if (opcion == 4) {
		generar_par_bueno_malo_aleatorio_fptas();
	}
	return 0;
}