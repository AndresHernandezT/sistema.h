#ifndef SISTEMA_H_
#define SISTEMA_H_ 
#include <cassert>

class Bus {
protected:
    std::vector<std::string> asientos_;
    std::string tipo_;
    std::string origen_;
    std::string destino_;
    int precio_;
    int hora_;
public:
    Bus(std::string tipo, size_t asientos, std::string origen, std::string destino, int precio, int hora) {
        for (unsigned int i = 0; i < asientos; i++)
        {
            asientos_.push_back("");
        }
        tipo_ = tipo;
        origen_ = origen;
        destino_ = destino;
        precio_ = precio;
        hora_ = hora;
    }

    void listarAsientos() {
        std::cout << "Asientos disponibles: ";
        for (unsigned int i = 0; i < asientos_.size(); i++)
        {  
            if(asientos_[i].size() == 0) 
            {
                std::cout << i+1 << " ";
            }
        }
        std::cout << std::endl;

        std::cout << "Asientos vendidos: ";
        for (unsigned int i = 0; i < asientos_.size(); i++)
        {
            if(asientos_[i].size() != 0)
            {
                std::cout << i+1 << ": " << asientos_[i] << std::endl;
            }
        }
        std::cout << std::endl;
    }

    bool venderAsiento(int asiento, std::string rut) {
        if(asientos_[asiento-1].size() == 0) {
            asientos_[asiento-1] = rut;
            return true;
        }
        return false;
    }

    void info() {
        std::cout << origen_ << "\t" << destino_ << "\t" << tipo_ << "\t" << hora_;
    }

    int get_hora(){
        return hora_;
    }
    
    void setPrecio(int n){
    	precio_ = n;
	}

    virtual int get_tipo(){
        if(tipo_ == "Semi-cama") return 0;
        if(tipo_ == "Salon-cama") return 1;
        if(tipo_ == "Premium") return 2;
        return -1;
    }

};

class Semi_cama: public Bus{
public:
    Semi_cama(std::string origen, std::string destino, int hora): Bus("Semi-cama", 45, origen, destino, 0, hora) {
        assert(origen != destino);
        setPrecio(dinero(origen, destino));
    }
    int get_tipo(){
        return 0;
    }
private:
    int dinero(std::string origen, std::string destino){
        int precios[4][4];
        precios[0][1] = 4000;
        precios[0][2] = 2000;
        precios[0][3] = 7000;
        precios[1][0] = 4000;
        precios[1][2] = 6000;
        precios[1][3] = 9000;
        precios[2][0] = 2000;
        precios[2][1] = 6000;
        precios[2][3] = 5000;
        precios[3][0] = 7000;
        precios[3][1] = 9000;
        precios[3][2] = 5000;
        int i, j;
        std::string lugares[] = {"Santiago", "Rancagua", "Valparaiso", "La Serena"};
        for(int k = 0; k < 4; k++){
            if(origen == lugares[k]) i = k;
            if(destino == lugares[k]) j = k;
        }
        return precios[i][j];
    }
};

class Salon_cama: public Bus{
public:
    Salon_cama(std::string origen, std::string destino, int hora): Bus("Salon-cama", 30, origen, destino, 0, hora){
        if(origen == destino) return;
        setPrecio(dinero(origen, destino));
    }
    int get_tipo(){
        return 1;
    }
private:
    int dinero(std::string origen, std::string destino){
        int precios[4][4];
        precios[0][1] = 8000;
        precios[0][2] = 4000;
        precios[0][3] = 10000;
        precios[1][0] = 8000;
        precios[1][2] = 8000;
        precios[1][3] = 14000;
        precios[2][0] = 4000;
        precios[2][1] = 8000;
        precios[2][3] = 8000;
        precios[3][0] = 10000;
        precios[3][1] = 14000;
        precios[3][2] = 8000;
        int i, j;
        std::string lugares[] = {"Santiago", "Rancagua", "Valparaiso", "La Serena"};
        for(int k = 0; k < 4; k++){
            if(origen == lugares[k]) i = k;
            if(destino == lugares[k]) j = k;
        }
        return precios[i][j];
    }
};

class Premium: public Bus{
public:
    Premium(std::string origen, std::string destino, int hora): Bus("Premium", 20, origen, destino, 0, hora){
        if(origen == destino) return;
        precio_ = dinero(origen, destino);
    }
    int get_tipo(){
        return 2;
    }
private:
    int dinero(std::string origen, std::string destino){
        int precios[4][4];
        precios[0][1] = 12000;
        precios[0][2] = 6000;
        precios[0][3] = 13000;
        precios[1][0] = 12000;
        precios[1][2] = 10000;
        precios[1][3] = 19000;
        precios[2][0] = 6000;
        precios[2][1] = 10000;
        precios[2][3] = 11000;
        precios[3][0] = 13000;
        precios[3][1] = 19000;
        precios[3][2] = 11000;
        int i, j;
        std::string lugares[] = {"Santiago", "Rancagua", "Valparaiso", "La Serena"};
        for(int k = 0; k < 4; k++){
            if(origen == lugares[k]) i = k;
            if(destino == lugares[k]) j = k;
        }
        return precios[i][j];
    }
};

class Sistema {
protected:
    std::vector<Bus> buses_;
    std::vector<int> est_h;
    std::vector<int> est_t;
public:
    Sistema(int buses) {
        buses_.reserve(buses);
        est_h.resize(24);
        est_t.resize(3);
    }
    
    void agendarBus(Bus bus) {
        buses_.push_back(bus);
    }
    
    void listarAgenda() {
        std::cout << "Selector\tOrigen\t\tDestino\t\tTipo\t\tHora" << std::endl;
        for (unsigned int i = 0; i < buses_.size(); i++)
        {
            std::cout << i+1 << "\t\t";
            buses_[i].info();
            std::cout << std::endl;
        }
    }
    
    void listarBus(int bus) {
        buses_[bus-1].listarAsientos();
    }
    
    bool venderPasaje(int bus, int asiento, std::string rut) {
        if (buses_[bus-1].venderAsiento(asiento, rut) == false) {
            std::cerr << "El asiento ya está vendido.\n";
            return false;
        }
        int h = buses_[bus-1].get_hora();
        int t = buses_[bus-1].get_tipo();
        est_h[h] += 1;
        est_t[t] += 1;
        return true;
    }

    void estadisticas(){
        int h = est_h[0], t = est_t[0];
        int hora = 0, tip = 0;
        std::vector<std::string> tipo = {"Semi-cama", "Salon-cama", "Premium"};
        for(int i = 1; i < 24; i++){
            if(est_h[i] > h) hora = i;
        }
        for(int i = 1; i < 3; i++){
            if(est_t[i] > t) tip = i;
        }
        std::cout << "Estadisticas:\nHora: " << hora << "\nTipo:" << tipo[tip];
    }
};

#endif
