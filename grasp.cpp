#include "greedy.cpp"
#include "localSearch.cpp"
#include <string>
#include <vector>
#include <math.h>

using namespace std;




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
        cout<<"solución inicial: "<<result.second<<endl;
        cout<<"costo inicial: "<<result.first<<endl;
        pair<int, string> localResult = localSearch(result, dataset);
        cout<<"solución local: "<<localResult.second<<endl;
        cout<<"costo local: "<<localResult.first<<endl;
        //elegir mejor valor 
    //}
    return 0;
}
