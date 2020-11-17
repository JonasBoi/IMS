#include "poruchy.h"

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


