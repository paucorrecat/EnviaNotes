#include "msgDades.h"


msgDades::msgDades(const QStringList &headers, const QStringList &row) {
    for (int i = 0; i < headers.size(); ++i) {
        fields[headers[i]] = i < row.size() ? row[i] : "";
    }
}

QString msgDades::getField(const QString &fieldName) const {
    return fields.value(fieldName, "");
}
