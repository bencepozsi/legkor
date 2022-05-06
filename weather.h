#pragma once
#include <string>

class Layer;
class Ozone;
class Oxygen;
class CarbonDioxide;

class Weather{
    public:
        Weather(){}
        virtual bool change(Ozone* m, Layer* &p) = 0;
        virtual bool change(Oxygen* m, Layer* &p) = 0;
        virtual bool change(CarbonDioxide* m, Layer* &p) = 0;
        virtual std::string getType() = 0;
        virtual ~Weather(){}
};

class Rainy: public Weather{
    private:
        static Rainy* _instance;
    public:
        static Rainy* instance();
        static void destroy();
        bool change(Ozone* m, Layer* &p) override;
        bool change(Oxygen* m, Layer* &p) override;
        bool change(CarbonDioxide* m, Layer* &p) override;
        std::string getType() override{
            return "Rainy";
        }
};

class Sunny: public Weather{
    private:
        static Sunny* _instance;
    public:
        static Sunny* instance();
        static void destroy();
        bool change(Ozone* m, Layer* &p) override;
        bool change(Oxygen* m, Layer* &p) override;
        bool change(CarbonDioxide* m, Layer* &p) override;
        std::string getType() override {
            return "Sunny";
        }
};

class Other: public Weather{
    private:
        static Other* _instance;
    public:
        static Other* instance();
        static void destroy();
        bool change(Ozone* m, Layer* &p) override;
        bool change(Oxygen* m, Layer* &p) override;
        bool change(CarbonDioxide* m, Layer* &p) override;
        std::string getType(){
            return "Other";
        }
};