#include <cstdlib>
#include <cstdio>
#include "Individual.h"

// Individual
Individual::Individual() {
    fitness = 0;
}

Individual::Individual(int size, int min, int max) {
    genes.resize(size);

    for (int i = 0 ; i < size ; i++) {
        genes[i] = (rand() % ((max-min)+1)) + min;
    }

    fitness = 0;
}

void Individual::printIndividual(int id) {
    printf("=== Individual %d ===\n", id);
    printf("Genes: ");
    for (auto i = genes.begin(); i != genes.end(); i++) {
        printf ("%d",*i);
    }
    printf("\n");

    printf("Fitness: %.2f\n", fitness);
}

float Individual::calculateFitness(GAL_FitnessFunction fitnessFunction, void* context) {
    std::vector<int> genes_int(genes.size());

    for(int i=0 ; i < genes.size(); i++) {
        genes_int[i] = genes[i];
    }

    fitness = fitnessFunction(context, genes_int.data(), genes.size());
    return fitness;
}
