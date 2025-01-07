#ifndef ENVMODEL_H
#define ENVMODEL_H

#include "msgDades.h"
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>

/**
 * @class envModel
 * @brief Representa un model per personalitzar dades basat en plantilles.
 *
 * Aquesta classe carrega un fitxer de plantilles i permet personalitzar
 * els textos substituint placeholders amb dades proporcionades.
 */
class envModel {
public:
    /**
     * @brief Plantilla per al destinatari del correu.
     *
     * Aquesta plantilla conté placeholders que seran substituïts amb dades reals.
     */
    QString destinatariTemplate;

    /**
     * @brief Plantilla per a l'assumpte del correu.
     */
    QString assumpteTemplate;

    /**
     * @brief Plantilla per al contingut del correu.
     */
    QString contingutTemplate;

    /**
     * @brief Constructor que carrega les plantilles des d'un fitxer.
     *
     * El fitxer de plantilles ha de tenir les següents línies:
     * - Primera línia: Plantilla del destinatari.
     * - Segona línia: Plantilla de l'assumpte.
     * - Restant: Plantilla del contingut.
     *
     * @param filePath Ruta del fitxer de plantilles.
     */
    envModel(const QString& filePath);

    /**
     * @brief Personalitza un text substituint placeholders amb dades.
     *
     * Aquesta funció substitueix els placeholders en forma `{camp}` pel
     * valor corresponent al camp dins de l'objecte `PersonalizationData`.
     *
     * @param templateText Text que conté placeholders a substituir.
     * @param data Objecte `PersonalizationData` amb les dades per substituir.
     * @return El text personalitzat amb els placeholders substituïts.
     */
    QString personalize(const QString& templateText, const msgDades& data) const;
};


#endif // ENVMODEL_H
