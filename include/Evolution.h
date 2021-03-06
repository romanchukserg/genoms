#ifndef EVOLUTION_H
#define EVOLUTION_H

#include <iostream>

#include "Person.h"
#include "PersonManager.h"
#include "Genotype.h"
//#include "Gene.h"

class Evolution
{
    public:
        Evolution(int countPerson, int maxAge, double minFitness, Genotype & gt);
        ~Evolution();

        void run();
        void run(double ** st);

    private:
        int maxAge;
        double minFitness;

        int countPerson;
        Person **population;
        Person **parents;
        Person **childs;

        bool clearPopulation();
        bool createPopulation();
        bool crossing();
        bool mutation();
        bool calculationFitness();
        bool selection();
};

#endif // EVOLUTION_H
