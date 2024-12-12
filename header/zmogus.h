/**
 * @file Zmogus.h
 * @brief Apraso abstrakcia baze klase `Zmogus`.
 *
 * Cia aprasoma abstrakti klase `Zmogus`, kuri naudojama paveldejimui ir
 * suteikia bazines savybes bei metodus zmogui aprasyti. Ji yra pagrindas
 * kitoms isvestinems klasems, tokioms kaip `Studentas`.
 */

#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <string>

 /**
  * @class Zmogus
  * @brief Abstrakti baze klase zmogui aprasyti.
  *
  * Klase `Zmogus` apibrezia bendrus atributus ir funkcionaluma, kuris yra
  * paveldimas isvestinese klaseje. Ji yra abstrakti, todel negalima sukurti
  * `Zmogus` klase objektu tiesiogiai.
  */
class Zmogus {
protected:
    std::string vardas; ///< Zmogaus vardas.
    std::string pavarde; ///< Zmogaus pavarde.

public:
    /**
     * @brief Numatytojo konstruktoriaus deklaracija.
     *
     * Inicializuoja varda ir pavarde kaip tuscias eilutes.
     */
    Zmogus() : vardas(""), pavarde("") {}

    /**
     * @brief Konstruktorius su parametrais.
     * @param v Vardas.
     * @param p Pavarde.
     *
     * Inicializuoja `vardas` ir `pavarde` nurodytomis reiksmes.
     */
    Zmogus(const std::string& v, const std::string& p) : vardas(v), pavarde(p) {}

    /**
     * @brief Virtualus destruktorius.
     *
     * Uztikrina teisinga paveldetos klases istekliu valyma.
     */
    virtual ~Zmogus() {}

    /**
     * @brief Grynai virtuali funkcija, skirta informacijai isvesti.
     *
     * Si funkcija turi buti igyvendinta isvestinese klaseje.
     */
    virtual void printInfo() const = 0;

    /**
     * @brief Grazina zmogaus varda.
     * @return Zmogaus vardas.
     */
    virtual std::string getVardas() const { return vardas; }

    /**
     * @brief Nustato zmogaus varda.
     * @param v Naujasis vardas.
     */
    virtual void setVardas(const std::string& v) { vardas = v; }

    /**
     * @brief Grazina zmogaus pavarde.
     * @return Zmogaus pavarde.
     */
    virtual std::string getPavarde() const { return pavarde; }

    /**
     * @brief Nustato zmogaus pavarde.
     * @param p Naujaja pavarde.
     */
    virtual void setPavarde(const std::string& p) { pavarde = p; }
};

#endif // ZMOGUS_H
