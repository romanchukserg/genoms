#include "Evolution.h"

Evolution::Evolution()
{
    countPerson = 100;

    population = 0;
    parents = 0;
    childs = 0;
}

Evolution::~Evolution()
{
}

void Evolution::run()
{
    std::cout << "run\n";

    Genotype * gt = GenotypeManager::create(1);
    gt->setGeneValueMax(1, 0.3);
    //gt->setGeneValueMax(1, 0.3);
    gt->setTarget(std::complex<double> (5, 5));
    PersonManager::ini(*gt);
    delete gt;

    int countAge = 0;

    createPopulation();

    while(countAge < 1000)
    {
        crossing();
        mutation();
        calculationFitness();
        if(selection())
        {
            std::cout << " - " << countAge;
            return;
        }

        countAge++;
    }

    std::cout << "NO";
}

bool Evolution::clearPopulation()
{
    std::cout << "clearPopulation\n";

    for(int i = 0; i < countPerson; i++)
    {
        delete parents[i];
        delete childs[i];
    }
    delete [] population;
}

bool Evolution::createPopulation()
{
    std::cout << "createPopulation\n";

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
    std::cout << "crossing\n";

    for(int i = 0; i < countPerson; i+=2)
    {
        PersonManager::crossing(*parents[i], *parents[i+1], &childs[i], &childs[i+1]);
    }

    return true;
}

bool Evolution::mutation()
{
    std::cout << "mutation\n";

    for(int i = 0; i < countPerson; i++)
    {
        PersonManager::mutation(*childs[i]);
    }
    return true;
}

bool Evolution::calculationFitness()
{
    std::cout << "calculationFitness\n";

    for(int i = 0; i < countPerson; i++)
    {
        PersonManager::calculateFitness(*childs[i]);
    }
    return true;
}

bool Evolution::selection()
{
    std::cout << "selection\n";

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

    //std::cout << parents[0]->getFitness() << std::endl;

    if(parents[0]->getFitness() < 0.001)
    {
        MaterialList mr;
            double re1, im1, re2, im2;
            mr.getMaterialNear(parents[0]->getGeneValue(2), parents[0]->getGeneValue(0), re1, im1);
            mr.getMaterialNear(parents[0]->getGeneValue(3), parents[0]->getGeneValue(0), re2, im2);

            std::cout << "YES " << parents[0]->getFitness();
            std::cout << "len: " << parents[0]->getGeneValue(0) << " ";
            std::cout << "v: " << parents[0]->getGeneValue(1) << " ";
            std::cout << "re1: " << re1 << " ";
            std::cout << "im1: " << im1 << " ";
            std::cout << "re2: " << re2 << " ";
            std::cout << "im2: " << im2 << " ";

        clearPopulation();

        return true;
    }

    return false;
}
