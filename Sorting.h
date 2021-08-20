#ifndef SORTING
#define SORTING

#include <vector>

#define RADIX_BASE 10

template <class T>
class Sorting {

    static void Merge(int low, int mid, int high, std::vector<T> & arr) {

        int left_size = mid - low + 1;
        int right_size = high - mid;

        std::vector<T> left_arr(left_size, 0);
        std::vector<T> right_arr(right_size, 0);

        for (int i = 0; i < left_size; i++)
        {
            left_arr[i] = arr[i + low];
        }

        for (int i = 0; i < right_size; i++)
        {
            right_arr[i] = arr[i + mid + 1];
        }

        int i = 0;
        int j = 0;
        int k = low;

        for (; i < left_size && j < right_size; k++)
        {
            if (left_arr[i] < right_arr[j])
            {
                arr[k] = left_arr[i];
                i++;
            }
            else
            {
                arr[k] = right_arr[j];
                j++;
            }
        }

        for (; j < right_size; j++, k++)
        {
            arr[k] = right_arr[j];
        }

        for (; i < left_size; i++, k++)
        {
            arr[k] = left_arr[i];
        }
    }

    static void MergeSortSubArray(int low, int high, std::vector<T> & arr) {
        if (low < high)
        {

            int mid = (low + high) / 2;

            MergeSortSubArray(low, mid, arr);
            MergeSortSubArray(mid + 1, high, arr);

            Merge(low, mid, high, arr);
        }
    }

    static int Partition(int low, int high, std::vector<T> & arr) {
        int pivot_value = arr[high];
        int pivot_point = low;
        for (int j = low; j < high; j++)
        {
            if (arr[j] < pivot_value)
            {
                swap(arr[pivot_point], arr[j]);
                pivot_point++;
            }
        }
        swap(arr[pivot_point], arr[high]);
        return pivot_point;
    }

    static void QuickSortSubArray(int low, int high, std::vector<T> & arr) {
        if (low < high)
        {
            int pivot = Partition(low, high, arr);

            QuickSortSubArray(low, pivot - 1, arr);
            QuickSortSubArray(pivot + 1, high, arr);
        }
    }

public:

    static void QuickSort(std::vector<T> & arr) {
        int size = arr.size();
        QuickSortSubArray(0, size - 1, arr);
    }

    static void MergeSort(std::vector<T> & arr) {
        int size = arr.size();
        MergeSortSubArray(0, size - 1, arr);
    }

    static void InsertionSort(std::vector<T> & arr) {
        int size = arr.size();

        for (int i = 0; i < size; i++)
        {
            for (int j = i; j > 0 && arr[j] < arr[j - 1]; j--)
            {
                swap(arr[j], arr[j - 1]);
            }
        }
    }

    static void SelectionSort(std::vector<T> & arr) {
        int size = arr.size();

        for (int i = 0; i < size; i++)
        {
            int min_idx = i;
            for (int j = i; j < size; j++)
            {
                if (arr[j] < arr[min_idx])
                {
                    min_idx = j;
                }
            }
            swap(arr[i], arr[min_idx]);
        }
    }

    static void BubbleSort(std::vector<T> & arr) {
        int size = arr.size();

        bool swapped;
        do
        {
            swapped = false;
            for (int i = 1; i < size; i++)
            {
                if (arr[i] < arr[i - 1])
                {
                    swap(arr[i], arr[i - 1]);
                    swapped = true;
                }
            }

        } while (swapped);
    }

    static void RadixSort(std::vector<T> & arr) {
        int size = arr.size();
        std::vector<T> sorted(size, 0);

        T max_val = std::numeric_limits<T>::min();
        for (const auto & val : arr)
        {
            max_val = std::max(max_val, val);
        }

        for (int divisor = 1; (max_val / divisor) > 0; divisor *= RADIX_BASE)
        {
            std::vector<T> count(RADIX_BASE, 0);

            for (int i = 0; i < size; i++)
            {
                T least_signif_digit = (arr[i] / divisor) % 10;
                count[least_signif_digit]++;
            }

            for (int i = 1; i < size; i++)
            {
                count[i] += count[i - 1];
            }

            for (int i = size - 1; i >= 0; i--)
            {
                T least_signif_digit = (arr[i] / divisor) % 10;
                int pos = count[least_signif_digit] - 1;
                sorted[pos] = arr[i];
                count[least_signif_digit]--;
            }

            for (int i = 0; i < size; i++)
            {
                arr[i] = sorted[i];
            }
        }
    }

};

#endif
