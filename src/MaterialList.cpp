#include "MaterialList.h"

MaterialList::MaterialList()
{
        materialCount = 0;
        materialRecord = 0;
        fileName = 0;
        path = 0;
}

MaterialList::MaterialList(char * path, char * fileName)
{
        materialCount = 0;
        materialRecord = 0;

        this->fileName = new char [strlen(fileName)+1];
        strncpy(this->fileName, fileName, strlen(fileName)+1);

        this->path = new char [strlen(path)+1];
        strncpy(this->path, path, strlen(path)+1);

        loadData();
}

MaterialList::~MaterialList()
{
        delete fileName;
        delete path;
        clearData();
}

int MaterialList::getCountMaterial()
{
        return materialCount;
}

bool MaterialList::getMaterialName(int number, char * name)
{
        if((number >= 0 || number < materialCount) && strlen(name) > 0)
        {
            //std::cout<<materialRecord[number].name<<std::endl;
            if(strlen(name) < strlen(materialRecord[number].name))
            {
                strncpy(name, materialRecord[number].name, strlen(name));
                //name[strlen(name)-1] = '\0';
            }
            else
            {
                strcpy(name, materialRecord[number].name);
            }
            return true;
        }

        return false;
}

bool MaterialList::getMaterialMinLength(int number, double &minLength)
{
        if(number >= 0 || number < materialCount)
        {
            minLength = materialRecord[number].propertyRecord[0].length;
            return true;
        }

        return false;
}

bool MaterialList::getMaterialMaxLength(int number, double &maxLength)
{
        if(number >= 0 || number < materialCount)
        {
            maxLength = materialRecord[number].propertyRecord[materialRecord[number].propertyCount - 1].length;
            return true;
        }

        return false;
}

bool MaterialList::getMaterialNearRe(int number, double length, double & re)
{
        double tmp = 0;

        return getMaterialNear(number, length, re, tmp);
}

bool MaterialList::getMaterialNearIm(int number, double length, double & im)
{
        double tmp = 0;

        return getMaterialNear(number, length, tmp, im);
}

double MaterialList::getMaterialNearRe(int number, double length)
{
    double re = 0;
    getMaterialNearRe(number, length, re);
    return re;
}

double MaterialList::getMaterialNearIm(int number, double length)
{
    double im = 0;
    getMaterialNearIm(number, length, im);
    return im;
}

bool MaterialList::getMaterialNear(int number, double length, double & re, double & im)
{
        if(number < 0 || number >= materialCount)
                return false;

        MaterialRecord * mr = &materialRecord[number];
        double coeffTmp;
        for(int i = 0; i < (mr->propertyCount - 1); i++)
        {
                if(length >= mr->propertyRecord[i].length &&
                        length <= mr->propertyRecord[i + 1].length)
                {
                        coeffTmp = (length - mr->propertyRecord[i].length) /
                                (mr->propertyRecord[i+1].length - mr->propertyRecord[i].length);

                        re = (mr->propertyRecord[i].re +
                                (mr->propertyRecord[i+1].re - mr->propertyRecord[i].re) * coeffTmp);

                        im = (mr->propertyRecord[i].im +
                                (mr->propertyRecord[i+1].im - mr->propertyRecord[i].im) * coeffTmp);

                        return true;
                }
        }

        return false;
}

std::complex<double> MaterialList::getMaterialNear(int number, double length)
{
    std::complex <double> e(getMaterialNearRe(number, length), getMaterialNearIm(number, length));
    return e;
}

