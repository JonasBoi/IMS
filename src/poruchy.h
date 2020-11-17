#include "main.h"


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
