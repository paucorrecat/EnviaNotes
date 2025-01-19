#include "envGenerador.h"

#include <QMessageBox>


envGenerador::envGenerador(const QString &templateFilePath) : model(templateFilePath) {}

void envGenerador::llegeixDades(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString headerLine = in.readLine();
        QStringList headers = headerLine.split(';');

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList row = line.split(';');
            dadesCombinacio.append(msgDades(headers, row));
        }
        file.close();
    }
}

void envGenerador::genera() {

    if (totOk()) {
        QFile outFile(SORTIDA_LOG);
        if (outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&outFile);
            out << "Destinatari;Assumpte;Contingut\n";
            missatges.clear();
            for (const msgDades& data : dadesCombinacio) {
                // Crear un nou objecte msgPers
                msgPers nouMissatge;
                // Assignar els valors als atributs
                nouMissatge.destinartari = model.personalize(model.destinatariTemplate, data);
                nouMissatge.assumpte = model.personalize(model.assumpteTemplate, data);
                nouMissatge.contingut = model.personalize(model.contingutTemplate, data);
                missatges.append(nouMissatge);
                out <<  nouMissatge.destinartari << ";" <<
                        nouMissatge.assumpte << ";" <<
                        nouMissatge.contingut << "\n";
            }

            outFile.close();
        }
    } else {
        QString missatge;
        if (!HiHaModel()) {
            missatge = "És necessari que hi hagi un model.";
        } else if (!HiHaDades()) {
            missatge = "És necessari llegir dades.";
        }

        QMessageBox::warning(nullptr, "Error", missatge);
    }

}

void envGenerador::genera(const QString &outputFilePath) {

    if (totOk()) {
        QFile outFile(outputFilePath);
        if (outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&outFile);
            out << "Destinatari;Assumpte;Contingut\n";
            missatges.clear();
            for (const msgDades& data : dadesCombinacio) {
                // Crear un nou objecte msgPers
                msgPers nouMissatge;
                // Assignar els valors als atributs
                nouMissatge.destinartari = model.personalize(model.destinatariTemplate, data);
                nouMissatge.assumpte = model.personalize(model.assumpteTemplate, data);
                nouMissatge.contingut = model.personalize(model.contingutTemplate, data);
                missatges.append(nouMissatge);
                out <<  nouMissatge.destinartari << ";" <<
                    nouMissatge.assumpte << ";" <<
                    nouMissatge.contingut << "\n";
            }

            outFile.close();
        }
    } else {
        QString missatge;
        if (!HiHaModel()) {
            missatge = "És necessari que hi hagi un model.";
        } else if (!HiHaDades()) {
            missatge = "És necessari llegir dades.";
        }

        QMessageBox::warning(nullptr, "Error", missatge);
    }

}

bool envGenerador::HiHaModel() const {
    // Comprova si les plantilles del model no són buides
    return !model.destinatariTemplate.isEmpty() ||
           !model.assumpteTemplate.isEmpty() ||
           !model.contingutTemplate.isEmpty();
}

bool envGenerador::HiHaDades() const {
    // Comprova si la llista de dades de combinació no està buida
    return !dadesCombinacio.isEmpty();
}

bool envGenerador::totOk() const {
    // Comprova si la llista de dades de combinació no està buida
    return (HiHaModel() && HiHaDades());
}
