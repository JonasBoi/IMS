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

Facility Micharna1("Micharna 1. stupen");
Facility Micharna2("Micharna 2. stupen");
Facility ValcovnaKordy("Pripravna kordu");
Facility ValcovnaLana("Pripravna lana");
Facility ValcovnaBehoun("Pripravna behounu");
Facility ValcovnaBocnice("Pripravna bocnice");
Facility Konfekce("Konfekce");
Facility Vulkanizace("Vulkanizace");
Facility Kontrola("Kontrola kvality");

int kordy, lana, behouny, bocnice = 0;
int transakce = 0;

// poruchy
bool poruchaMicharna1, poruchaMicharna2 = false;
bool poruchaKordy, poruchaLana, poruchaBehoun, poruchaBocnice = false;
bool poruchaKonfekceObsluha, poruchaKonfekceJine = false;
bool poruchaVulkanizaceUnik, poruchaVulkanizaceNastaveni = false;
bool poruchaMichEl1, poruchaMichEl2, poruchaLanEl, poruchaKordEl, poruchaBocEl, poruchaBehEl, poruchaKonfEl, poruchaVulkEl = false;

class PoruchaHWSW : public Event {
    void Behavior() {

        if (Random() < 0.5)
            poruchaMicharna1 = true;
        else
            poruchaMicharna2 = true;

        (new PoruchaHWSW)->Activate(Time+Exponential(1440));
    }
};

class PoruchaUnik : public Event {
    void Behavior() {
        
        poruchaVulkanizaceUnik = true;
        (new PoruchaUnik)->Activate(Time+Exponential(1440));
    }
};

class PoruchaObsluha : public Event {
    void Behavior() {
        
        poruchaKonfekceObsluha = true;
        (new PoruchaObsluha)->Activate(Time+Exponential(1440));
    }
};

class PoruchaJine : public Event {
    void Behavior() {
        
        poruchaKonfekceJine = true;
        (new PoruchaJine)->Activate(Time+Exponential(1440));
    }
};

class PoruchaMechanicka : public Event {
    void Behavior() {
        
        double rnd = Random();

        if (rnd < 0.25)
            poruchaKordy = true;
        else if (rnd < 0.5)
            poruchaLana = true;
        else if (rnd < 0.75)
            poruchaBehoun = true;
        else 
            poruchaBocnice = true;

        (new PoruchaMechanicka)->Activate(Time+Exponential(1440));
    }
};

class PoruchaElektro : public Event {
    void Behavior() {
        poruchaMichEl1 = true;
        poruchaMichEl2 = true;
        poruchaLanEl = true;
        poruchaKordEl = true;
        poruchaBocEl = true;
        poruchaBehEl = true;
        poruchaKonfEl = true;
        poruchaVulkEl = true;

        (new PoruchaElektro)->Activate(Time+Exponential(1440));
    }
};

class PoruchaNastaveni : public Event {
    void Behavior() {
        poruchaVulkanizaceNastaveni = true;

        (new PoruchaNastaveni)->Activate(Time+Exponential(1440));
    }
};

class Poruchy : public Event {
    void Behavior() {
        (new PoruchaHWSW)->Activate(Time+Exponential(1440));
        (new PoruchaUnik)->Activate(Time+Exponential(1440));
        (new PoruchaObsluha)->Activate(Time+Exponential(1440));
        (new PoruchaJine)->Activate(Time+Exponential(1440));
        (new PoruchaMechanicka)->Activate(Time+Exponential(1440));
        (new PoruchaElektro)->Activate(Time+Exponential(1440));
        (new PoruchaNastaveni)->Activate(Time+Exponential(1440));
    }
};

class GenSmenMicharna1 : public Process {
public:
    double Interval;

    GenSmenMicharna1(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(Micharna1, 1);

        Wait(1440-Interval);

        Release(Micharna1);

        (new GenSmenMicharna1(Interval))->Activate(Time + Interval);
    }
};

class GenSmenMicharna2 : public Process {
public:
    double Interval;

    GenSmenMicharna2(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(Micharna2, 1);

        Wait(1440-Interval);

        Release(Micharna2);

        (new GenSmenMicharna2(Interval))->Activate(Time + Interval);
    }
};

class GenSmenKordy : public Process {
public:
    double Interval;

    GenSmenKordy(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(ValcovnaKordy, 1);

        Wait(1440-Interval);

        Release(ValcovnaKordy);

        (new GenSmenKordy(Interval))->Activate(Time + Interval);
    }
};

class GenSmenLana : public Process {
public:
    double Interval;

    GenSmenLana(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(ValcovnaLana, 1);

        Wait(1440-Interval);

        Release(ValcovnaLana);

        (new GenSmenLana(Interval))->Activate(Time + Interval);
    }
};


class GenSmenBehoun : public Process {
public:
    double Interval;

    GenSmenBehoun(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(ValcovnaBehoun, 1);

        Wait(1440-Interval);

        Release(ValcovnaBehoun);

        (new GenSmenBehoun(Interval))->Activate(Time + Interval);
    }
};

class GenSmenBocnice : public Process {
public:
    double Interval;

