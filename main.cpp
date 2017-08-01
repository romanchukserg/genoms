#include <iostream>

#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>

#include "Evolution.h"
#include "Person.h"
#include "Gene.h"

//using namespace std;

void sample();

int main()
{
    srand(time(0));

    int countAge = 100;
    int countPers = 1000;

    std::vector<int> m2;
    m2.push_back(14);
    m2.push_back(0);
    m2.push_back(1);
    m2.push_back(4);
    m2.push_back(9);
    m2.push_back(31);
    m2.push_back(35);

    Genotype * gt = GenotypeManager::create(1);
    gt->setGeneValueMax(1, 0.3);
    //gt->setGeneValue(2, 1);
    //gt->setGeneStable(2, 0);
    //gt->setGeneValue(3, 9);
    //gt->setGeneStable(3, 0);
    gt->setGeneStable(0, 0);
    //gt->setTarget(std::complex<double> (-8.437, 0.9), 0);
    gt->setTarget(std::complex<double> (-5, 3), 0);
    gt->setAml(m2, 3);

    Evolution *e = new Evolution(countPers, countAge, 0.001, *gt);

    e->run();
    e->run();
    e->run();

    delete e;
    delete gt;

    return 0;
}

void sample()
{
    std::ofstream infile("sample.txt");
    if(!infile.is_open())
    {
        std::cout << "NO FILE";
        return;
    }

    int countItem = 1;
    int countAge = 100;
    int countPers = 1000;

    double *** st = new double ** [countItem];
    for(int i = 0; i < countItem; i++)
    {
        st[i] = new double * [countAge];
        for(int j = 0; j < countAge; j++)
        {
            st[i][j] = new double [countPers];
        }
    }

    Genotype * gt = GenotypeManager::create(1);
    gt->setGeneValueMax(1, 0.3);
    gt->setGeneValue(2, 1);
    //gt->setGeneStable(2, 0);
    //gt->setGeneValue(3, 9);
    //gt->setGeneStable(3, 0);
    gt->setGeneStable(0, 0);
    gt->setTarget(std::complex<double> (-8.437, 0.9), 0);

    Evolution *e = new Evolution(countPers, countAge, 0.0001, *gt);

    for(int i = 0; i < 1; i++)
    {
        e->run(st[i]);
    }

    infile << "N \t max \t min \t ave \n";

    double mx, mn, ae, sm;
    for(int i = 0; i < countItem; i++)
    {
        std::cout << "- " << i << std::endl;
        for(int j = 0; j < countAge; j++)
        {
            mx = mn = st[i][j][0];
            sm = 0;

            for(int k = 0; k < countPers; k++)
            {
                if(mx < st[i][j][k])    mx = st[i][j][k];
                if(mn > st[i][j][k])    mn = st[i][j][k];
                sm += st[i][j][k];
            }

            infile << j << "\t";
            infile << mx << "\t";
            infile << mn << "\t";
            infile << sm / countPers << "\n";
        }
    }

    infile.close();

    for(int i = 0; i < countItem; i++)
    {
        for(int j = 0; j < countAge; j++)
        {
            delete [] st[i][j];
        }
        delete [] st[i];
    }
    delete [] st;

    delete e;
    delete gt;
}
