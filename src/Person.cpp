#include "Person.h"

Person::Person()
{
    numGenotype = 0;
    fitness = -1;
    countGene = 0;
    gens = 0;
}

/*Person::Person(int countGene)
{
    fitness = -1;
    this->countGene = countGene;
    gens = new Gene*[countGene];
}*/

Person::Person(Person & p)
{
    numGenotype = p.numGenotype;
    fitness = p.fitness;
    countGene = p.countGene;
    gens = new Gene*[countGene];
    for(int i = 0; i < countGene; i++)
    {
        gens[i] = new Gene(*p.gens[i]);
    }
}

Person::~Person()
{
    for(int i = 0; i < countGene; i++)
    {
        delete gens[i];
    }
    delete [] gens;
}

int Person::getNumGenotype()
{
    return numGenotype;
}

double Person::getFitness()
{
    return fitness;
}

int Person::getCountGene()
{
    return countGene;
}

Gene Person::getGene(int num)
{
    return *gens[num];
}

typeGene Person::getGeneType(int num)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->getType();
    }
    return tgNone;
}

double Person::getGeneValue(int num)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->getValue();
    }
    return 0;
}

double Person::getGeneValueMax(int num)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->getValueMax();
    }
    return 0;
}

double Person::getGeneValueMin(int num)
{
    if(num >= 0 && num < countGene)
    {
        return gens[num]->getValueMin();
    }
    return 0;
}
