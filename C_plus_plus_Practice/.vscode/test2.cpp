#include <iostream>
#include <vector>
using namespace std;

/* Function to print an array */
void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// } Driver Code Ends
class Solution
{
    public:
    //Function to sort an array using quick sort algorithm.
    void quickSort(int arr[], int low, int high)
    {
        // code here
        if(low>=high) return;
        
        int part_index=partition(arr,low,high);
        
        quickSort(arr, low, part_index-1);
        quickSort(arr, part_index+1, high);
    }
    
    public:
    int partition (int arr[], int low, int high)
    {
       // Your code here
       int pivot=high;
       int l=low, r=high;
       
       while(l<r){
           if(arr[l]<=arr[pivot]) {l++; continue;}
           else {
               while(l<r){
                   if(arr[r]>=arr[pivot]){r--; continue;}
                   else { swap(arr[l],arr[r]); }
               }
           }
       }
       swap(arr[l],arr[pivot]);
       return l;
    }
};


//{ Driver Code Starts.
int main()
{
    int arr[1000],n,T,i;
    scanf("%d",&T);
    while(T--){
    scanf("%d",&n);
    for(i=0;i<n;i++)
      scanf("%d",&arr[i]);
      Solution ob;
    ob.quickSort(arr, 0, n-1);
    printArray(arr, n);
    }
    return 0;
}
// } Driver Code Ends