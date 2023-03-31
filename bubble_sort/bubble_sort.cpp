#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int randNum(int minNum, int maxNum);
bool isInArray(int traget, int* arr, int size);
int* randArray(int size, int minNum = 0, int maxNum = INT_MAX, bool unique = true);

void bubble_sort1(int *arr, int size, int &counter);
void bubble_sort2(int *arr, int size, int &counter);
void bubble_sort3(int *arr, int size, int &counter);
float func_statistics(int size, void (*sort_function)(int *array, int size, int &counter), int iterations);
float** test_run(int start_size, int stop_size, int step, void (*sort_function)(int *, int, int &), int iterations);
void saveCSV(float** arr , int size, string filename);


//==========
int main(){
    srand(time(NULL));
    int start = 10;
    int stop = 1000;
    int step = 5;
    int rows = (stop-start)/step + 1;

    float** bs1 = test_run(start, stop, step, bubble_sort1, 10);
    float** bs2 = test_run(start, stop, step, bubble_sort2, 10);
    
    saveCSV(bs1, rows, "Bubble_sort1.csv");
    saveCSV(bs2, rows, "Bubble_sort2.csv");
    return 0;
}

//=========================================
int randNum(int minNum=INT_MIN, int maxNum=INT_MAX){
    int value;
    do{
        value = rand();
    }while(value < minNum || value > maxNum);
    return value;
}

bool isInArray(int traget, int* arr, int size){
    bool result = 0;
    for(int i=0; i<size; i++){
        if(arr[i] == traget)
            return 1;
    }
    return result;
}

int* randArray(int size, int minNum, int maxNum, bool unique){
    int* arr = new int[size];
    if(size-1 > maxNum-minNum && unique == true) // if wrong range
        return arr;
    int value;
    int index = 0;
    fill_n(arr, size, INT_MAX); // fill with INT_MAX
    while(index < size){
        value = randNum();
        if(value < minNum || value > maxNum)
            continue;
        if(unique == true  && !isInArray(value, arr, size)){
            arr[index] = value;
            index++;
            continue;
        }
        arr[index] = value;
        index++;
    }
    return arr;
}

void bubble_sort1(int *arr, int size, int &counter){ // bubble_sort without optimizations
    for(int i=0; i<size-1; i++){
        for(int j=1; j<size; j++){
            counter++;
            if(arr[j-1] > arr[j])
                swap(arr[j-1], arr[j]);
        }
    }
}
void bubble_sort2(int *arr, int size, int &counter){ //bubble_sort with i decrementation in the second loop
    for(int i=0; i<size-1; i++){
        for(int j=1; j<size-i; j++){
            counter++;
            if(arr[j-1] > arr[j])
                swap(arr[j-1], arr[j]);
        }
    }
}
void bubble_sort3(int *arr, int size, int &counter){ // bubble sort with early termination
    for(int i=0; i<size-1; i++){
        bool swapped = false;
        for(int j=1; j<size-i; j++){
            counter++;
            if(arr[j-1] > arr[j]){
                swap(arr[j-1], arr[j]);
                swapped = true;
            }
        }
        if(!swapped){
            return;
        }       
    }
}
float func_statistics(int size, void (*sort_function)(int *array, int size, int &counter), int iterations) {
    int counter = 0;
    for(int i=0; i<iterations; i++){
        int*arr = randArray(size);
        sort_function(arr, size, counter);
        delete[] arr;
    }
    return (float)counter/iterations;
}
float** test_run(
    int start_size, int stop_size, int step, void (*sort_function)(int *, int, int &), int iterations){
    int rows = (stop_size-start_size)/step + 1;
    float** result = new float*[rows];
    int arr_size = start_size;
    for(int i=0; i<rows; i++){
        result[i] = new float[2];
        result[i][0] = arr_size;
        result[i][1] = func_statistics(arr_size, sort_function, iterations);
        arr_size += step;
    }
    return result;
}
void saveCSV(float** arr , int size, string filename){ 
    ofstream results_file(filename); 
    results_file.precision(5);
    results_file << "sep=,\n" <<"Size" << "," << "Average operations" << "\n";
    for (int i = 0; i < size; i++) 
        results_file << arr[i][0] << "," << arr[i][1] << "\n";  
    results_file.close(); 
}