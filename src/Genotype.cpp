#include "Genotype.h"

Genotype::~Genotype()
{
    for(int i = 0; i < countGene; i++)
    {
        delete gens[i];
    }
    delete [] gens;
    delete ml;
}

int Genotype::getNum()
{
    return num;
}

int Genotype::getCountGene()
{
    return countGene;
}

typeGene Genotype::getGeneType(int num)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->getType();
    }
    return tgNone;
}

double Genotype::getGeneValue(int num)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->getValue();
    }
    return 0;
}

double Genotype::getGeneValueMax(int num)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->getValueMax();
    }
    return 0;
}

double Genotype::getGeneValueMin(int num)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->getValueMin();
    }
    return 0;
}

typeCrossing Genotype::getTypeCrossing()
{
    return typeC;
}

bool Genotype::getMaskCrossingValue(int num)
{
    if(num >= 0 && num < countGene)
    {
        return maskCrossing[num];
    }
    return false;
}

double Genotype::getCoeffMutation()
{
    return coeffMutation;
}

bool Genotype::setGeneType(int num, typeGene tg)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->setType(tg);
    }
    return false;
}

bool Genotype::setGeneValue(int num, double value)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->setValue(value);
    }
    return false;
}

bool Genotype::setGeneValueMax(int num, double valueMax)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->setValueMax(valueMax);
    }
    return false;
}

bool Genotype::setGeneValueMin(int num, double valueMin)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->setValueMin(valueMin);
    }
    return false;
}

bool Genotype::setGeneStable(int num, double stable)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->setStable(stable);
    }
    return false;
}

bool Genotype::setTypeCrossing(typeCrossing typeC)
{
    this->typeC = typeC;
    return true;
}

bool Genotype::setMaskCrossingValue(int num, bool value)
{
    if(num >= 0 && num < countGene)
    {
        return maskCrossing[num] = value;
    }
    return false;
}

bool Genotype::setCoeffMutation(double coeffMutation)
{
    this->coeffMutation = coeffMutation;
    return true;
}

std::complex <double> Genotype::getTarget(int index)
{
    if(targets.empty() || index < 0 || index > targets.size())
        return 0;

    return targets[index];
}

bool Genotype::setTarget(std::complex <double> target, int index)
{
    if(targets.empty() || index < 0 || index > targets.size())
        return false;

    targets[index] = target;

    return true;
}

bool Genotype::addTarget(std::complex <double> target)
{
    targets.push_back(target);
    return true;
}

bool Genotype::delTarget(int index)
{
    /*std::vector<std::complex <double> >::iterator it = targets.begin();
    std::advance(it, index);
    targets.erase(it);
    return true;*/

    targets.erase(targets.begin() + index);
    return true;
}

std::vector <int> Genotype::getAml(int index)
{
    if(aml.empty() || index < 0 || index > aml.size())
        return std::vector <int>();

    return aml[index];
}

bool Genotype::setAml(std::vector <int> value, int index)
{
    if(aml.empty() || index < 0 || index > aml.size())
        return false;

    aml[index] = value;
    gens[index]->setValueMax(value.size());

    return true;
}

bool Genotype::delAml(int index)
{
    if(aml.empty() || index < 0 || index > aml.size())
        return false;

    aml[index].clear();
    gens[index]->setValueMax(ml->getCountMaterial());

    return true;
}


