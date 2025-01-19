#ifndef ENV_GENERADOR_H
#define ENV_GENERADOR_H

#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>
#include "msgDades.h"
#include "envModel.h"
#include "msgPers.h"

#define SORTIDA_LOG "log_sortida.csv"

/**
 * @class envGenerador
 * @brief Gestiona el procés de generació d'emails personalitzats.
 *
 * Aquesta classe permet carregar dades de personalització des d'un fitxer CSV,
 * generar textos personalitzats basats en un model i escriure els resultats
 * en un fitxer de sortida.
 */
class envGenerador {
public:
    /**
     * @brief Llista de dades de personalització carregades des d'un fitxer CSV.
     */
    QList<msgDades> dadesCombinacio;
    /**
     * @brief Comprova si hi ha dades carregades.
     * @return Cert si hi ha dades carregades; fals en cas contrari.
     */
    bool HiHaDades() const;

    /**
     * @brief Llista de missatges personalitzats.
     *
     * Només la part personalitzada:
     * Assumpte, Destinatari i Contingut
     * A envGenerador s'hi guarda la versió original. Normalment aquesta copia passarà
     * al gestor d'enviaments on es podrà editar
     *
     */
    QList<msgPers> missatges;


    /**
     * @brief model de plantilla utilitzat per generar els emails.
     */
    envModel model;

    /**
     * @brief Comprova si hi ha un model carregat.
     * @return Cert si hi ha un model carregat; fals en cas contrari.
     */
    bool HiHaModel() const;

    /**
     * @brief Si és plenament funcional.
     * @return Cert si hi ha un model carregat i dades carregades; fals en cas contrari.
     */
    bool totOk() const;

    /**
     * @brief Constructor que inicialitza el model de plantilla.
     *
     * @param templateFilePath Ruta del fitxer que conté el model de plantilla.
     */
    envGenerador(const QString& templateFilePath);

    /**
     * @brief Carrega les dades de personalització des d'un fitxer CSV.
     *
     * El fitxer CSV ha de tenir una primera línia amb els noms dels camps (capçaleres).
     * És important NO deixar espai entre el ; i el nom del camp. nota1;nota2 Ok,  nota1 ; nota2 NO FUNCIONA
     * Cada línia posterior ha de contenir les dades corresponents a cada camp.
     * També separades per ; Aquí l'espai no importa excepte que el llegirà i el posarà en el missatge
     *
     * @param filePath Ruta del fitxer CSV que conté les dades de personalització.
     */
    void llegeixDades(const QString& filePath);

    /**
     * @brief Genera un fitxer amb els emails personalitzats.
     *
     * Aquesta funció personalitza el destinatari, l'assumpte i el contingut de cada email
     * utilitzant el model de plantilla i les dades carregades, i escriu el resultat
     * en un fitxer CSV de sortida.
     *
     *Si no se li passa cap paràmetre, la sortida és a SORTIDA_LOG, un #define d'aquesta capçalera
     *
     * @param outputFilePath Ruta del fitxer on es guardarà la sortida generada.
     */
    void genera(const QString& outputFilePath);
    void genera();
};

#endif // ENV_GENERADOR_H
