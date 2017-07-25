#include <iostream>

#include <stdlib.h>
#include <time.h>

#include "Evolution.h"
#include "Person.h"
#include "Gene.h"

//using namespace std;

int main()
{
    srand(time(0));

    Genotype * gt = GenotypeManager::create(1);
    gt->setGeneValueMax(1, 0.3);
    gt->setGeneValue(2, 1);
    gt->setGeneStable(2, 0);
    //gt->setGeneValue(3, 9);
    //gt->setGeneStable(3, 0);
    gt->setGeneStable(0, 0);
    gt->setTarget(std::complex<double> (-8.4375, 0.9), 0);

    Evolution *e = new Evolution(100, 1000, 0.001, *gt);
    e->run();
    e->run();
    e->run();
    delete e;
    delete gt;

/*
    MaterialList ml("c:\\MaterialListCreate", "_mlData.bin");
    double re, im;
    ml.getMaterialNear(3.5, 457.6, re, im);
    std::cout << re << " - " << im;
    //std::cout << ml.getCountMaterial();
*/

    return 0;
}