//---------------------------------------------------------------------------
//�������� �������� ��������������� ������������� (��) ���������� �� ������ ������
//������������ ��� ��������� PCM.
//1.��������� ���� ���������� (*.ini), ��������� ���������� ����������,
//����������� ��������� � ��� ����� (*.bin) �� ���������� ��.
//2.��������� ��������������� ��� ����� ���������� � ��������� ������.
//���������:    ���������� ������� (4)
//              ������ �������� (1), ������� ����� (8)
//              ������ �������� (1), ����� ����� (8)
//              ������ �������� (1), �� �������� ����� (8)
//              ������ �������� (1), �� ������ ����� (8)
//              ������ �������� (1), ����. ����������� (8)
//              ������ �������� (1), ����. ���������� (8)
//�� ��������: ���������� �������, ����� �����, �� �������� � ������ ����� (3 ��������)
//---------------------------------------------------------------------------
bool MaterialList::loadData()
{
    clearData();

    char fullPath[1000] = "";
    strcat(fullPath, path);
    strcat(fullPath, "\\");
    strcat(fullPath, fileName);

    std::ifstream fin(fullPath, std::ios_base::binary);

    fin.read((char*)&materialCount, sizeof materialCount);
    materialRecord = new MaterialRecord[materialCount];

    for(int i = 0; i < materialCount; i++)
    {
        int len;
        fin.read((char*)&len, sizeof len);
        materialRecord[i].name = new char[len+1];
        fin.read(materialRecord[i].name, len);

        fin.read((char*)&materialRecord[i].propertyCount, sizeof materialRecord[i].propertyCount);
        materialRecord[i].propertyRecord = new PropertyRecord[materialRecord[i].propertyCount];

        for(int j = 0; j < materialRecord[i].propertyCount; j++)
        {
            fin.read((char*)&materialRecord[i].propertyRecord[j].length, sizeof materialRecord[i].propertyRecord[j].length);
            fin.read((char*)&materialRecord[i].propertyRecord[j].re, sizeof materialRecord[i].propertyRecord[j].re);
            fin.read((char*)&materialRecord[i].propertyRecord[j].im, sizeof materialRecord[i].propertyRecord[j].im);
        }
    }
    fin.close();

    return true;
}

bool MaterialList::saveData()
{

        //�������� ����������
        /*TSearchRec sr;
        if(FindFirst(String(contentPath) + "*.*", faAnyFile, sr) == 0)
        {
                if(sr.Attr != faDirectory)
                {
                        DeleteFileA(String(contentPath) + sr.Name);
                }

                while(FindNext(sr) == 0)
                {
                        if(sr.Attr != faDirectory)
                        {
                                DeleteFileA(String(contentPath) + sr.Name);
                        }
                }
        }
        FindClose(sr);

        //������� ��� ����

        TIniFile *Ini = new TIniFile(String(contentPath) + String(contentFileName));
        Ini->WriteString("main", "count", String(materialCount));
        Ini->WriteString("main", "item", "");
        Ini->WriteString("main", "path", "");
        AnsiString section;
        AnsiString patch = "00000000";

        if(materialCount > 0)
        {
                for(int i = 0; i < materialCount; i++)
                {
                        section = "item_" + String(i);
                        Ini->WriteString(section, "name", materialRecord[i].name);
                        Ini->WriteString(section, "fileName", String(materialRecord[i].name) + ".bin");
                        Ini->WriteString(section, "memo", "");

                        fstream file(String(String(contentPath) + String(materialRecord[i].name) + ".bin").c_str(), ios::binary|ios::out);
                        if(!file.fail())
                        {
                                file.write((char*)&materialRecord[i].propertyCount, 4);

                                for(int j = 0; j < materialRecord[i].propertyCount; j++)
                                {
                                        file.write((char*)&patch, 1);
                                        file.write((char*)&patch, 8);

                                        file.write((char*)&patch, 1);
                                        file.write((char*)&materialRecord[i].propertyRecord[j].length, 8);

                                        file.write((char*)&patch, 1);
                                        file.write((char*)&materialRecord[i].propertyRecord[j].re, 8);

                                        file.write((char*)&patch, 1);
                                        file.write((char*)&materialRecord[i].propertyRecord[j].im, 8);

                                        file.write((char*)&patch, 1);
                                        file.write((char*)&patch, 8);

                                        file.write((char*)&patch, 1);
                                        file.write((char*)&patch, 8);
                                }

                                file.close();
                        }
                }
        }*/
        return true;
}

void MaterialList::clearData()
{
        for(int i = 0; i < materialCount; i++)
        {
                delete [] materialRecord[i].name;
                delete [] materialRecord[i].propertyRecord;
        }
        delete [] materialRecord;

        materialCount = 0;
        materialRecord = 0;
}

