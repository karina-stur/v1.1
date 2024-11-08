#include "funkcijos.h"

int readInteger() {
    int value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail() || value < 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Klaida: Prasome ivesti teigiama skaiciu." << std::endl;
        }
        else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
    return value;
}

void generuotiStudentuFailus() {
    std::vector<int> record_counts = { 1000, 10000, 100000, 1000000, 10000000 };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 10);

    for (int count : record_counts) {
        std::string filename = "studentai_" + std::to_string(count) + ".txt";
        if (std::ifstream(filename)) {
            std::cout << "Failas " << filename << " jau egzistuoja." << std::endl;
            continue;
        }

        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Nepavyko sukurti failo: " << filename << std::endl;
            continue;
        }

        file << std::left << std::setw(20) << "Vardas" << std::setw(20) << "Pavarde";
        for (int i = 1; i <= 15; ++i) file << std::setw(10) << ("ND" + std::to_string(i));
        file << "Egz" << std::endl;

        for (int i = 1; i <= count; ++i) {
            file << "Vardas" << i << " Pavarde" << i;
            for (int j = 0; j < 15; ++j) file << std::setw(10) << dist(gen);
            file << std::setw(10) << dist(gen) << '\n';
        }

        std::cout << "Sukurtas failas: " << filename << " su " << count << " irasu." << std::endl;
    }
}

int generuotiAtsitiktiniPazymi(int min = 1, int max = 10) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

void generuotiPazymius(Studentas& studentas, int namuDarbuKiekis) {
    studentas.namuDarbai.clear();
    for (int i = 0; i < namuDarbuKiekis; ++i) {
        studentas.namuDarbai.push_back(generuotiAtsitiktiniPazymi());
    }
    studentas.egzaminas = generuotiAtsitiktiniPazymi();
}

void ivestiStudentuDuomenis(std::vector<Studentas>& studentaiVektorius) {
    int kiekMokiniu;
    std::cout << "Kiek studentu norite ivesti? ";
    kiekMokiniu = readInteger();

    for (int i = 0; i < kiekMokiniu; ++i) {
        Studentas studentas;
        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::getline(std::cin, studentas.vardas);
        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::getline(std::cin, studentas.pavarde);

        int ndKiekis;
        std::cout << "Kiek namu darbu pazymiu norite sugeneruoti? ";
        ndKiekis = readInteger();

        generuotiPazymius(studentas, ndKiekis);
        studentaiVektorius.push_back(studentas);

        std::cout << "Studentas " << studentas.vardas << " " << studentas.pavarde
            << " atminties adresas: " << &studentas << std::endl;
    }
}

void ivestiStudentuDuomenis(std::list<Studentas>& studentaiSarasas) {
    int kiekMokiniu;
    std::cout << "Kiek studentu norite ivesti? ";
    kiekMokiniu = readInteger();

    for (int i = 0; i < kiekMokiniu; ++i) {
        Studentas studentas;
        std::cout << "Iveskite " << i + 1 << "-ojo studento varda: ";
        std::getline(std::cin, studentas.vardas);
        std::cout << "Iveskite " << i + 1 << "-ojo studento pavarde: ";
        std::getline(std::cin, studentas.pavarde);

        int ndKiekis;
        std::cout << "Kiek namu darbu pazymiu norite sugeneruoti? ";
        ndKiekis = readInteger();

        generuotiPazymius(studentas, ndKiekis);
        studentaiSarasas.push_back(studentas);

        std::cout << "Studentas " << studentas.vardas << " " << studentas.pavarde
            << " atminties adresas: " << &studentas << std::endl;
    }
}

void nuskaitytiStudentus(const std::string& failoPavadinimas, std::vector<Studentas>& studentai) {
    std::ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    std::string header;
    std::getline(failas, header);
    studentai.reserve(10000000);

    while (failas) {
        Studentas studentas;
        failas >> studentas.vardas >> studentas.pavarde;
        studentas.namuDarbai.resize(15);
        for (int& nd : studentas.namuDarbai) failas >> nd;
        failas >> studentas.egzaminas;
        studentai.push_back(std::move(studentas));
    }
}

