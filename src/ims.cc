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
#include <iomanip>

// doby obsluhy poruch
#define obsluhaHWSW 3.84
#define obsluhaUnik 1.37
#define obsluhaObsluha 1.1
#define obsluhaJine 0.96
#define obsluhaMech 0.55
#define obsluhaEl 0.27
#define obsluhaNastav 0.22

// linky
Facility Micharna1("Micharna 1. stupen");
Facility Micharna2("Micharna 2. stupen");
Facility ValcovnaKordy("Pripravna kordu");
Facility ValcovnaLana("Pripravna lana");
Facility ValcovnaBehoun("Pripravna behounu");
Facility ValcovnaBocnice("Pripravna bocnice");
Facility Konfekce("Konfekce");
Facility Vulkanizace("Vulkanizace");
Facility Kontrola("Kontrola kvality");

// casy vystupu transakci
std::vector <double> transactionExitTimes; 

// casy behu linek
double tMicharna1 = 266;
double tMicharna2 = 193;
double tKordy = 117;
double tLana = 57;
double tBehouny = 102;
double tBocnice = 94;
double tKonfekce = 74;
double tVulkanizace = 119;
double tKontrola = 15;

// polotovary
int kordy, lana, behouny, bocnice = 0;

// pocitadlo transakci
int transakce = 0;
int stopcount = INT32_MAX;

// indikatory poruch
bool poruchaMicharna1, poruchaMicharna2 = false;
bool poruchaKordy, poruchaLana, poruchaBehoun, poruchaBocnice = false;
bool poruchaKonfekceObsluha, poruchaKonfekceJine = false;
bool poruchaVulkanizaceUnik, poruchaVulkanizaceNastaveni = false;
bool poruchaMichEl1, poruchaMichEl2, poruchaLanEl, poruchaKordEl, poruchaBocEl, poruchaBehEl, poruchaKonfEl, poruchaVulkEl = false;


/*
 * =====================================          poruchy          ====================================
 */

// udalost poruchy hw
class PoruchaHWSW : public Event {
    void Behavior() {

        if (Random() < 0.5)
            poruchaMicharna1 = true;
        else
            poruchaMicharna2 = true;

        (new PoruchaHWSW)->Activate(Time+Exponential(1440));
    }
};


// udalost poruchy uniku medii
class PoruchaUnik : public Event {
    void Behavior() {
        
        poruchaVulkanizaceUnik = true;
        (new PoruchaUnik)->Activate(Time+Exponential(1440));
    }
};


// udalost poruchy nepozornosti obsluhy
class PoruchaObsluha : public Event {
    void Behavior() {
        
        poruchaKonfekceObsluha = true;
        (new PoruchaObsluha)->Activate(Time+Exponential(1440));
    }
};


// udalost poruchy kategorie jine
class PoruchaJine : public Event {
    void Behavior() {
        
        poruchaKonfekceJine = true;
        (new PoruchaJine)->Activate(Time+Exponential(1440));
    }
};


// udalost poruchy mechanicke zavady
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


// udalost poruchy elektricke zavady
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


// udalost poruchy nastaveni
class PoruchaNastaveni : public Event {
    void Behavior() {
        poruchaVulkanizaceNastaveni = true;

        (new PoruchaNastaveni)->Activate(Time+Exponential(1440));
    }
};


// udalost pro pocatek generovani poruch
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

/*
 * =====================================          SMENY          ====================================
 */

// proces konce smeny micharna1
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


// proces konce smeny micharna2
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


// proces konce smeny valcovna1
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


// proces konce smeny valcovna2
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


// proces konce smeny valcovna3
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


// proces konce smeny valcovna4
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


// proces konce smeny konfekce
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


// proces konce smeny kontroly
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


// proces konce smeny vulkanizace
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


/*
 * =====================================         VYROBA         ====================================
 */

// proces kontroly vyrobku
class HotovyVyrobek : public Process {
    void Behavior() {

        Seize(Kontrola);
        Wait(tKontrola);
        Release(Kontrola);

        transakce++;
        transactionExitTimes.push_back(Time);

        if (transakce >= stopcount) {
            Stop();
        }

    }
};


// proces vulkanizace karkasu
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


// proces konfekce polotovaru
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


// proces zjistujici dostupnost polotovaru pro konfekci
class BeginKonfekce : public Process {

    void Behavior() {
        if (kordy > 0 && lana > 0 && behouny > 0 && bocnice > 0) {
            kordy--; lana--; behouny--; bocnice--;
            (new PolotovaryKonfekce)->Activate();
        }
    }
};


// proces pripravy behounu
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


// proces pripravy bocnice
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


// proces pripravy kordu
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


// proces pripravy lana
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


