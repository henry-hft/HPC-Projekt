#include <omp.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <iterator>
#include <algorithm>
#include <ctime>

using namespace std;

#define THREADS 4
// Training image file name

extern const string train_images = "mnist/train-images.idx3-ubyte";

// Training label file name
extern const string train_labels = "mnist/train-labels.idx1-ubyte";

// Weights file name
extern const string model = "model/model.txt";

// Report file name
extern const string report_fn = "training-report.dat";

// Number of training samples
extern const int train_amount = 60000;

// Image size in MNIST database
extern const int width = 28;
extern const int height = 28;

// n1 = Number of input neurons
// n2 = Number of hidden neurons ResearchPriority1
// n3 = Number of output neurons
// epochs = Number of iterations for back-propagation algorithm
// learning_rate = Learing rate
// momentum = Momentum (heuristics to optimize back-propagation algorithm)
// epsilon = Epsilon, no more iterations if the learning error is smaller than epsilon

extern const int input_layer = width * height; // = 784, without bias neuron 
extern const int hidden_layer = 128; 
extern const int output_layer = 10; // Ten classes: 0 - 9
extern const int epochs = 10;
extern const double learning_rate = 0.001;

// Info
void info(bool training) {
        string data = "";
        string type = "";
        if(training == true){
                type = "Training";
                data = "Trainingsdaten";
        } else {
                type = "Test";
                data = "Testdaten";
        }

    cout << "------ " << type << " ------" << endl;
    cout << "HPC-Computing Projekt WiSe 21/22" << endl;
    cout << "Neuronales Netz mit OpenMP für MNIST Datensatz" << endl;
    cout << endl;
    cout << "Input-Layer: " << input_layer << " Neuronen" << endl;
    cout << "Hidden-Layer: " << hidden_layer << " Neuronen" << endl;
    cout << "Output-Layer: " << output_layer << " Neuronen" << endl;
    if(training == true) {
        cout << "Anzahl Epochen: " << epochs << endl;
        cout << "Lernrate: " << learning_rate << endl;
	cout << "Anzahl Threads: " << THREADS << endl;
    }
    cout << data << " (Bilder): " << train_images << endl;
    cout << data << " (Labels): " << train_labels << endl;
    cout << "Anzahl " << data << ": " << train_amount << endl << endl;
}

// Sigmoidfunktion
double sigmoid_function(double x) {
    double result;
    result = 1 / (1 + exp(-x));
    return result;
}
