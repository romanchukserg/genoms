#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H

#include "Person.h"
#include "Gene.h"
#include "Genotype.h"
#include "GenotypeManager.h"

#include <iostream>

class PersonManager
{
    public:
        static bool ini(Genotype & gt);

        static Person * create();
        static Person * create(Person & person);

        static bool mutation(Person & person);
        static bool crossing(Person & parent1, Person & parent2, Person ** child1, Person ** child2);
        static bool calculateFitness(Person & person);

    private:
        PersonManager(){};

        static Genotype * GENOTYPE;
};



#endif // PERSONMANAGER_H
