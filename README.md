# High Performance Computing WiSe 21/22

MNIST dataset source: http://yann.lecun.com/exdb/mnist/


Compile train.cpp:
```
g++ -c train.cpp -o train.o -fopenmp
g++ train.o -o train -fopenmp -lpthread
```

Compile test.cpp:
```
g++ -c test.cpp -o test.o -fopenmp
g++ test.o -o test -fopenmp -lpthread
```