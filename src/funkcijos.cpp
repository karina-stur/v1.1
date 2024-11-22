#include "funkcijos.h"
#include "studentas.h"

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
    studentas.setNamuDarbai({});

    for (int i = 0; i < namuDarbuKiekis; ++i) {
        studentas.addNamuDarbai(generuotiAtsitiktiniPazymi());
    }
    studentas.setEgzaminas(generuotiAtsitiktiniPazymi());
}

double skaiciuotiGalutiniVidurki(const std::vector<int>& namuDarbai, int egzaminas) {
    double total = std::accumulate(namuDarbai.begin(), namuDarbai.end(), 0);
    return (total + egzaminas) / (namuDarbai.size() + 1);
}

double skaiciuotiGalutiniMediana(const std::vector<int>& namuDarbai) {
    std::vector<int> sortedNamuDarbai = namuDarbai;
    std::sort(sortedNamuDarbai.begin(), sortedNamuDarbai.end());

    if (sortedNamuDarbai.size() % 2 == 0) {
        return (sortedNamuDarbai[sortedNamuDarbai.size() / 2 - 1] + sortedNamuDarbai[sortedNamuDarbai.size() / 2]) / 2.0;
    }
    else {
        return sortedNamuDarbai[sortedNamuDarbai.size() / 2];
    }
}

double skaiciuotiGalutiniVidurki(const std::list<int>& namuDarbai, int egzaminas) {
    double total = std::accumulate(namuDarbai.begin(), namuDarbai.end(), 0);
    return (total + egzaminas) / (namuDarbai.size() + 1);
}

