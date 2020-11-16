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


class GeneratorSmen : public Process {
public:
    double Interval;

    GeneratorSmen(double interv) {
        Interval = interv;
    }

    void Behavior() {
        Seize(ValcovnaKordy, 1);
        Seize(ValcovnaLana, 1);
        Seize(ValcovnaBehoun, 1);
        Seize(ValcovnaBocnice, 1);
        Seize(Konfekce, 1);
        Seize(Vulkanizace, 1);
        Seize(Kontrola, 1);

        Wait(1440-Interval);

        Release(ValcovnaKordy);
        Release(ValcovnaLana);
        Release(ValcovnaBehoun);
        Release(ValcovnaBocnice);
        Release(Konfekce);
        Release(Vulkanizace);
        Release(Kontrola);

        (new GeneratorSmen(Interval))->Activate(Time + Interval);
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
    }
};

class Karkas : public Process {
    void Behavior() {
        //sklad pro vulkanizaci
        Wait(360);

        Seize(Vulkanizace);
        Wait(119);
        Release(Vulkanizace);

        (new HotovyVyrobek)->Activate();
    }
};

class PolotovaryKonfekce : public Process {
    void Behavior() {
        Seize(Konfekce);
        Wait(74);
        Release(Konfekce);

        (new Karkas)->Activate();
    }
};

class BeginKonfekce : public Process {
    void Behavior() {
        // mutex???
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
        Wait(102);
        Release(ValcovnaBehoun);

        Wait(1140);
        behouny++;
        (new BeginKonfekce)->Activate();
    }
};

class PripravaBocnice : public Process {
    void Behavior() {
        // navezeni ze skladu
        Wait(14);

        Seize(ValcovnaBocnice);
        Wait(94);
        Release(ValcovnaBocnice);

        Wait(1020);
        bocnice++;
        (new BeginKonfekce)->Activate();
    }
};

class PripravaKordu : public Process {
    void Behavior() {
        // navezeni ze skladu
        Wait(18);

        Seize(ValcovnaKordy);
        Wait(117);
        Release(ValcovnaKordy);

        Wait(1200);
        kordy++;
        (new BeginKonfekce)->Activate();
    }
};

class PripravaLana : public Process {
    void Behavior() {
        // navezeni ze skladu
        Wait(35);

        Seize(ValcovnaLana);
        Wait(57);
        Release(ValcovnaLana);

        Wait(1020);
        lana++;
        (new BeginKonfekce)->Activate();
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
        Wait(360);

        double tEntry = Time;
        double obsluha;

        Seize(Micharna2);
        Wait(193);
        Release(Micharna2);

        (new SmesProValcovnu)->Activate();
    }
};

class Suroviny : public Process {
    void Behavior() {
        double tEntry = Time;
        double obsluha;

        Seize(Micharna1);
        Wait(266);
        Release(Micharna1);

        (new Suroviny)->Activate();
        (new SurProDruhyStupen)->Activate();
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
}

void get_args(int argc, char *argv[], double *smenaMicharna1, double* smenaMicharna2, double* smenaKordy, double* smenaLana,\
            double* smenaBehouny, double* smenaBocnice, double* smenaKonfekce, double* smenaVulkanizace, double * smenaKontrola)
{

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
        {0, 0, 0, 0}
    };

    int opt_index = 0;
    int c;
    double val;

    while (1)
    {
        c = getopt_long_only(argc,argv, "a:b:c:d:e:f:g:h:i:0", long_options, &opt_index);

        if(c == -1) //end of args
            break;

        //ziskani a prevod hodnoty v argumentu, pokud je zadan
        if(optarg != NULL)
        {
            std::string strval(optarg); //argument value char * -> string

            try
            {
                val = std::stod(strval);    //string -> double hodnota
            }
            catch(std::exception &e)
            {
                std::cerr << "Nevhodna hodnota argumentu:" << optarg << "\n";
                exit(1);
            }


            if(val < 0 || val >= 1440)
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

        default:
            exit(1);
        }

    }
}


int main(int argc, char* argv[]) {

    Init(0, 525600);
    double smenaMicharna1 = 1440;
    double smenaMicharna2 = 1440;
    double smenaKordy = 1440;
    double smenaLana = 1440;
    double smenaBehouny = 1440;
    double smenaBocnice = 1440;
    double smenaKonfekce = 1440;
    double smenaVulkanizace = 1440;
    double smenaKontrola = 1440;

    get_args(argc,argv, &smenaMicharna1, &smenaMicharna2, &smenaKordy, &smenaLana, &smenaBehouny, &smenaBocnice, &smenaKonfekce, &smenaVulkanizace, &smenaKontrola);

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

    // delka smeny v minutach na vsech linkach krome micharny
    //(new GeneratorSmen(960))->Activate();
    
    /*
     TODO:
     -poruchy
     -samostatne planovani smen pro jednotlive casti provozu
     -parametrizace
    */

    Run();

    printStats();
    return EXIT_SUCCESS;
}

