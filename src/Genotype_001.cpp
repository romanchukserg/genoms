#include "Genotype_001.h"

Genotype_001::Genotype_001()
{
    ml = new MaterialList("c:\\MaterialListCreate", "_mlData.bin");

    num = 1;
    countGene = 4;
    gens = new Gene * [countGene];
    gens[0] = new Gene(tgLength, 500.0, 1000.0, 400.0, 1.0);
    gens[1] = new Gene(tgVolume, 0.0, 1.0, 0.0, 1.0);
    gens[2] = new Gene(tgMatter, 0.0, ml->getCountMaterial(), 0.0, 1.0);
    gens[3] = new Gene(tgMatter, 0.0, ml->getCountMaterial(), 0.0, 1.0);

    typeC = tcOnePoint;
    maskCrossing = new bool[countGene];
    maskCrossing[0] = false;
    maskCrossing[1] = false;
    maskCrossing[2] = true;
    maskCrossing[3] = true;

    coeffMutation = 0.3;

    addTarget(std::complex<double>(1, 1));
    //target.real(1);
    //target.imag(1);

    aml.resize(countGene);
}

double Genotype_001::calculateFitness(Gene ** gens)
{
    double re, im;

    if(!getDielectric(gens, re, im))
    {
        return 100;
    }

    double a, b, s = 0;
    //std::complex<double> target;
    std::vector<std::complex<double> >::iterator it = targets.begin();

    for(it = targets.begin(); it != targets.end(); it++)
    {
        a = (*it).real();
        a = sqrt((*it).real()*(*it).real() + (*it).imag()*(*it).imag());
        b = sqrt(((*it).real() - re)*((*it).real() - re) + ((*it).imag() - im)*((*it).imag() - im));
        s += b/a;
    }
    //double a = sqrt((target.real()*target.real()) + (target.imag()*target.imag()));
    //double b = sqrt((target.real() - re)*(target.real() - re) + (target.imag() - im)*(target.imag() - im));

    //std::cout << " - " << gens[2]->getValue() << " - " << gens[3]->getValue();
    //if(ml->getMaterialNearIm(0, 400, re))
    //std::cout << " - " << ml->getCountMaterial();
    return s/targets.size();
}

bool Genotype_001::getDielectric(Gene ** gens, double & re, double & im)
{
    double re1, re2;
    double im1, im2;

    std::complex <double> e, e1, e2;
    int ixM1 = gens[2]->getValue();
    int ixM2 = gens[3]->getValue();

    if(aml[2].size() > 0)  ixM1 = aml[2][gens[2]->getValue()];
    if(aml[3].size() > 0)  ixM2 = aml[3][gens[3]->getValue()];

    //std::cout << aml[2].size() << " . \n";
    //std::cout << aml[3].size() << " . \n";
    //std::cout << ixM1 << "\n";
    //std::cout << ixM2 << "\n";
    //std::cout << gens[index]->getValueMax() << "\n";

    if(!ml->getMaterialNear(ixM1, gens[0]->getValue(), re1, im1) ||
        !ml->getMaterialNear(ixM2, gens[0]->getValue(), re2, im2))
    {
        return false;
    }

    e1.real(re1);
    e1.imag(im1);
    e2.real(re2);
    e2.imag(im2);

    //e = (e1*e2)/(e1*gens[1]->getValue() + e2*(1.0 - gens[1]->getValue()));
    e = e1 * (1.0 - gens[1]->getValue()) + e2 * gens[1]->getValue();

    re = e.real();
    im = e.imag();

    return true;
}
