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

// Anazhl der OpenMP Threads
#define THREADS 12


// Trainingsdaten
// Bilder
extern const string train_images = "mnist/train-images.idx3-ubyte";
// Labels
extern const string train_labels = "mnist/train-labels.idx1-ubyte";

// Testdaten
// Bilder
extern const string test_images = "mnist/t10k-images.idx3-ubyte";
// Labels
extern const string test_labels = "mnist/t10k-labels.idx1-ubyte";

// Datei, die die Gewichte enthält, also das neuronale Netz.
extern const string model = "models/model.txt";

// Ausgabedatei Training
extern const string training_output = "output/training.txt";

// Ausgabedatei Test
extern const string test_output = "output/test.txt";


// Anzahl der Trainingsbilder
extern const int train_amount = 60000;

// Anzahl der Testbilder
extern const int test_amount = 10000;

// Größe der Bilder des MNIST-Datensatzes in Pixeln
extern const int width = 28;
extern const int height = 28;

// Input Layer
// Anzahl der Input-Neuronen
// Ein Input-Neuronen pro Pixel. Da die Bilder in Grauwerten gespeichert sind, koennen diese Werte zwsichen 0 und 255 annehmen.
extern const int input_layer = width * height; // 28 * 28 = 784 (784 Neuronen)


// Hidden Layer
extern const int hidden_layer = 128; // 128 Neuronen

// Output Layer
extern const int output_layer = 10; // 0-9 (10 moegliche Ausgaenge), 10 Neuronen


// Epochen (Anzahl der Durchläufe durch das Traningsset)
extern const int epochs = 10;

// Lernrate
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
