#ifndef ENV_GENERADOR_H
#define ENV_GENERADOR_H

#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>
#include "msgDades.h"
#include "envModel.h"

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
    QList<msgDades> personalitzacions;

    /**
     * @brief model de plantilla utilitzat per generar els emails.
     */
    envModel model;

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
     * @param outputFilePath Ruta del fitxer on es guardarà la sortida generada.
     */
    void genera(const QString& outputFilePath);
};

#endif // ENV_GENERADOR_H
