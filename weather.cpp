#include "weather.h"
#include "layer.h"

using namespace std;

Rainy* Rainy::_instance = nullptr;
Rainy* Rainy::instance(){
    if(_instance == nullptr) {
        _instance = new Rainy();
    }
    return _instance;
}
void Rainy::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

bool Rainy::change(Ozone* m, Layer* &p){
    return  false;
}

bool Rainy::change(Oxygen* m, Layer* &p){
    double size = m->getSize();
    m->setSize(size*0.5);
    p = new Ozone(size*0.5);
    return true;
}

bool Rainy::change(CarbonDioxide* m, Layer* &p){
    return false;
}

Sunny* Sunny::_instance = nullptr;
Sunny* Sunny::instance(){
    if(_instance == nullptr) {
        _instance = new Sunny();
    }
    return _instance;
}

void Sunny::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

bool Sunny::change(Ozone* m, Layer* &p){
    return false;
}

bool Sunny::change(Oxygen* m, Layer* &p){
    double size = m->getSize();
    m->setSize(size*0.95);
    p = new Ozone(size*0.05);
    return true;
}

bool Sunny::change(CarbonDioxide* m, Layer* &p){
    double size = m->getSize();
    m->setSize(size*0.95);
    p = new Oxygen(size*0.05);
    return true;
}

Other* Other::_instance = nullptr;
Other* Other::instance(){
    if(_instance == nullptr) {
        _instance = new Other();
    }
    return _instance;
}
void Other::destroy()
{
    if ( nullptr!=_instance )
    {
        delete _instance;
        _instance = nullptr;
    }
}

bool Other::change(Ozone* m, Layer* &p){
    double size = m->getSize();
    m->setSize(size*0.95);
    p = new Oxygen(size*0.05);
    return true;
}

bool Other::change(Oxygen* m, Layer* &p){
    double size = m->getSize();
    m->setSize(size*0.9);
    p = new CarbonDioxide(size*0.1);
    return true;
}

bool Other::change(CarbonDioxide* m, Layer* &p){
    return false;   
}