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

/**
 * @brief Pirmoji strategija studentu rusiavimui (naudoja vektorius)
 *
 * Funkcija, atliekanti pirma strategija studentu padalinimui i dvi grupes (vargsiukai ir kietekai) pagal pasirinktus kriterijus.
 *
 * @param studentai Studentai, kurie bus apdoroti
 * @param pagalVidurki Nustato, ar rusiavimas bus pagal vidurki
 * @param vargsiukai Grupes, kuriuose bus issaugoti vargsesni studentai
 * @param kietekai Grupes, kuriuose bus issaugoti geresni studentai
 */
void strategija1(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);

/**
 * @brief Pirmoji strategija studentu rusiavimui (naudoja sarasa)
 *
 * Funkcija, atliekanti pirma strategija studentu padalinimui i dvi grupes (vargsiukai ir kietekai) pagal pasirinktus kriterijus.
 *
 * @param studentai Studentai, kurie bus apdoroti
 * @param pagalVidurki Nustato, ar rusiavimas bus pagal vidurki
 * @param vargsiukai Grupes, kuriuose bus issaugoti vargsesni studentai
 * @param kietekai Grupes, kuriuose bus issaugoti geresni studentai
 */
void strategija1(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

/**
 * @brief Antroji strategija studentu rusiavimui (naudoja vektorius)
 *
 * Funkcija, atliekanti antraja strategija studentu padalinimui i dvi grupes (vargsiukai ir kietekai) pagal pasirinktus kriterijus.
 *
 * @param studentai Studentai, kurie bus apdoroti
 * @param pagalVidurki Nustato, ar rusiavimas bus pagal vidurki
 * @param vargsiukai Grupes, kuriuose bus issaugoti vargsesni studentai
 * @param kietekai Grupes, kuriuose bus issaugoti geresni studentai
 */
void strategija2(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);

/**
 * @brief Antroji strategija studentu rusiavimui (naudoja sarasa)
 *
 * Funkcija, atliekanti antraja strategija studentu padalinimui i dvi grupes (vargsiukai ir kietekai) pagal pasirinktus kriterijus.
 *
 * @param studentai Studentai, kurie bus apdoroti
 * @param pagalVidurki Nustato, ar rusiavimas bus pagal vidurki
 * @param vargsiukai Grupes, kuriuose bus issaugoti vargsesni studentai
 * @param kietekai Grupes, kuriuose bus issaugoti geresni studentai
 */
void strategija2(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

/**
 * @brief Trecioji strategija studentu rusiavimui (naudoja vektorius)
 *
 * Funkcija, atliekanti treciaja strategija studentu padalinimui i dvi grupes (vargsiukai ir kietekai) pagal pasirinktus kriterijus.
 *
 * @param studentai Studentai, kurie bus apdoroti
 * @param pagalVidurki Nustato, ar rusiavimas bus pagal vidurki
 * @param vargsiukai Grupes, kuriuose bus issaugoti vargsesni studentai
 * @param kietekai Grupes, kuriuose bus issaugoti geresni studentai
 */
void strategija3(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai);

/**
 * @brief Trecioji strategija studentu rusiavimui (naudoja sarasus)
 *
 * Funkcija, atliekanti treciaja strategija studentu padalinimui i dvi grupes (vargsiukai ir kietekai) pagal pasirinktus kriterijus.
 *
 * @param studentai Studentai, kurie bus apdoroti
 * @param pagalVidurki Nustato, ar rusiavimas bus pagal vidurki
 * @param vargsiukai Grupes, kuriuose bus issaugoti vargsesni studentai
 * @param kietekai Grupes, kuriuose bus issaugoti geresni studentai
 */
void strategija3(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai);

/**
 * @brief Isaugoti studentu grupe i faila (naudojant vektorius)
 *
 * Funkcija isaugoti studentu grupe i faila naudojant vektorius.
 *
 * @param studentai Studentai, kuriuos norima issaugoti
 */
void isaugotiStudentuGrupe(const std::vector<Studentas>& studentai);

/**
 * @brief Isaugoti studentu grupe i faila (naudojant sarasus)
 *
 * Funkcija isaugoti studentu grupe i faila naudojant sarasus.
 *
 * @param studentai Studentai, kuriuos norima issaugoti
 */
void isaugotiStudentuGrupe(const std::list<Studentas>& studentai);

/**
 * @brief Ivesti studentu duomenis i vektoriu
 *
 * Funkcija leidzia ivesti studentu duomenis ir issaugoti juos vektoriuje.
 *
 * @param studentaiVektorius Vektorius, kuriame bus issaugoti studentu duomenys
 */
void ivestiStudentuDuomenis(std::vector<Studentas>& studentaiVektorius);

/**
 * @brief Ivesti studentu duomenis i sarasa
 *
 * Funkcija leidzia ivesti studentu duomenis ir issaugoti juos sarase.
 *
 * @param studentaiSarasas Sarasas, kuriame bus issaugoti studentu duomenys
 */
void ivestiStudentuDuomenis(std::list<Studentas>& studentaiSarasas);

/**
 * @brief Testuoti konteinerius su duomenimis
 *
 * Funkcija atlieka konteineriu testavimus su studentu duomenimis naudojant pasirinktus rusiavimo metodus.
 *
 * @param studentaiVektorius Studentai, kurie bus naudojami testavimui
 * @param pagalVidurki Nustato, ar rusiavimas bus pagal vidurki
 * @param totalPartitionTimeVec Laikas partition funkcijai
 * @param totalNuskriaustukaiSaveTimeVec Laikas isaugoti vargsesnius studentus
 * @param totalKietiakaiSaveTimeVec Laikas isaugoti kietesnius studentus
 * @param strategija Funkcija, kuri apdoroja studentus pagal pasirinkta strategija
 */
void testKonteinerius(const std::vector<Studentas>& studentaiVektorius, bool pagalVidurki,
    double& totalPartitionTimeVec, double& totalNuskriaustukaiSaveTimeVec, double& totalKietiakaiSaveTimeVec,
    void (*strategija)(std::vector<Studentas>&, bool, std::vector<Studentas>&, std::vector<Studentas>&));

/**
 * @brief Testuoti konteinerius su duomenimis
 *
 * Funkcija atlieka konteineriu testavimus su studentu duomenimis naudojant pasirinktus rusiavimo metodus.
 *
 * @param studentaiList Studentai, kurie bus naudojami testavimui
 * @param pagalVidurki Nustato, ar rusiavimas bus pagal vidurki
 * @param totalPartitionTimeList Laikas partition funkcijai
 * @param totalNuskriaustukaiSaveTimeList Laikas isaugoti vargsesnius studentus
 * @param totalKietiakaiSaveTimeList Laikas isaugoti kietesnius studentus
 * @param strategija Funkcija, kuri apdoroja studentus pagal pasirinkta strategija
 */
void testKonteinerius(const std::list<Studentas>& studentaiList, bool pagalVidurki,
    double& totalPartitionTimeList, double& totalNuskriaustukaiSaveTimeList, double& totalKietiakaiSaveTimeList,
    void (*strategija)(std::list<Studentas>&, bool, std::list<Studentas>&, std::list<Studentas>&));

/**
 * @brief Triju metodu testavimas
 *
 * Funkcija atlieka triju metodu testavimus.
 */
void trysMetodai();

#endif // FUNKCIJOS_H
