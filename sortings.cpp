#include <iostream>

using namespace std;

//returns first index where a match is found
//returns -1 if no patch found
int search(int num, int arr[], int size)
{
	for(int i = 0; i < size; ++i)
	{
		if(arr[i] == num)
			return i;
	}
	return -1;
}

//writes in-place by swapping
void selection_sort(int *arr, int size, int start = 0)
{
	//exit when we're done
	if(start == size)
		return;
	
	//start by assuming the first element (arr[0]) is the minimum
	int min = start;
	for(int i = start + 1; i < size; ++i)
	{
		//if we have found a new minimum
		if(arr[i] < arr[min])
		{
			min = i;
			//cout<<"new minimum: "<<arr[min]<<endl;
		}
	}
	
	//if there is a new minimum, push it into place by swapping it with its previous location
	if(min != start)
	{
		int temp = arr[min];
		arr[min] = arr[start];
		arr[start] = temp;
	}
	
	selection_sort(arr, size, start+1);
}

void bubble_sort(int arr[], int size)
{
	bool swapped = false; //if no swaps occur, then the list is sorted
	for(int i = 0; i < size - 1; ++i)
	{
		if(arr[i] > arr[i + 1])
		{
			int temp = arr[i + 1];
			arr[i + 1] = arr[i];
			arr[i] = temp;
			swapped = true;
		}
	}
	if(swapped)
		bubble_sort(arr, size); //keep going until no swaps are reported
}

int choosePivot(int arr[], int start, int end)
{
	//project guidelines. :^)
	return arr[start];
}

