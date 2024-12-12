#include "funkcijos.h"
#include "studentas.h"

/**
 * @brief Funkcija, skirta ivesti sveikaji skaiciu su patikra, kad jis butu teigiamas.
 *
 * Si funkcija nuolat praso vartotojo ivesti teigiamaji sveikaji skaiciu. Jeigu ivestas
 * skaicius yra klaidingas arba neigiamas, bus rodomas klaidos pranesimas ir vartotojas
 * bus paprasytas ivesti skaiciu is naujo, kol bus ivestas teisingas teigiamas skaicius.
 *
 * @return int Teisingai ivestas sveikasis skaicius.
 */
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

/**
 * @brief Funkcija, skirta generuoti studentu failus su atsitiktiniais duomenimis.
 *
 * Si funkcija sukuria kelis studentu duomenu failus su atsitiktiniais pazymiais
 * uz namu darbus ir egzaminus. Failai kuriami pagal is anksto nustatyta irasu kieki
 * (1000, 10000 ir t.t.). Jeigu failas jau egzistuoja, jis bus praleistas.
 *
 * @return void
 */
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

/**
 * @brief Funkcija, skirta generuoti atsitiktini pazymi.
 *
 * Funkcija sugeneruoja atsitiktini pazymi pagal nurodytus minimalu ir maksimalu diapazonus.
 *
 * @param min Minimalus galimas pazymys (numatytoji reiksme: 1).
 * @param max Maksimalus galimas pazymys (numatytoji reiksme: 10).
 *
 * @return int Atsitiktinai sugeneruotas pazymys.
 */
int generuotiAtsitiktiniPazymi(int min = 1, int max = 10) {
    static std::random_device rd;
    static std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(mt);
}

/**
 * @brief Funkcija, skirta generuoti studento pazymius.
 *
 * Si funkcija sugeneruoja atsitiktinius pazymius studentui uz nurodyta namu darbu kieki.
 *
 * @param studentas Studentas, kuriam generuojami pazymiai.
 * @param namuDarbuKiekis Namu darbu kieki, pagal kuri bus sugeneruoti pazymiai.
 *
 * @return void
 */
void generuotiPazymius(Studentas& studentas, int namuDarbuKiekis) {
    studentas.setNamuDarbai({});

    for (int i = 0; i < namuDarbuKiekis; ++i) {
        studentas.addNamuDarbai(generuotiAtsitiktiniPazymi());
    }
}

/**
 * @brief Funkcija, skirta skaiciuoti galutini studento vidurki.
 *
 * Si funkcija apskaiciuoja galutini studento vidurki, atsizvelgiant i visus namu darbus ir egzamina.
 *
 * @param namuDarbai Studentui uzduoti namu darbu pazymiai.
 * @param egzaminas Egzamino pazymys.
 *
 * @return double Galutinis vidurkis.
 */
double skaiciuotiGalutiniVidurki(const std::vector<int>& namuDarbai, int egzaminas) {
    double total = std::accumulate(namuDarbai.begin(), namuDarbai.end(), 0);
    return (total + egzaminas) / (namuDarbai.size() + 1);
}

/**
 * @brief Funkcija, skirta skaiciuoti galutine mediana.
 *
 * Si funkcija apskaiciuoja galutine studento pazymiu mediana is visu namu darbu.
 *
 * @param namuDarbai Studentui uzduoti namu darbu pazymiai.
 *
 * @return double Galutine mediana.
 */
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

/**
 * @brief Funkcija, skirta skaiciuoti galutini studento vidurki su lista.
 *
 * Si funkcija apskaiciuoja galutini studento vidurki, atsizvelgiant i visus namu darbus ir egzamina.
 *
 * @param namuDarbai Studentui uzduoti namu darbu pazymiai.
 * @param egzaminas Egzamino pazymys.
 *
 * @return double Galutinis vidurkis.
 */
double skaiciuotiGalutiniVidurki(const std::list<int>& namuDarbai, int egzaminas) {
    double total = std::accumulate(namuDarbai.begin(), namuDarbai.end(), 0);
    return (total + egzaminas) / (namuDarbai.size() + 1);
}

/**
 * @brief Funkcija, skirta skaiciuoti galutine mediana su lista.
 *
 * Si funkcija apskaiciuoja galutine studento pazymiu mediana is visu namu darbu.
 *
 * @param namuDarbai Studentui uzduoti namu darbu pazymiai.
 *
 * @return double Galutine mediana.
 */
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

