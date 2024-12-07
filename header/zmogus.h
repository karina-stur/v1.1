#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

class Zmogus {
protected:
    std::string vardas;
    std::string pavarde;

public:
    Zmogus() : vardas(""), pavarde("") {}
    Zmogus(const std::string& v, const std::string& p) : vardas(v), pavarde(p) {}
    virtual ~Zmogus() {}

    virtual std::string getVardas() const { return vardas; }
    virtual void setVardas(const std::string& v) { vardas = v; }

    virtual std::string getPavarde() const { return pavarde; }
    virtual void setPavarde(const std::string& p) { pavarde = p; }

    virtual void printInfo() const = 0;
};

#endif // ZMOGUS_H
