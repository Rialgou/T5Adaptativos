#include <string>
#include <vector>
#include <math.h>

using namespace std;

string createNeighbor(string result){
    string neighbor = result;
    //se obtiene una posición de la cadena
    int index = rand() % (result.size() -1)+1;
    //se reemplaza por un nuevo nucleotido
    char list[4] = {'A', 'C', 'T', 'G'};
    int randomIndex = rand() % 4;
    char nucleotide = list[randomIndex];
    neighbor[index] = nucleotide;

    return neighbor; 
}
double acceptanceProbability(int currentCost, int newCost, double temperature){
    if (newCost < currentCost) {
        return 1.0;  // Acepta la nueva solución si es mejor.
    }
    return exp((currentCost - newCost) / temperature);
}

int calculateCost(string result, vector<string> dataset){
    int cost = 0;
    vector<int> distances(dataset.size(),0);
    //se rellena el vector de distancias
    for (int i = 0; i < result.size(); i++){
        for (int sequence = 0; sequence < dataset.size(); sequence++){
            if(result[i] != dataset[sequence][i]){
                distances[sequence]++;
            }
        }
    }
    //se calcula el costo
    for (auto value :distances) {
        cost += value * value;
    }
    return cost;
}

pair<int,string> localSearch(pair<int,string> greedyResult, vector<string> dataset){
    int currentCost = greedyResult.first;
    string currentResult = greedyResult.second;
    double initialTemperature = 1000.0;
    double coolingRate= 0.99;

    while(initialTemperature > 0.1){
        string newResult = createNeighbor(currentResult);
        int newCost = calculateCost(newResult, dataset);
        double probability = acceptanceProbability(currentCost, newCost, initialTemperature);

        if(probability > static_cast<double>(rand()) / RAND_MAX){
            currentResult = newResult;
            currentCost = newCost;
        }

        initialTemperature *= coolingRate;
    }
    
    return make_pair(currentCost,currentResult);
}