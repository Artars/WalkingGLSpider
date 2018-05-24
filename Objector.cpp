#include "Objector.h"

Objector::Objector() {
    hasConverted = 0;
    vertices = NULL;
    faces = NULL;
}

Objector::Objector(char* filePath) {
    hasConverted = 0;
    vertices = NULL;
    faces = NULL;

    parseFile(filePath);
}

int Objector::parseFile(char *filePath) {
    //Openfile


    FILE * file = fopen(filePath, "r");
    if( file == NULL ){
        printf("Impossible to open the file \"%s\"!\n", path);
        hasConverted = -1;
        return hasConverted;
    }

    //Initialize structures
    if(vertices == NULL)
        delete vertices;
    vertices = new vector<Vector3>();

    if(faces == NULL) {
        delete faces;
    }
    faces = new vector<unsigned int>();

    float x,y,z;

    while( 1 ){

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.
        
        if ( strcmp( lineHeader, "v" ) == 0 ) {
            fscanf(file, "%f %f %f\n", &x, &y,&z);
            vertices->push_back(Vector3(x,y,z));
        }

        // Ler mapeamento de UV, não vai ser tratado por enquanto
        else if (strcmp( lineHeader, "vt" ) == 0){
            fscanf(file, "%f %f\n", &x, &y);            
        }

        //Ler mapeamento de normais. Não vai ser tratado por enquanto
        else if(strcmp( lineHeader, "vn" ) == 0){
            fscanf(file, "%f %f %f\n", &x, &y,&z);
        }

        else if(strcmp( lineHeader, "f" ) == 0) {
            unsigned int vertexIndex[3], uvIndex[3];

            int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
            if (matches != 6){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                printf("Has found: %d", matches);
                hasConverted = -1;
                return hasConverted;
            }

            faces->push_back(vertexIndex[0]);
            faces->push_back(vertexIndex[1]);
            faces->push_back(vertexIndex[2]);
            

        }

        //Trata comentário, eliminando toda a linha
        else if(lineHeader[0] == '#'){
            char c, error;
            do {
                error = fscanf(file, "%c", &c);
            }
            while(c != '\n' || error == EOF);
            if(error == EOF){
                break;
            }
        }


    }

    hasConverted = 1;
    return hasConverted;


}