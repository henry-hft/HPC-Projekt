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

// Number of OpenMP Threads
#define THREADS 12

// Training images file name
extern const string train_images = "mnist/train-images.idx3-ubyte";

// Training labels file name
extern const string train_labels = "mnist/train-labels.idx1-ubyte";

// Test images file name
extern const string test_images = "mnist/t10k-images.idx3-ubyte";

// Test labels file name
extern const string test_labels = "mnist/t10k-labels.idx1-ubyte";

// Weights file name
extern const string model = "models/model.txt";

// Training output file name
extern const string training_output = "output/training.txt";

// Test output file name
extern const string test_output = "output/test.txt";


// Number of training samples
extern const int train_amount = 60000;

// Number of test samples
extern const int test_amount = 10000;

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

int reverse_integer(int i) {
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i&255;
    ch2 = (i>>8)&255;
    ch3 = (i>>16)&255;
    ch4 = (i>>24)&255;
    return((int)ch1<<24)+((int)ch2<<16)+((int)ch3<<8)+ch4;
}
