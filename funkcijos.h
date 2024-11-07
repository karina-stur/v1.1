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
#include <chrono>
#include <limits>
#include "studentas.h"

void generuotiStudentuFailus();
void generuotiPazymius(Studentas& studentas, int namuDarbuKiekis);
void nuskaitytiStudentus(const std::string& failoPavadinimas, std::vector<Studentas>& studentai);
void nuskaitytiStudentus(const std::string& failoPavadinimas, std::list<Studentas>& studentai);
void grupuotiIrIssaugotiStudentus(std::vector<Studentas>& studentai, bool pagalVidurki);
void grupuotiIrIssaugotiStudentus(std::list<Studentas>& studentai, bool pagalVidurki);
void isaugotiStudentuGrupe(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas, bool pagalVidurki);
void isaugotiStudentuGrupe(const std::list<Studentas>& studentai, const std::string& failoPavadinimas, bool pagalVidurki);
void ivestiStudentuDuomenis(std::vector<Studentas>& studentaiVektorius, std::list<Studentas>& studentaiSarasas);
int readInteger();

void testKonteinerius(const std::vector<Studentas>& studentaiVektorius, const std::list<Studentas>& studentaiSarasas, bool pagalVidurki,
    double& totalPartitionTimeVec, double& totalNuskriaustukaiSaveTimeVec, double& totalKietiakaiSaveTimeVec, double& readingTimeVec,
    double& totalReadingTimeList, double& totalPartitionTimeList, double& totalNuskriaustukaiSaveTimeList, double& totalKietiakaiSaveTimeList);

#endif // FUNKCIJOS_H
