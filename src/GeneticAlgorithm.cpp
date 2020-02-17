#include <cstdio>
#include <algorithm>
#include "GeneticAlgorithm.h"

// Genetic Algorithm
GeneticAlgorithm::GeneticAlgorithm(int population, int individualSize, int minGene, int maxGene) {
    mPopulationSize = population;
    mIndividualSize = individualSize;
    mMaxGene = maxGene;
    mMinGene = minGene;
    this->population.clear();

    //Fill population with new individuals
    while(population--) {
        this->population.push_back(Individual(individualSize, minGene, maxGene));
    }
}

void GeneticAlgorithm::calculateFitness(GAL_FitnessFunction func) {
    for (int i=0 ; i < population.size() ; i++) {
        population[i].calculateFitness(func);
    }
}


void GeneticAlgorithm::crossOver() {
    //TODO: Crossover
    int cnt = 1;
    for (int i=0 ; i < mPopulationSize ; i = i + 2) {
        if (i+1 >= mPopulationSize)
            continue;

        Individual newIndividual;

        for(int j=0 ; j< mIndividualSize ; j++){
            if(rand()%2){
                newIndividual.genes.push_back(population[i].genes[j]);
            }
            else{
                newIndividual.genes.push_back(population[i+1].genes[j]);
            }
        }

        population.push_back(newIndividual);
    }
}

void GeneticAlgorithm::printIndividual(int id) {
    //TODO: Check provided id is in range
    population[id].printIndividual(id);
}

Individual GeneticAlgorithm::getIndividual(int id) {
    return population[id];
}

void GeneticAlgorithm::sortIndividuals(GAL_SortFunction sortFunction) {
    std::sort(population.begin(), population.end(), [sortFunction](const Individual &i1, const Individual &i2){
        return sortFunction(i1.fitness, i2.fitness);
    });
}

int GeneticAlgorithm::getPopulationSize() {
    return mPopulationSize;
}