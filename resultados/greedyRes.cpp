#include <string>
#include <vector>
#include <math.h>
#include <chrono>
#include "../greedy.cpp"

using namespace std;

int main(){
    int m, l;
    cin >> m >> l;
    string outputFileName = "greedy"+to_string(m)+"_"+to_string(l)+".csv";

    ofstream outputFile(outputFileName);

    if (!outputFile) {
        cerr << "Error al abrir el archivo de salida." << endl;
        return 1;
    }

    // Escribe el encabezado del archivo CSV
    outputFile << "inst; m; l; greedy;" << endl;

    
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

        pair<int, string> result = greedyAlgorithm(dataset, 0);

        // Escribe los resultados en el archivo CSV
        outputFile << inst << ";" << m << ";" << l << ";" << result.first << ";"
                   << endl;
    }

    outputFile.close();
    cout << "Resultados guardados en " << outputFileName << endl;

    return 0;

}