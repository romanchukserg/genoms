#include "GenotypeManager.h"

Genotype * GenotypeManager::create(int num)
{
    switch(num)
    {
        case 1: return new Genotype_001();
    }
    return 0;
}

Genotype * GenotypeManager::create(Genotype & gt)
{
    Genotype * new_gt = create(gt.num);

    new_gt->typeC = gt.typeC;
    new_gt->coeffMutation = gt.coeffMutation;
    new_gt->target.real(gt.target.real());
    new_gt->target.imag(gt.target.imag());

    for(int i = 0; i < gt.countGene; i++)
    {
        new_gt->gens[i]->setType(gt.gens[i]->getType());
        new_gt->gens[i]->setValue(gt.gens[i]->getValue());
        new_gt->gens[i]->setValueMax(gt.gens[i]->getValueMax());
        new_gt->gens[i]->setValueMin(gt.gens[i]->getValueMin());
        new_gt->gens[i]->setStable(gt.gens[i]->getStable());

        new_gt->maskCrossing[i] = gt.maskCrossing[i];
    }

    return new_gt;
}

void GenotypeManager::copyGens(Genotype & src, Gene *** gens)
{
    *gens = new Gene * [src.countGene];
    for(int i = 0; i < src.countGene; i++)
    {
        (*gens)[i] = new Gene(*src.gens[i]);
    }
}

int GenotypeManager::getCount()
{
    return COUNT;
}
