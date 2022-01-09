// MNIST Datensatz
const string folder = "mnist/";

// Trainingsdaten
// Labels
extern const string train_labels = folder + "train_labels.dat";
// Bilder
extern const string train_images = folder + "train_images.dat";

// Anzahl der Traningsbilder
const int train_amount = 60000;


// Testdaten
// Labels
extern const string test_labels = folder + "test_labels.dat";
// Bilder
extern const string test_images = folder + "test_images.dat";

// Anzahl der Testbilder
extern const int test_amount = 10000;

// Größe der Bilder in Pixel
extern const int width = 28;
extern const int height = 28;


// Datei, die die trainierten Gewichte enthält
extern const string model = "model.txt";

// Ausgabedatei Training
extern const string train_output = "train_output.csv";

// Ausgabedatei Test
extern const string test_output = "test_output.txt";

// Input Layer
// Anzahl der Input-Neuronen
// Ein Input-Neuronen pro Pixel. Da die Bilder in Grauwerten gespeichert sind, koennen diese Werte zwsichen 0 und 255 annehmen.
extern const int input = width * height; // 28 * 28 = 784 (784 Neuronen)

// Hidden Layer
extern const int hidden = 128; // 128 Neuronen

// Output Layer
extern const int output = 10; // 0-9 (10 moegliche Ausgaenge), 10 Neuronen

// Anzahl der Durchläufe durch das Traningsset
extern const int epochs = 512;

// Lernrate
extern const double learning_rate = 0.001;


// Sigmoidfunktion
double sigmoid_function(double x) {
    double result;
    result = 1 / (1 + exp(-x));
    return result;
}


// Info
void info() {
    cout << "HPC-Computing Projekt WiSe 21/22 (Neuronales Netz für MNIST Datensatz)" << endl;
    cout << "Input-Layer: " << input << " Neuronen" << endl;
    cout << "Hidden-Layer: " << hidden << " Neuronen" << endl;
    cout << "Output-Layer: " << output << " Neuronen" << endl;
    cout << "Anzahl Epochen: " << epochs << endl;
    cout << "Lernrate: " << learning_rate << endl;
    cout << "Trainingsdaten (Bilder): " << train_images << endl;
    cout << "Trainingsdaten (Labels): " << train_labels << endl;
    cout << "Anzahl Trainingsdaten: " << train_amount << endl << endl;
}
