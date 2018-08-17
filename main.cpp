#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <fstream>
#include <math.h>
#include <random>

#define N_OF_INPUT_NODES 4
#define N_OF_HIDDEN_NODES 32
#define LEARNING_RATE 0.05
#define MAX_ERROR 0.05

double w_input_hidden[N_OF_INPUT_NODES][N_OF_HIDDEN_NODES];
double w_hidden_output[N_OF_HIDDEN_NODES];

double a_input[N_OF_INPUT_NODES];
double a_hidden[N_OF_HIDDEN_NODES];
double a_output[1];

double in_input[N_OF_INPUT_NODES];
double in_hidden[N_OF_HIDDEN_NODES];
double in_output[1];

double delta_input[N_OF_INPUT_NODES];
double delta_hidden[N_OF_HIDDEN_NODES];
double delta_output[1];

unsigned int epochs = 0;

double sigmoid(double v){
    return 1.0 / (1.0 + std::exp(-v));
}

double sigmoidDerivatived(double v){
    return std::exp(-v) / std::pow(1.0 + std::exp(-v), 2);
}

void back_prop_learning(std::vector<std::vector<int> > examples){

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1.0, 1.0);

    for(unsigned int i=0; i<N_OF_INPUT_NODES; i++)
        for(unsigned int j=0; j<N_OF_HIDDEN_NODES; j++)
            w_input_hidden[i][j] = distribution(generator);

    for(unsigned int i=0; i<N_OF_HIDDEN_NODES; i++)
        w_hidden_output[i] = distribution(generator);

    bool stop;
    do{
        stop = true;
        epochs++;
        for(unsigned int i=0; i<examples.size(); i++){

            for(unsigned int j=0; j<examples[i].size()-1; j++)
                a_input[j] = examples[i][j];

            for(unsigned int j=0; j<N_OF_HIDDEN_NODES; j++){
                in_hidden[j] = 0;
                for(unsigned int k=0; k<N_OF_INPUT_NODES; k++)
                    in_hidden[j] += w_input_hidden[k][j] * a_input[k];
                a_hidden[j] = sigmoid(in_hidden[j]);
            }
            in_output[0] = 0;
            for(unsigned int k=0; k<N_OF_HIDDEN_NODES; k++)
                in_output[0] += w_hidden_output[k] * a_hidden[k];
            a_output[0] = sigmoid(in_output[0]);

            delta_output[0] = sigmoidDerivatived(in_output[0]) * (examples[i][examples[i].size()-1] - a_output[0]);

            for(unsigned int k=0; k<N_OF_HIDDEN_NODES; k++)
                delta_hidden[k] = sigmoidDerivatived(in_hidden[k]) * w_hidden_output[k] * delta_output[0];

            for(unsigned int k=0; k<N_OF_INPUT_NODES; k++){
                delta_input[k] = 0;
                for(unsigned int j=0; j<N_OF_HIDDEN_NODES; j++)
                    delta_input[k] += w_input_hidden[k][j] * delta_hidden[j];
                delta_input[k] *= sigmoidDerivatived(in_input[k]);
            }

            for(unsigned int k=0; k<N_OF_INPUT_NODES; k++)
                for(unsigned int j=0; j<N_OF_HIDDEN_NODES; j++)
                    w_input_hidden[k][j] += LEARNING_RATE * a_input[k] * delta_hidden[j];

            for(unsigned int k=0; k<N_OF_HIDDEN_NODES; k++)
                w_hidden_output[k] += LEARNING_RATE * a_hidden[k] * delta_output[0];

            if(std::abs(examples[i][examples[i].size()-1] - a_output[0]) > MAX_ERROR){
                /* Uncomment to see which examples aren't learned yet
                for(unsigned int j=0; j<N_OF_INPUT_NODES; j++)
                    std::cout << examples[i][j];
                std::cout << "\texpected: " << examples[i][examples[i].size()-1] << " got: " << a_output[0] << "  \terror: " << std::abs(examples[i][examples[i].size()-1] - a_output[0]) << std::endl;
                */
                stop = false;
            }
        }
    }while(!stop);

    std::cout << "\nNumber of times that the examples where analized: " << epochs << std::endl;
}

double test_network(int test[]){

    for(unsigned int i=0; i<N_OF_INPUT_NODES; i++)
        a_input[i] = test[i];

    for(unsigned int j=0; j<N_OF_HIDDEN_NODES; j++){
        in_hidden[j] = 0;
        for(unsigned int k=0; k<N_OF_INPUT_NODES; k++)
            in_hidden[j] += w_input_hidden[k][j] * a_input[k];
        a_hidden[j] = sigmoid(in_hidden[j]);
    }
    in_output[0] = 0;
    for(unsigned int k=0; k<N_OF_HIDDEN_NODES; k++)
        in_output[0] += w_hidden_output[k] * a_hidden[k];
    a_output[0] = sigmoid(in_output[0]);

    return a_output[0];
}

int main(int argc, char const *argv[]){

    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " <FILE_WITH_EXAMPLES>" << std::endl;
        return 1;
    }
    
    //Put examples in to a vector
    std::ifstream csvFile;
    csvFile.open(argv[1], std::ifstream::in);

    //Load everything in to a vector
    std::string buffer;
    std::vector<std::vector<int> > examples;

    while(std::getline(csvFile, buffer)){
        std::vector<int> aux;
        size_t last = 0;
        size_t next = 0;
        while((next = buffer.find(" ", last)) != std::string::npos){
            aux.push_back(std::stoi(buffer.substr(last, next-last)));
            last = next + 1;
        }
        aux.push_back(std::stoi(buffer.substr(last)));

        examples.push_back(aux);
    }

    back_prop_learning(examples);



    std::string input_str;

    int size;
    int input[N_OF_INPUT_NODES];

    std::cout << "\n\nPlease insert the number of tests that you want to make: ";
    std::cin >> size;

    for(unsigned int i=0; i<size; i++){
        std::cout << "\nInsert a input: ";
        for(unsigned int j=0; j<N_OF_INPUT_NODES; j++){
            std::cin >> input_str;
            input[j] = input_str[0] - '0';
        }
        
        double result = test_network(input);
        std::cout << "Output: " << result << std::endl;
    }


    return 0;
}
