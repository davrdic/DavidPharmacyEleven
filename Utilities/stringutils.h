#pragma once

#include <QString>
#include <string>

namespace StringUtils {

    inline std::string toStdString(const QString& qstr) {
        return qstr.toStdString();
    }

    inline QString toQString(const std::string& str) {
        return QString::fromStdString(str);
    }
}