void nuskaitytiStudentus(const std::string& failoPavadinimas, std::list<Studentas>& studentai) {
    std::ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    std::string header;
    std::getline(failas, header);

    while (failas) {
        Studentas studentas;
        failas >> studentas.vardas >> studentas.pavarde;
        studentas.namuDarbai.resize(15);
        for (int& nd : studentas.namuDarbai) failas >> nd;
        failas >> studentas.egzaminas;
        studentai.push_back(studentas);
    }
}

double skaiciuotiGalutiniVidurki(const Studentas& studentas) {
    double total = std::accumulate(studentas.namuDarbai.begin(), studentas.namuDarbai.end(), 0);
    return (total + studentas.egzaminas) / (studentas.namuDarbai.size() + 1);
}

double skaiciuotiGalutiniMediana(Studentas studentas) {
    std::sort(studentas.namuDarbai.begin(), studentas.namuDarbai.end());
    if (studentas.namuDarbai.size() % 2 == 0) {
        return (studentas.namuDarbai[studentas.namuDarbai.size() / 2 - 1] + studentas.namuDarbai[studentas.namuDarbai.size() / 2]) / 2.0;
    }
    else {
        return studentas.namuDarbai[studentas.namuDarbai.size() / 2];
    }
}

void isaugotiStudentuGrupe(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas, bool pagalVidurki) {
    std::ofstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        std::cerr << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
        return;
    }

    failas << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(20) << "Galutinis (Vid.)"
        << "Galutinis (Med.)" << std::endl;
    failas << std::string(80, '-') << std::endl;

    if (pagalVidurki) {
        std::vector<Studentas> sortedStudentai = studentai;
        std::sort(sortedStudentai.begin(), sortedStudentai.end(), [](const Studentas& a, const Studentas& b) {
            return skaiciuotiGalutiniVidurki(a) > skaiciuotiGalutiniVidurki(b);
            });

        for (const Studentas& studentas : sortedStudentai) {
            double galutinisVidurkis = skaiciuotiGalutiniVidurki(studentas);
            double galutinisMediana = skaiciuotiGalutiniMediana(studentas);
            failas << std::left << std::setw(20) << studentas.vardas
                << std::setw(20) << studentas.pavarde
                << std::setw(20) << galutinisVidurkis
                << galutinisMediana << std::endl;
        }
    }
    else {
        std::vector<Studentas> sortedStudentai = studentai;
        std::sort(sortedStudentai.begin(), sortedStudentai.end(), [](const Studentas& a, const Studentas& b) {
            return skaiciuotiGalutiniMediana(a) > skaiciuotiGalutiniMediana(b);
            });

        for (const Studentas& studentas : sortedStudentai) {
            double galutinisVidurkis = skaiciuotiGalutiniVidurki(studentas);
            double galutinisMediana = skaiciuotiGalutiniMediana(studentas);
            failas << std::left << std::setw(20) << studentas.vardas
                << std::setw(20) << studentas.pavarde
                << std::setw(20) << galutinisVidurkis
                << galutinisMediana << std::endl;
        }
    }
}

void isaugotiStudentuGrupe(const std::list<Studentas>& studentai, const std::string& failoPavadinimas, bool pagalVidurki) {
    std::ofstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        std::cerr << "Nepavyko sukurti failo: " << failoPavadinimas << std::endl;
        return;
    }

    failas << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(20) << "Galutinis (Vid.)"
        << "Galutinis (Med.)" << std::endl;
    failas << std::string(80, '-') << std::endl;

    if (pagalVidurki) {
        std::list<Studentas> sortedStudentai = studentai; 
        sortedStudentai.sort([](const Studentas& a, const Studentas& b) {
            return skaiciuotiGalutiniVidurki(a) > skaiciuotiGalutiniVidurki(b);
            });

        for (const Studentas& studentas : sortedStudentai) {
            double galutinisVidurkis = skaiciuotiGalutiniVidurki(studentas);
            double galutinisMediana = skaiciuotiGalutiniMediana(studentas);
            failas << std::left << std::setw(20) << studentas.vardas
                << std::setw(20) << studentas.pavarde
                << std::setw(20) << galutinisVidurkis
                << galutinisMediana << std::endl;
        }
    }
    else {
        std::list<Studentas> sortedStudentai = studentai;
        sortedStudentai.sort([](const Studentas& a, const Studentas& b) {
            return skaiciuotiGalutiniMediana(a) > skaiciuotiGalutiniMediana(b);
            });

        for (const Studentas& studentas : sortedStudentai) {
            double galutinisVidurkis = skaiciuotiGalutiniVidurki(studentas);
            double galutinisMediana = skaiciuotiGalutiniMediana(studentas);
            failas << std::left << std::setw(20) << studentas.vardas
                << std::setw(20) << studentas.pavarde
                << std::setw(20) << galutinisVidurkis
                << galutinisMediana << std::endl;
        }
    }
}

