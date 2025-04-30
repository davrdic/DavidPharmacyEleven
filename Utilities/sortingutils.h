#include <algorithm>

// PURE C++ ONLY - TODO - Mark all files that are C++ only and mild restructure to separate the files into marked folders.

template <typename T>
class SortingUtils {
public:
    template <typename KeySelector>
    static void sortBy(std::vector<T>& list, KeySelector selector, bool ascending = true) {
        std::sort(list.begin(), list.end(), [=](const T& a, const T& b) {
            return ascending ? selector(a) < selector(b) : selector(a) > selector(b);
        });
    }
};
