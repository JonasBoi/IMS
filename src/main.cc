#include "vyroba.h"
#include "poruchy.h"
#include "smeny.h"


void HotovyVyrobek::Behavior() {
    Seize(Kontrola);
    Wait(tKontrola);
    Release(Kontrola);
    transakce++;
}


void Karkas::Behavior() {
    //sklad pro vulkanizaci
    Wait(360);

    Seize(Vulkanizace);
    Porucha();
    Wait(tVulkanizace);
    Release(Vulkanizace);

    (new HotovyVyrobek)->Activate();
}

void Karkas::Porucha() {
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


void PolotovaryKonfekce::Behavior() {
    Seize(Konfekce);
    Porucha();
    Wait(tKonfekce);
    Release(Konfekce);

    (new Karkas)->Activate();
}

void PolotovaryKonfekce::Porucha() {
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


void BeginKonfekce::Behavior() {
    if (kordy > 0 && lana > 0 && behouny > 0 && bocnice > 0) {
        kordy--; lana--; behouny--; bocnice--;
        (new PolotovaryKonfekce)->Activate();
    }
}


void PripravaBehoun::Behavior() {
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

void PripravaBehoun::Porucha() {
    if (poruchaBehoun) {
        Wait(obsluhaMech);
        poruchaBehoun = false;
    }
    if (poruchaBehEl) {
        Wait(obsluhaEl);
        poruchaBehEl = false;
    }
}


void PripravaBocnice::Behavior() {
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

void PripravaBocnice::Porucha() {
    if (poruchaBocnice) {
        Wait(obsluhaMech);
        poruchaBocnice = false;
    }
    if (poruchaBocEl) {
        Wait(obsluhaEl);
        poruchaBocEl = false;
    }
}


void PripravaKordu::Behavior() {
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

void PripravaKordu::Porucha() {
    if (poruchaKordy) {
        Wait(obsluhaMech);
        poruchaKordy = false;
    }
    if (poruchaKordEl) {
        Wait(obsluhaEl);
        poruchaKordEl = false;
    }
}


void PripravaLana::Behavior() {
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

void PripravaLana::Porucha() {
    if (poruchaLana) {
        Wait(obsluhaMech);
        poruchaLana = false;
    }
    if (poruchaLanEl) {
        Wait(obsluhaEl);
        poruchaLanEl = false;
    }
}


void SmesProValcovnu::Behavior() {
    Wait(1440);

    (new PripravaKordu)->Activate();
    (new PripravaLana)->Activate();
    (new PripravaBehoun)->Activate();
    (new PripravaBocnice)->Activate();
}

void SurProDruhyStupen::Behavior() {
    //cekani ve sklade
    Wait(360);
    Seize(Micharna2);
    Porucha();
    Wait(tMicharna2);
    Release(Micharna2);

    (new SmesProValcovnu)->Activate();
}

void SurProDruhyStupen::Porucha() {
    if (poruchaMicharna2) {
        Wait(obsluhaHWSW);
        poruchaMicharna2 = false;
    }
    if (poruchaMichEl2) {
        Wait(obsluhaEl);
        poruchaMichEl2 = false;
    }
}

void Suroviny::Behavior() {
    Seize(Micharna1);
    Porucha();
    Wait(tMicharna1);
    Release(Micharna1);

    (new Suroviny)->Activate();
    (new SurProDruhyStupen)->Activate();
}

void Suroviny::Porucha() {
    if (poruchaMicharna1) {
        Wait(obsluhaHWSW);
        poruchaMicharna1 = false;
    }
    if (poruchaMichEl1) {
        Wait(obsluhaEl);
        poruchaMichEl1 = false;
    }
}


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
    std::cout << "Casy behu linek: t[linka]/[j-r] [cas behu v minutach]";
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