void strategija1(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {

    for (const Studentas& studentas : studentai) {
        double galutinisRezultatas;

        if (pagalVidurki) {
            galutinisRezultatas = skaiciuotiGalutiniVidurki(studentas);
        }
        else {
            galutinisRezultatas = skaiciuotiGalutiniMediana(studentas);
        }

        if (galutinisRezultatas < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietekai.push_back(studentas);
        }
    }
}

void strategija1(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {

    for (const Studentas& studentas : studentai) {
        double galutinisRezultatas;

        if (pagalVidurki) {
            galutinisRezultatas = skaiciuotiGalutiniVidurki(studentas);
        }
        else {
            galutinisRezultatas = skaiciuotiGalutiniMediana(studentas);
        }

        if (galutinisRezultatas < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietekai.push_back(studentas);
        }
    }
}

void strategija2(std::vector<Studentas>& studentai, bool pagalVidurki,
    std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {
    for (size_t i = 0; i < studentai.size(); ) {
        double galutinisRezultatas;

        if (pagalVidurki) {
            galutinisRezultatas = skaiciuotiGalutiniVidurki(studentai[i]);
        }
        else {
            galutinisRezultatas = skaiciuotiGalutiniMediana(studentai[i]);
        }

        if (galutinisRezultatas < 5.0) {
            vargsiukai.push_back(studentai[i]);
            studentai.erase(studentai.begin() + i);
        }
        else {
            kietekai.push_back(studentai[i]); 
            ++i; 
        }
    }
}


void strategija2(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {
    for (auto it = studentai.begin(); it != studentai.end(); ) {
        double galutinisRezultatas;

        if (pagalVidurki) {
            galutinisRezultatas = skaiciuotiGalutiniVidurki(*it);
        }
        else {
            galutinisRezultatas = skaiciuotiGalutiniMediana(*it);
        }

        if (galutinisRezultatas < 5.0) {
            vargsiukai.splice(vargsiukai.end(), studentai, it++);
        }
        else {
            ++it;
        }
    }
}

void strategija3(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {
    auto isVargsiukas = [&](const Studentas& studentas) {
        double galutinisRezultatas = pagalVidurki
            ? skaiciuotiGalutiniVidurki(studentas)
            : skaiciuotiGalutiniMediana(studentas);
        return galutinisRezultatas < 5.0;
        };

    auto it = std::remove_if(studentai.begin(), studentai.end(), isVargsiukas);

    studentai.erase(it, studentai.end());
}

void strategija3(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {
    auto isVargsiukas = [&](const Studentas& studentas) {
        double galutinisRezultatas = pagalVidurki
            ? skaiciuotiGalutiniVidurki(studentas)
            : skaiciuotiGalutiniMediana(studentas);
        return galutinisRezultatas < 5.0;
        };

    studentai.remove_if(isVargsiukas);
}

void testKonteinerius(const std::vector<Studentas>& studentaiVektorius, bool pagalVidurki,
    double& totalPartitionTimeVec, double& totalNuskriaustukaiSaveTimeVec, double& totalKietiakaiSaveTimeVec,
    void (*strategija)(std::vector<Studentas>&, bool, std::vector<Studentas>&, std::vector<Studentas>&)) {

    std::vector<Studentas> vectorCopy = studentaiVektorius;
    std::vector<Studentas> vargsiukai;
    std::vector<Studentas> kietekai;

    auto start = std::chrono::high_resolution_clock::now();
    strategija(vectorCopy, pagalVidurki, vargsiukai, kietekai); 
    auto end = std::chrono::high_resolution_clock::now();
    totalPartitionTimeVec = std::chrono::duration<double>(end - start).count();

    double saveNuskriaustukaiTime = 0.0;
    double saveKietiakaiTime = 0.0;

    if (pagalVidurki) {
        start = std::chrono::high_resolution_clock::now();
        isaugotiStudentuGrupe(vargsiukai, "nuskriaustukai_list_vid.txt", pagalVidurki);
        end = std::chrono::high_resolution_clock::now();
        saveNuskriaustukaiTime = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        isaugotiStudentuGrupe(kietekai, "kietekai_list_vid.txt", pagalVidurki);
        end = std::chrono::high_resolution_clock::now();
        saveKietiakaiTime = std::chrono::duration<double>(end - start).count();
    } 
    else {
        start = std::chrono::high_resolution_clock::now();
        isaugotiStudentuGrupe(vargsiukai, "nuskriaustukai_list_med.txt", pagalVidurki);
        end = std::chrono::high_resolution_clock::now();
        saveNuskriaustukaiTime = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        isaugotiStudentuGrupe(kietekai, "kietekai_list_med.txt", pagalVidurki);
        end = std::chrono::high_resolution_clock::now();
        saveKietiakaiTime = std::chrono::duration<double>(end - start).count();
    }

    double totalTimeList = totalPartitionTimeVec + saveNuskriaustukaiTime + saveKietiakaiTime;

    std::cout << "Testuojama su std::list<Studentas>...\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "grupavimas uztruko: " << totalPartitionTimeVec << " sekundziu.\n";
    std::cout << "nuskriaustukai isaugoti per: " << saveNuskriaustukaiTime << " sekundziu.\n";
    std::cout << "kietiakai isaugoti per: " << saveKietiakaiTime << " sekundziu.\n";
    std::cout << "bendrai uztruko: " << totalTimeList << " sekundziu.\n";
}


void testKonteinerius(const std::list<Studentas>& studentaiLista, bool pagalVidurki,
    double& totalPartitionTimeList, double& totalNuskriaustukaiSaveTimeList, double& totalKietiakaiSaveTimeList,
    void (*strategija)(std::list<Studentas>&, bool, std::list<Studentas>&, std::list<Studentas>&)) {

    std::list<Studentas> listCopy = studentaiLista;
    std::list<Studentas> vargsiukai;
    std::list<Studentas> kietekai;

    auto start = std::chrono::high_resolution_clock::now();
    strategija(listCopy, pagalVidurki, vargsiukai, kietekai);
    auto end = std::chrono::high_resolution_clock::now();
    totalPartitionTimeList = std::chrono::duration<double>(end - start).count();

    double saveNuskriaustukaiTime = 0.0;
    double saveKietiakaiTime = 0.0;

    if (pagalVidurki) {
        start = std::chrono::high_resolution_clock::now();
        isaugotiStudentuGrupe(vargsiukai, "nuskriaustukai_list_vid.txt", pagalVidurki);
        end = std::chrono::high_resolution_clock::now();
        saveNuskriaustukaiTime = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        isaugotiStudentuGrupe(kietekai, "kietekai_list_vid.txt", pagalVidurki);
        end = std::chrono::high_resolution_clock::now();
        saveKietiakaiTime = std::chrono::duration<double>(end - start).count();
    }
    else {
        start = std::chrono::high_resolution_clock::now();
        isaugotiStudentuGrupe(vargsiukai, "nuskriaustukai_list_med.txt", pagalVidurki);
        end = std::chrono::high_resolution_clock::now();
        saveNuskriaustukaiTime = std::chrono::duration<double>(end - start).count();

        start = std::chrono::high_resolution_clock::now();
        isaugotiStudentuGrupe(kietekai, "kietekai_list_med.txt", pagalVidurki);
        end = std::chrono::high_resolution_clock::now();
        saveKietiakaiTime = std::chrono::duration<double>(end - start).count();
    }

    double totalTimeList = totalPartitionTimeList + saveNuskriaustukaiTime + saveKietiakaiTime;

    std::cout << "Testuojama su std::list<Studentas>...\n";
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "grupavimas uztruko: " << totalPartitionTimeList << " sekundziu.\n";
    std::cout << "nuskriaustukai isaugoti per: " << saveNuskriaustukaiTime << " sekundziu.\n";
    std::cout << "kietiakai isaugoti per: " << saveKietiakaiTime << " sekundziu.\n";
    std::cout << "bendrai uztruko: " << totalTimeList << " sekundziu.\n";
}
