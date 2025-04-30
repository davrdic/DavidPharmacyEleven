#pragma once

#include <QString>
#include <QVariantMap>
#include "customerdto.h"
#include "stringutils.h"

/**
 * @brief Adapter class to convert UI data into CustomerDTO objects.
 */
class CustomerUIAdapter {
public:
    /**
     * @brief Create a CustomerDTO from a QVariantMap.
     * @param map The map containing customer data.
     * @param nameOverride Optional name override.
     * @param doctorIdOverride Optional doctor ID override.
     * @return A populated CustomerDTO.
     */
    static CustomerDTO fromVariantMap(const QVariantMap& map, const QString& nameOverride = "", int doctorIdOverride = -1) {
        CustomerDTO dto;
        dto.id = map.contains("id") ? map["id"].toInt() : 0;
        dto.name = !nameOverride.isEmpty() ? StringUtils::toStdString(nameOverride)
                                           : StringUtils::toStdString(map["name"].toString());
        dto.doctor.id = doctorIdOverride > 0 ? doctorIdOverride : map["doctor_id"].toInt();
        return dto;
    }
};
