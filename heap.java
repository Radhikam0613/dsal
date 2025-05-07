// Implement the Heap/Shell sort algorithm implemented in Java demonstrating heap/shell data
// structure with modularity of programming language
// heapify int[] arr, int n, int i
// heapSort int[] arr
// printArray int[] arr
class HeapSort {
    static void heapify(int arr[], int n, int i) {
        int largest = i;       // Initialize largest as root
        int left = 2 * i + 1;  // Left child index
        int right = 2 * i + 2; // Right child index
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
        if (largest != i) {
            int temp = arr[i];
            arr[i] = arr[largest];
            arr[largest] = temp;
            heapify(arr, n, largest); // Recursively fix the heap
        }
    }

    static void heapSort(int arr[]) {
        int n = arr.length;
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }
        for (int i = n - 1; i > 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            heapify(arr, i, 0);
        }
    }

    static void printArray(int arr[]) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    public static void main(String args[]) {
        int arr[] = {45, 12, 23, 6, 89, 34}; // Predefined array
        System.out.println("Original array:");
        printArray(arr);
        heapSort(arr); // Sort the array
        System.out.println("Sorted array:");
        printArray(arr);
    }
}
