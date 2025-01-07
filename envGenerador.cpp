#include "envGenerador.h"


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
            personalitzacions.append(msgDades(headers, row));
        }
        file.close();
    }
}

void envGenerador::genera(const QString &outputFilePath) {
    QFile outFile(outputFilePath);
    if (outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&outFile);
        out << "Destinatari;Assumpte;Contingut\n";

        for (const msgDades& data : personalitzacions) {
            QString destinatari = model.personalize(model.destinatariTemplate, data);
            QString assumpte = model.personalize(model.assumpteTemplate, data);
            QString contingut = model.personalize(model.contingutTemplate, data);

            out << destinatari << ";" << assumpte << ";" << contingut << "\n";
        }

        outFile.close();
    }
}