bool MaterialList::addMaterialRecord(MaterialRecord *mr)
{/*
        //��������� ������ �� ������� ������
        MaterialRecord * materialRecordTmp = materialRecord;

        //��������� ������ ��� ����� ������
        materialRecord = new MaterialRecord[materialCount + 1];

        //����������� ������� ������ � ������� ��� ���� ������
        for(int i = 0; i < materialCount; i++)
        {
                materialRecord[i].name = strdup(materialRecordTmp[i].name);
                materialRecord[i].propertyCount = materialRecordTmp[i].propertyCount;
                materialRecord[i].propertyRecord = new PropertyRecord[materialRecord[i].propertyCount];

                for(int j = 0; j < materialRecord[i].propertyCount; j++)
                {
                        materialRecord[i].propertyRecord[j].length = materialRecordTmp[i].propertyRecord[j].length;
                        materialRecord[i].propertyRecord[j].re = materialRecordTmp[i].propertyRecord[j].re;
                        materialRecord[i].propertyRecord[j].im = materialRecordTmp[i].propertyRecord[j].im;
                }
        }

        //�������� ������� ������ �� ��������� ������
        for(int i = 0; i < materialCount; i++)
        {
                delete materialRecordTmp[i].name;
                delete [] materialRecordTmp[i].propertyRecord;
        }
        delete [] materialRecordTmp;

        //����������� ������ ������ ���������
        materialRecord[materialCount].name = strdup(mr->name);
        materialRecord[materialCount].propertyCount = mr->propertyCount;
        materialRecord[materialCount].propertyRecord = new PropertyRecord[mr->propertyCount];
        for(int j = 0; j < materialRecord[materialCount].propertyCount; j++)
        {
                materialRecord[materialCount].propertyRecord[j].length = mr->propertyRecord[j].length;
                materialRecord[materialCount].propertyRecord[j].re = mr->propertyRecord[j].re;
                materialRecord[materialCount].propertyRecord[j].im = mr->propertyRecord[j].im;
        }

        materialCount++;
*/
        return true;
}

bool MaterialList::delMaterialRecord(int number)
{/*
        //�������� ������
        if(number < 0 || number >= materialCount)
                return false;

        //��������� ������ �� ������� ������
        MaterialRecord * materialRecordTmp = materialRecord;

        //��������� ������ ��� ����� ������
        materialRecord = new MaterialRecord[materialCount - 1];

        //����������� ������� ������ � ������� ��� ���� ������
        for(int i = 0, l = 0; i < materialCount - 1; i++, l++)
        {
                if(number == i)
                {
                        l++;
                        //continue;
                }

                materialRecord[i].name = strdup(materialRecordTmp[l].name);
                materialRecord[i].propertyCount = materialRecordTmp[l].propertyCount;
                materialRecord[i].propertyRecord = new PropertyRecord[materialRecordTmp[l].propertyCount];

                for(int j = 0; j < materialRecord[i].propertyCount; j++)
                {
                        materialRecord[i].propertyRecord[j].length = materialRecordTmp[l].propertyRecord[j].length;
                        materialRecord[i].propertyRecord[j].re = materialRecordTmp[l].propertyRecord[j].re;
                        materialRecord[i].propertyRecord[j].im = materialRecordTmp[l].propertyRecord[j].im;
                }
        }

        //�������� ������� ������ �� ��������� ������
        for(int i = 0; i < materialCount; i++)
        {
                delete materialRecordTmp[i].name;
                delete [] materialRecordTmp[i].propertyRecord;
        }
        delete [] materialRecordTmp;

        materialCount--;
*/
        return true;
}

int MaterialList::getMaterialCountRec(int number)
{
        if(number < 0 || number >= materialCount)
                return 0;

        return materialRecord[number].propertyCount;
}

double MaterialList::getMaterialLength(int number, int index)
{
        if(number < 0 || number >= materialCount)
                return 0;

        if(index < 0 || index >= materialRecord[number].propertyCount)
                return 0;

        return materialRecord[number].propertyRecord[index].length;
}

double MaterialList::getMaterialRe(int number, int index)
{
        if(number < 0 || number >= materialCount)
                return 0;

        if(index < 0 || index >= materialRecord[number].propertyCount)
                return 0;

        return materialRecord[number].propertyRecord[index].re;
}

