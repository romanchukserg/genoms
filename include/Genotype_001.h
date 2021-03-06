#ifndef GENOTYPE_001_H
#define GENOTYPE_001_H

#include "Gene.h"
#include "Genotype.h"

class Genotype_001 : public Genotype
{
    public:
        Genotype_001();
        virtual double calculateFitness(Gene ** gens);
        virtual bool getDielectric(Gene ** gens, double & re, double & im);
};

#endif // GENOTYPE_001_H
