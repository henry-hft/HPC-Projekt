# High Performance Computing WiSe 21/22

MNIST dataset source: http://yann.lecun.com/exdb/mnist/

![](https://github.com/henry-hft/HPC-Projekt/blob/main/neural_network.png)

Compile train.cpp:
```
g++ -fopenmp train.cpp -o train.out
```

Compile test.cpp:
```
g++ test.cpp -o test.out
```

Run train.out:
```
chmod +x train.out
./train.out
```

Run test.out:
```
chmod +x test.out
./test.out
```
