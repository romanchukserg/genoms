//---------------------------------------------------------------------------
#ifndef MaterialListH
#define MaterialListH
//---------------------------------------------------------------------------
//#include <fstream.h>
//#include <IniFiles.hpp>
#include <math.h>
#include <cstring>
//---------------------------------------------------------------------------
struct PropertyRecord
{
        double length;
        double re;
        double im;
};
//---------------------------------------------------------------------------
struct MaterialRecord
{
        int propertyCount;
        PropertyRecord * propertyRecord;
        char * name;
};
//---------------------------------------------------------------------------
class MaterialList
{
    public:
        MaterialList();
        MaterialList(char * fileName, char * path);
        ~MaterialList();

        int getCountMaterial();
        bool getMaterialName(int number, char * name);
        bool getMaterialMinLength(int number, double &minLength);
        bool getMaterialMaxLength(int number, double &maxLength);
        bool getMaterialNear(int number, double length, double & re, double & im);
        bool getMaterialNearRe(int number, double length, double & re);
        bool getMaterialNearIm(int number, double length, double & im);

    private:
        char * fileName;
        char * path;

        int materialCount;
        MaterialRecord * materialRecord;

        bool loadData();
        bool saveData();
        void clearData();

        bool addMaterialRecord(MaterialRecord *mr);
        bool delMaterialRecord(int number);

        int getMaterialCountRec(int number);
        double getMaterialLength(int number, int index);
        double getMaterialRe(int number, int index);
        double getMaterialIm(int number, int index);

        //bool getMaterialPropery(int number, double lengthMax, double lengthMin,
        //                        double lengthStep, double ** data);



        //void set
};
//---------------------------------------------------------------------------
#endif
