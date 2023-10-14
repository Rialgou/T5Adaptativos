#include "greedy.cpp"
#include "localSearch.cpp"
#include <string>
#include <vector>
#include <math.h>
#include <chrono>

using namespace std;

pair<int,string> grasp(vector <string> dataset, int alpha, int timeLimit){

    pair<int,string> best = make_pair(INT_MAX,"");

    auto startTime = chrono::high_resolution_clock::now();
    double getTime = 0.0;
    while (true) {
        // Comprueba el tiempo transcurrido en cada iteración.
        auto currentTime = chrono::high_resolution_clock::now();
        auto elapsedSeconds = chrono::duration_cast<chrono::seconds>(currentTime - startTime).count();
        
        if (elapsedSeconds >= timeLimit) {
            break;  // Detener GRASP si se excede el límite de tiempo.
        }

        // Genera una solución inicial con el algoritmo Greedy.
        pair<int,string> initialSolution = greedyAlgorithm(dataset, alpha);

        // Aplica Simulated Annealing para mejorar la solución inicial.
        pair<int,string> improvedSolution = localSearch(initialSolution, dataset);

        if (improvedSolution.first < best.first) {
            best.second = improvedSolution.second;
            best.first = improvedSolution.first;
            getTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - startTime).count();

            // Imprime la mejor solución, costo y tiempo.
            cout << "Mejor solución encontrada:" << endl;
            cout << best.second << endl;
            cout << "Costo: " << best.first << endl;
            cout << "Tiempo transcurrido: " << getTime << " segundos" << endl;
        }
    }
    cout<<"Tiempo mejor solución final "<<getTime<< "s"<<endl; 
    return best;
}

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    if (argc > 5) {
        if (argv[1][0] != '-' || argv[1][1] != 'i') {
            cout << "Debes ingresar el comando -i " << endl;
            return 0;
        }
        if(argv[3][0] != '-' ||argv[3][1] != 't'){
            cout <<"Debes ingresar el comando -t" <<endl;
            return 0;
        }
    } else {
        cout << "Debes ingresar el formato de ejecución <Greedy> -i "
                "<instancia-problema> -t <tiempo-maximo-segundos> <probabilidad-aleatoriedad> "
             << endl;
        return 0;
    }

    fstream file;
    string path = argv[2];
    vector<string> dataset;
    int alpha = atoi(argv[5]);
    int timeLimit = atoi(argv[4]);
    //cout<<"tiempo limite"<<timeLimit<<endl;
    file.open(path, ios::in);

    if (file.is_open()) {
        string data;
        while (getline(file, data)) {
            dataset.push_back(data);
        }
        file.close();
    }

    pair<int,string> result = grasp(dataset,alpha,timeLimit);
    cout<<"Mejor solución final"<<endl;
    cout<<result.second<<" "<<result.first<<endl;
    /*
        ciclo donde se aplica grasp
    */
    /*string bestSolution;
    //while(true)
    //{ 
        pair<int, string> result = greedyAlgorithm(dataset, alpha);
        cout<<"solución inicial: "<<result.second<<endl;
        cout<<"costo inicial: "<<result.first<<endl;
        pair<int, string> localResult = localSearch(result, dataset);
        cout<<"solución local: "<<localResult.second<<endl;
        cout<<"costo local: "<<localResult.first<<endl;
        //elegir mejor valor 
    //}*/
    return 0;
}
