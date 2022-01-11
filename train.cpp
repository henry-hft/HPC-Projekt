#include "header.hpp"

// Von Layer 1 zu Layer 2 bzw. Input-Layer zu Hidden-Layer
double *global_w1[input_layer];

// Von Layer 2 zu Layer 3 bzw. Hidden-Layer zu Output-Layer
double *global_w2[hidden_layer];


double mnist_training_data[60000][784];
double mnist_label_data[60000][10];

// File stream für Messergebnisse
ofstream report;

void read_images()
{
    //"mnist/train-images.idx3-ubyte"
    ifstream file (train_images,ios::in | ios::binary);
    if (file.is_open())
    {
        int magic_number = 0;
        int number_of_images = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*)&magic_number,sizeof(magic_number));
        magic_number= reverse_integer(magic_number);
        file.read((char*)&number_of_images,sizeof(number_of_images));
        number_of_images= reverse_integer(number_of_images);
        file.read((char*)&n_rows,sizeof(n_rows));
        n_rows= reverse_integer(n_rows);
        file.read((char*)&n_cols,sizeof(n_cols));
        n_cols= reverse_integer(n_cols);
		
        for(int i=0;i<number_of_images;++i)
        {
            for(int r = 0; r < n_rows; ++r)
            {
                for(int c = 0; c < n_cols; ++c)
                {
                    unsigned char temp = 0;
                    file.read((char*)&temp,sizeof(temp));
                    if(temp == 0){
                        mnist_training_data[i][(n_rows*r)+c]= (double)temp;
                    }
                    else {
                        mnist_training_data[i][(n_rows*r)+c]=1;
                    }
                    
                }
            }
        }
    }
    file.close();
}
void read_labels(){
    //"mnist/train-labels.idx1-ubyte"
    ifstream file (train_labels,ios::in | ios::binary);

    if (file.is_open()){
        int num = 0;
        int magic_number = 0;
        int n_rows = 0;
        int n_cols = 0;
        file.read((char*) &magic_number, sizeof(magic_number));
        magic_number = reverse_integer(magic_number);
        file.read((char*) &num,sizeof(num));
        num = reverse_integer(num);

        for(int i = 0; i < train_amount; ++i) {
            unsigned char temp = 0;

            file.read((char*) &temp, sizeof(temp));

            int number = (double)temp;
            
            for (int j = 0; j < output_layer; ++j) {
                mnist_label_data[i][j] = 0.0;
            }
            mnist_label_data[i][number] = 1.0;

        }

    }
}

// Speicherzuweisung
void initialize(){
	for (int i = 0; i < input_layer; ++i) {
        global_w1[i] = new double[hidden_layer];
    }

	// on Layer 2 zu Layer 3 bzw. Hidden-Layer zu Output-Layer
    for (int i =0; i < hidden_layer; ++i) {
        global_w2[i] = new double[output_layer];
    }
	// Initalisierung der Gewichte vom Input-Layer zu Hidden-Layer
    for (int i = 0; i < input_layer; ++i) {
        for (int j = 0; j < hidden_layer; ++j) {
            
            global_w1[i][j] = 0.2;
        }
	}
	
	// Initalisierung der Gewichte vom Hidden-Layer zum Output-Layer
    for (int i = 0; i < hidden_layer; ++i) {
        for (int j = 0; j < output_layer; ++j) {
            
            global_w2[i][j] = 0.3;
        }
	}
}

// Gewichte in Datei Speichern
void save_weights() {
    ofstream file(model.c_str(), ios::out);
	
	// Input-Layer zu Hidden-Layer
    for (int i = 0; i < input_layer; ++i) {
        for (int j =0; j < hidden_layer; ++j) {
			file << global_w1[i][j] << " ";
		}
		file << endl;
    }
	
	// Hidden-Layer zu Output-Layer
    for (int i = 0; i < hidden_layer; ++i) {
        for (int j = 0; j < output_layer; ++j) {
			file << global_w2[i][j] << " ";
		}
        file << endl;
    }
	
	file.close();
}

