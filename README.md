# XOR-Neural-Network
Fourth project for the subject Artificial Inteligence, which consisted in developing a neural network to analize a binary number and output a result telling if the number had en even or odd number of ones (XOR).
Our implementation was in C++.


### Compilation
``` bash
$ g++ -O3 main.cpp -o main
```

### Usage
#### Execution
``` bash
$ ./main examples_file
```

#### Output
The output of the network will be 0 if the binary number has an even number of zeros or 1 if it has an odd number of ones.

#### Changing variables
To change the number of input and/or hidden nodes, simple edit the constants N_OF_INPUT_NODES and/or N_OF_HIDDEN_NODES in file main.cpp.

When executing the program, the weights of the nodes in the neural network will be calculated and when the learning has finished (error < 0.05), you will be able to test it.

You can also change the learning rate and/or maximum error allowed in the network by changing the constants LEARNING_RATE and/or MAX_ERROR in file main.cpp.

To see what examples weren't learned by the network, uncomment lines 92-95 in file main.cpp.


### Files
* main.cpp - Generated the neural network and calculates the output of examples.
* 4.txt, 6.txt - Files with examples for the network to learn (4.txt: number number number number expected_output).


### Authors
* Ana Rita Santos Lopes da Costa - up201605706 - [ritasantos11](https://www.github.com/ritasantos11)
* Frederico Emanuel Almeida Lopes - up201604674 - [FredyR4zox](https://www.github.com/FredyR4zox)
* João Lucas Faria de Pires - up201606617 - [iSynthx](https://www.github.com/iSynthx)
