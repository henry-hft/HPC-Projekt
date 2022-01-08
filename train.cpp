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

using namespace std;

// Bildgroesse MNIST Datensatz
const int breite = 28;
const int hoehe = 28;

// Anzahl der Trainingsdatensaetze
const int training = 60000;

// Input Layer
// Anzahl der Input-Neuronen
// Ein Input-Neuronen pro Pixel. Da die Bilder in Grauwerten gespeichert sind, koennen diese Werte zwsichen 0 und 255 annehmen.
const int input = breite * hoehe; // 28 * 28 = 784

// Hidden Layer
const int hidden = 128; // 128 Neuronen

// Output Layer
const int output = 10; // 0-9 (10 moegliche Ausgaenge)

// Sigmoidfunktion
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}


void init_array() {
    
    for (int i = 1; i <= input; ++i) {
        w1[i] = new double [hidden + 1];
        delta1[i] = new double [hidden + 1];
    }
    
    out1 = new double [input + 1];
    
    for (int i = 1; i <= hidden; ++i) {
        w2[i] = new double [output + 1];
        delta2[i] = new double [output + 1];
    }
    
    in2 = new double [hidden + 1];
    out2 = new double [hidden + 1];
    theta2 = new double [hidden + 1];

	// Output layer
    in3 = new double [output + 1];
    out3 = new double [output + 1];
    theta3 = new double [output + 1];
    
    #pragma omp parallel for
    for (int i = 1; i <= input; ++i) {
        for (int j = 1; j <= hidden; ++j) {
            int sign = rand() % 2;
            
            w1[i][j] = (double)(rand() % 6) / 10.0;
            if (sign == 1) {
				w1[i][j] = - w1[i][j];
			}
        }
	}
	
    #pragma omp parallel for
    for (int i = 1; i <= hidden; ++i) {
        for (int j = 1; j <= output; ++j) {
            int sign = rand() % 2;

            w2[i][j] = (double)(rand() % 10 + 1) / (10.0 * output);
            if (sign == 1) {
				w2[i][j] = - w2[i][j];
			}
        }
	}
}