//adapted from Hoare's partition scheme
int partition(int arr[], int start, int end)
{
	int i = start - 1;
	int j = end + 1;
	int pivot = choosePivot(arr, start, end);
	
	while(true) //keep sorting until the two sub-arrays overlap, then stop
	{
		/*for(int k = start; k < end; ++k) {
			cout<<arr[k]<<" ";
		}
		cout<<endl;*/
		
		do
		{
			i++; //keep traversing the left of the array, find a value that should go on the other side
		}
		while(arr[i] < pivot); //(if the value is on the correct side, keep going)
		
		do
		{
			j--; //traverse the right of the array, find any value that should go on the other side
		}
		while(arr[j] > pivot);
		
		if(i < j) //if the two values are on the wrong side, and the sides don't overlap, swap them
		{
			//cout<<"swap"<<endl;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
		else
		{
			return j;
		}
	}
}

void quick_sort(int arr[], int start, int end)
{
	if(start < end) //safety check
	{
		int p = partition(arr, start, end);
		//repeat above process across sub-arrays
		quick_sort(arr, start, p);
		quick_sort(arr, p+1, end);
	}
}



void insertion_sort(int arr[], int size, int &counter, int index = 1)
{
	if(index == size - 1)
		return;
	
	int i = index;
	//loop from the current index to the start of the array, 
	//swap elements if they are out of order
	while(i > 0 && arr[i - 1] > arr[i])
	{
		counter++;
		int temp = arr[i - 1];
		arr[i - 1] = arr[i];
		arr[i] = temp;
		i--;
	}
	//repeat until we've traversed the entire array
	insertion_sort(arr, size, counter, index+1);
}


void merge(int arr[], int start, int midpoint, int end, int &counter)
{
	int i, j, k; //iterators
	int length1 = midpoint - start + 1; //length of left-facing sub-array
	int length2 = end - midpoint; //length of right-facing sub-array
	
	int arr_l[length1], arr_r[length2];
	
	//fill the sub-arrays with their respective content
	for(i = 0; i < length1; ++i)
		arr_l[i] = arr[start + i];
	for(j = 0; j < length2; ++j)
		arr_r[j] = arr[(midpoint + 1) + j];
		
	i = 0; //reset iterators
	j = 0;
	k = start;
	
	//iterate through the master array, until both sub-arrays are exhausted
	while(i < length1 && j < length2)
	{
		//place an element into the master array
		//depending on which subarray is smaller, 
		//keep doing this until the other is smaller
		//then go back and repeat but with the subarrays reversed
		counter++;
		if(arr_l[i] <= arr_r[j])
		{
			arr[k] = arr_l[i];
			i++;
		}
		else
		{
			arr[k] = arr_r[j];
			j++;
		}
		k++;
	}
	
	//copy down the remaining elements to the end of the array
	while(i < length1)
	{
		arr[k] = arr_l[i];
		i++;
		k++;
	}
	
	while(j < length2)
	{
		arr[k] = arr_r[j];
		j++;
		k++;
	}
}

void merge_sort(int arr[], int start, int end, int &counter)
{
	if(start < end)
	{
		int midpoint = start + (end - start)/2;
		merge_sort(arr, start, midpoint, counter);
		merge_sort(arr, midpoint + 1, end, counter);
		merge(arr, start, midpoint, end, counter);
	}
}


int main(int argc, char **argv)
{
	
	int array1[5] = {10, 7, 11, 5, 12}; //selection sort
	int array2[5] = {10, 7, 11, 5, 12}; //bubble sort
	int array3[5] = {10, 7, 11, 5, 12}; //quick sort
	
	cout<<"Selection sort"<<endl;
	selection_sort(array1, 5);
	for(int i : array1)
		cout<<i<<endl;
		
	cout<<"Bubble sort"<<endl;
	bubble_sort(array2, 5);
	for(int i : array2)
		cout<<i<<endl;
		
	cout<<"Quick sort"<<endl;
	quick_sort(array3, 0, 5);
	for(int i : array3)
		cout<<i<<endl;
		
	
	int iarray1[5] = {10, 7, 11, 5, 12}; //the i stands for 'insertion'
	int iarray2[10] = {10, 7, 11, 5, 12, 28, 2, 3, 47, 23};
	int iarray3[30] = {10, 7, 11, 5, 12, 28, 2, 3, 47, 23,
											46, 62, 49, 39, 26, 1, 35, 9, 13, 4,
											67, 83, 54, 90, 24, 25, 68, 6, 8, 14
										};
										
	int marray1[5] = {10, 7, 11, 5, 12}; //the m stands for 'merge'
	int marray2[10] = {10, 7, 11, 5, 12, 28, 2, 3, 47, 23};
	int marray3[30] = {10, 7, 11, 5, 12, 28, 2, 3, 47, 23,
											46, 62, 49, 39, 26, 1, 35, 9, 13, 4,
											67, 83, 54, 90, 24, 25, 68, 6, 8, 14
										};
	
	cout<<"Insertion sort & Merge sort"<<endl;
	int insertion_counter = 0;
	int merge_counter = 0;
	insertion_sort(iarray1, 5, insertion_counter);
	merge_sort(marray1, 0, 4, merge_counter);
	cout<<"Number of comparisons for insertion sort at  5 elements: "<<insertion_counter<<endl;
	cout<<"Number of comparisons for merge sort at 5 elements: "<<merge_counter<<endl;
	
	insertion_counter = 0;
	merge_counter = 0;
	insertion_sort(iarray2, 10, insertion_counter);
	merge_sort(marray2, 0, 9, merge_counter);
	cout<<"Number of comparisons for insertion sort at  10 elements: "<<insertion_counter<<endl;
	cout<<"Number of comparisons for merge sort at 10 elements: "<<merge_counter<<endl;
	
	insertion_counter = 0;
	merge_counter = 0;
	insertion_sort(iarray3, 30, insertion_counter);
	merge_sort(marray3, 0, 29, merge_counter);
	cout<<"Number of comparisons for insertion sort at  30 elements: "<<insertion_counter<<endl;
	cout<<"Number of comparisons for merge sort at 30 elements: "<<merge_counter<<endl;
	
	cout<<"merge sort becomes faster than insertion sort between 10 and 30 elements."<<endl;
	
	return 0;
}