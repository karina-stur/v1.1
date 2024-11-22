#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

class Studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> namuDarbai;
    int egzaminas;

public:
    Studentas() : vardas(""), pavarde(""), egzaminas(0) {}

    Studentas(const std::string& v, const std::string& p, const std::vector<int>& nd, int egz)
        : vardas(v), pavarde(p), namuDarbai(nd), egzaminas(egz) {}

    void setVardas(const std::string& v) { vardas = v; }
    std::string getVardas() const { return vardas; }

    void setPavarde(const std::string& p) { pavarde = p; }
    std::string getPavarde() const { return pavarde; }

    void setNamuDarbai(const std::vector<int>& nd) { namuDarbai = nd; }
    std::vector<int> getNamuDarbai() const { return namuDarbai; }

    void addNamuDarbai(int pazymys) { namuDarbai.push_back(pazymys); }

    void setEgzaminas(int eg) { egzaminas = eg; }
    int getEgzaminas() const { return egzaminas; }

    double skaiciuotiGalutiniVidurki() const {
        double total = std::accumulate(namuDarbai.begin(), namuDarbai.end(), 0);
        return (total + egzaminas) / (namuDarbai.size() + 1);
    }

    double skaiciuotiGalutiniMediana() const {
        std::vector<int> sortedNamuDarbai = namuDarbai;
        std::sort(sortedNamuDarbai.begin(), sortedNamuDarbai.end());

        if (sortedNamuDarbai.size() % 2 == 0) {
            return (sortedNamuDarbai[sortedNamuDarbai.size() / 2 - 1] + sortedNamuDarbai[sortedNamuDarbai.size() / 2]) / 2.0;
        }
        else {
            return sortedNamuDarbai[sortedNamuDarbai.size() / 2];
        }
    }
};

#endif // STUDENTAS_H
