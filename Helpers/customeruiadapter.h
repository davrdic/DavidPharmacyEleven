#ifndef CUSTOMERUIADAPTER_H
#define CUSTOMERUIADAPTER_H

#include <QString>
#include <QVariantMap>
#include "customerdto.h"
#include "stringutils.h"

class CustomerUIAdapter {
public:
    static CustomerDTO fromVariantMap(const QVariantMap& map, const QString& nameOverride = "", int doctorIdOverride = -1) {
        CustomerDTO dto;
        dto.id = map.contains("id") ? map["id"].toInt() : 0;
        dto.name = !nameOverride.isEmpty() ? StringUtils::toStdString(nameOverride)
                                           : StringUtils::toStdString(map["name"].toString());
        dto.doctor.id = doctorIdOverride > 0 ? doctorIdOverride : map["doctor_id"].toInt();
        return dto;
    }
};

#endif // CUSTOMERUIADAPTER_H