/**
 * @brief Funkcija, skirta ivesti studentu duomenis i vektoriu.
 *
 * Si funkcija leidzia vartotojui ivesti studentu duomenis ir saugoti juos vektoriuje.
 *
 * @param studentaiVektorius Vektorius, kuriame bus saugomi studentai.
 *
 * @return void
 */
void ivestiStudentuDuomenis(std::vector<Studentas>& studentaiVektorius) {
    int kiekMokiniu;
    std::cout << "Kiek studentu norite ivesti? ";
    kiekMokiniu = readInteger();

    for (int i = 0; i < kiekMokiniu; ++i) {
        Studentas studentas;
        std::cin >> studentas;
        studentaiVektorius.push_back(studentas);

        std::cout << "Studentas " << studentas.getVardas() << " " << studentas.getPavarde()
            << " atminties adresas: " << &studentas << std::endl;
    }
}

/**
 * @brief Funkcija, skirta ivesti studentu duomenis i sarasa.
 *
 * Si funkcija leidzia vartotojui ivesti studentu duomenis ir saugoti juos sarase.
 *
 * @param studentaiSarasas Sarasas, kuriame bus saugomi studentai.
 *
 * @return void
 */
void ivestiStudentuDuomenis(std::list<Studentas>& studentaiSarasas) {
    int kiekMokiniu;
    std::cout << "Kiek studentu norite ivesti? ";
    kiekMokiniu = readInteger();

    for (int i = 0; i < kiekMokiniu; ++i) {
        Studentas studentas;
        std::cin >> studentas;
        studentaiSarasas.push_back(studentas);

        std::cout << "Studentas " << studentas.getVardas() << " " << studentas.getPavarde()
            << " atminties adresas: " << &studentas << std::endl;
    }
}

/**
 * @brief Nuskaityti studentus is failo ir issaugoti i vektoriu.
 *
 * Si funkcija atidaro faila pagal pateikta pavadinima, nuskaityti studento duomenis
 * (vardas, pavarde, namu darbai ir egzaminas) ir issaugo juos i vektoriu.
 *
 * @param failoPavadinimas Failo, is kurio bus nuskaityti studentu duomenys, pavadinimas.
 * @param studentai Vektorius, kuriame bus issaugoti studentai.
 */
void nuskaitytiStudentus(const std::string& failoPavadinimas, std::vector<Studentas>& studentai) {
    std::ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    std::string header;
    std::getline(failas, header);

    while (failas) {
        std::string vardas, pavarde;
        std::vector<int> namuDarbai(15);
        int egzaminas;

        failas >> vardas >> pavarde;

        for (int i = 0; i < 15; ++i) {
            failas >> namuDarbai[i];
        }

        failas >> egzaminas;

        if (failas) {
            Studentas studentas(vardas, pavarde, namuDarbai, egzaminas);

            studentai.push_back(studentas);
        }
    }
}

/**
 * @brief Nuskaityti studentus is failo ir issaugoti i sarasa.
 *
 * Si funkcija atidaro faila pagal pateikta pavadinima, nuskaityti studento duomenis
 * (vardas, pavarde, namu darbai ir egzaminas) ir issaugo juos i sarasa.
 *
 * @param failoPavadinimas Failo, is kurio bus nuskaityti studentu duomenys, pavadinimas.
 * @param studentai Sarasas, kuriame bus issaugoti studentai.
 */
void nuskaitytiStudentus(const std::string& failoPavadinimas, std::list<Studentas>& studentai) {
    std::ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        std::cerr << "Nepavyko atidaryti failo: " << failoPavadinimas << std::endl;
        return;
    }

    std::string header;
    std::getline(failas, header);

    while (failas) {
        std::string vardas, pavarde;
        std::vector<int> namuDarbai(15);
        int egzaminas;

        failas >> vardas >> pavarde;

        for (int i = 0; i < 15; ++i) {
            failas >> namuDarbai[i];
        }

        failas >> egzaminas;

        if (failas) {
            Studentas studentas(vardas, pavarde, namuDarbai, egzaminas);
            studentai.push_back(studentas);
        }
    }
}

