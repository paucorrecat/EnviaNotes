#include "envModel.h"


envModel::envModel(const QString &filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        destinatariTemplate = in.readLine();
        assumpteTemplate = in.readLine();
        contingutTemplate = in.readAll();
        file.close();
    }
}

QString envModel::personalize(const QString &templateText, const msgDades &data) const {
    QString result = templateText;
    static const QRegularExpression regex("\\{([^}]+)\\}");
    // Explicació:
    //   \\{: Busca una { literal (cal escapar el caràcter amb \\).
    //   ([^}]+): Busca qualsevol seqüència de caràcters (excepte }) i l'emmagatzema com a grup capturat.
    //   \\}: Busca una } literal.
    QRegularExpressionMatch match; //s'utilitzarà per emmagatzemar cada coincidència trobada amb el regex.

    while ((match = regex.match(result)).hasMatch()) {
        QString placeholder = match.captured(1); // El contingut entre claus {}
        QString replacement = data.getField(placeholder);
        result.replace(match.capturedStart(0), match.capturedLength(0), replacement);
    }


    return result;
}
