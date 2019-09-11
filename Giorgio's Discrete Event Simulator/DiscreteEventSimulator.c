#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

//Global Variables
float SEED = 0;
int INIT_TIME = 0;
int  FIN_TIME = 0;
int ARRIVE_MIN = 0;
int ARRIVE_MAX = 0;
int CPU_MIN = 0;
int CPU_MAX = 0;
int DISK1_MIN = 0;
int DISK1_MAX = 0;
int DISK2_MIN = 0;
int DISK2_MAX = 0;
float QUIT_PROB = 0;

//Function Prototypes
void readFile();

int main() {

    readFile();
    

}


//Function to read the values from values.txt
void readFile () {

    //file reader variables
    const char *conf_types[12] = {"SEED", "INIT_TIME", "FIN_TIME", "ARRIVE_MIN", "ARRIVE_MAX", "CPU_MIN", "CPU_MAX","DISK1_MIN", "DISK1_MAX", "DISK2_MIN", "DISK2_MAX", "QUIT_PROB"};
    int conf_values[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    //File reading
    FILE *configFile = NULL;
    configFile = fopen("values.txt", "r");
    
    
    if (configFile != NULL) {
        
        int lineLength = 1024;
        char *token;
        char stringSearch[lineLength];
        float valueSearch;
        char line[lineLength];
        int i;
        
        while (fgets(line, lineLength, configFile) != NULL) {

            token = strtok(line, " ");
            
            if (token != NULL) {

                strcpy(stringSearch, token);
            }
            else {

                continue;
            }

            token = strtok(NULL, " ");

            if (token != NULL) {

                valueSearch = atof(token);
            }
            else {

                valueSearch = 0;
            }
            
            for (i = 0; i < 12; i++) {

                if (strcmp(stringSearch, conf_types[i]) == 0) {

                    conf_values[i] = (int)valueSearch;
                }
            }
        }
    }
    
    for (int k = 0; k < 12; k++) {
        
        printf("%s: %d\n", conf_types[k], conf_values[k]);
    }
    
    SEED = conf_values[0];
    INIT_TIME = conf_values[1];
    FIN_TIME = conf_values[2];
    ARRIVE_MIN = conf_values[3];
    ARRIVE_MAX = conf_values[4];
    QUIT_PROB = conf_values[5];
    CPU_MIN = conf_values[6];
    CPU_MAX = conf_values[7];
    DISK1_MIN = conf_values[8];
    DISK1_MAX = conf_values[9];
    DISK2_MIN = conf_values[10];
    DISK2_MAX = conf_values[11];

}



