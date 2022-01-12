#include "header.hpp"

// Von Layer 1 zu layer 2 bzw. Input-Layer zu Hidden-Layer
double *w1[input_layer + 1], *out1;

// Von Layer 2 zu layer 3 bzw. Hidden-Layer zu Output-Layer
double *w2[hidden_layer + 1], *ihidden_layer, *out2;

// Layer 3 bzw Output-Layer
double *ioutput_layer, *out3;
double expected[output_layer + 1];

// Bilder des MNIST-Datensatzes (28x28 Pixel, Grauwerte)
int d[width + 1][height + 1];

// File streams zum Einlesen der Bilder
ifstream image;
// File streams zum Einlesen der Labels
ifstream label;
// File streams zum Schreiben der Ergebnisse in die Ausgabedatei
ofstream output;

// Speicherzuweisung
void init_array() {
	// Layer 1 zu Layer 2 bzw. Input-Layer zu Hidden-Layer
    for (int i = 1; i <= input_layer; ++i) {
        w1[i] = new double [hidden_layer + 1];
    }
    
    out1 = new double [input_layer + 1];

	// Layer 2 zu Layer 3 bzw. Hidden-Layer zu Output-Layer
    for (int i = 1; i <= hidden_layer; ++i) {
        w2[i] = new double [output_layer + 1];
    }
    
    ihidden_layer = new double [hidden_layer + 1];
    out2 = new double [hidden_layer + 1];

	// Layer 3 bzw. Output-Layer
    ioutput_layer = new double [output_layer + 1];
    out3 = new double [output_layer + 1];
}

// Lade Modell des traininieren neuronalen Netzes
void load_model() {
	ifstream file(model.c_str(), ios::in);
	
	// Input-Layer zu Hidden-Layer
    for (int i = 1; i <= input_layer; ++i) {
        for (int j = 1; j <= hidden_layer; ++j) {
			file >> w1[i][j];
		}
    }
	
	// Hidden-Layer zu Output-Layer
    for (int i = 1; i <= hidden_layer; ++i) {
        for (int j = 1; j <= output_layer; ++j) {
			file >> w2[i][j];
		}
    }
	
	file.close();
}

void perceptron() {
    for (int i = 1; i <= hidden_layer; ++i) {
		ihidden_layer[i] = 0.0;
	}

    for (int i = 1; i <= output_layer; ++i) {
		ioutput_layer[i] = 0.0;
	}

    for (int i = 1; i <= input_layer; ++i) {
        for (int j = 1; j <= hidden_layer; ++j) {
            ihidden_layer[j] += out1[i] * w1[i][j];
		}
	}

    for (int i = 1; i <= hidden_layer; ++i) {
		out2[i] = sigmoid_function(ihidden_layer[i]);
	}

    for (int i = 1; i <= hidden_layer; ++i) {
        for (int j = 1; j <= output_layer; ++j) {
            ioutput_layer[j] += out2[i] * w2[i][j];
		}
	}

    for (int i = 1; i <= output_layer; ++i) {
		out3[i] = sigmoid_function(ioutput_layer[i]);
	}
}

// L2 error
double square_error(){
    double res = 0.0;
    for (int i = 1; i <= output_layer; ++i) {
        res += (out3[i] - expected[i]) * (out3[i] - expected[i]);
	}
    res *= 0.5;
    return res;
}

// Graustufenbilder mit den zugehörigen Labels einlesen
int input() {
	// Bilder einlesen
    char number;
    for (int j = 1; j <= height; ++j) {
        for (int i = 1; i <= width; ++i) {
            image.read(&number, sizeof(char));
            if (number == 0) {
				d[i][j] = 0; 
			} else {
				d[i][j] = 1;
			}
        }
	}

    for (int j = 1; j <= height; ++j) {
        for (int i = 1; i <= width; ++i) {
            int pos = i + (j - 1) * width;
            out1[pos] = d[i][j];
        }
	}

	// Labels einlesen
    label.read(&number, sizeof(char));
    for (int i = 1; i <= output_layer; ++i) {
		expected[i] = 0.0;
	}
    expected[number + 1] = 1.0;
        
    return (int)(number);
}

// Main
int main(int argc, char *argv[]) {
	
	info(false);
	
    output.open(test_output.c_str(), ios::out);
    image.open(test_images.c_str(), ios::in | ios::binary); // Binärdatei mit den Bildern
    label.open(test_labels.c_str(), ios::in | ios::binary ); // Binärdatei mit den Labels

	// Dateiheader lesen
    char number;
    for (int i = 1; i <= 16; ++i) {
        image.read(&number, sizeof(char));
	}
    for (int i = 1; i <= 8; ++i) {
        label.read(&number, sizeof(char));
	}
		
	// Initalisierung des neuronalen Netes
    init_array(); // Speicherzuweisung
    load_model(); // Lädt die Gewichte des trainieren neuronalen Netzes
    
    int correct = 0;
    for (int sample = 1; sample <= test_amount; ++sample) {
        cout << "Testbild Nr. " << sample << endl;
        
        // Getting (image, label)
        int label = input();
		
		// Klassifizierung
        perceptron();
        
        // Vorhersage
        int predict = 1;
        for (int i = 2; i <= output_layer; ++i) {
			if (out3[i] > out3[predict]) {
				predict = i;
			}
		}
		--predict;

		double error = square_error();
		printf("Fehler: %0.6lf\n", error);
		
		if (label == predict) {
			++correct;
			cout << "Klassifizierung: JA, Label: " << label << ", Vorhersage: " << predict << endl << endl;
            output << "Testbild Nr. " << sample << ": JA. Label = " << label << ". Vorhersage: " << predict << ", Fehler = " << error << endl;
		} else {
			cout << "Klassifizierung: NEIN, Label: " << label << ", Vorhersage: " << predict << endl;
            cout << "Bild:" << endl;
            for (int j = 1; j <= height; ++j) {
                for (int i = 1; i <= width; ++i) {
                    cout << d[i][j];
                }
                cout << endl;
            }
            cout << endl;
            output << "Testbild Nr. " << sample << ": NEIN,  Label = " << label << ", Vorhersage: " << predict << ", Fehler: " << error << endl;
		}
    }

    // Zusammenfassung
    double accuracy = (double)(correct) / test_amount * 100.0;
    cout << "Anzahl korrekter Vorhersagen: " << correct << " / " << test_amount << endl;
    printf("Genauigkeit: %0.2lf\n", accuracy);

    output << "Anzahl korrekter Vorhersagen: " << correct << " / " << test_amount << endl;
    output << "Genauigkeit: " << accuracy << "%" << endl;

    output.close();
    image.close();
    label.close();
    
    return 0;
}
