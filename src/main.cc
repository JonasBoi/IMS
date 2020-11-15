#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <vector>
#include <simlib.h>


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

int main(int argc, char* argv[]) {

    Init(0, 525600);
    (new Suroviny)->Activate();

    // delka smeny v minutach na vsech linkach krome micharny
    // (new GeneratorSmen(960))->Activate();
    
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

