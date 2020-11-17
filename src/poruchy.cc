#include "poruchy.h"


void PoruchaHWSW::Behavior() {
    if (Random() < 0.5)
        poruchaMicharna1 = true;
    else
        poruchaMicharna2 = true;

    (new PoruchaHWSW)->Activate(Time+Exponential(1440));
}


void PoruchaUnik::Behavior() {
    
    poruchaVulkanizaceUnik = true;
    (new PoruchaUnik)->Activate(Time+Exponential(1440));
}


void PoruchaObsluha::Behavior() {
    
    poruchaKonfekceObsluha = true;
    (new PoruchaObsluha)->Activate(Time+Exponential(1440));
}


void PoruchaJine::Behavior() {    
    poruchaKonfekceJine = true;
    (new PoruchaJine)->Activate(Time+Exponential(1440));
}



void PoruchaMechanicka::Behavior() {
    
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


void PoruchaElektro::Behavior() {
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



void PoruchaNastaveni::Behavior() {
    poruchaVulkanizaceNastaveni = true;
    (new PoruchaNastaveni)->Activate(Time+Exponential(1440));
}


void Poruchy::Behavior() {
    (new PoruchaHWSW)->Activate(Time+Exponential(1440));
    (new PoruchaUnik)->Activate(Time+Exponential(1440));
    (new PoruchaObsluha)->Activate(Time+Exponential(1440));
    (new PoruchaJine)->Activate(Time+Exponential(1440));
    (new PoruchaMechanicka)->Activate(Time+Exponential(1440));
    (new PoruchaElektro)->Activate(Time+Exponential(1440));
    (new PoruchaNastaveni)->Activate(Time+Exponential(1440));
}

