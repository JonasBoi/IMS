#include <simlib.h>

// poruchy
bool poruchaMicharna1, poruchaMicharna2 = false;
bool poruchaKordy, poruchaLana, poruchaBehoun, poruchaBocnice = false;
bool poruchaKonfekceObsluha, poruchaKonfekceJine = false;
bool poruchaVulkanizaceUnik, poruchaVulkanizaceNastaveni = false;
bool poruchaMichEl1, poruchaMichEl2, poruchaLanEl, poruchaKordEl, poruchaBocEl, poruchaBehEl, poruchaKonfEl, poruchaVulkEl = false;


class PoruchaHWSW : public Event {
    void Behavior();
};

class PoruchaUnik : public Event {
    void Behavior();
};

class PoruchaObsluha : public Event {
    void Behavior();
};

class PoruchaJine : public Event {
    void Behavior();
};

class PoruchaMechanicka : public Event {
    void Behavior();
};

class PoruchaElektro : public Event {
    void Behavior();
};

class PoruchaNastaveni : public Event {
    void Behavior();
};

class Poruchy : public Event {
    void Behavior();
};
