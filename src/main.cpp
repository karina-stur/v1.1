#include "funkcijos.h"
#include "studentas.h"
#include <functional>
#include <iostream>
#include <chrono>
#include <vector>
#include <list>

int main() {
    char generateOption;
    std::cout << "Norite sugeneruoti studentu failus? (y/n): ";
    std::cin >> generateOption;
    std::cin.ignore();

    /**
     * @brief Tikrina, ar vartotojas nori sugeneruoti studentu failus.
     *
     * Jei vartotojas pasirenka "y" arba "Y", iskvieciama funkcija generuotiStudentuFailus.
     */
    if (generateOption == 'y' || generateOption == 'Y') {
        generuotiStudentuFailus();
    }

    std::cout << "Pasirinkite duomenu ivedimo buda:\n";
    std::cout << "1 - Ivesti duomenis ranka\n";
    std::cout << "2 - Nuskaityti duomenis is failo\n";
    int pasirinkimas = readInteger();

    std::cout << "Pasirinkite konteinerio tipa:\n";
    std::cout << "1 - Vector\n";
    std::cout << "2 - List\n";
    int containerChoice = readInteger();

    std::cout << "Pasirinkite strategija:\n";
    std::cout << "1 - Naudoti du konteinerius (vargsiukai ir kietekai)\n";
    std::cout << "2 - Naudoti viena konteineri (vargsiukai, o kietekai lieka pradiniame konteineryje)\n";
    std::cout << "3 - Naudoti patobulinta strategija nr.2\n";
    int strategija = readInteger();

    /**
     * @brief Pasirinkimas, jei vartotojas nusprendzia naudoti vector konteineri.
     *
     * Jei pasirenkamas vector konteineris, priklausomai nuo vartotojo pasirinkimo,
     * arba ivesti studentu duomenis ranka, arba nuskaityti juos is failo.
     * Po to pasirenkama ir pritaikoma norima strategija.
     */
    if (containerChoice == 1) {
        std::vector<Studentas> studentaiVektorius;

        if (pasirinkimas == 1) {
            ivestiStudentuDuomenis(studentaiVektorius);
        }
        else if (pasirinkimas == 2) {
            std::string failoPavadinimas;
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> failoPavadinimas;

            auto startReadingVec = std::chrono::high_resolution_clock::now();
            nuskaitytiStudentus(failoPavadinimas, studentaiVektorius);
            auto endReadingVec = std::chrono::high_resolution_clock::now();
            double readingTimeVec = std::chrono::duration<double>(endReadingVec - startReadingVec).count();
            std::cout << "Failo nuskaitymo laikas i Vector: " << readingTimeVec << " sekundes" << std::endl;
        }

        int kriterijus;
        std::cout << "Pasirinkite rusiavimo kriteriju (0 - mediana, 1 - vidurkis): ";
        kriterijus = readInteger();
        bool pagalVidurki = (kriterijus == 1);

        /**
         * @brief Pasirenkama ir pritaikoma strategija pagal vartotojo pasirinkima.
         *
         * Naudojama funkcija testKonteinerius, kad atlikti reikiamus veiksmus su vektoriu.
         */
        if (strategija == 1) {
            double totalPartitionTimeVec, totalNuskriaustukaiSaveTimeVec, totalKietiakaiSaveTimeVec;
            testKonteinerius(studentaiVektorius, pagalVidurki, totalPartitionTimeVec,
                totalNuskriaustukaiSaveTimeVec, totalKietiakaiSaveTimeVec, strategija1);
        }
        else if (strategija == 2) {
            double totalPartitionTimeVec, totalNuskriaustukaiSaveTimeVec, totalKietiakaiSaveTimeVec;
            testKonteinerius(studentaiVektorius, pagalVidurki, totalPartitionTimeVec,
                totalNuskriaustukaiSaveTimeVec, totalKietiakaiSaveTimeVec, strategija2);
        }
        else if (strategija == 3) {
            double totalPartitionTimeVec, totalNuskriaustukaiSaveTimeVec, totalKietiakaiSaveTimeVec;
            testKonteinerius(studentaiVektorius, pagalVidurki, totalPartitionTimeVec,
                totalNuskriaustukaiSaveTimeVec, totalKietiakaiSaveTimeVec, strategija3);
        }
    }
    /**
     * @brief Pasirinkimas, jei vartotojas nusprendzia naudoti list konteineri.
     *
     * Jei pasirenkamas list konteineris, priklausomai nuo vartotojo pasirinkimo,
     * arba ivesti studentu duomenis ranka, arba nuskaityti juos is failo.
     * Po to pasirenkama ir pritaikoma norima strategija.
     */
    else if (containerChoice == 2) {
        std::list<Studentas> studentaiSarasas;

        if (pasirinkimas == 1) {
            ivestiStudentuDuomenis(studentaiSarasas);
        }
        else if (pasirinkimas == 2) {
            std::string failoPavadinimas;
            std::cout << "Iveskite failo pavadinima: ";
            std::cin >> failoPavadinimas;

            auto startReadingList = std::chrono::high_resolution_clock::now();
            nuskaitytiStudentus(failoPavadinimas, studentaiSarasas);
            auto endReadingList = std::chrono::high_resolution_clock::now();
            double readingTimeList = std::chrono::duration<double>(endReadingList - startReadingList).count();
            std::cout << "Failo nuskaitymo laikas i List: " << readingTimeList << " sekundes" << std::endl;
        }

        int kriterijus;
        std::cout << "Pasirinkite rusiavimo kriteriju (0 - mediana, 1 - vidurkis): ";
        kriterijus = readInteger();
        bool pagalVidurki = (kriterijus == 1);

        /**
         * @brief Pasirenkama ir pritaikoma strategija pagal vartotojo pasirinkima.
         *
         * Naudojama funkcija testKonteinerius, kad atlikti reikiamus veiksmus su list.
         */
        if (strategija == 1) {
            double totalPartitionTimeList, totalNuskriaustukaiSaveTimeList, totalKietiakaiSaveTimeList;
            testKonteinerius(studentaiSarasas, pagalVidurki, totalPartitionTimeList,
                totalNuskriaustukaiSaveTimeList, totalKietiakaiSaveTimeList, strategija1);
        }
        else if (strategija == 2) {
            double totalPartitionTimeList, totalNuskriaustukaiSaveTimeList, totalKietiakaiSaveTimeList;
            testKonteinerius(studentaiSarasas, pagalVidurki, totalPartitionTimeList,
                totalNuskriaustukaiSaveTimeList, totalKietiakaiSaveTimeList, strategija2);
        }
        else if (strategija == 3) {
            double totalPartitionTimeList, totalNuskriaustukaiSaveTimeList, totalKietiakaiSaveTimeList;
            testKonteinerius(studentaiSarasas, pagalVidurki, totalPartitionTimeList,
                totalNuskriaustukaiSaveTimeList, totalKietiakaiSaveTimeList, strategija3);
        }
    }
    else {
        std::cerr << "Neteisingas konteinerio pasirinkimas.\n";
    }

    /**
     * @brief Testuoja tris metodus.
     *
     * Tikrinamas triju metodu veikimas.
     */
    trysMetodai();

    //Zmogus zmogus;

    /**
     * @brief Sukuria studento objekta ir isveda jo informacija.
     *
     * Sukuriamas studento objektas su vardo, pavardes, pazymiu ir amziaus duomenimis,
     * po to isvedama visa informacija apie si studenta.
     */
    Studentas student("Jonas", "Jonaitis", { 9, 8, 7 }, 10);
    student.printInfo();
    return 0;
}
