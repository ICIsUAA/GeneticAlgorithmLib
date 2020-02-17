#ifndef GENETICALGORITHMLIB_GENETICALGORITHM_H
#define GENETICALGORITHMLIB_GENETICALGORITHM_H

#include <vector>
#include <public/GeneticAlgorithmLib.h>

class Individual{
public:
    Individual(int size, int min, int max);
    std::vector<int> genes;
    float fitness;

    void printIndividual(int id);
    float calculateFitness(GAL_FitnessFunction fitnessFunction);

};

class GeneticAlgorithm {
private:
    std::vector<Individual> population;
    int mPopulationSize, mIndividualSize;
    int mMinGene, mMaxGene;

public:
    GeneticAlgorithm(int population, int individualSize, int minGene, int maxGene);

    void calculateFitness(GAL_FitnessFunction fitnessFunction);
    void crossOver();
    void printIndividual(int id);
    Individual getIndividual(int id);
};

#endif //GENETICALGORITHMLIB_GENETICALGORITHM_H
