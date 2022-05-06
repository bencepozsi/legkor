#pragma once
#include "weather.h"

class Layer{
    protected:
        double _size;
        Layer(double s):_size(s){}
    public:
        virtual bool isOxygen(){return false;}
        virtual bool isOzone(){return false;}
        virtual bool isCarbonDioxide(){return false;}
        virtual bool change(Weather* w, Layer* &l) = 0;
        void add(Layer* p){_size += p->getSize();}
        double getSize(){return _size;}
        void setSize(double size){_size = size;}
        virtual ~Layer(){}
};

class Ozone : public Layer{
    public:
        bool isOzone()override{return true;}
        bool change(Weather* w, Layer* &l)override{ return w->change(this,l);}
        Ozone(double s): Layer(s) {}
};

class Oxygen: public Layer{
    public:
        bool isOxygen() override {return true;}
        bool change(Weather* w, Layer* &l)override{ return w->change(this,l);}
        Oxygen(double s): Layer(s) {}
};

class CarbonDioxide: public Layer{
    public:
        bool isCarbonDioxide() override {return true;}
        bool change(Weather* w, Layer* &l)override{ return w->change(this,l);}
        CarbonDioxide(double s): Layer(s) {}
};