#ifndef SORTINGUTILS_H
#define SORTINGUTILS_H

#include <QList>
#include <QString>
#include <algorithm>

template <typename T>
class SortingUtils {
public:
    static void sortList(QList<T>& list, bool ascending = true) {
        std::sort(list.begin(), list.end(), [ascending](const T& a, const T& b) {
            if (ascending) {
                return a.name < b.name;
            } else {
                return a.name > b.name;
            }
        });
    }
};

#endif // SORTINGUTILS_H
