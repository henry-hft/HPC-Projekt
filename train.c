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

// Sigmoidfunktion
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}


void init_array() {
    
    for (int i = 1; i <= n1; ++i) {
        w1[i] = new double [n2 + 1];
        delta1[i] = new double [n2 + 1];
    }
    
    out1 = new double [n1 + 1];
    
    for (int i = 1; i <= n2; ++i) {
        w2[i] = new double [n3 + 1];
        delta2[i] = new double [n3 + 1];
    }
    
    in2 = new double [n2 + 1];
    out2 = new double [n2 + 1];
    theta2 = new double [n2 + 1];

	// Output layer
    in3 = new double [n3 + 1];
    out3 = new double [n3 + 1];
    theta3 = new double [n3 + 1];
    
    #pragma omp parallel for
    for (int i = 1; i <= n1; ++i) {
        for (int j = 1; j <= n2; ++j) {
            int sign = rand() % 2;
            
            w1[i][j] = (double)(rand() % 6) / 10.0;
            if (sign == 1) {
				w1[i][j] = - w1[i][j];
			}
        }
	}
	
    #pragma omp parallel for
    for (int i = 1; i <= n2; ++i) {
        for (int j = 1; j <= n3; ++j) {
            int sign = rand() % 2;

            w2[i][j] = (double)(rand() % 10 + 1) / (10.0 * n3);
            if (sign == 1) {
				w2[i][j] = - w2[i][j];
			}
        }
	}
}
