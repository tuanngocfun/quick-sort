/* Quicksort in either ascending or descending order, and the
 * input from the user's keyboard to prompt whether they want 
 * ascending or descending order, and also dive deep into algo*/
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

struct read{
    char first_alpha;
    int len_alpha;
};

bool check = true;

enum {INPUT_MAX = 100};

void process(int arr[]);
void user_choice(char* choice);
int user_num();
void user_input(int arr[], int arr_size);
void readArray(int arr[], int arr_size);
void swap(int* arr1, int* arr2);
int partition_desc(int arr[], int low, int high);
void quickSort_desc(int arr[], int low, int high);
int partition_asc(int arr[], int low, int high);
int partition_asc2(int arr[], int low, int high);
void quickSort_asc(int arr[], int low, int high);
void printArray(int arr[], int arr_size);
struct read getch();

int main()
{
    int arr[INPUT_MAX];

    process(arr);

    return 0;
}

void process(int arr[])
{
    char choice;
    user_choice(&choice);

    int arr_size = user_num();

    user_input(arr, arr_size);

    readArray(arr, arr_size);

    if(choice == 'A'){
        printf("The ascending order of number in array: \n");
        // Passing arr_size - 1 because array-index-counting starts from 0
        quickSort_asc(arr, 0, arr_size - 1);
        printArray(arr, arr_size);
    }
    else{
        printf("The descending order of number in array: \n");
        // Passing arr_size - 1 because array-index-counting starts from 0
        quickSort_desc(arr, 0, arr_size - 1);
        printArray(arr, arr_size);
    }
}

int user_num()
{
    int num;

    do{
        if(num <= 20 || num > 0){
            printf("Please enter the length of array: ");
            scanf("%d", &num);
            while(getchar() != '\n')
                ;
        }
    }while(num > 20 || num <= 0);

    return num;
}

void user_input(int arr[], int arr_size)
{
    int i;

    for(i = 0; i < arr_size; i++){
        printf("Please enter number in array[%d]: ", i + 1);
        scanf("%d", &arr[i]);
    }
}

void swap(int* arr1, int* arr2)
{
    int temp = *arr1;
    *arr1 = *arr2;
    *arr2 = temp;
}

// Pick first element as pivot (implemented above)
int partition_desc(int arr[], int low, int high){
    int pivot = arr[low];
    int left = low; // Index of smaller element

    for(int right = low + 1; right <= high; right++){
        // THIS CONDITION SORTS IN DESCENDING ORDER
        // If current element is larger than the pivot
        if (arr[right] > pivot){
            left++; // Increment index of smaller element
            printf("left:%d right:%d pivot:%d arr[right]:%d arr[left]:%d\n",
                    left, right, pivot, arr[right], arr[left]); // check algorithm
            swap(&arr[left], &arr[right]);
            printf("left:%d right:%d pivot:%d arr[right]:%d arr[left]:%d\n",
                    left, right, pivot, arr[right], arr[left]); // check algorithm
        }
    }
    printf("left:%d pivot:%d low:%d arr[left]:%d arr[low]:%d\n",
                    left, pivot, low, arr[left], arr[low]); // check algorithm
    swap(&arr[left], &arr[low]);
    printf("left:%d pivot:%d low:%d arr[left]:%d arr[low]:%d\n",
                    left, pivot, low, arr[left], arr[low]); // check algorithm

    //returning the position that the pivot would take in the sorted array
    return left;
}

void quickSort_desc(int arr[], int low, int high)
{
    //This condition checks whether the array contains more than 1 element
    if(low < high){
        //getting the index of the pivot after partition of the array
        int partitionPoint = partition_desc(arr, low, high);

        // Recursive of sub-array in left hand side of pivot
        quickSort_desc(arr, low, partitionPoint);
        printf("arr:%d low:%d partitionPoint:%d\n",
                *arr, low, partitionPoint); // check algorithm
        // Recursive of sub-array in right hand side of pivot
        quickSort_desc(arr, partitionPoint + 1, high);
        printf("arr:%d high:%d partitionPoint:%d\n",
                *arr, high, partitionPoint); // check algorithm
    }
}

// Another way to write ascending order in partition function
int partition_asc2(int arr[], int low, int high)
{
    int pivot = arr[high]; // pivot
    int left = low - 1; // Index of smaller element

    for(int right = low; right <= high - 1; right++){
        // If current element is smaller than the pivot
        if(arr[right] < pivot){
            left++; // Increment index of smaller element
            printf("left:%d right:%d pivot:%d arr[right]:%d arr[left]:%d\n",
                    left, right, pivot, arr[right], arr[left]); // check algorithm
            swap(&arr[left], &arr[right]);
            printf("left:%d right:%d pivot:%d arr[right]:%d arr[left]:%d\n",
                    left, right, pivot, arr[right], arr[left]); // check algorithm
        }
    }
    /* // If have 3 lines below then remove + 1 in swap and return
    left++;
    printf("left:%d pivot:%d high:%d arr[left]:%d arr[high]:%d\n",
                    left, pivot, high, arr[left], arr[high]); // check algorithm
    */
    swap(&arr[left + 1], &arr[high]);
    printf("left:%d pivot:%d high:%d arr[left]:%d arr[high]:%d\n",
                    left, pivot, high, arr[left], arr[high]); // check algorithm
    return left + 1;
}

/* The main function that implements Quicksort
 * arr[] --> Array to be sorted,
 * low --> Starting index,
 * high --> Ending index */
void quickSort_asc(int arr[], int low, int high)
{
    //This condition checks whether the array contains more than 1 element
    if(low < high){
        /* partitionPint is index which is currently staying
         * and is element divide the array into 2,i.e,
         * 1st sub-array is left hand side and
         * 2nd sub-array is right hand side */
         //getting the index of the pivot after partition of the array
        //int parttionPoint = partition_asc(arr, low, high);
        int pi = partition_asc2(arr, low, high); // pi stands for partition index

        // Recursive of sub-array in left hand side of pivot
        //quickSort_asc(arr, low, parttionPoint - 1);
        quickSort_asc(arr, low, pi - 1);
        printf("arr:%d low:%d pi:%d\n",
                *arr, low, pi); // check algorithm
        // Recursive of sub-array in right hand side of pivot
        //quickSort_asc(arr, parttionPoint + 1, high);
        quickSort_asc(arr, pi + 1, high);
        printf("arr:%d high:%d pi:%d\n",
                *arr, high, pi); // check algorithm
    }
}

void printArray(int arr[], int arr_size)
{
    int i;
    printf("Sorted array:\n");
    for(i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

void readArray(int arr[], int arr_size)
{
    int i;
    printf("Original array:\n");
    for(i = 0; i < arr_size; i++)
        printf("%d ", arr[i]);
    putchar('\n');
}

void user_choice(char* choice)
{
    printf("Type A for ascending order of the number in array or type D for descending order of the number in array: ");
    struct read halo;

    do{
        halo = getch();
        *choice = toupper(halo.first_alpha);

        if((*choice == 'A' || *choice == 'D') && halo.len_alpha == 1)
            break;
        printf("Please try enter again: ");
    }while(check == true);

    *choice = toupper(halo.first_alpha);

    putchar('\n');
}

struct read getch()
{
    int count = 1;
    struct read input;
    input.first_alpha = getc(stdin);
    while(getc(stdin) != '\n')
        count++;
    input.len_alpha = count;
    return input;
}
