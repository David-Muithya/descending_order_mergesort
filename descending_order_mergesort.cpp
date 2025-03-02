using System;
using System.Diagnostics;

namespace MergeSortDescending
{
    internal class Program
    {
        static void Main(string[] args)
        {
            const int arrayLength = 1_000_000;

            int[] inputArray = new int[arrayLength];

            Random random = new();
            for (int i = 0; i < arrayLength; i++)
                inputArray[i] = random.Next();

            Stopwatch stopwatch = new();
            stopwatch.Start();

            PerformMergeSort(inputArray);

            stopwatch.Stop();

            // Uncomment the following lines to print the sorted array
            // for (int i = 0; i < inputArray.Length; i++)
            //     Console.Write($"{inputArray[i]}  ");

            Console.WriteLine();
            Console.WriteLine($"Sorted {arrayLength:#,#} elements in {stopwatch.Elapsed.TotalMilliseconds} milliseconds");
        }

        private static void PerformMergeSort(Span<int> arr)
        {
            if (arr.Length <= 1)
                return;

            int middle = arr.Length / 2;

            Span<int> left = arr.Slice(0, middle);
            Span<int> right = arr.Slice(middle);

            PerformMergeSort(left);
            PerformMergeSort(right);
            MergeTwoArrays(arr, left, right);
        }

        private static void MergeTwoArrays(Span<int> originalArray, Span<int> left, Span<int> right)
        {
            int leftIndex = 0, rightIndex = 0, originalIndex = 0;

            // Compare elements and place the larger one first (descending order)
            while (leftIndex < left.Length && rightIndex < right.Length)
            {
                if (left[leftIndex] >= right[rightIndex]) // Changed condition for descending order
                    originalArray[originalIndex++] = left[leftIndex++];
                else
                    originalArray[originalIndex++] = right[rightIndex++];
            }

            // Copy remaining elements from the left partition
            while (leftIndex < left.Length)
                originalArray[originalIndex++] = left[leftIndex++];

            // Copy remaining elements from the right partition
            while (rightIndex < right.Length)
                originalArray[originalIndex++] = right[rightIndex++];
        }
    }
}