double skaiciuotiGalutiniMediana(const std::list<int>& namuDarbai) {
    std::vector<int> sortedNamuDarbai(namuDarbai.begin(), namuDarbai.end());
    std::sort(sortedNamuDarbai.begin(), sortedNamuDarbai.end());

    if (sortedNamuDarbai.size() % 2 == 0) {
        return (sortedNamuDarbai[sortedNamuDarbai.size() / 2 - 1] + sortedNamuDarbai[sortedNamuDarbai.size() / 2]) / 2.0;
    }
    else {
        return sortedNamuDarbai[sortedNamuDarbai.size() / 2];
    }
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

    while (failas) {
        Studentas studentas;
        failas >> studentas.vardas >> studentas.pavarde;
        studentas.namuDarbai.resize(15);
        for (int& nd : studentas.namuDarbai) failas >> nd;
        failas >> studentas.egzaminas;
        studentai.push_back(studentas);
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

void isaugotiStudentuGrupe(const std::vector<Studentas>& studentai, const std::string& failoPavadinimas) {
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

    std::stringstream buffer;
    for (const Studentas& studentas : studentai) {
        double galutinisVidurkis = skaiciuotiGalutiniVidurki(studentas);
        double galutinisMediana = skaiciuotiGalutiniMediana(studentas);
        buffer << std::left << std::setw(20) << studentas.vardas
            << std::setw(20) << studentas.pavarde
            << std::setw(20) << galutinisVidurkis
            << galutinisMediana << std::endl;
    }
    failas << buffer.str();
}

void isaugotiStudentuGrupe(const std::list<Studentas>& studentai, const std::string& failoPavadinimas) {
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

    std::stringstream buffer;
    for (const Studentas& studentas : studentai) {
        double galutinisVidurkis = skaiciuotiGalutiniVidurki(studentas);
        double galutinisMediana = skaiciuotiGalutiniMediana(studentas);
        buffer << std::left << std::setw(20) << studentas.vardas
            << std::setw(20) << studentas.pavarde
            << std::setw(20) << galutinisVidurkis
            << galutinisMediana << std::endl;
    }
    failas << buffer.str();
}

void strategija1(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {
    std::vector<std::pair<Studentas, double>> studentScores;
    studentScores.reserve(studentai.size());

    for (const Studentas& studentas : studentai) {
        double finalScore = pagalVidurki ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutiniMediana(studentas);
        studentScores.emplace_back(studentas, finalScore);
    }

    std::partition(studentScores.begin(), studentScores.end(), [](const std::pair<Studentas, double>& studentScore) {
        return studentScore.second < 5.0;
        });

    vargsiukai.clear();
    kietekai.clear();
    for (const auto& studentScore : studentScores) {
        if (studentScore.second < 5.0) {
            vargsiukai.push_back(studentScore.first);
        }
        else {
            kietekai.push_back(studentScore.first);
        }
    }
}

void strategija1(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {
    studentai.sort([pagalVidurki](const Studentas& a, const Studentas& b) {
        double galutinisA = pagalVidurki ? skaiciuotiGalutiniVidurki(a) : skaiciuotiGalutiniMediana(a);
        double galutinisB = pagalVidurki ? skaiciuotiGalutiniVidurki(b) : skaiciuotiGalutiniMediana(b);
        return galutinisA > galutinisB;
        });

    for (const Studentas& studentas : studentai) {
        double galutinisRezultatas = pagalVidurki ? skaiciuotiGalutiniVidurki(studentas) : skaiciuotiGalutiniMediana(studentas);

        if (galutinisRezultatas < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietekai.push_back(studentas);
        }
    }
}

void strategija2(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {
    vargsiukai.clear();
    kietekai.clear();

    size_t writeIndex = 0;

    for (auto it = studentai.begin(); it != studentai.end(); ++it) {
        double finalScore = pagalVidurki ? skaiciuotiGalutiniVidurki(*it) : skaiciuotiGalutiniMediana(*it);

        if (finalScore < 5.0) {
            vargsiukai.push_back(std::move(*it));
        }
        else {
            if (it != studentai.begin() + writeIndex) {
                studentai[writeIndex] = std::move(*it);
            }
            ++writeIndex;
        }
    }
    studentai.resize(writeIndex); 
}

void strategija2(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {
    vargsiukai.clear();
    kietekai.clear();

    auto it = studentai.begin();
    while (it != studentai.end()) {
        double finalScore = pagalVidurki ? skaiciuotiGalutiniVidurki(*it) : skaiciuotiGalutiniMediana(*it);

        if (finalScore < 5.0) {
            vargsiukai.push_back(std::move(*it)); 
            it = studentai.erase(it);
        }
        else {
            ++it;
        }
    }
}

void strategija3(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {
    vargsiukai.clear(); 
    kietekai.clear(); 

    auto partitionIt = std::partition(studentai.begin(), studentai.end(), [&](const Studentas& student) {
        double finalScore = pagalVidurki ? skaiciuotiGalutiniVidurki(student) : skaiciuotiGalutiniMediana(student);
        return finalScore >= 5.0; 
        });

    for (auto it = partitionIt; it != studentai.end(); ++it) {
        vargsiukai.push_back(std::move(*it)); 
    }

    studentai.resize(std::distance(studentai.begin(), partitionIt));
}

void strategija3(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {
    vargsiukai.clear();
    kietekai.clear();

    std::list<Studentas> studentScoresAboveFive;

    for (auto it = studentai.begin(); it != studentai.end();) {
        double score = pagalVidurki ? skaiciuotiGalutiniVidurki(*it) : skaiciuotiGalutiniMediana(*it);

        if (score < 5.0) {
            vargsiukai.push_back(*it);
            it = studentai.erase(it);
        }
        else {
            ++it;
        }
    }
}

void testKonteinerius(const std::vector<Studentas>& studentaiVector, bool pagalVidurki,
    double& totalPartitionTimeVec, double& totalNuskriaustukaiSaveTimeVec, double& totalKietiakaiSaveTimeVec,
    void (*strategija)(std::vector<Studentas>&, bool, std::vector<Studentas>&, std::vector<Studentas>&)) {

    std::cout << "Testuojama su std::vector<Studentas>...\n";

    std::vector<Studentas> vectorCopy = studentaiVector;
    std::vector<Studentas> vargsiukai;                
    std::vector<Studentas> kietekai;                  

    auto start = std::chrono::high_resolution_clock::now();
    strategija(vectorCopy, pagalVidurki, vargsiukai, kietekai);
    auto end = std::chrono::high_resolution_clock::now();
    totalPartitionTimeVec = std::chrono::duration<double>(end - start).count();

    double saveNuskriaustukaiTime = 0.0;
    double saveKietekaiTime = 0.0;

    std::vector<Studentas>& kietekaiToSave = kietekai.empty() ? vectorCopy : kietekai;

    if (!vargsiukai.empty()) {
        std::sort(vargsiukai.begin(), vargsiukai.end(), [&](const Studentas& a, const Studentas& b) {
            double scoreA = pagalVidurki ? skaiciuotiGalutiniVidurki(a) : skaiciuotiGalutiniMediana(a);
            double scoreB = pagalVidurki ? skaiciuotiGalutiniVidurki(b) : skaiciuotiGalutiniMediana(b);
            return scoreA > scoreB;
            });
    }

    std::sort(kietekaiToSave.begin(), kietekaiToSave.end(), [&](const Studentas& a, const Studentas& b) {
        double scoreA = pagalVidurki ? skaiciuotiGalutiniVidurki(a) : skaiciuotiGalutiniMediana(a);
        double scoreB = pagalVidurki ? skaiciuotiGalutiniVidurki(b) : skaiciuotiGalutiniMediana(b);
        return scoreA > scoreB;
        });

    std::string nuskriaustukaiFile = pagalVidurki ? "nuskriaustukai_vec_vid.txt" : "nuskriaustukai_vec_med.txt";
    start = std::chrono::high_resolution_clock::now();
    isaugotiStudentuGrupe(vargsiukai, nuskriaustukaiFile);
    end = std::chrono::high_resolution_clock::now();
    saveNuskriaustukaiTime = std::chrono::duration<double>(end - start).count();

    std::string kietekaiFile = pagalVidurki ? "kietekai_vec_vid.txt" : "kietekai_vec_med.txt";
    start = std::chrono::high_resolution_clock::now();
    isaugotiStudentuGrupe(kietekaiToSave, kietekaiFile);
    end = std::chrono::high_resolution_clock::now();
    saveKietekaiTime = std::chrono::duration<double>(end - start).count();

    double totalTimeVec = totalPartitionTimeVec + saveNuskriaustukaiTime + saveKietekaiTime;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "grupavimas uztruko: " << totalPartitionTimeVec << " sekundziu.\n";
    std::cout << "nuskriaustukai isaugoti per: " << saveNuskriaustukaiTime << " sekundziu.\n";
    std::cout << "kietekai isaugoti per: " << saveKietekaiTime << " sekundziu.\n";
    std::cout << "bendrai uztruko: " << totalTimeVec << " sekundziu.\n";
}

void testKonteinerius(const std::list<Studentas>& studentaiList, bool pagalVidurki,
    double& totalPartitionTimeList, double& totalNuskriaustukaiSaveTimeList, double& totalKietiakaiSaveTimeList,
    void (*strategija)(std::list<Studentas>&, bool, std::list<Studentas>&, std::list<Studentas>&)) {

    std::cout << "Testuojama su std::list<Studentas>...\n";

    std::list<Studentas> listCopy = studentaiList; 
    std::list<Studentas> vargsiukai;          
    std::list<Studentas> kietekai;               

    auto start = std::chrono::high_resolution_clock::now();
    strategija(listCopy, pagalVidurki, vargsiukai, kietekai);
    auto end = std::chrono::high_resolution_clock::now();
    totalPartitionTimeList = std::chrono::duration<double>(end - start).count();

    double saveNuskriaustukaiTime = 0.0;
    double saveKietiakaiTime = 0.0;

    std::list<Studentas>& kietekaiToSave = kietekai.empty() ? listCopy : kietekai;

    kietekaiToSave.sort([&](const Studentas& a, const Studentas& b) {
        double scoreA = pagalVidurki ? skaiciuotiGalutiniVidurki(a) : skaiciuotiGalutiniMediana(a);
        double scoreB = pagalVidurki ? skaiciuotiGalutiniVidurki(b) : skaiciuotiGalutiniMediana(b);
        return scoreA > scoreB;
        });

    std::string nuskriaustukaiFile = pagalVidurki ? "nuskriaustukai_list_vid.txt" : "nuskriaustukai_list_med.txt";
    start = std::chrono::high_resolution_clock::now();
    isaugotiStudentuGrupe(vargsiukai, nuskriaustukaiFile);
    end = std::chrono::high_resolution_clock::now();
    saveNuskriaustukaiTime = std::chrono::duration<double>(end - start).count();

    std::string kietekaiFile = pagalVidurki ? "kietekai_list_vid.txt" : "kietekai_list_med.txt";
    start = std::chrono::high_resolution_clock::now();
    isaugotiStudentuGrupe(kietekaiToSave, kietekaiFile);
    end = std::chrono::high_resolution_clock::now();
    saveKietiakaiTime = std::chrono::duration<double>(end - start).count();

    double totalTimeList = totalPartitionTimeList + saveNuskriaustukaiTime + saveKietiakaiTime;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "grupavimas uztruko: " << totalPartitionTimeList << " sekundziu.\n";
    std::cout << "nuskriaustukai isaugoti per: " << saveNuskriaustukaiTime << " sekundziu.\n";
    std::cout << "kietekai isaugoti per: " << saveKietiakaiTime << " sekundziu.\n";
    std::cout << "bendrai uztruko: " << totalTimeList << " sekundziu.\n";
}
