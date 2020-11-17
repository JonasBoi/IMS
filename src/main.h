#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <ctype.h>
#include <vector>
#include <simlib.h>
#include <getopt.h>
#include <string.h>

#define obsluhaHWSW 3.84
#define obsluhaUnik 1.37
#define obsluhaObsluha 1.1
#define obsluhaJine 0.96
#define obsluhaMech 0.55
#define obsluhaEl 0.27
#define obsluhaNastav 0.22

//linky
Facility Micharna1("Micharna 1. stupen");
Facility Micharna2("Micharna 2. stupen");
Facility ValcovnaKordy("Pripravna kordu");
Facility ValcovnaLana("Pripravna lana");
Facility ValcovnaBehoun("Pripravna behounu");
Facility ValcovnaBocnice("Pripravna bocnice");
Facility Konfekce("Konfekce");
Facility Vulkanizace("Vulkanizace");
Facility Kontrola("Kontrola kvality");


// poruchy
bool poruchaMicharna1, poruchaMicharna2 = false;
bool poruchaKordy, poruchaLana, poruchaBehoun, poruchaBocnice = false;
bool poruchaKonfekceObsluha, poruchaKonfekceJine = false;
bool poruchaVulkanizaceUnik, poruchaVulkanizaceNastaveni = false;
bool poruchaMichEl1, poruchaMichEl2, poruchaLanEl, poruchaKordEl, poruchaBocEl, poruchaBehEl, poruchaKonfEl, poruchaVulkEl = false;

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
    void Behavior() {
        Seize(Kontrola);
        Wait(tKontrola);
        Release(Kontrola);
        transakce++;
    }
};

class Karkas : public Process {
    void Behavior() {
        //sklad pro vulkanizaci
        Wait(360);

        Seize(Vulkanizace);
        Porucha();
        Wait(tVulkanizace);
        Release(Vulkanizace);

        (new HotovyVyrobek)->Activate();
    }
    void Porucha() {
        if (poruchaVulkanizaceNastaveni) {
            Wait(obsluhaNastav);
            poruchaVulkanizaceNastaveni = false;
        }
        if (poruchaVulkanizaceUnik) {
            Wait(obsluhaUnik);
            poruchaVulkanizaceUnik = false;
        }
        if (poruchaVulkEl) {
            Wait(obsluhaEl);
            poruchaVulkEl = false;
        }
    }
};

class PolotovaryKonfekce : public Process {
    void Behavior() {
        Seize(Konfekce);
        Porucha();
        Wait(tKonfekce);
        Release(Konfekce);

        (new Karkas)->Activate();
    }
    void Porucha() {
        if (poruchaKonfekceJine) {
            Wait(obsluhaJine);
            poruchaKonfekceJine = false;
        }
        if (poruchaKonfekceObsluha) {
            Wait(obsluhaObsluha);
            poruchaKonfekceObsluha = false;
        }
        if (poruchaKonfEl) {
            Wait(obsluhaEl);
            poruchaKonfEl = false;
        }
    }
};

class BeginKonfekce : public Process {
    void Behavior() {
        if (kordy > 0 && lana > 0 && behouny > 0 && bocnice > 0) {
            kordy--; lana--; behouny--; bocnice--;
            (new PolotovaryKonfekce)->Activate();
        }
    }
};

class PripravaBehoun : public Process {
    void Behavior() {
        // navezeni ze skladu
        Wait(15);

        Seize(ValcovnaBehoun);
        Porucha();
        Wait(tBehouny);
        Release(ValcovnaBehoun);

        Wait(1140);
        behouny++;
        (new BeginKonfekce)->Activate();
    }
    void Porucha() {
        if (poruchaBehoun) {
            Wait(obsluhaMech);
            poruchaBehoun = false;
        }
        if (poruchaBehEl) {
            Wait(obsluhaEl);
            poruchaBehEl = false;
        }
    }
};

class PripravaBocnice : public Process {
    void Behavior() {
        // navezeni ze skladu
        Wait(14);

        Seize(ValcovnaBocnice);
        Porucha();
        Wait(tBocnice);
        Release(ValcovnaBocnice);

        Wait(1020);
        bocnice++;
        (new BeginKonfekce)->Activate();
    }
    void Porucha() {
        if (poruchaBocnice) {
            Wait(obsluhaMech);
            poruchaBocnice = false;
        }
        if (poruchaBocEl) {
            Wait(obsluhaEl);
            poruchaBocEl = false;
        }
    }
};

class PripravaKordu : public Process {
    void Behavior() {
        // navezeni ze skladu
        Wait(18);

        Seize(ValcovnaKordy);
        Porucha();
        Wait(tKordy);
        Release(ValcovnaKordy);

        Wait(1200);
        kordy++;
        (new BeginKonfekce)->Activate();
    }
    void Porucha() {
        if (poruchaKordy) {
            Wait(obsluhaMech);
            poruchaKordy = false;
        }
        if (poruchaKordEl) {
            Wait(obsluhaEl);
            poruchaKordEl = false;
        }
    }
};

class PripravaLana : public Process {
    void Behavior() {
        // navezeni ze skladu
        Wait(35);

        Seize(ValcovnaLana);
        Porucha();
        Wait(tLana);
        Release(ValcovnaLana);

        Wait(1020);
        lana++;
        (new BeginKonfekce)->Activate();
    }
    void Porucha() {
        if (poruchaLana) {
            Wait(obsluhaMech);
            poruchaLana = false;
        }
        if (poruchaLanEl) {
            Wait(obsluhaEl);
            poruchaLanEl = false;
        }
    }
};

class SmesProValcovnu : public Process {
    void Behavior() {
        Wait(1440);

        (new PripravaKordu)->Activate();
        (new PripravaLana)->Activate();
        (new PripravaBehoun)->Activate();
        (new PripravaBocnice)->Activate();
    }
};

class SurProDruhyStupen : public Process {
    void Behavior() {
        //cekani ve sklade
        Wait(360);

        Seize(Micharna2);
        Porucha();
        Wait(tMicharna2);
        Release(Micharna2);

        (new SmesProValcovnu)->Activate();
    }

    void Porucha() {
        if (poruchaMicharna2) {
            Wait(obsluhaHWSW);
            poruchaMicharna2 = false;
        }
        if (poruchaMichEl2) {
            Wait(obsluhaEl);
            poruchaMichEl2 = false;
        }
    }
};

class Suroviny : public Process {
    void Behavior() {

        Seize(Micharna1);
        Porucha();
        Wait(tMicharna1);
        Release(Micharna1);

        (new Suroviny)->Activate();
        (new SurProDruhyStupen)->Activate();
    }

    void Porucha() {
        if (poruchaMicharna1) {
            Wait(obsluhaHWSW);
            poruchaMicharna1 = false;
        }
        if (poruchaMichEl1) {
            Wait(obsluhaEl);
            poruchaMichEl1 = false;
        }
    }
};