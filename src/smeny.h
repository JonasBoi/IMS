#include <simlib.h>


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

class GenSmenMicharna1 : public Process {
public:
    double Interval;

    GenSmenMicharna1(double interv);

    void Behavior();
};

class GenSmenMicharna2 : public Process {
public:
    double Interval;

    GenSmenMicharna2(double interv);

    void Behavior();
};

class GenSmenKordy : public Process {
public:
    double Interval;

    GenSmenKordy(double interv);

    void Behavior();
};

class GenSmenLana : public Process {
public:
    double Interval;

    GenSmenLana(double interv);

    void Behavior();
};


class GenSmenBehoun : public Process {
public:
    double Interval;

    GenSmenBehoun(double interv);

    void Behavior();
};

class GenSmenBocnice : public Process {
public:
    double Interval;

    GenSmenBocnice(double interv);

    void Behavior();
};

class GenSmenKonfekce: public Process {
public:
    double Interval;

    GenSmenKonfekce(double interv);

    void Behavior();
};

class GenSmenKontrola : public Process {
public:
    double Interval;

    GenSmenKontrola(double interv);

    void Behavior();
};

class GenSmenVulkanizace : public Process {
public:
    double Interval;

    GenSmenVulkanizace(double interv);

    void Behavior();
};


