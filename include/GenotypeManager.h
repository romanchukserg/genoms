#ifndef GENOTYPEMANAGER_H
#define GENOTYPEMANAGER_H

#include "Genotype.h"
#include "Genotype_001.h"

class GenotypeManager
{
    public:
        static Genotype * create(int num);
        static Genotype * create(Genotype & gt);
        static void copyGens(Genotype & src, Gene *** gens);
        static int getCount();

    private:
        GenotypeManager(){};

        static int const COUNT = 1;
};


#endif // GENOTYPEMANAGER_H
