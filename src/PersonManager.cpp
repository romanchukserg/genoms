#include "PersonManager.h"

Genotype * PersonManager::GENOTYPE = 0;

bool PersonManager::ini(Genotype & gt)
{
    if(GENOTYPE != 0)
    {
        delete GENOTYPE;
    }

    GENOTYPE = GenotypeManager::create(gt);

    //std::cout<<GENOTYPE
    return true;
}

Person * PersonManager::create()
{
    Person *p = new Person();
    p->numGenotype = GENOTYPE->getNum();
    p->countGene = GENOTYPE->getCountGene();
    GenotypeManager::copyGens(*GENOTYPE, &p->gens);

    for(int i = 0; i < p->countGene; i++)
    {
        p->gens[i]->mutation();
    }

    return p;
}

Person * PersonManager::create(Person & person)
{
    return new Person(person);
}

bool PersonManager::mutation(Person & person)
{
    if((rand() / RAND_MAX) < GENOTYPE->getCoeffMutation())
    {
        int num = rand() % person.countGene;
        return person.gens[num]->mutation();
    }
    return false;
}

bool PersonManager::crossing(Person & parent1, Person & parent2, Person ** child1, Person ** child2)
{
    if(parent1.numGenotype != parent2.numGenotype)
    {
        return false;
    }

    *child1 = new Person(parent1);
    *child2 = new Person(parent2);

    Gene *tmp;

    for(int i = 0; i < GENOTYPE->getCountGene(); i++)
    {
        if(GENOTYPE->getMaskCrossingValue(i))
        {
            tmp = (*child1)->gens[i];
            (*child1)->gens[i] = (*child2)->gens[i];
            (*child2)->gens[i] = tmp;
        }
    }

    return true;
}

bool PersonManager::calculateFitness(Person & person)
{
    if(person.numGenotype != GENOTYPE->getNum())
    {
        return false;
    }

    person.fitness = GENOTYPE->calculateFitness(person.gens);

    return true;
}
