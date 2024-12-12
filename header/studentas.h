/**
 * @file Studentas.h
 * @brief Apraso isvestine klase `Studentas`.
 *
 * Siame faile pateikiama `Studentas` klase, paveldeta is `Zmogus`. Ji apraso
 * studento duomenis, iskaitant namu darbus ir egzamino rezultatus.
 */

#ifndef STUDENTAS_H
#define STUDENTAS_H

#include "zmogus.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iomanip>

 /**
  * @class Studentas
  * @brief Klase studentui aprasyti.
  *
  * `Studentas` yra isvestine klase is `Zmogus`. Ji prideda savybes ir metodus,
  * skirtus dirbti su studento namu darbu rezultatais ir egzamino pazymiu.
  */
class Studentas : public Zmogus {
private:
    std::vector<int> namuDarbai; ///< Studento namu darbu pazymiai.
    int egzaminas; ///< Studento egzamino pazymys.

public:
    /**
     * @brief Numatytojo konstruktoriaus deklaracija.
     *
     * Inicializuoja varda, pavarde kaip tuscias eilutes ir egzamino pazymi kaip 0.
     */
    Studentas() : Zmogus(), egzaminas(0) {}

    /**
     * @brief Konstruktorius su parametrais.
     * @param v Vardas.
     * @param p Pavarde.
     * @param nd Namu darbu pazymiai.
     * @param egz Egzamino pazymys.
     */
    Studentas(const std::string& v, const std::string& p, const std::vector<int>& nd, int egz)
        : Zmogus(v, p), namuDarbai(nd), egzaminas(egz) {}

    /**
     * @brief Kopijavimo konstruktorius.
     * @param other Kitas `Studentas` objektas, kuris bus nukopijuotas.
     */
    Studentas(const Studentas& other)
        : Zmogus(other.vardas, other.pavarde), namuDarbai(other.namuDarbai), egzaminas(other.egzaminas) {}

    /**
     * @brief Destruktorius.
     */
    ~Studentas() {}

    /**
     * @brief Priskyrimo operatorius.
     * @param other Kitas `Studentas` objektas, kuris bus priskirtas.
     * @return Nuoroda i priskirta objekta.
     */
    Studentas& operator=(const Studentas& other) {
        if (this != &other) {
            vardas = other.vardas;
            pavarde = other.pavarde;
            namuDarbai = other.namuDarbai;
            egzaminas = other.egzaminas;
        }
        return *this;
    }

    /**
     * @brief Nustato studento namu darbu pazymius.
     * @param nd Nauji namu darbu pazymiai.
     */
    void setNamuDarbai(const std::vector<int>& nd) {
        namuDarbai = nd;
    }

    /**
     * @brief Prideda viena namu darbu pazymi.
     * @param pazymys Naujas pazymys.
     */
    void addNamuDarbai(int pazymys) {
        namuDarbai.push_back(pazymys);
    }

    /**
     * @brief Sugeneruoja atsitiktinius namu darbu pazymius.
     * @param kiek Kiek pazymiu sugeneruoti.
     */
    void generuotiPazymius(int kiek) {
        namuDarbai.clear();
        for (int i = 0; i < kiek; ++i) {
            namuDarbai.push_back(1 + rand() % 10);
        }
    }

    /**
     * @brief Skaiciuoja galutini ivertinima kaip vidurki.
     * @return Galutinis ivertinimas.
     */
    double skaiciuotiGalutiniVidurki() const {
        if (namuDarbai.empty()) return egzaminas;
        double total = std::accumulate(namuDarbai.begin(), namuDarbai.end(), 0);
        return (total + egzaminas) / (namuDarbai.size() + 1);
    }

    /**
     * @brief Skaiciuoja galutini ivertinima kaip mediana.
     * @return Galutinis ivertinimas.
     */
    double skaiciuotiGalutiniMediana() const {
        if (namuDarbai.empty()) return egzaminas;
        std::vector<int> sortedNamuDarbai = namuDarbai;
        std::sort(sortedNamuDarbai.begin(), sortedNamuDarbai.end());
        size_t size = sortedNamuDarbai.size();
        return (size % 2 == 0) ?
            (sortedNamuDarbai[size / 2 - 1] + sortedNamuDarbai[size / 2]) / 2.0
            : sortedNamuDarbai[size / 2];
    }

    /**
     * @brief Isveda studento informacija i srauta.
     * @param out Isvedimo srautas.
     * @param s Studento objektas.
     * @return Atnaujintas isvedimo srautas.
     */
    friend std::ostream& operator<<(std::ostream& out, const Studentas& s) {
        out << std::left << std::setw(20) << s.vardas
            << std::setw(20) << s.pavarde
            << std::setw(20) << std::fixed << std::setprecision(2) << s.skaiciuotiGalutiniVidurki()
            << std::fixed << std::setprecision(2) << s.skaiciuotiGalutiniMediana() << std::endl;
        return out;
    }

    /**
     * @brief Nuskaitymo operatorius.
     * @param is Nuskaitymo srautas.
     * @param studentas Studento objektas.
     * @return Atnaujintas nuskaitymo srautas.
     *
     * Nuskaitymo operatorius, skirtas isvedimui.
     * Leidžia vartotojui įvesti studento varda, pavarde,
     * namu darbu pazymius arba generuoti juos atsitiktinai ir
     * ivesti egzamino pazymi.
     */
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

    /**
     * @brief Isveda studento informacija.
     */
    virtual void printInfo() const override {
        std::cout << *this;
    }
};

#endif // STUDENTAS_H
