// Implement the Heap/Shell sort algorithm implemented in Java demonstrating heap/shell data
// structure with modularity of programming language
import java.util.*;
public class ass5 {
    public static void heapify(int[] arr, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;  // Left child
        int right = 2 * i + 2; // Right child
        if (left < n && arr[left] > arr[largest]) { // Check if left child is larger than root
            largest = left;
        }
        if (right < n && arr[right] > arr[largest]) { // Check if right child is larger than the largest so far

            largest = right;
        }
        if (largest != i) { // If largest is not root, swap and heapify the affected subtree
            swap(arr, i, largest);
            heapify(arr, n, largest);
        }
    }

    public static void buildHeap(int[] arr, int n) {   // Function to build a Max Heap
        for (int i = n / 2 - 1; i >= 0; i--) { // Start from the last non-leaf node and heapify each node
            heapify(arr, n, i);
        }
    }

    public static void heapSort(int[] arr) {
        int n = arr.length;
        buildHeap(arr, n);
        for (int i = n - 1; i >= 1; i--) { // One by one extract elements from the heap
            swap(arr, 0, i); // Move current root to end
            heapify(arr, i, 0);  // Call heapify on the reduced heap
        }
    }
    public static void swap(int[] arr, int i, int j) { // Utility function to swap two elements
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }

    public static void printArray(int[] arr) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    public static void main(String[] args) {
        int[] arr = {4, 10, 3, 5, 1};
        System.out.println("Original Array:");
        printArray(arr);

        heapSort(arr);
        System.out.println("Sorted Array using Heap Sort:");
        printArray(arr);
    }
}