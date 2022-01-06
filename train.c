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

// Sigmoidfunktion
double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}
