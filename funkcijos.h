#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>
#include <chrono>
#include <limits>
#include "studentas.h"

int readInteger();
void generuotiStudentuFailus();
void generuotiPazymius(Studentas& studentas, int namuDarbuKiekis);

void nuskaitytiStudentus(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);
void nuskaitytiStudentus(const std::string& failoPavadinimas, std::list<Studentas>& studentai);

void strategija1(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);
void strategija1(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

void strategija2(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);
void strategija2(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

void strategija3(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);
void strategija3(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

void isaugotiStudentuGrupe(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas, bool pagalVidurki);
void isaugotiStudentuGrupe(const std::list<Studentas>& studentai, const std::string& failoPavadinimas, bool pagalVidurki);

void ivestiStudentuDuomenis(std::vector<Studentas>& studentaiVektorius);
void ivestiStudentuDuomenis(std::list<Studentas>& studentaiSarasas);

void testKonteinerius(const std::vector<Studentas>& studentaiVektorius, bool pagalVidurki,
    double& totalPartitionTimeVec, double& totalNuskriaustukaiSaveTimeVec, double& totalKietiakaiSaveTimeVec,
    void (*strategija)(std::vector<Studentas>&, bool, std::vector<Studentas>&, std::vector<Studentas>&));

void testKonteinerius(const std::list<Studentas>& studentaiLista, bool pagalVidurki,
    double& totalPartitionTimeList, double& totalNuskriaustukaiSaveTimeList, double& totalKietiakaiSaveTimeList,
    void (*strategija)(std::list<Studentas>&, bool, std::list<Studentas>&, std::list<Studentas>&));

#endif // FUNKCIJOS_H
