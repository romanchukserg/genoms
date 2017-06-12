#ifndef GENE_H
#define GENE_H

#include <stdlib.h>

#include <iostream>

enum typeGene{ tgLength, tgNone, tgVolume, tgMatter };

class Gene
{
    public:
        Gene(typeGene type, double value, double valueMax, double valueMin, double stable);
        Gene(Gene & gene);

        typeGene getType();
        double getValue();
        double getValueMax();
        double getValueMin();
        double getStable();

        bool setType(typeGene type);
        bool setValue(double value);
        bool setValueMax(double valueMax);
        bool setValueMin(double valueMin);
        bool setStable(double stable);

        bool mutation();

    private:
        Gene(){}

        typeGene type;
        double value;
        double valueMax;
        double valueMin;
        double stable;
};

#endif // GENE_H
