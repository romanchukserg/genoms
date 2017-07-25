#ifndef GENOTYPE_H
#define GENOTYPE_H

#include "Gene.h"
#include "MaterialList.h"
#include <complex>
#include <vector>

enum typeCrossing{ tcOnePoint, tsMultiPoint, tcMask };

class GenotypeManager;

class Genotype
{
    public:
        friend GenotypeManager;

        virtual ~Genotype();
        virtual double calculateFitness(Gene ** gens) = 0;
        virtual bool getDielectric(Gene ** gens, double & re, double & im) = 0;

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

        bool setGeneType(int num, typeGene tg);
        bool setGeneValue(int num, double value);
        bool setGeneValueMax(int num, double valueMax);
        bool setGeneValueMin(int num, double valueMin);
        bool setGeneStable(int num, double stable);

        bool setTypeCrossing(typeCrossing typeC);
        bool setMaskCrossingValue(int num, bool value);

        bool setCoeffMutation(double coeffMutation);

        std::complex <double> getTarget(int index);
        bool setTarget(std::complex <double> target, int index);
        bool addTarget(std::complex <double> target);
        bool delTarget(int index);

    protected:
        Genotype(){};

        int num;
        int countGene;
        Gene **gens;

        typeCrossing typeC;
        bool * maskCrossing;

        double coeffMutation;

        std::vector<std::complex <double> > targets;

        MaterialList * ml;
};

#endif // GENOTYPE_H
