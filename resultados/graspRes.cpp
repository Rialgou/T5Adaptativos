#include <math.h>

#include <chrono>
#include <string>
#include <vector>

#include "../greedy.cpp"
#include "../localSearch.cpp"

using namespace std;

pair<int, double> grasp(vector<string> dataset, int alpha, int timeLimit) {
    pair<int, string> best = make_pair(INT_MAX, "");

    auto startTime = chrono::high_resolution_clock::now();
    double getTime = 0.0;
    while (true) {
        // Comprueba el tiempo transcurrido en cada iteración.
        auto currentTime = chrono::high_resolution_clock::now();
        auto elapsedSeconds =
            chrono::duration_cast<chrono::seconds>(currentTime - startTime)
                .count();

        if (elapsedSeconds >= timeLimit) {
            break;  // Detener GRASP si se excede el límite de tiempo.
        }

        // Genera una solución inicial con el algoritmo Greedy.
        pair<int, string> initialSolution = greedyAlgorithm(dataset, alpha);

        // Aplica Simulated Annealing para mejorar la solución inicial.
        pair<int, string> improvedSolution =
            localSearch(initialSolution, dataset);

        if (improvedSolution.first < best.first) {
            best.second = improvedSolution.second;
            best.first = improvedSolution.first;
            getTime = chrono::duration_cast<chrono::duration<double>>(
                          chrono::high_resolution_clock::now() - startTime)
                          .count();

            // Imprime la mejor solución, costo y tiempo.
            // cout << "Mejor solución encontrada:" << endl;
            // cout << best.second << endl;
            // cout << "Costo: " << best.first << endl;
            // cout << "Tiempo transcurrido: " << getTime << " segundos" <<
            // endl;
        }
    }
    return make_pair(best.first, getTime);
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    int m, l;
    cin >> m >> l;
    string outputFileName = "results"+to_string(m)+"_"+to_string(l)+".csv";

    ofstream outputFile(outputFileName);

    if (!outputFile) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return 1;
    }

    // Escribe el encabezado del archivo CSV
    outputFile << "inst; m; l; mh; mhtime" << endl;
    int alpha = 15;
    int timeLimit = 60;
    
    for (int inst = 0; inst < 100; inst++) {
        // Construye el nombre del archivo de instancia según el formato
        // deseado.
        string instanceFileName = "inst_" + to_string(m) + "_" + to_string(l) +
                                  "_4_" + to_string(inst) + ".txt";
        fstream file;
        file.open("../nuevo_dataset/" + instanceFileName);
        // Lee la instancia desde el archivo, parsea los datos, y almacena en
        // 'dataset'.
        vector<string> dataset;  // Llena dataset con los datos de la instancia.

        if (file.is_open()) {
            string data;
            while (getline(file, data)) {
                dataset.push_back(data);
            }
            file.close();
        }

        pair<int, double> result = grasp(dataset, alpha, timeLimit);

        // Escribe los resultados en el archivo CSV
        outputFile << inst << ";" << m << ";" << l << ";" << result.first << ";"
                   << result.second << endl;
    }

    outputFile.close();
    cout << "Resultados guardados en " << outputFileName << endl;

    return 0;
}
