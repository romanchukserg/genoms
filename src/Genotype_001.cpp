#include "Genotype_001.h"

Genotype_001::Genotype_001()
{
    num = 1;
    countGene = 4;
    gens = new Gene * [countGene];
    gens[0] = new Gene(tgLength, 500.0, 1000.0, 400.0, 1.0);
    gens[1] = new Gene(tgVolume, 0.0, 1.0, 0.0, 1.0);
    gens[2] = new Gene(tgMatter, 0.0, 4.0, 0.0, 1.0);
    gens[3] = new Gene(tgMatter, 0.0, 4.0, 0.0, 1.0);

    typeC = tcOnePoint;
    maskCrossing = new bool[countGene];
    maskCrossing[0] = false;
    maskCrossing[1] = false;
    maskCrossing[2] = true;
    maskCrossing[3] = true;

    coeffMutation = 0.3;

    target.real(1);
    target.imag(1);

    ml = new MaterialList();//("mlData.bin", "none");
}

double Genotype_001::calculateFitness(Gene ** gens)
{
    double re, re1, re2;
    double im, im1, im2;

    ml->getMaterialNear(gens[2]->getValue(), gens[0]->getValue(), re1, im1);
    ml->getMaterialNear(gens[3]->getValue(), gens[0]->getValue(), re2, im2);

    re = re1 * gens[1]->getValue() + re2 * (1.0 - gens[1]->getValue());
    im = im1 * gens[1]->getValue() + im2 * (1.0 - gens[1]->getValue());

    double a = sqrt((target.real()*target.real()) + (target.imag()*target.imag()));
    double b = sqrt((target.real() - re)*(target.real() - re) + (target.imag() - im)*(target.imag() - im));

    //std::cout << " - " << gens[2]->getValue() << " - " << gens[3]->getValue();
    //if(ml->getMaterialNearIm(0, 400, re))
    //std::cout << " - " << ml->getCountMaterial();
    return b/a;
}