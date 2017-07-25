#include "Evolution.h"

Evolution::Evolution(int countPerson, int maxAge, double minFitness, Genotype & gt)
{
    this->countPerson = countPerson;
    this->maxAge = maxAge;
    this->minFitness = minFitness;

    PersonManager::ini(gt);

    population = 0;
    parents = 0;
    childs = 0;
}

Evolution::~Evolution()
{
    clearPopulation();
}

void Evolution::run()
{
    std::cout << "\n\n run";

    createPopulation();

    int countAge = 0;
    while(countAge < maxAge)
    {
        crossing();
        mutation();
        calculationFitness();
        if(selection())
        {
            std::cout << "\ncountAge " << countAge;

            return;
        }
        countAge++;
    }

    std::cout << "-NO";
}

bool Evolution::clearPopulation()
{
    //std::cout << "clearPopulation\n";

    for(int i = 0; i < countPerson; i++)
    {
        delete parents[i];
        delete childs[i];
    }
    delete [] population;
}

bool Evolution::createPopulation()
{
    //std::cout << "createPopulation\n";

    population = new Person*[countPerson*2];
    parents = population;
    childs = population + countPerson;

    for(int i = 0; i < countPerson; i++)
    {
        parents[i] = PersonManager::create();
        PersonManager::mutation(*parents[i]);
        PersonManager::calculateFitness(*parents[i]);
    }

    return true;
}

bool Evolution::crossing()
{
    //std::cout << "crossing\n";

    for(int i = 0; i < countPerson; i+=2)
    {
        PersonManager::crossing(*parents[i], *parents[i+1], &childs[i], &childs[i+1]);
    }

    return true;
}

bool Evolution::mutation()
{
    //std::cout << "mutation\n";

    for(int i = 0; i < countPerson; i++)
    {
        PersonManager::mutation(*childs[i]);
    }
    return true;
}

bool Evolution::calculationFitness()
{
    //std::cout << "calculationFitness\n";

    for(int i = 0; i < countPerson; i++)
    {
        PersonManager::calculateFitness(*childs[i]);
    }
    return true;
}

bool Evolution::selection()
{
    //std::cout << "selection\n";

    bool flag = true;
    Person *p;

    while(flag)
    {
        flag = false;

        for(int i = 1; i < countPerson*2; i++)
        {
            if(population[i-1]->getFitness() > population[i]->getFitness())
            {
               flag = true;

               p = population[i-1];
               population[i-1] = population[i];
               population[i] = p;
            }
        }
    }

    for(int i = 0; i < countPerson; i++)
    {
        delete childs[i];
        childs[i] = 0;
    }

    if(parents[0]->getFitness() < minFitness)
    {
            MaterialList mr("C:\\MaterialListCreate", "_mlData.bin");
            double re, im, re1, im1, re2, im2;
            mr.getMaterialNear(parents[0]->getGeneValue(2), parents[0]->getGeneValue(0), re1, im1);
            mr.getMaterialNear(parents[0]->getGeneValue(3), parents[0]->getGeneValue(0), re2, im2);
            PersonManager::getDielectric(*(parents[0]), re, im);
            char name[100] = "String for name materials";
            std::cout << "-YES ";
            std::cout << "\nfitness: " << parents[0]->getFitness();
            std::cout << "\nre: " << re;
            std::cout << "\nim: " << im;
            std::cout << "\nlen: " << parents[0]->getGeneValue(0);
            std::cout << "\nv: " << parents[0]->getGeneValue(1);
            mr.getMaterialName(parents[0]->getGeneValue(2), name);
            std::cout << "\nM1: " << name;
            std::cout << "\nre1: " << re1;
            std::cout << "\nim1: " << im1;
            mr.getMaterialName(parents[0]->getGeneValue(3), name);
            std::cout << "\nM2: " << name;
            std::cout << "\nre2: " << re2;
            std::cout << "\nim2: " << im2;

        return true;
    }

    return false;
}
