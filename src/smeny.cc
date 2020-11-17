#include "smeny.h"


GenSmenMicharna1::GenSmenMicharna1(double interv) {
    Interval = interv;
}

void GenSmenMicharna1::Behavior() {
    Seize(Micharna1, 1);
    Wait(1440-Interval);
    Release(Micharna1);
    (new GenSmenMicharna1(Interval))->Activate(Time + Interval);
}



GenSmenMicharna2::GenSmenMicharna2(double interv) {
    Interval = interv;
}

void GenSmenMicharna2::Behavior() {
    Seize(Micharna2, 1);
    Wait(1440-Interval);
    Release(Micharna2);
    (new GenSmenMicharna2(Interval))->Activate(Time + Interval);
}



GenSmenKordy::GenSmenKordy(double interv) {
    Interval = interv;
}

void GenSmenKordy::Behavior() {
    Seize(ValcovnaKordy, 1);
    Wait(1440-Interval);
    Release(ValcovnaKordy);
    (new GenSmenKordy(Interval))->Activate(Time + Interval);
}



GenSmenLana::GenSmenLana(double interv) {
    Interval = interv;
}

void GenSmenLana::Behavior() {
    Seize(ValcovnaLana, 1);
    Wait(1440-Interval);
    Release(ValcovnaLana);
    (new GenSmenLana(Interval))->Activate(Time + Interval);
}



GenSmenBehoun::GenSmenBehoun(double interv) {
    Interval = interv;
}

void GenSmenBehoun::Behavior() {
    Seize(ValcovnaBehoun, 1);
    Wait(1440-Interval);
    Release(ValcovnaBehoun);
    (new GenSmenBehoun(Interval))->Activate(Time + Interval);
}


GenSmenBocnice::GenSmenBocnice(double interv) {
    Interval = interv;
}

void GenSmenBocnice::Behavior() {
    Seize(ValcovnaBocnice, 1);
    Wait(1440-Interval);
    Release(ValcovnaBocnice);
    (new GenSmenBocnice(Interval))->Activate(Time + Interval);
}


GenSmenKonfekce::GenSmenKonfekce(double interv) {
    Interval = interv;
}

void GenSmenKonfekce::Behavior() {
    Seize(Konfekce, 1);
    Wait(1440-Interval);
    Release(Konfekce);
    (new GenSmenKonfekce(Interval))->Activate(Time + Interval);
}


GenSmenKontrola::GenSmenKontrola(double interv) {
    Interval = interv;
}

void GenSmenKontrola::Behavior() {
    Seize(Kontrola, 1);
    Wait(1440-Interval);
    Release(Kontrola);
    (new GenSmenKontrola(Interval))->Activate(Time + Interval);
}


GenSmenVulkanizace::GenSmenVulkanizace(double interv) {
    Interval = interv;
}

void GenSmenVulkanizace::Behavior() {
    Seize(Vulkanizace, 1);
    Wait(1440-Interval);
    Release(Vulkanizace);
    (new GenSmenVulkanizace(Interval))->Activate(Time + Interval);
}


