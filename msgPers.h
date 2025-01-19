#ifndef MSG_PERS_H
#define MSG_PERS_H

#include <QString>
#include <QMap>
#include <QStringList>

/**
 * @class msgPers
 * @brief És la part del missatge que es personalitza, és a dir, assumpte, destinarari i contingut.
 *
 * Aquesta classe emmagatzema les dades d'un missateg que han estat credes pel generador, és a dir,
 * un element de la combinació de model+dades. Juntament amb el remitent i el adjunts (que són fixes)
 * formen les dades del missatge complet.
 */
class msgPers {
public:    
    /**
     * @brief Assumpte.
     *
     * Aquest atribut és l'assumpte un cop ja ha estat personalitzat.
     */
    QString assumpte;


    /**
     * @brief Destinatari.
     *
     * L'adreça de correu electrònic del destinatari concret
     *      */
    QString destinartari;

    /**
     * @brief Contingut.
     *
     * El contingut del missatge ja personalitzat
     *
     */
    QString contingut;
};

#endif // MSG_PERS_H
