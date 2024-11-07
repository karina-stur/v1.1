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
#include <chrono>
#include <limits>
#include "studentas.h"

int readInteger();
void generuotiStudentuFailus();
void generuotiPazymius(Studentas& studentas, int namuDarbuKiekis);

void nuskaitytiStudentus(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);
void nuskaitytiStudentus(const std::string& failoPavadinimas, std::list<Studentas>& studentai);

void strategija1(std::vector<Studentas>& studentai, bool pagalVidurki);
void strategija1(std::list<Studentas>& studentai, bool pagalVidurki);

void strategija2(std::vector<Studentas>& studentai, bool pagalVidurki);
void strategija2(std::list<Studentas>& studentai, bool pagalVidurki);

void isaugotiStudentuGrupe(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas, bool pagalVidurki);
void isaugotiStudentuGrupe(const std::list<Studentas>& studentai, const std::string& failoPavadinimas, bool pagalVidurki);

void ivestiStudentuDuomenis(std::vector<Studentas>& studentaiVektorius);
void ivestiStudentuDuomenis(std::list<Studentas>& studentaiSarasas);

void testKonteinerius(const std::vector<Studentas>& studentaiVektorius, bool pagalVidurki,
    double& totalPartitionTimeVec, double& totalNuskriaustukaiSaveTimeVec, double& totalKietiakaiSaveTimeVec,
    void (*strategija)(std::vector<Studentas>&, bool));

void testKonteinerius(const std::list<Studentas>& studentaiSarasas, bool pagalVidurki,
    double& totalPartitionTimeList, double& totalNuskriaustukaiSaveTimeList, double& totalKietiakaiSaveTimeList,
    void (*strategija)(std::list<Studentas>&, bool));

#endif // FUNKCIJOS_H

