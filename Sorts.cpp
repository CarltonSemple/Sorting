#include <vector>

namespace Sorting
{
	template<typename T>
	class Sorts
	{
		static void swapvals(T &val1, T &val2)
		{
			T temp = val1;
			val1 = val2;
			val2 = temp;
		}

		static void reverse(std::vector<T> &arr)
		{
			int l = 0, u = arr.size() - 1;

			while (l < u)
			{
				swapvals(arr[l], arr[u]);
				l++;
				u--;
			}
		}

		// quicksort
		static int partition(std::vector<T> &arr, int l, int r)
		{
			int i = l - 1, j = l;

			while (j < r)
			{
				if (arr[j] <= arr[r])
				{
					i++;
					swapvals(arr[j], arr[i]);	// swap a[i] & a[j]
				}
				j++;
			}
			
			swapvals(arr[i + 1], arr[r]);

			return i + 1;
		}

		// merge sort
		static void merge(std::vector<T> &arr, int l, int mid, int r)
		{
			std::vector<T> left, right;

			for (int i = l; i <= mid; i++)
				left.push_back(arr[i]);
			for (int i = mid + 1; i <= r; i++)
				right.push_back(arr[i]);

			int index = l, i = 0, j = 0;
			while (index <= r)
			{
				if (i == left.size())
				{
					if (j != right.size())
					{
						arr[index] = right[j];
						j++;
					}
				}
				else if (j == right.size())
				{
					if (i != left.size())
					{
						arr[index] = left[i];
						i++;
					}
				}
				else if (left[i] <= right[j])
				{
					arr[index] = left[i];
					i++;
				}
				else
				{
					arr[index] = right[j];
					j++;
				}
				index++;
			}
		}

		// heap
		static void max_heapify(std::vector<T> &arr, int heapSize, int index)
		{
			int largest;				// index of the largest of the 'node' & its child nodes
			int left = 2 * index + 1, right = 2 * index + 2;

			if (left < heapSize && arr[left] > arr[index])
				largest = left;			// left child is largest so far
			else
				largest = index;		// current node is largest so far

			if (right < heapSize && arr[right] > arr[largest])
				largest = right;		// right child is largest

			if (largest != index)		// if current node isn't the largest
			{
				swapvals(arr[largest], arr[index]);		// swap with the largest node
				max_heapify(arr, heapSize, largest);	// call heapify on the lower node
			}
		}

	public:
		// Quicksort
		static void quicksort(std::vector<T> &arr, int l, int r)
		{
			if (l >= r)
				return;

			int index = partition(arr, l, r);

			quicksort(arr, l, index - 1);		// left
			quicksort(arr, index + 1, r);		// right
		}

		// Merge sort
		static void mergesort(std::vector<T> &arr, int l, int r)
		{
			if (l >= r)
				return;

			int mid = (l + r) / 2;

			mergesort(arr, l, mid);		// left
			mergesort(arr, mid + 1, r);	// right
			merge(arr, l, mid, r);
		}

		// Build Heap
		static void build_maxHeap(std::vector<T> &arr, int heapSize)
		{
			for (int i = (heapSize / 2); i >= 0; i--)
				max_heapify(arr, heapSize, i);		// call heapify to build, bottom-up
		}

		// Heap Sort
		static void heap_sort(std::vector<T> &heap)
		{
			int size = heap.size();

			while (size > 0)
			{
				extract_max(heap, size);
				size--;
			}
		}

	};

	template<typename SequenceContainer>
	class SortingT
	{
	public:
		// Merge sort iterative
		static void mergesort_i(SequenceContainer &arr)
		{
			for (int j = 0; j < arr.size() / 2; j++)	// must do the inner loops size/2 times
				for (int i = 1; i <= (arr.size() / 2) + 1; i *= 2)
				for (int m = i; m < arr.size(); m += 2 * i)
				{
					int r;
					((m + i) < arr.size()) ? r = (m + i) : r = arr.size() - 1;
					merge(arr, (m - i), m, r);
				}
		}

	private:
		// merge sort
		static void merge(SequenceContainer &arr, int l, int mid, int r)
		{
			SequenceContainer left, right;				// two sub-lists

			for (int i = l; i <= mid; i++)
				left.push_back(std::move(arr[i]));				// create left list
			for (int i = mid + 1; i <= r; i++)
				right.push_back(std::move(arr[i]));			// create right list


			int index = l, i = 0, j = 0;
			while (index <= r)						// merge the two lists
			{
				if (i == left.size())
				{
					if (j != right.size())
					{
						arr[index] = std::move(right[j]);
						j++;
					}
				}
				else if (j == right.size())
				{
					if (i != left.size())
					{
						arr[index] = std::move(left[i]);
						i++;
					}
				}
				else if (*left[i] <= *right[j])
				{
					arr[index] = std::move(left[i]);
					i++;
				}
				else
				{
					arr[index] = std::move(right[j]);
					j++;
				}
				index++;
			}
		}

	};
}