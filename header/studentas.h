#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>

class Studentas : public Zmogus {
private:
    std::vector<int> namuDarbai;
    int egzaminas;

public:
    Studentas() : Zmogus(), egzaminas(0) {}
    Studentas(const std::string& v, const std::string& p, const std::vector<int>& nd, int egz)
        : Zmogus(v, p), namuDarbai(nd), egzaminas(egz) {}

    Studentas(const Studentas& other)
        : Zmogus(other.vardas, other.pavarde), namuDarbai(other.namuDarbai), egzaminas(other.egzaminas) {}

    ~Studentas() {}

    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas = other.vardas;
            pavarde = other.pavarde;
            namuDarbai = other.namuDarbai;
            egzaminas = other.egzaminas;
        }
        return *this;
    }

    void setNamuDarbai(const std::vector<int>& nd) {
        namuDarbai = nd;
    }

    void addNamuDarbai(int pazymys) {
        namuDarbai.push_back(pazymys);
    }

    friend std::istream& operator>>(std::istream& is, Studentas& studentas) {
        std::cout << "Iveskite studento varda: ";
        std::getline(is >> std::ws, studentas.vardas);

        std::cout << "Iveskite studento pavarde: ";
        std::getline(is >> std::ws, studentas.pavarde);

        std::cout << "Norite:\n";
        std::cout << "1 - Ivesti namu darbu pazymius ranka\n";
        std::cout << "2 - Sugeneruoti pazymius atsitiktinai\n";
        int pasirinkimas;
        do {
            std::cout << "Pasirinkimas (1 arba 2): ";
            is >> pasirinkimas;
            if (pasirinkimas != 1 && pasirinkimas != 2) {
                std::cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
            }
        } while (pasirinkimas != 1 && pasirinkimas != 2);

        if (pasirinkimas == 1) {
            studentas.namuDarbai.clear();
            std::cout << "Iveskite namu darbu pazymius (iveskite 0, kai baigsite):\n";
            int pazymys;
            while (true) {
                std::cout << "Pazymys: ";
                is >> pazymys;
                if (pazymys == 0) break;
                if (pazymys < 1 || pazymys > 10) {
                    std::cout << "Iveskite pazymi nuo 1 iki 10.\n";
                    continue;
                }
                studentas.namuDarbai.push_back(pazymys);
            }
        }
        else if (pasirinkimas == 2) {
            std::cout << "Kiek namu darbu pazymiu sugeneruoti? ";
            int kiek;
            is >> kiek;
            studentas.generuotiPazymius(kiek);
        }

        std::cout << "Iveskite egzamino pazymi: ";
        is >> studentas.egzaminas;

        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return is;
    }

    friend std::ostream& operator<<(std::ostream& out, const Studentas& s) {
        out << std::left << std::setw(20) << s.vardas
            << std::setw(20) << s.pavarde
            << std::setw(20) << std::fixed << std::setprecision(2) << s.skaiciuotiGalutiniVidurki()
            << std::fixed << std::setprecision(2) << s.skaiciuotiGalutiniMediana() << std::endl;
        return out;
    }

    void generuotiPazymius(int kiek) {
        namuDarbai.clear();
        for (int i = 0; i < kiek; ++i) {
            namuDarbai.push_back(1 + rand() % 10);
        }
    }

    double skaiciuotiGalutiniVidurki() const {
        if (namuDarbai.empty()) return egzaminas;
        double total = std::accumulate(namuDarbai.begin(), namuDarbai.end(), 0);
        return (total + egzaminas) / (namuDarbai.size() + 1);
    }

    double skaiciuotiGalutiniMediana() const {
        if (namuDarbai.empty()) return egzaminas;
        std::vector<int> sortedNamuDarbai = namuDarbai;
        std::sort(sortedNamuDarbai.begin(), sortedNamuDarbai.end());
        size_t size = sortedNamuDarbai.size();
        return (size % 2 == 0) ?
            (sortedNamuDarbai[size / 2 - 1] + sortedNamuDarbai[size / 2]) / 2.0
            : sortedNamuDarbai[size / 2];
    }

    virtual void printInfo() const override {
        std::cout << *this;
    }
};

#endif // STUDENTAS_H