// proces startujici vyrobu ve valcovne
class SmesProValcovnu : public Process {

    void Behavior() {
        Wait(1440);

        (new PripravaKordu)->Activate();
        (new PripravaLana)->Activate();
        (new PripravaBehoun)->Activate();
        (new PripravaBocnice)->Activate();
    }
};


// proces hneteni 2. stupne
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


// proces hneteni prvniho stupne
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

/*
 * =====================================          funkce          ====================================
 */

// statistiky o intervalu mezi vystupem dvou transakti ze systemu
void printMeanValue(std::vector <double> values) {
    int cnt = values.size();
    double interval;
    Stat intervals("=== Interval mezi vystupem dvou transakci ===");

    intervals(values.at(0));

    // ziskani intervalu ve kterych ktransakce opoustely system
    for (int i = 1; i < cnt-1; i++) {

        interval = values.at(i+1) - values.at(i);
        intervals(interval);
    }

    intervals.Output();
}

void PrintMeanUtil() {
    double mean = (Micharna1.tstat.MeanValue() + Micharna2.tstat.MeanValue() + ValcovnaKordy.tstat.MeanValue() + ValcovnaLana.tstat.MeanValue() + ValcovnaBehoun.tstat.MeanValue()\
    + ValcovnaBocnice.tstat.MeanValue()+Konfekce.tstat.MeanValue()+Vulkanizace.tstat.MeanValue()+Kontrola.tstat.MeanValue()) ;
    
    mean = mean/9.0;

    std::cout << "Prumerne celkove vyuziti: " << std::fixed << std::setprecision(3) << mean * 100 << "%\n";
    std::cout << "+----------------------------------------------------------+\n";
}
// funkce pro minimalisticky prehled statistik
void printStatsMini() {
    std::cout << "+----------------------------------------------------------+\n";
    std::cout << "| VYUZITI LINEK                                            |\n";
    std::cout << "+----------------------------------------------------------+\n";
    std::cout << "Vyuziti Micharny 1. stupne: " << std::fixed << std::setprecision(3) << Micharna1.tstat.MeanValue()* 100 << "%\n";
    std::cout << "Vyuziti Micharny 2. stupne: " << std::fixed << std::setprecision(3) << Micharna2.tstat.MeanValue()* 100 << "%\n";
    std::cout << "Vyuziti Valcovny Kordy: " << std::fixed << std::setprecision(3) << ValcovnaKordy.tstat.MeanValue()* 100 << "%\n";
    std::cout << "Vyuziti Valcovny Lana: " << std::fixed << std::setprecision(3) << ValcovnaLana.tstat.MeanValue()* 100 << "%\n";
    std::cout << "Vyuziti Valcovny Behouny: " << std::fixed << std::setprecision(3) << ValcovnaBehoun.tstat.MeanValue()* 100 << "%\n";
    std::cout << "Vyuziti Valcovny Bocnice: " << std::fixed << std::setprecision(3) << ValcovnaBocnice.tstat.MeanValue()* 100 << "%\n";
    std::cout << "Vyuziti Konfekce: " << std::fixed << std::setprecision(3) << Konfekce.tstat.MeanValue()* 100 << "%\n";
    std::cout << "Vyuziti Vulkanizace: " << std::fixed << std::setprecision(3) << Vulkanizace.tstat.MeanValue()* 100 << "%\n";
    std::cout << "Vyuziti Kontroly: " << std::fixed << std::setprecision(3) << Kontrola.tstat.MeanValue()* 100 << "%\n";
    std::cout << "+----------------------------------------------------------+\n";
  
    PrintMeanUtil();
    
    std::cout << "\nDokoncene transakce :" + std::to_string(transakce) + "\n";

    if (stopcount < INT32_MAX) {
        std::cout << "Cas dokonceni davky transakci: " << Time / 60 / 24 << " dní (" << Time << " minut).\n";
    }

    printMeanValue(transactionExitTimes);
}


//funkce pro tisk statistik
void printStats(bool verbose) {

    if (verbose) {

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
    }

    printStatsMini();

}


