#ifndef GENOTYPE_H
#define GENOTYPE_H

#include "Gene.h"
#include "MaterialList.h"
#include <complex>

enum typeCrossing{ tcOnePoint, tsMultiPoint, tcMask };

class GenotypeManager;

class Genotype
{
    public:
        friend GenotypeManager;

        virtual ~Genotype();
        virtual double calculateFitness(Gene ** gens) = 0;

        int getNum();
        int getCountGene();
        typeGene getGeneType(int num);
        double getGeneValue(int num);
        double getGeneValueMax(int num);
        double getGeneValueMin(int num);
        double getGeneStable(int num);

        typeCrossing getTypeCrossing();
        bool getMaskCrossingValue(int num);

        double getCoeffMutation();

        std::complex <double> getTarget();

        bool setGeneType(int num, typeGene tg);
        bool setGeneValue(int num, double value);
        bool setGeneValueMax(int num, double valueMax);
        bool setGeneValueMin(int num, double valueMin);
        bool setGeneStable(int num, double stable);

        bool setTypeCrossing(typeCrossing typeC);
        bool setMaskCrossingValue(int num, bool value);

        bool setCoeffMutation(double coeffMutation);

        bool setTarget(std::complex <double> target);

    protected:
        Genotype(){};

        int num;
        int countGene;
        Gene **gens;

        typeCrossing typeC;
        bool * maskCrossing;

        double coeffMutation;

        std::complex <double> target;

        MaterialList * ml;
};

#endif // GENOTYPE_H
