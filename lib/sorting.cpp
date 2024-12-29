#include "../inc/sorting.hpp"
#include <utility>

// Median of three method and swap low, mid, and high elements to correct position
int median_of_three(std::vector<Book>& books, int low, int high) {
    int mid = (low + high) / 2;

    if (books[low].get_id() > books[mid].get_id()) std::swap(books[low], books[mid]);
    if (books[mid].get_id() > books[high].get_id()) std::swap(books[mid], books[high]);
    if (books[low].get_id() > books[mid].get_id()) std::swap(books[low], books[mid]);

    std::swap(books[mid], books[high]);

    return high;
}

// Partition the array, and return pivot's index
int partition(std::vector<Book>& books, int low, int high) {
    // Get the pivot value
    int pivot_value = books[high].get_id();
    int i = low - 1;

    for (int j = low; j <= high - 1; ++j) {
        if (books[j].get_id() < pivot_value) {
            i++;
            std::swap(books[i], books[j]);
        }
    }

    // Swap pivot to its correct position
    std::swap(books[i+1], books[high]);
    return i + 1;
}

void quick_sort(std::vector<Book>& books, int low, int high) {
    if (low < high) {
       int pivot_idx = median_of_three(books, low, high);
       int pivot_location = partition(books, low, high);
       quick_sort(books, low, pivot_location - 1);
       quick_sort(books, pivot_location + 1, high);
    }
}
