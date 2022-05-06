#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "layer.h"
#include "weather.h"

using namespace std;

void create(const string fn, vector<Layer*> &layers, vector<Weather*> &weather){
    ifstream fs(fn);
    if(fs.fail()){
        cout << "Wrong file name!"<< endl;
        exit(1);
    }

    int layercount;
    fs >> layercount;
    cout << layercount << endl;
    layers.resize(layercount);
    for(int i=0;i<int(layers.size());i++){
        char material;
        double size;
        fs >> material >> size;
        cout << material << " " << size << endl;
        if (size>0)
        {
            switch(material){
                case 'x' :
                    layers[i] = new Oxygen(size);
                    break;
                case 'z' :
                    layers[i] = new Ozone(size);
                    break;
                case 's' :
                    layers[i] = new CarbonDioxide(size);
                    break;
            }
        }
    }

    string weatherline;
    fs >> weatherline;
    cout << weatherline << endl;
    weather.resize(weatherline.size());
    for(int i=0;i<int(weatherline.size());i++){
        switch(weatherline[i]){
            case 'z' :
                weather[i] = Rainy::instance();
                break;
            case 'n' :
                weather[i] = Sunny::instance();
                break;
            case 'm' :
                weather[i] = Other::instance();
                break;
        }
    }
}

bool search(Layer* l, vector<Layer*> layers, int startind, int &endind){
    bool x = false;
    int j=startind+1;
    while (!x && j<int(layers.size())){
        bool ox = l->isOxygen() && layers[j]->isOxygen();
        bool oz = l->isOzone() && layers[j]->isOzone();
        bool cd = l->isCarbonDioxide() && layers[j]->isCarbonDioxide();
        if(ox || oz || cd){
            x = true;
            endind = j;
        }
        j++; 
    }
    return x;
}

bool testlayers(vector<Layer*> &layers){
    for(int i=0;i<int(layers.size());i++){
        if (layers[i]->getSize()<0.5){
            cerr << "Problem in input file" << endl;
            return false;
        } 
    }
    return true;
}

void round(Weather* weather, vector<Layer*> &layers){
    //double sum = 0;
    for(int i=0;i<int(layers.size());){
        Layer* l = nullptr;

        // Ha változik a réteg
        if (layers[i]->change(weather,l)){
            int endind = -1;
            // Lebegtessük föl a képzett értéket
            if (search(l,layers,i,endind)){
                // Ha van fölötte ugyan olyan réteg, akkor adjuk hozzá
                layers[endind]->add(l);
                l = nullptr;
            } else if(l->getSize()>0.5) {
                // Ha nincs, akkor képezzünk új réteget, ha nagyobb, mint 0.5
                layers.push_back(l);
            }

            // Ha a maradék kisebb, mint 0.5, akkor lebegtessük fel vagy töröljük
            if (layers[i]->getSize()<0.5 && search(layers[i],layers,i,endind)){
                l = layers[i];
                layers.erase(layers.begin()+i);
                layers[endind]->add(l);
            } else if(layers[i]->getSize()<0.5 && !search(layers[i],layers,i,endind)){
                layers.erase(layers.begin()+i);
            } else {
                i++;
            }
        } else {
            i++;
        }

    }

    for(int i=0;i<int(layers.size());i++){
        // Kiírás
        if(layers[i]->isOxygen()){
            cout << "Oxygen: " << layers[i]->getSize() << endl;
        } else if(layers[i]->isOzone()){
            cout << "Ozone: " << layers[i]->getSize() << endl;
        } else if(layers[i]->isCarbonDioxide()){
            cout << "CarbonDioxide: " << layers[i]->getSize() << endl;
        } else {
            cout << "Nullpointer" << endl;
        }
        //sum += layers[i]->getSize();
    }
    //cout << sum << endl;  
}

int simulate(vector<Layer*> layers, const vector<Weather*> weather){
    int startcount = int(weather.size());
    int roundcount = 1;
    if(testlayers(layers)){
        while(int(layers.size())>=3 && int(layers.size()) < startcount*3){
            int weatherindex = (roundcount - 1)  % startcount;

            cout << endl;
            cout << "---------------------------------" << endl;
            cout << "       "<< roundcount << ". simulation round" << endl;
            cout << "             "<< weather[weatherindex]->getType() << endl;
            cout << "---------------------------------" << endl;

            round(weather[weatherindex], layers);

            roundcount++;
        }
    }
    return roundcount-1;
}

template <typename Item>
void clear(vector<Item*> &vec)
{
    for(int i = 0; i < int(vec.size()); ++i){
        delete vec[i];
    }
}

void clearWeather(){
    Rainy::destroy();
    Sunny::destroy();
    Other::destroy();
}

#define NORMAL_MODE
#ifdef NORMAL_MODE
int main(){
    vector<Layer*> layers;
    vector<Weather*> weather;

    string fn;
    cout << "Enter file name: ";
    cin >> fn;

    // Read data from file
    create(fn, layers, weather);

    // Start simulation
    simulate(layers, weather);


    // Clear pointers
    clear(layers);
    clearWeather();

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("no input layer", "input01.txt"){
    vector<Layer*> layers;
    vector<Weather*> weather;

    create("input01.txt",layers,weather);
    CHECK(simulate(layers,weather)==0);

    clear(layers);
    clearWeather();
}

TEST_CASE("no input weather", "input02.txt"){
    vector<Layer*> layers;
    vector<Weather*> weather;

    create("input02.txt",layers,weather);
    CHECK(simulate(layers,weather)==0);

    clear(layers);
    clearWeather();
}
TEST_CASE("no input weather and layer", "input03.txt"){
    vector<Layer*> layers;
    vector<Weather*> weather;

    create("input03.txt",layers,weather);
    CHECK(simulate(layers,weather)==0);

    clear(layers);
    clearWeather();
}
TEST_CASE("empty file", "input04.txt"){
    vector<Layer*> layers;
    vector<Weather*> weather;

    create("input04.txt",layers,weather);
    CHECK(simulate(layers,weather)==0);

    clear(layers);
    clearWeather();
}
TEST_CASE("less than 3 layer", "input05.txt"){
    vector<Layer*> layers;
    vector<Weather*> weather;

    create("input05.txt",layers,weather);
    CHECK(simulate(layers,weather)==0);

    clear(layers);
    clearWeather();
}
TEST_CASE("a layer has less than 0.5", "input06.txt"){
    vector<Layer*> layers;
    vector<Weather*> weather;

    create("input06.txt",layers,weather);
    CHECK(simulate(layers,weather)==0);

    clear(layers);
    clearWeather();
}
TEST_CASE("input file as inten","input07.txt"){
    vector<Layer*> layers;
    vector<Weather*> weather;

    create("input07.txt",layers,weather);
    CHECK(simulate(layers,weather)==80);

    clear(layers);
    clearWeather();
}
#endif