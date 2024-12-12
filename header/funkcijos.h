/**
 * @file Funkcijos.h
 * @brief Apraso naudojamas funkcijas.
 *
 * Siame faile pateikiamos funkcijos.
 */
#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <chrono>
#include <limits>

class Studentas;

/**
 * @brief Nuskaityti sveika skaiciu nuo vartotojo
 *
 * Funkcija atlieka sveiko skaiciaus nuskaityma is vartotojo.
 *
 * @return Nuskaitytas sveikas skaicius
 */
int readInteger();

/**
 * @brief Generuoti studentu failus
 *
 * Funkcija generuoja studentu duomenis ir isaugo juos failuose.
 */
void generuotiStudentuFailus();

/**
 * @brief Generuoti pazymius studentui
 *
 * Funkcija sugeneruoja atsitiktinius pazymius studentui.
 *
 * @param studentas Studentas, kuriam bus sugeneruoti pazymiai
 * @param namuDarbuKiekis Namu darbu kiekis, kuriems bus sugeneruoti pazymiai
 */
void generuotiPazymius(Studentas& studentas, int namuDarbuKiekis);

/**
 * @brief Nuskaityti studentus is failo i vektoriu
 *
 * Funkcija nuskaityti studentu duomenis is failo ir juos issaugoti vektoriuje.
 *
 * @param failoPavadinimas Failo pavadinimas is kurio bus nuskaityti studentai
 * @param studentai Vektorius, kuriame bus issaugoti studentai
 */
void nuskaitytiStudentus(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);

/**
 * @brief Nuskaityti studentus is failo i sarasa
 *
 * Funkcija nuskaityti studentu duomenis is failo ir juos issaugoti sarase.
 *
 * @param failoPavadinimas Failo pavadinimas is kurio bus nuskaityti studentai
 * @param studentai Sarasas, kuriame bus issaugoti studentai
 */
void nuskaitytiStudentus(const std::string& failoPavadinimas, std::list<Studentas>& studentai);

void strategija1( std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);
void strategija1(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

void strategija2(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);
void strategija2(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

void strategija3(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);
void strategija3(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

void isaugotiStudentuGrupe(const std::vector<Studentas>& studentai);
void isaugotiStudentuGrupe(const std::list<Studentas>& studentai);

void ivestiStudentuDuomenis(std::vector<Studentas>& studentaiVektorius);
void ivestiStudentuDuomenis(std::list<Studentas>& studentaiSarasas);

void testKonteinerius(const std::vector<Studentas>& studentaiVektorius, bool pagalVidurki,
    double& totalPartitionTimeVec, double& totalNuskriaustukaiSaveTimeVec, double& totalKietiakaiSaveTimeVec,
    void (*strategija)(std::vector<Studentas>&, bool, std::vector<Studentas>&, std::vector<Studentas>&));

void testKonteinerius(const std::list<Studentas>& studentaiList, bool pagalVidurki,
    double& totalPartitionTimeList, double& totalNuskriaustukaiSaveTimeList, double& totalKietiakaiSaveTimeList,
    void (*strategija)(std::list<Studentas>&, bool, std::list<Studentas>&, std::list<Studentas>&));

void trysMetodai();

#endif // FUNKCIJOS_H
