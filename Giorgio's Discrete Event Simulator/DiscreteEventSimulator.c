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

    srand(SEED);

     //adding two events to priority queue, job 1 arrival and simulation finished.


}


//Function to read the values from values.txt
void readFile () {

    //file reader variables
    const char *configTypes[12] = {"SEED", "INIT_TIME", "FIN_TIME", "ARRIVE_MIN", "ARRIVE_MAX", "CPU_MIN", "CPU_MAX","DISK1_MIN", "DISK1_MAX", "DISK2_MIN", "DISK2_MAX", "QUIT_PROB"};
    int configValues[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    //File reading
    FILE *fp = NULL;
    fp = fopen("values.txt", "r");
    
    
    if (fp != NULL) {
        
        int lineLength = 1024;
        char *token;
        char stringSearch[lineLength];
        float valueSearch;
        char line[lineLength];
        int i;
        
        while (fgets(line, lineLength, fp) != NULL) {

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

                if (strcmp(stringSearch, configTypes[i]) == 0) {

                    configValues[i] = (int)valueSearch;
                }
            }
        }
    }
    
    for (int t = 0; t < 12; t++) {
        
        printf("%s: %d\n", configTypes[t], configValues[t]);
    }
    
    SEED = configValues[0];
    INIT_TIME = configValues[1];
    FIN_TIME = configValues[2];
    ARRIVE_MIN = configValues[3];
    ARRIVE_MAX = configValues[4];
    CPU_MIN = configValues[5];
    CPU_MAX = configValues[6];
    DISK1_MIN = configValues[7];
    DISK1_MAX = configValues[8];
    DISK2_MIN = configValues[9];
    DISK2_MAX = configValues[10];
    QUIT_PROB = configValues[11];

}



