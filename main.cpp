#include <iostream>

#include <stdlib.h>
#include <time.h>

#include "Evolution.h"
#include "Person.h"
#include "Gene.h"

using namespace std;

int main()
{
    srand(time(0));

    Evolution *e = new Evolution();
    e->run();
    delete e;

    /*MaterialList ml;
    double re, im;
    ml.getMaterialNear(3.5, 457.6, re, im);
    cout << re << " - " << im;*/

    return 0;
}