//funkce pro zpracovani argumentu
void get_args(int argc, char *argv[], double *smenaMicharna1, double* smenaMicharna2, double* smenaKordy, double* smenaLana,\
            double* smenaBehouny, double* smenaBocnice, double* smenaKonfekce, double* smenaVulkanizace, double * smenaKontrola,
             bool * verbose, bool * poruchy, int* timespan)
{

    if (argc > 1 && (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-help"))) {
        // todo USE
        std::cout << "Pouziti:\n\n";
        std::cout << "-t/-time [dni] ......... delka behu simulace (pocet dni)\n";
        std::cout << "-v/-verbose ............ vypis vsech informaci o linkach\n";
        std::cout << "-x/-bezporuch .......... beh simulace bez poruch \n";
        std::cout << "-s/stop [transakci] .... zastavi beh simulace po propusteni zadaneho poctu \n";
        std::cout << "-[linka] [delka smeny v minutach]\n";
        std::cout << "linky: micharna1/a , micharna2/b, kordy/c, lana/d, behouny/e,\n";
        std::cout << "bocnice/f, konfekce/g, vulkanizace/h, kontrola/i\n";
        std::cout << "-t[linka]/[j-r] [doba obsluhy v minutach] Zmena doby obsluhy linky\n\n";
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
        {"tmicharna1", required_argument, NULL, 'j'},
        {"tmicharna2", required_argument, NULL, 'k'},
        {"tkordy", required_argument, NULL, 'l'},
        {"tlana", required_argument, NULL, 'm'},
        {"tbehouny", required_argument, NULL, 'n'},
        {"tbocnice", required_argument, NULL, 'o'},
        {"tkonfekce", required_argument, NULL, 'p'},
        {"tvulkanizace", required_argument, NULL, 'q'},
        {"tkontrola", required_argument, NULL, 'r'},
        {"verbose", no_argument, NULL, 'v'},
        {"bezporuch", no_argument, NULL, 'x'},
        {"time", required_argument, NULL, 't'},
        {"stop", required_argument, NULL, 's'},
        {0, 0, 0, 0}
    };

    int opt_index = 0;
    int c;
    double val;

    while (1)
    {
        c = getopt_long_only(argc,argv, "a:b:c:d:e:f:g:h:i:0vxt:s:j:k:l:m:n:o:p:q:r:", long_options, &opt_index);

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


            if(c != 't' && c != 's' && (val <= 0 || val > 1440))
            {
                std::cerr << "Nevhodna hodnota argumentu: " << optarg << " ...musi byt mezi 0-1440\n";
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

        case 'j':
            std::cout << "doba behu linky micharna 1. stupne nastavena na: " << val << " minut\n";;
            tMicharna1 = val;
            break;

        case 'k':
            std::cout << "doba behu linky micharna 2. stupne nastavena na: " << val << " minut\n";;
            tMicharna2 = val;
            break;

        case 'l':
            std::cout << "doba behu linky pripravna kordu nastavena na: " << val << " minut\n";;
            tKordy = val;
            break;

        case 'm':
            std::cout << "doba behu linky pripravna lan nastavena na: " << val << " minut\n";;
            tLana = val;
            break;

        case 'n':
            std::cout << "doba behu linky pripravna behounu nastavena na: " << val << " minut\n";;
            tBehouny = val;
            break;

        case 'o':
            std::cout << "doba behu linky pripravna bocnic nastavena na: " << val << " minut\n";;
            tBocnice = val;
            break;

        case 'p':
            std::cout << "doba behu linky kofekce nastavena na: " << val << " minut\n";
            tKonfekce = val;
            break;

        case 'q':
            std::cout << "doba behu linky vulkanizace nastavena na: " << val << " minut\n";
            tVulkanizace = val;
            break;

        case 'r':
            std::cout << "doba behu linky kontrola nastavena na: " << val << " minut\n";
            tKontrola = val;
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

        case 's':
            std::cout << "pozadovany pocet transakci nastaven na: " << val << "\n";
            stopcount = val;
            break;

        default:
            exit(1);
        }

    }
    std::cout << "\n";
}

// -------------------------------------------======== MAIN =========----------------------------------------------------
int main(int argc, char* argv[]) {

    // puvodni delka smen - 24h nonstop
    double smenaMicharna1 = 1440;
    double smenaMicharna2 = 1440;
    double smenaKordy = 1440;
    double smenaLana = 1440;
    double smenaBehouny = 1440;
    double smenaBocnice = 1440;
    double smenaKonfekce = 1440;
    double smenaVulkanizace = 1440;
    double smenaKontrola = 1440;

    bool verbose = false; // implicitne strucny mod
    bool poruchy = true; // implicitne poruchy zapnuty
    int timespan = 1440 * 365; // implicitni timespan 1 rok

    // zpracovani argumentu
    get_args(argc,argv, &smenaMicharna1, &smenaMicharna2, &smenaKordy, &smenaLana,
     &smenaBehouny, &smenaBocnice, &smenaKonfekce, &smenaVulkanizace, &smenaKontrola,
      &verbose, &poruchy, &timespan);

    // init timespan
    Init(0, timespan);

    // zahajeni vyroby
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

    // zahajeni simulace
    Run();

    // print stats
    printStats(verbose);

    return EXIT_SUCCESS;
}