// Main
int main(int argc, char *argv[]) {
    read_images();
    read_labels();
    
    info(true);

    report.open(report_fn.c_str(), ios::out);
		
	cout << "Start Training..." << endl;
	
	// Initalisierung des neuronalen Netzes
    clock_t begin = clock();
	initialize();
    int sample_per_thread = train_amount / THREADS;
    #pragma omp parallel num_threads(THREADS) default(none) shared(cout, mnist_label_data,mnist_training_data,sample_per_thread,global_w2,global_w1)
    {
        const string model = "model/model.txt";
        
		// Von Layer 1 zu Layer 2 bzw. Input-Layer zu Hidden-Layer
        double w1[784][128], delta1[784][128], out1[784];

        // Von Layer 2 zu Layer 3 bzw. Hidden-Layer zu Output-Layer
        double w2[128][10], delta2[128][10], ihidden_layer[128], out2[128], theta2[128];

        // Layer 3 bzw. Output-Layer
        double ioutput_layer[10], out3[10], theta3[10];
        double expected[10];


        for (int i = 0; i < input_layer; ++i) {
            for (int j = 0; j < hidden_layer; ++j) {
                int sign = rand() % 2;
                 
                w1[i][j] = (double)(rand() % 6) / 10.0;
                if (sign == 1) {
                    w1[i][j] = - w1[i][j];
                }
            }
        }
		
        // Initalisierung der Gewichte vom Hidden-Layer zum Output-Layer
        for (int i = 0; i < hidden_layer; ++i) {
            for (int j = 0; j < output_layer; ++j) {
                int sign = rand() % 2;

                w2[i][j] = (double)(rand() % 10) / (10.0 * output_layer);
                if (sign == 1) {
                    w2[i][j] = - w2[i][j];
                }
            }
        }

        for(int r = 0; r < epochs; r++){
            #pragma omp for 
            for (int sample =0; sample < train_amount; ++sample) {

                for (int i =0; i < 784; ++i) {
                    out1[i] = mnist_training_data[sample][i];
                }
                for (int i = 0; i < output_layer; ++i) {
                    expected[i] = mnist_label_data[sample][i];
                }


                // Lernprozess
                for (int i = 0; i < input_layer; ++i) {
                    for (int j = 0; j < hidden_layer; ++j) {
                        delta1[i][j] = 0.0;
                    }
                }

                for (int i = 0; i < hidden_layer; ++i) {
                    for (int j = 0; j < output_layer; ++j) {
                        delta2[i][j] = 0.0;
                    }
                }

                for (int i = 0; i < epochs; ++i) {

                    for (int j = 0; j < hidden_layer; ++j) {
                        ihidden_layer[j] = 0.0;
                    }

                    for (int j = 0; j < output_layer; ++j) {
                        ioutput_layer[j] = 0.0;
                    }

                    for (int j = 0; j < input_layer; ++j) {
                        for (int x = 0; x < hidden_layer; ++x) {
                            ihidden_layer[x] += out1[j] * w1[j][x];
                        }
                    }

                    for (int j = 0; j < hidden_layer; ++j) {
                        out2[j] = sigmoid_function(ihidden_layer[j]);
                    }

                    for (int j = 0; j < hidden_layer; ++j) {
                        for (int x = 0; x < output_layer; ++x) {
                            ioutput_layer[x] += out2[j] * w2[j][x];
                        }
                    }

                    for (int j = 0; j < output_layer; ++j) {
                        out3[j] = sigmoid_function(ioutput_layer[j]);
                    }

                    double sum;
                    for (int j = 0; j < output_layer; ++j) {
                        theta3[j] = out3[j] * (1 - out3[j]) * (expected[j] - out3[j]);
                    }

                    for (int j = 0; j < hidden_layer; ++j) {
                        sum = 0.0;
                        for (int x = 0; x < output_layer; ++x) {
                            sum += w2[j][x] * theta3[x];
                        }
                        theta2[j] = out2[j] * (1 - out2[j]) * sum;
                    }

                    for (int j = 0; j < hidden_layer; ++j) {
                        for (int x = 0; x < output_layer; ++x) {
                            delta2[j][x] = (learning_rate * theta3[x] * out2[j]) + (0.9 * delta2[j][x]);
                            w2[j][x] += delta2[j][x];
                            
                        }
                    }

                    for (int j = 0; j < input_layer; ++j) {
                        for (int x = 0; x < hidden_layer; x++ ) {
                            delta1[j][x] = (learning_rate * theta2[x] * out1[j]) + (0.9 * delta1[j][x]);
                            w1[j][x] += delta1[j][x];
                        }
                    }
                }
                if((sample + 1) % sample_per_thread == 0)
                {
                    for (int i =0; i < input_layer; ++i) {
                        for (int j = 0; j < hidden_layer ; j++ ) {
                            #pragma omp critical
                            {
                                global_w1[i][j] += w1[i][j];
                            }
                        }
                    }
                    for (int i =0; i < hidden_layer; ++i) {
                        for (int j = 0; j < output_layer ; j++ ) {
                            #pragma omp critical
                            {
                                global_w2[i][j] += w2[i][j];
                            }
                        }
                    }
                }
            }                       
        }
    }
	cout << "Training beendet!" << endl;
	clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Laufzeit: " << elapsed_secs << " Sekunden" << " (" << THREADS << " Threads" << ")" << endl;
	cout << elapsed_secs / THREADS << " Sekunden pro Thread" << endl;
    for (int i =0; i < input_layer; ++i) {
        for (int j = 0; j < hidden_layer; j++ ) {
           global_w1[i][j] /= THREADS;
            
        }
    }
    for (int i =0; i < hidden_layer; ++i) {
        for (int j = 0; j < output_layer; j++ ) {
          global_w2[i][j] /= THREADS;
            
        }
    }

	// Neuronales Netz speichern
    save_weights();
    report << "Laufzeit: " << elapsed_secs << " Sekunden" << " (" << THREADS << " Threads" << ")" << endl;
    report.close();
    
    return 0;
}
