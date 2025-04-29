#pragma once

#include <vector>
#include <algorithm>

template <typename T>
class SortingUtils {
public:

    static void sortVectorByDTOName(std::vector<T>& list, bool ascending = true) {
        std::sort(list.begin(), list.end(), [ascending](const T& a, const T& b) {
            if (ascending) {
                return a.name < b.name;
            } else {
                return a.name > b.name;
            }
        });
    }
};
