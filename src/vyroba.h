#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <ctype.h>
#include <vector>
#include <getopt.h>
#include <string.h>
#include <simlib.h>

#define obsluhaHWSW 3.84
#define obsluhaUnik 1.37
#define obsluhaObsluha 1.1
#define obsluhaJine 0.96
#define obsluhaMech 0.55
#define obsluhaEl 0.27
#define obsluhaNastav 0.22



//casy behu linek
double tMicharna1 = 266;
double tMicharna2 = 193;
double tKordy = 117;
double tLana = 57;
double tBehouny = 102;
double tBocnice = 94;
double tKonfekce = 74;
double tVulkanizace = 119;
double tKontrola = 15;


int kordy, lana, behouny, bocnice = 0;
int transakce = 0;

//funkce vypise kompletni statistiky
void printStats();

//funkce vypise zakladni statistiky
void printStatsMini();

//funkce pro nacteni a overeni argumentu programu
void get_args(int argc, char *argv[], double *smenaMicharna1, double* smenaMicharna2, double* smenaKordy, double* smenaLana,\
            double* smenaBehouny, double* smenaBocnice, double* smenaKonfekce, double* smenaVulkanizace, double * smenaKontrola,
             bool * verbose, bool * poruchy, int* timespan);



class HotovyVyrobek : public Process {
    void Behavior();
};

class Karkas : public Process {
    void Behavior();
    
    void Porucha();
};

class PolotovaryKonfekce : public Process {
    void Behavior();

    void Porucha();
};

class BeginKonfekce : public Process {
    void Behavior();
};

class PripravaBehoun : public Process {
    void Behavior();

    void Porucha();
};

class PripravaBocnice : public Process {
    void Behavior();

    void Porucha();
};

class PripravaKordu : public Process {
    void Behavior();

    void Porucha();
};

class PripravaLana : public Process {
    void Behavior();

    void Porucha();
};

class SmesProValcovnu : public Process {
    void Behavior();
};

class SurProDruhyStupen : public Process {
    void Behavior();

    void Porucha();
};

class Suroviny : public Process {
    void Behavior();

    void Porucha();
};