double MaterialList::getMaterialIm(int number, int index)
{
        if(number < 0 || number >= materialCount)
                return 0;

        if(index < 0 || index >= materialRecord[number].propertyCount)
                return 0;

        return materialRecord[number].propertyRecord[index].im;
}

//---------------------------------------------------------------------------
//����� ��� ��������� ������ �� ���������.
//��������:
//1. ���� lengthMax = lengthMin = 0
//      ���������� ������ �������� �� ����� ��������
//   ���� lengthMax > 0 � lengthMin = 0
//      ���������� ������ �������� �� �� ������ ��������� �� lengthMax
//   ���� lengthMax = 0 � lengthMin > 0
//      ���������� ������ �������� �� �� lengthMin �� ����� ���������
//   ���� lengthMax = 0 � lengthMin > 0
//      ���������� ������ �������� �� �� lengthMin �� lengthMax
//2. ���� lengthStep = 0, �����
//      ������������ �� �� ����������
//   ���� lengthStep > 0, �����
//      ���������� ������ ����������������� �������� ��
//---------------------------------------------------------------------------
/*bool MaterialList::getMaterialPropery(int number, double lengthMax, double lengthMin,
                                        double lengthStep, double ** data)
{
        if(number < 0 || number >= materialCount || lengthStep < 0 )
                return false;

        MaterialRecord * mr = &materialRecord[number];

        //����� ������� �����������
        int indexStart = -1;
        int indexEnd = -1;

        if(lengthMax > lengthMin && lengthMin > 0)
        {
                for(int i = 0; i < (mr->propertyCount - 1); i++)
                {
                        if(lengthMin >= mr->propertyRecord[i].length && lengthMin < mr->propertyRecord[i + 1].length)
                                indexStart = i;
                        if(lengthMax > mr->propertyRecord[i].length && lengthMin <= mr->propertyRecord[i + 1].length)
                                indexEnd = i + 1;
                }
        }
        else
        {
                if(lengthMin == 0)
                {
                        indexStart = 0;
                        lengthMin = mr->propertyRecord[indexStart].length;
                }

                if(lengthMax == 0)
                {
                        indexEnd = mr->propertyCount - 1;
                        lengthMax = mr->propertyRecord[indexEnd].length;
                }
        }

        if(indexStart == -1 || indexEnd == -1)
                return false;

        //������ ������
        int dataCount;

        if(lengthStep == 0) dataCount = indexEnd - indexStart + 1;
        else dataCount = ceil((lengthMax - lengthMin) / lengthStep) + 1;

        data = new double * [4];
        data[0] = new double[dataCount];
        data[1] = new double[dataCount];
        data[2] = new double[dataCount];
        data[3] = new double[dataCount];

        if(lengthStep == 0)
        {
                for(int i = 0; i < dataCount; i++)
                {
                        data[0][i] = mr->propertyRecord[i + indexStart].length;
                        data[1][i] = mr->propertyRecord[i + indexStart].re;
                        data[2][i] = mr->propertyRecord[i + indexStart].im;
                        data[3][i] = 1;
                }
        }
        else
        {
                double lengthTmp;
                double coeffTmp;
                for(int i = 0; i < (dataCount - 1); i++)
                {
                        lengthTmp = lengthMin + lengthStep * i;
                        data[3][i] = 0;

                        for(int j = indexStart; j < indexEnd; j++)
                        {
                                if(lengthTmp >= mr->propertyRecord[j].length && lengthTmp < mr->propertyRecord[j + 1].length)
                                {
                                        coeffTmp = lengthTmp / (mr->propertyRecord[j+1].length - mr->propertyRecord[j].length);
                                        data[0][i] = lengthTmp;
                                        data[1][i] = mr->propertyRecord[j].re + (mr->propertyRecord[j+1].re - mr->propertyRecord[j].re) * coeffTmp;
                                        data[2][i] = mr->propertyRecord[j].im + (mr->propertyRecord[j+1].im - mr->propertyRecord[j].im) * coeffTmp;
                                        data[3][i] = 1;
                                        indexStart = j;
                                        break;
                                }
                        }
                }
        }

        return true;
}*/

