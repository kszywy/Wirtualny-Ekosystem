#include <iostream>
#include "environment.h"
#include <fstream>


using namespace std;

int main()
{
    Environment ekoSystem = Environment::readFromFile("start.txt");

    unsigned long i = 0;

    ofstream resultFile("simulation.txt");
    if (!resultFile.is_open())
        return 1;
    string simulationState;

    do{
        system("clear");
        cout << "Krok symulacji: " << i << endl;
        resultFile << "Krok symulacji: " << i+1 <<  endl;
        simulationState = ekoSystem.toText();

        cout << endl << simulationState << endl;
        resultFile << simulationState << endl;
        cin.ignore(1);
        ekoSystem++;
        i++;
    } while (i < 200 && !ekoSystem);

    cout << endl;
    resultFile.close();


    return 0;
}
