#include <algorithm>

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
