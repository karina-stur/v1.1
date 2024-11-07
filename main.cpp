#include "funkcijos.h"
#include "studentas.h"

int main() {
    char generateOption;
    std::cout << "Norite sugeneruoti studentu failus? (y/n): ";
    std::cin >> generateOption;
    std::cin.ignore();

    if (generateOption == 'y' || generateOption == 'Y') {
        generuotiStudentuFailus();
    }

    int pasirinkimas;
    std::cout << "Pasirinkite duomenu ivedimo buda: 1 - ivesti duomenis, 2 - nuskaityti is failo: ";
    pasirinkimas = readInteger();

    std::vector<Studentas> studentaiVektorius;
    std::list<Studentas> studentaiSarasas;

    if (pasirinkimas == 1) {
        ivestiStudentuDuomenis(studentaiVektorius, studentaiSarasas);
    }
    else if (pasirinkimas == 2) {
        std::string failoPavadinimas;
        std::cout << "Iveskite failo pavadinima: ";
        std::cin >> failoPavadinimas;

        auto startReadingVec = std::chrono::high_resolution_clock::now();
        nuskaitytiStudentus(failoPavadinimas, studentaiVektorius);
        auto endReadingVec = std::chrono::high_resolution_clock::now();
        double readingTimeVec = std::chrono::duration<double>(endReadingVec - startReadingVec).count();
        std::cout << "Failo nuskaitymo laikas i vektoriu: " << readingTimeVec << " sekundes" << std::endl;

        auto startReadingList = std::chrono::high_resolution_clock::now();
        nuskaitytiStudentus(failoPavadinimas, studentaiSarasas);
        auto endReadingList = std::chrono::high_resolution_clock::now();
        double readingTimeList = std::chrono::duration<double>(endReadingList - startReadingList).count();
        std::cout << "Failo nuskaitymo laikas i sarasa: " << readingTimeList << " sekundes" << std::endl;
    }

    int kriterijus;
    std::cout << "Pasirinkite rusiavimo kriteriju (0 - mediana, 1 - vidurkis): ";
    kriterijus = readInteger();
    bool pagalVidurki = (kriterijus == 1);

    double totalPartitionTimeVec, totalNuskriaustukaiSaveTimeVec, totalKietiakaiSaveTimeVec;
    double readingTimeVec, totalReadingTimeList, totalPartitionTimeList, totalNuskriaustukaiSaveTimeList, totalKietiakaiSaveTimeList;

    testKonteinerius(studentaiVektorius, studentaiSarasas, pagalVidurki, totalPartitionTimeVec, totalNuskriaustukaiSaveTimeVec,
        totalKietiakaiSaveTimeVec, readingTimeVec, totalReadingTimeList, totalPartitionTimeList, totalNuskriaustukaiSaveTimeList,
        totalKietiakaiSaveTimeList);

    void testKonteinerius(const std::vector<Studentas>&studentaiVektorius, const std::list<Studentas>&studentaiSarasas, bool pagalVidurki,
        double& totalPartitionTimeVec, double& totalNuskriaustukaiSaveTimeVec, double& totalKietiakaiSaveTimeVec, double& readingTimeVec,
        double& totalReadingTimeList, double& totalPartitionTimeList, double& totalNuskriaustukaiSaveTimeList, double& totalKietiakaiSaveTimeList);

    return 0;
}
