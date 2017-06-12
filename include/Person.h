#ifndef PERSON_H
#define PERSON_H

#include <stdlib.h>

#include "Gene.h"

class PersonManager;

class Person
{
    public:
        friend PersonManager;

        Person(Person & p);
        ~Person();

        int getNumGenotype();
        double getFitness();
        int getCountGene();

        typeGene getGeneType(int num);
        double getGeneValue(int num);
        double getGeneValueMax(int num);
        double getGeneValueMin(int num);

    private:
        Person();
        //Person(int countGene);

        Gene getGene(int num);

        int numGenotype;
        double fitness;
        int countGene;
        Gene **gens;
};

#endif // PERSON_H
