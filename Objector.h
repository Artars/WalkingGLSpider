#ifndef OBJECTOR
#define OBJECTOR

#include "Vector3.h"
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Clase conversora de modelos .obj
class Objector{
    public:
        Objector();
        Objector(char* filePath);
        vector<Vector3> *vertices;
        vector<unsigned int> *faces;
        /* Pode assumir 3 valores:
            -1: Falhou em converter
            0: Não converteu
            1: Convertido (Wololo)
        */
        int hasConverted = 0;
        int parseFile(char *filePath);

    private:
        char* path;


};

#endif