#include <cstdio>
#include <algorithm>
#include <iostream>
#include "GeneticAlgorithm.h"

#define MUTATION_PROBABILITY 5

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

bool GeneticAlgorithm::isInRage(int id) {
    if (id >= mPopulationSize)
        return false;

    return true;
}

void GeneticAlgorithm::calculateFitness(GAL_FitnessFunction func, void* context) {
    for (int i=0 ; i < population.size() ; i++) {
        population[i].calculateFitness(func, context);
    }
}


void GeneticAlgorithm::crossOver() {
    std::vector<Individual> newIndividuals;
    for (int i=0 ; i < mPopulationSize ; i = i + 2) {
        if (i+1 >= mPopulationSize)
            continue;

        Individual newIndividual;

        for(int j=0 ; j< mIndividualSize ; j++) {
            if(rand() % 2) {
                newIndividual.genes.push_back(population[i].genes[j]);
            }
            else {
                newIndividual.genes.push_back(population[i+1].genes[j]);
            }

            // Check for mutation
            int mutationAux = rand() % 101;
            if (mutationAux <= MUTATION_PROBABILITY) {
                //TODO: Right now mutation only works for 0 or 1 values
                if (newIndividual.genes[j] == 0) {
                    newIndividual.genes[j] = 1;
                }
                else {
                    newIndividual.genes[j] = 0;
                }
            }
        }

        newIndividuals.push_back(newIndividual);
    }

    // Replace last n/2 individuals with the new ones
    int firstIndex = population.size() / 2;
    int newIndex = 0;
    for (int i = firstIndex; i < population.size(); i++) {
        population[i] = newIndividuals[newIndex++];
    }
}

void GeneticAlgorithm::printIndividual(int id) {
    population[id].printIndividual(id);
}

Individual GeneticAlgorithm::getIndividual(int id) {
    return population[id];
}

void GeneticAlgorithm::sortIndividuals(GAL_SortFunction sortFunction, void* context) {
    std::sort(population.begin(), population.end(), [=](const Individual &i1, const Individual &i2){
        return sortFunction(context, i1.fitness, i2.fitness);
    });
}

int GeneticAlgorithm::getPopulationSize() {
    return mPopulationSize;
}