    GenSmenBocnice(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(ValcovnaBocnice, 1);

        Wait(1440-Interval);

        Release(ValcovnaBocnice);

        (new GenSmenBocnice(Interval))->Activate(Time + Interval);
    }
};

class GenSmenKonfekce: public Process {
public:
    double Interval;

    GenSmenKonfekce(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(Konfekce, 1);

        Wait(1440-Interval);

        Release(Konfekce);

        (new GenSmenKonfekce(Interval))->Activate(Time + Interval);
    }
};

class GenSmenKontrola : public Process {
public:
    double Interval;

    GenSmenKontrola(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(Kontrola, 1);

        Wait(1440-Interval);

        Release(Kontrola);

        (new GenSmenKontrola(Interval))->Activate(Time + Interval);
    }
};

class GenSmenVulkanizace : public Process {
public:
    double Interval;

    GenSmenVulkanizace(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(Vulkanizace, 1);

        Wait(1440-Interval);

        Release(Vulkanizace);

        (new GenSmenVulkanizace(Interval))->Activate(Time + Interval);
    }
};


class HotovyVyrobek : public Process {
    void Behavior() {
        Seize(Kontrola);
        Wait(15);
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
        Wait(119);
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
        Wait(74);
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
        Wait(102);
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
        Wait(94);
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
        Wait(117);
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
        Wait(57);
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
        Wait(193);
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
        Wait(266);
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

void printStats() {

    printf("Micharna:--------------------------------------------------\n\n");
    Micharna1.Output();
    Micharna2.Output();
    printf("Micharna---konec:------------------------------------------\n\n");

    printf("Valcovna:--------------------------------------------------\n\n");
    ValcovnaKordy.Output();
    ValcovnaLana.Output();
    ValcovnaBehoun.Output();
    ValcovnaBocnice.Output();
    printf("Valcovna---konec-------------------------------------------\n\n");

    Konfekce.Output();

    Vulkanizace.Output();

    Kontrola.Output();

    std::cout << "\nDokoncene transakce:" + std::to_string(transakce) + "\n";

}

void printStatsMini() {
    std::cout << "Vyuziti Micharny 1. stupne: " + std::to_string(Micharna1.tstat.MeanValue()) + "\n";
    std::cout << "Vyuziti Micharny 2. stupne: " + std::to_string(Micharna2.tstat.MeanValue()) + "\n";
    std::cout << "Vyuziti Valcovny Kordy: " + std::to_string(ValcovnaKordy.tstat.MeanValue()) + "\n";
    std::cout << "Vyuziti Valcovny Lana: " + std::to_string(ValcovnaLana.tstat.MeanValue()) + "\n";
    std::cout << "Vyuziti Valcovny Behouny: " + std::to_string(ValcovnaBehoun.tstat.MeanValue()) + "\n";
    std::cout << "Vyuziti Valcovny Bocnice: " + std::to_string(ValcovnaBocnice.tstat.MeanValue()) + "\n";
    std::cout << "Vyuziti Konfekce: " + std::to_string(Konfekce.tstat.MeanValue()) + "\n";
    std::cout << "Vyuziti Vulkanizace: " + std::to_string(Vulkanizace.tstat.MeanValue()) + "\n";
    std::cout << "Vyuziti Kontroly: " + std::to_string(Kontrola.tstat.MeanValue()) + "\n";
    std::cout << "\nDokoncene transakce:" + std::to_string(transakce) + "\n";
}

void get_args(int argc, char *argv[], double *smenaMicharna1, double* smenaMicharna2, double* smenaKordy, double* smenaLana,\
            double* smenaBehouny, double* smenaBocnice, double* smenaKonfekce, double* smenaVulkanizace, double * smenaKontrola,
             bool * verbose, bool * poruchy, int* timespan)
{

if (argc > 1 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-help"))) {
    // todo USE
    std::cout << "Pouziti:\n\n";
    std::cout << "-t/-time ......... delka behu simulace (pocet dni)\n";
    std::cout << "-v/-verbose ...... vypis vsech informaci o linkach\n";
    std::cout << "-x/-bezporuch .... beh simulace bez poruch \n\n";
    std::cout << "-[linka] [delka smeny v minutach]\n";
    std::cout << "linky: micharna1/a , micharna2/b, kordy/c, lana/d, behouny/e,\n";
    std::cout << "bocnice/f, konfekce/g, vulkanizace/h, kontrola/i\n\n";
    exit(0);
}

//mozne argumenty
    static struct option long_options[] =
    {
        {"", no_argument, NULL, '0'},
        {"micharna1", required_argument, NULL, 'a'},
        {"micharna2", required_argument, NULL, 'b'},
        {"kordy", required_argument, NULL, 'c'},
        {"lana", required_argument, NULL, 'd'},
        {"behouny", required_argument, NULL, 'e'},
        {"bocnice", required_argument, NULL, 'f'},
        {"konfekce", required_argument, NULL, 'g'},
        {"vulkanizace", required_argument, NULL, 'h'},
        {"kontrola", required_argument, NULL, 'i'},
        {"verbose", no_argument, NULL, 'v'},
        {"bezporuch", no_argument, NULL, 'x'},
        {"time", required_argument, NULL, 't'},
        {0, 0, 0, 0}
    };

    int opt_index = 0;
    int c;
    double val;

    std::cout << "\n";

    while (1)
    {
        c = getopt_long_only(argc,argv, "a:b:c:d:e:f:g:h:i:0vxt:", long_options, &opt_index);

        if(c == -1) //end of args
            break;

        //ziskani a prevod hodnoty v argumentu, pokud je zadan
        if(optarg != NULL)
        {
            std::string strval(optarg); //argument value char * -> string

            try
            {
                val = std::stod(strval);//string -> double hodnota
            }
            catch(std::exception &e)
            {
                std::cerr << "Nevhodna hodnota argumentu:" << optarg << "\n";
                exit(1);
            }


            if(c != 't' && (val < 0 || val >= 1440))
            {
                std::cerr << "Nevhodna hodnota argumentu: " << optarg << " ...musi byt mezi 0-1439\n";
                exit(1);
            }
        }

        switch (c)
        {
        case '0':
            break;

        case 'a':
            std::cout << "delka smeny pro micharnu 1. stupne nastavena na: " << val << " minut\n";;
            *smenaMicharna1 = val;
            break;

        case 'b':
            std::cout << "delka smeny pro micharnu 2. stupne nastavena na: " << val << " minut\n";;
            *smenaMicharna2 = val;
            break;

        case 'c':
            std::cout << "delka smeny pro pripravnu kordu nastavena na: " << val << " minut\n";;
            *smenaKordy = val;
            break;

        case 'd':
            std::cout << "delka smeny pro pripravnu lan nastavena na: " << val << " minut\n";;
            *smenaLana = val;
            break;

        case 'e':
            std::cout << "delka smeny pro pripravnu behounu nastavena na: " << val << " minut\n";;
            *smenaBehouny = val;
            break;

        case 'f':
            std::cout << "delka smeny pro pripravnu bocnic nastavena na: " << val << " minut\n";;
            *smenaBocnice = val;
            break;

        case 'g':
            std::cout << "delka smeny pro kofekci nastavena na: " << val << " minut\n";
            *smenaKonfekce = val;
            break;

        case 'h':
            std::cout << "delka smeny pro vulkanizaci nastavena na: " << val << " minut\n";
            *smenaVulkanizace = val;
            break;

        case 'i':
            std::cout << "delka smeny pro kontrolu nastavena na: " << val << " minut\n";
            *smenaKontrola = val;
            break;

        case 'v':
            *verbose = true;
            break;

        case 'x':
            std::cout << "Poruchy vypnuty.\n";
            *poruchy = false;
            break;
        
        case 't':
            std::cout << "delka simulace nastavena na: " << val << " dní\n";
            *timespan = val * 1440;
            break;

        default:
            exit(1);
        }

    }
    std::cout << "\n";
}


int main(int argc, char* argv[]) {

    double smenaMicharna1 = 1440;
    double smenaMicharna2 = 1440;
    double smenaKordy = 1440;
    double smenaLana = 1440;
    double smenaBehouny = 1440;
    double smenaBocnice = 1440;
    double smenaKonfekce = 1440;
    double smenaVulkanizace = 1440;
    double smenaKontrola = 1440;
    bool verbose = false;
    bool poruchy = true;
    int timespan = 1440 * 365;

    get_args(argc,argv, &smenaMicharna1, &smenaMicharna2, &smenaKordy, &smenaLana,
     &smenaBehouny, &smenaBocnice, &smenaKonfekce, &smenaVulkanizace, &smenaKontrola,
      &verbose, &poruchy, &timespan);

    // init timespan
    Init(0, timespan);

    (new Suroviny)->Activate();

    //omezeni linek u kterych byla nastavena delka smeny
    if(smenaMicharna1 != 1440)
        (new GenSmenMicharna1(smenaMicharna1))->Activate();
    if(smenaMicharna2 != 1440)
        (new GenSmenMicharna2(smenaMicharna2))->Activate();
    if(smenaKordy != 1440)
        (new GenSmenKordy(smenaKordy))->Activate();
    if(smenaLana != 1440)
        (new GenSmenLana(smenaLana))->Activate();
    if(smenaBehouny != 1440)
        (new GenSmenBehoun(smenaBehouny))->Activate();
    if(smenaBocnice != 1440)
        (new GenSmenBocnice(smenaBocnice))->Activate();
    if(smenaKonfekce!= 1440)
        (new GenSmenKonfekce(smenaKonfekce))->Activate();
    if(smenaVulkanizace!= 1440)
        (new GenSmenVulkanizace(smenaVulkanizace))->Activate();
    if(smenaKontrola!= 1440)
        (new GenSmenKontrola(smenaKontrola))->Activate();

    // zapnout generovani poruch
    if (poruchy)
        (new Poruchy)->Activate();

    Run();

    // print stats
    if (verbose) 
        printStats();
    else 
        printStatsMini();

    return EXIT_SUCCESS;
}

