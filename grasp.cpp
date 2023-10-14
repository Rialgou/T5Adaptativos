#include "greedy.cpp"
#include <string>
#include <vector>

using namespace std;


pair<int,string> localSearch(pair<int,string> greedyResult, vector<string> dataset){
    int cost = greedyResult.first;
    string result = greedyResult.second;

    /*
    ciclo while, se ira cambiando una letra y recalculando para ver si mejora el costo final
    */
    return make_pair(0,"nao");
}


int main(int argc, char const *argv[]) {
    srand(time(NULL));

    if (argc > 3) {
        if (argv[1][0] != '-' || argv[1][1] != 'i') {
            cout << "Debes ingresar el comando -i " << endl;
            return 0;
        }
    } else {
        cout << "Debes ingresar el formato de ejecución <Greedy> -i "
                "<instancia-problema> <probabilidad-aleatoriedad> "
             << endl;
        return 0;
    }

    fstream file;
    string path = argv[2];
    vector<string> dataset;
    int alpha = atoi(argv[3]);
    file.open(path, ios::in);

    if (file.is_open()) {
        string data;
        while (getline(file, data)) {
            dataset.push_back(data);
        }
        file.close();
    }
    /*
        ciclo donde se aplica grasp
    */
    string bestSolution;
    //while(true)
    //{ 
        pair<int, string> result = greedyAlgorithm(dataset, alpha);
        //busquedalocal, lo quiero hacer en otro archivo pero para probar lo estoy haciendo en este mismo mientras jaja
        
        //elegir mejor valor 
    //}
    
    
    cout << result.second << endl;
    cout << result.first << endl;

    return 0;
}