/**
 * @brief Iraso studentu grupe i ekrana.
 *
 * Si funkcija parodo studentu duomenis (vardas, pavarde, galutinis vidurkis ir galutinis mediana)
 * ekrane is pateikto studentu vektoriaus.
 *
 * @param studentai Vektorius, kuriame yra studentai, kuriu duomenys bus atvaizduoti.
 */
void isaugotiStudentuGrupe(const std::vector<Studentas>& studentai) {
    if (studentai.empty()) {
        std::cerr << "Studentu nera, nera ka irasyti!" << std::endl;
        return;
    }

    std::cout << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(20) << "Galutinis (Vid.)"
        << "Galutinis (Med.)" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const Studentas& studentas : studentai) {
        std::cout << studentas;
    }
}

/**
 * @brief Iraso studentu grupe i ekrana.
 *
 * Si funkcija parodo studentu duomenis (vardas, pavarde, galutinis vidurkis ir galutinis mediana)
 * ekrane is pateikto studentu saraso.
 *
 * @param studentai Sarasas, kuriame yra studentai, kuriu duomenys bus atvaizduoti.
 */
void isaugotiStudentuGrupe(const std::list<Studentas>& studentai) {
    if (studentai.empty()) {
        std::cerr << "Studentu nera, nera ka irasyti!" << std::endl;
        return;
    }

    std::cout << std::left << std::setw(20) << "Vardas"
        << std::setw(20) << "Pavarde"
        << std::setw(20) << "Galutinis (Vid.)"
        << "Galutinis (Med.)" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const Studentas& studentas : studentai) {
        std::cout << studentas;
    }
}

/**
 * @brief Strategija 1: Studentu suskirstymas i vargsiukus ir kietekus naudojant viena kontineri.
 *
 * Si funkcija suskirsto studentus i dvi grupes - vargsiukus (studentai su galutiniu rezultatu
 * maziau nei 5) ir kietekus (studentai su galutiniu rezultatu 5 ir daugiau) pagal vidurki arba
 * mediana.
 *
 * @param studentai Vektorius studentu, kurie bus suskirstyti.
 * @param pagalVidurki Jei true, naudojamas galutinis vidurkis, jei false - galutinis mediana.
 * @param vargsiukai Vektorius, i kuri bus irasomi vargsiukai.
 * @param kietekai Vektorius, i kuri bus irasomi kietekai.
 */
