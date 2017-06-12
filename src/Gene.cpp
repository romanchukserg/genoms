#include "Gene.h"

Gene::Gene(typeGene type, double value, double valueMax, double valueMin, double stable)
{
    this->type = type;
    this->value = value;
    this->valueMax = valueMax;
    this->valueMin = valueMin;
    this->stable = stable;
}

Gene::Gene(Gene & gene)
{
    type = gene.type;
    value = gene.value;
    valueMax = gene.valueMax;
    valueMin = gene.valueMin;
    stable = gene.stable;
}

typeGene Gene::getType()
{
    return type;
}

double Gene::getValue()
{
    return value;
}

double Gene::getValueMax()
{
    return valueMax;
}

double Gene::getValueMin()
{
    return valueMin;
}

double Gene::getStable()
{
    return stable;
}

bool Gene::setType(typeGene type)
{
    this->type = type;
    return true;
}

bool Gene::setValue(double value)
{
    if((value >= valueMin && value <= valueMax) || (valueMin == valueMax))
    {
        this->value = value;
        return true;
    }
    return false;
}

bool Gene::setValueMax(double valueMax)
{
    if(valueMax >= valueMin)
    {
        this->valueMax = valueMax;
        if(valueMax < value)
        {
            value = valueMax;
        }
        return true;
    }
    return false;
}

bool Gene::setValueMin(double valueMin)
{
    if(valueMax >= valueMin)
    {
        this->valueMin = valueMin;
        if(valueMin > value)
        {
            value = valueMin;
        }
        return true;
    }
    return false;
}

bool Gene::setStable(double stable)
{
    this->stable = stable;
    return true;
}

bool Gene::mutation()
{
    if((double(rand()) / RAND_MAX) < stable)
    {
        value = (double(rand()) / RAND_MAX) * (valueMax - valueMin) + valueMin;
    }

    return true;
}

