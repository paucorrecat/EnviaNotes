#ifndef MSG_DADES_H
#define MSG_DADES_H

#include <QString>
#include <QMap>
#include <QStringList>

/**
 * @class msgDades
 * @brief Representa una fila d'un fitxer CSV amb camps dinàmics.
 *
 * Aquesta classe emmagatzema les dades d'una fila d'un fitxer CSV com un mapa
 * dinàmic de parelles "nom del camp" -> "valor". És útil per gestionar dades
 * personalitzades amb noms de camp variables.
 */
class msgDades {
public:
    /**
     * @brief Mapa de camps dinàmics.
     *
     * Aquest atribut emmagatzema les parelles "nom del camp" -> "valor".
     */
    QMap<QString, QString> fields;


    /**
     * @brief Constructor que inicialitza els camps dinàmics des de les
     * capçaleres i la fila.
     *
     * @param headers Llista dels noms dels camps (capçaleres del CSV).
     * @param row Llista de valors corresponents a una fila del CSV.
     *
     * Cada camp de les capçaleres s'associa amb el valor corresponent de la
     * fila. Si la fila no conté prou valors, els camps restants s'inicialitzen
     * com a cadenes buides.
     */
    msgDades(const QStringList& headers, const QStringList& row);

    /**
     * @brief Obté el valor associat a un camp específic.
     *
     * @param fieldName El nom del camp que es vol obtenir.
     * @return El valor associat al camp especificat o una cadena buida si el camp no existeix.
     */
    QString getField(const QString& fieldName) const;
};

#endif // MSG_DADES_H