void strategija1(std::vector<Studentas>& studentai, bool pagalVidurki,
    std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {
    std::vector<std::pair<Studentas, double>> studentScores;
    studentScores.reserve(studentai.size());

    for (const Studentas& studentas : studentai) {
        double finalScore = pagalVidurki ? studentas.skaiciuotiGalutiniVidurki() : studentas.skaiciuotiGalutiniMediana();
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

/**
 * @brief Strategija 1: Studentu suskirstymas i vargsiukus ir kietekus naudojant viena konteineri.
 *
 * Si funkcija suskirsto studentus i dvi grupes - vargsiukus (studentai su galutiniu rezultatu
 * maziau nei 5) ir kietekus (studentai su galutiniu rezultatu 5 ir daugiau) pagal vidurki arba
 * mediana. Naudoja sarasa vietoj vektoriaus.
 *
 * @param studentai Sarasas studentu, kurie bus suskirstyti.
 * @param pagalVidurki Jei true, naudojamas galutinis vidurkis, jei false - galutinis mediana.
 * @param vargsiukai Sarasas, i kuri bus irasomi vargsiukai.
 * @param kietekai Sarasas, i kuri bus irasomi kietekai.
 */
void strategija1(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {
    std::list<Studentas> listCopy = studentai;

    studentai.sort([pagalVidurki](const Studentas& a, const Studentas& b) {
        double galutinisA = pagalVidurki ? a.skaiciuotiGalutiniVidurki() : a.skaiciuotiGalutiniMediana();
        double galutinisB = pagalVidurki ? b.skaiciuotiGalutiniVidurki() : b.skaiciuotiGalutiniMediana();
        return galutinisA > galutinisB;
        });

    for (const Studentas& studentas : studentai) {
        double galutinisRezultatas = pagalVidurki ? studentas.skaiciuotiGalutiniVidurki() : studentas.skaiciuotiGalutiniMediana();

        if (galutinisRezultatas < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietekai.push_back(studentas);
        }
    }
}


/**
 * @brief Strategija 2: Studentu suskirstymas i vargsiukus ir kietekus naudojant 2 atskirus konteinerius.
 *
 * Si funkcija naudoja vektoriu ir perkelia studentus i atskiras grupes (vargsiukai ir kietekai),
 * remiantis galutiniu rezultatu, kuris apskaiciuojamas pagal vidurki arba medianna. Studentai su
 * galutiniu rezultatu maziau nei 5 yra perkelti i vargsiuku grupe, o visi kiti - i kieteku grupe.
 *
 * @param studentai Vektorius studentu, kuriuos reikia suskirstyti.
 * @param pagalVidurki Jei true, naudojamas galutinis vidurkis, jei false - galutinis mediana.
 * @param vargsiukai Vektorius, kuriame bus issaugoti vargsiukai.
 * @param kietekai Vektorius, kuriame bus issaugoti kietekai.
 */
void strategija2(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {
    vargsiukai.clear();
    kietekai.clear();

    size_t writeIndex = 0;

    vargsiukai.reserve(studentai.size());
    kietekai.reserve(studentai.size());

    for (auto it = studentai.begin(); it != studentai.end(); ++it) {
        double finalScore = pagalVidurki ? it->skaiciuotiGalutiniVidurki() : it->skaiciuotiGalutiniMediana();

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

/**
 * @brief Studentu suskirstymas i vargsiukus ir kietekus naudojant 2 atskirus konteinerius.
 *
 * Si funkcija naudoja sarasa ir perkelia studentus i atskiras grupes (vargsiukai ir kietekai),
 * remiantis galutiniu rezultatu, kuris apskaiciuojamas pagal vidurki arba medianna. Studentai su
 * galutiniu rezultatu maziau nei 5 yra perkelti i vargsiuku grupe, o visi kiti - i kieteku grupe.
 *
 * @param studentai Sarasas studentu, kuriuos reikia suskirstyti.
 * @param pagalVidurki Jei true, naudojamas galutinis vidurkis, jei false - galutinis mediana.
 * @param vargsiukai Sarasas, kuriame bus issaugoti vargsiukai.
 * @param kietekai Sarasas, kuriame bus issaugoti kietekai.
 */
void strategija2(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {
    vargsiukai.clear();
    kietekai.clear();

    auto it = studentai.begin();
    while (it != studentai.end()) {
        double finalScore = pagalVidurki ? it->skaiciuotiGalutiniVidurki() : it->skaiciuotiGalutiniMediana();

        if (finalScore < 5.0) {
            vargsiukai.push_back(std::move(*it));
            it = studentai.erase(it);
        }
        else {
            kietekai.push_back(std::move(*it));
            ++it;
        }
    }
}

/**
 * @brief Strategija 3: Studentu suskirstymas i vargsiukus ir kietekus naudojant geriausia strategija.
 *
 * Si funkcija naudoja vektoriu ir padalina studentus i vargsiukus ir kietekus, naudodama
 * std::partition funkcija. Studentai, kuriu galutinis rezultatas yra maziau nei 5, bus perkelti
 * i vargsiuku grupe, o visi kiti - i kieteku grupe.
 *
 * @param studentai Vektorius studentu, kuriuos reikia suskirstyti.
 * @param pagalVidurki Jei true, naudojamas galutinis vidurkis, jei false - galutinis mediana.
 * @param vargsiukai Vektorius, kuriame bus issaugoti vargsiukai.
 * @param kietekai Vektorius, kuriame bus issaugoti kietekai.
 */
void strategija3(std::vector<Studentas>& studentai, bool pagalVidurki, std::vector<Studentas>& vargsiukai, std::vector<Studentas>& kietekai) {
    vargsiukai.clear();
    kietekai.clear();

    auto partitionIt = std::partition(studentai.begin(), studentai.end(), [&](Studentas& student) {
        double finalScore = pagalVidurki ? student.skaiciuotiGalutiniVidurki() : student.skaiciuotiGalutiniMediana();
        return finalScore >= 5.0;
        });

    for (auto it = partitionIt; it != studentai.end(); ++it) {
        vargsiukai.push_back(std::move(*it));
    }

    studentai.resize(std::distance(studentai.begin(), partitionIt));
}

/**
 * @brief Strategija 3: Studentu suskirstymas i vargsiukus ir kietekus naudojant geriausia strategija.
 *
 * Si funkcija naudoja sarasa ir padalina studentus i vargsiukus ir kietekus. Studentai,
 * kuriu galutinis rezultatas yra maziau nei 5, bus perkelti i vargsiuku grupe, o visi kiti -
 * i kieteku grupe.
 *
 * @param studentai Sarasas studentu, kuriuos reikia suskirstyti.
 * @param pagalVidurki Jei true, naudojamas galutinis vidurkis, jei false - galutinis mediana.
 * @param vargsiukai Sarasas, kuriame bus issaugoti vargsiukai.
 * @param kietekai Sarasas, kuriame bus issaugoti kietekai.
 */
void strategija3(std::list<Studentas>& studentai, bool pagalVidurki, std::list<Studentas>& vargsiukai, std::list<Studentas>& kietekai) {
    vargsiukai.clear();
    kietekai.clear();

    for (auto it = studentai.begin(); it != studentai.end();) {
        double score = pagalVidurki ? it->skaiciuotiGalutiniVidurki() : it->skaiciuotiGalutiniMediana();

        if (score < 5.0) {
            vargsiukai.push_back(std::move(*it));
            it = studentai.erase(it);
        }
        else {
            ++it;
        }
    }
}

/**
 * @brief Testuoja konteinerius su std::vector<Studentas>.
 *
 * Funkcija testuoja strategija su std::vector<Studentas> konteineriu, suskirstydama studentus i vargsiukus ir kietekus.
 * Atlikus strategija, rezultatai gali buti isvedami i ekrana arba issaugomi faile.
 * Matuojamas laikas, reikalingas grupei suskirstyti ir rezultatams issaugoti.
 *
 * @param studentaiVector Vektorius studentu, kurie bus testuojami.
 * @param pagalVidurki Kintamasis, nurodantis, ar naudoti vidurki (true) ar mediana (false) kaip galutini rezultata.
 * @param totalPartitionTimeVec Busimas kintamasis, kuriame bus saugomas laikas, per kuri buvo suskirstyti studentai.
 * @param totalNuskriaustukaiSaveTimeVec Busimas kintamasis, kuriame bus saugomas laikas, per kuri buvo issaugoti nuskriaustukai.
 * @param totalKietiakaiSaveTimeVec Busimas kintamasis, kuriame bus saugomas laikas, per kuri buvo issaugoti kietekai.
 * @param strategija Funkcija, kuri atlieka studentu suskirstyma pagal tam tikra strategija.
 */

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
            double scoreA = pagalVidurki ? a.skaiciuotiGalutiniVidurki() : a.skaiciuotiGalutiniMediana();
            double scoreB = pagalVidurki ? b.skaiciuotiGalutiniVidurki() : b.skaiciuotiGalutiniMediana();
            return scoreA > scoreB;
            });
    }

    std::sort(kietekaiToSave.begin(), kietekaiToSave.end(), [&](const Studentas& a, const Studentas& b) {
        double scoreA = pagalVidurki ? a.skaiciuotiGalutiniVidurki() : a.skaiciuotiGalutiniMediana();
        double scoreB = pagalVidurki ? b.skaiciuotiGalutiniVidurki() : b.skaiciuotiGalutiniMediana();
        return scoreA > scoreB;
        });

    int pasirinkimas;
    std::cout << "Kur norite isvesti studentu duomenis?\n";
    std::cout << "1 - I ekrana\n";
    std::cout << "2 - I faila\n";
    do {
        std::cout << "Pasirinkimas (1 arba 2): ";
        std::cin >> pasirinkimas;
        if (pasirinkimas != 1 && pasirinkimas != 2) {
            std::cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
    } while (pasirinkimas != 1 && pasirinkimas != 2);

    if (pasirinkimas == 1) {
        std::cout << "Vargsiukai (Nuskriaustukai):\n";
        isaugotiStudentuGrupe(vargsiukai);

        std::cout << "Kietekai:\n";
        isaugotiStudentuGrupe(kietekaiToSave);
    }
    else if (pasirinkimas == 2) {
        std::string nuskriaustukaiFile = pagalVidurki ? "nuskriaustukai_vec_vid.txt" : "nuskriaustukai_vec_med.txt";
        start = std::chrono::high_resolution_clock::now();
        std::ofstream nuskriaustukaiFailas(nuskriaustukaiFile);
        if (nuskriaustukaiFailas.is_open()) {
            nuskriaustukaiFailas << std::left << std::setw(20) << "Vardas"
                << std::setw(20) << "Pavarde"
                << std::setw(20) << "Galutinis (Vid.)"
                << "Galutinis (Med.)" << std::endl;
            nuskriaustukaiFailas << std::string(80, '-') << std::endl;
            for (const Studentas& studentas : vargsiukai) {
                nuskriaustukaiFailas << studentas; 
            }
            std::cout << "Nuskriaustukai isaugoti i faila: " << nuskriaustukaiFile << std::endl;
        }
        end = std::chrono::high_resolution_clock::now();
        saveNuskriaustukaiTime = std::chrono::duration<double>(end - start).count();

        std::string kietekaiFile = pagalVidurki ? "kietekai_vec_vid.txt" : "kietekai_vec_med.txt";
        start = std::chrono::high_resolution_clock::now();
        std::ofstream kietekaiFailas(kietekaiFile);
        if (kietekaiFailas.is_open()) {
            kietekaiFailas << std::left << std::setw(20) << "Vardas"
                << std::setw(20) << "Pavarde"
                << std::setw(20) << "Galutinis (Vid.)"
                << "Galutinis (Med.)" << std::endl;
            kietekaiFailas << std::string(80, '-') << std::endl;
            for (const Studentas& studentas : kietekaiToSave) {
                kietekaiFailas << studentas;
            }
            std::cout << "Kietekai isaugoti i faila: " << kietekaiFile << std::endl;
        }
        end = std::chrono::high_resolution_clock::now();
        saveKietekaiTime = std::chrono::duration<double>(end - start).count();
    }

    double totalTimeVec = totalPartitionTimeVec + saveNuskriaustukaiTime + saveKietekaiTime;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Grupavimas uztruko: " << totalPartitionTimeVec << " sekundziu.\n";
    std::cout << "Nuskriaustukai isaugoti per: " << saveNuskriaustukaiTime << " sekundziu.\n";
    std::cout << "Kietekai isaugoti per: " << saveKietekaiTime << " sekundziu.\n";
    std::cout << "Bendrai uztruko: " << totalTimeVec << " sekundziu.\n";
}

/**
 * @brief Testuoja konteinerius su std::list<Studentas>.
 *
 * Funkcija testuoja strategija su std::list<Studentas> konteineriu, suskirstydama studentus i vargsiukus ir kietekus.
 * Atlikus strategija, rezultatai gali buti isvedami i ekrana arba issaugomi faile.
 * Matuojamas laikas, reikalingas grupei suskirstyti ir rezultatams issaugoti.
 *
 * @param studentaiList Sarasas studentu, kurie bus testuojami.
 * @param pagalVidurki Kintamasis, nurodantis, ar naudoti vidurki (true) ar mediana (false) kaip galutini rezultata.
 * @param totalPartitionTimeList Busimas kintamasis, kuriame bus saugomas laikas, per kuri buvo suskirstyti studentai.
 * @param totalNuskriaustukaiSaveTimeList Busimas kintamasis, kuriame bus saugomas laikas, per kuri buvo issaugoti nuskriaustukai.
 * @param totalKietiakaiSaveTimeList Busimas kintamasis, kuriame bus saugomas laikas, per kuri buvo issaugoti kietekai.
 * @param strategija Funkcija, kuri atlieka studentu suskirstyma pagal tam tikra strategija.
 */

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
    double saveKietekaiTime = 0.0;

    std::list<Studentas>& kietekaiToSave = kietekai.empty() ? listCopy : kietekai;

    if (!vargsiukai.empty()) {
        vargsiukai.sort([&](const Studentas& a, const Studentas& b) {
            double scoreA = pagalVidurki ? a.skaiciuotiGalutiniVidurki() : a.skaiciuotiGalutiniMediana();
            double scoreB = pagalVidurki ? b.skaiciuotiGalutiniVidurki() : b.skaiciuotiGalutiniMediana();
            return scoreA > scoreB;
            });
    }

    kietekaiToSave.sort([&](const Studentas& a, const Studentas& b) {
        double scoreA = pagalVidurki ? a.skaiciuotiGalutiniVidurki() : a.skaiciuotiGalutiniMediana();
        double scoreB = pagalVidurki ? b.skaiciuotiGalutiniVidurki() : b.skaiciuotiGalutiniMediana();
        return scoreA > scoreB;
        });

    int pasirinkimas;
    std::cout << "Kur norite isvesti studentu duomenis?\n";
    std::cout << "1 - I ekrana\n";
    std::cout << "2 - I faila\n";
    do {
        std::cout << "Pasirinkimas (1 arba 2): ";
        std::cin >> pasirinkimas;
        if (pasirinkimas != 1 && pasirinkimas != 2) {
            std::cout << "Neteisingas pasirinkimas. Bandykite dar karta.\n";
        }
    } while (pasirinkimas != 1 && pasirinkimas != 2);

    if (pasirinkimas == 1) {
        std::cout << "Vargsiukai (Nuskriaustukai):\n";
        isaugotiStudentuGrupe(vargsiukai);

        std::cout << "Kietekai:\n";
        isaugotiStudentuGrupe(kietekaiToSave);
    }
    else if (pasirinkimas == 2) {
        std::string nuskriaustukaiFile = pagalVidurki ? "nuskriaustukai_list_vid.txt" : "nuskriaustukai_list_med.txt";
        start = std::chrono::high_resolution_clock::now();
        std::ofstream nuskriaustukaiFailas(nuskriaustukaiFile);
        if (nuskriaustukaiFailas.is_open()) {
            nuskriaustukaiFailas << std::left << std::setw(20) << "Vardas"
                << std::setw(20) << "Pavarde"
                << std::setw(20) << "Galutinis (Vid.)"
                << "Galutinis (Med.)" << std::endl;
            nuskriaustukaiFailas << std::string(80, '-') << std::endl;
            for (const Studentas& studentas : vargsiukai) {
                nuskriaustukaiFailas << studentas;
            }
            std::cout << "Nuskriaustukai isaugoti i faila: " << nuskriaustukaiFile << std::endl;
        }
        end = std::chrono::high_resolution_clock::now();
        saveNuskriaustukaiTime = std::chrono::duration<double>(end - start).count();

        std::string kietekaiFile = pagalVidurki ? "kietekai_list_vid.txt" : "kietekai_list_med.txt";
        start = std::chrono::high_resolution_clock::now();
        std::ofstream kietekaiFailas(kietekaiFile);
        if (kietekaiFailas.is_open()) {
            kietekaiFailas << std::left << std::setw(20) << "Vardas"
                << std::setw(20) << "Pavarde"
                << std::setw(20) << "Galutinis (Vid.)"
                << "Galutinis (Med.)" << std::endl;
            kietekaiFailas << std::string(80, '-') << std::endl;
            for (const Studentas& studentas : kietekaiToSave) {
                kietekaiFailas << studentas;
            }
            std::cout << "Kietekai isaugoti i faila: " << kietekaiFile << std::endl;
        }
        end = std::chrono::high_resolution_clock::now();
        saveKietekaiTime = std::chrono::duration<double>(end - start).count();
    }

    double totalTimeList = totalPartitionTimeList + saveNuskriaustukaiTime + saveKietekaiTime;

    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Grupavimas uztruko: " << totalPartitionTimeList << " sekundziu.\n";
    std::cout << "Nuskriaustukai isaugoti per: " << saveNuskriaustukaiTime << " sekundziu.\n";
    std::cout << "Kietekai isaugoti per: " << saveKietekaiTime << " sekundziu.\n";
    std::cout << "Bendrai uztruko: " << totalTimeList << " sekundziu.\n";
}

/**
 * @brief Demonstracija su trimis studento objektais.
 *
 * Funkcija demonstruoja, kaip veikia priskyrimo operatorius ir kopijavimo konstruktorius su Studentas objektais.
 *
 * @note Funkcija sukuria studento objekta `a`, tada priskiria ji i objekta `b` ir sukuria objekta `c` naudodama kopijavimo konstruktoriumi.
 *
 * @param none
 */

void trysMetodai() {
    Studentas a;
    std::cout << "Iveskite studento informacija:\n";
    std::cin >> a;

    Studentas b;
    b = a;

    Studentas c(a);

    std::cout << "\nDemonstracija:\n";
    std::cout << "Pradinis studentas (a):\n" << a;
    std::cout << "Po priskyrimo operatoriaus (b = a):\n" << b;
    std::cout << "Po kopijavimo konstruktoriaus (c(a)):\n" << c;
}
