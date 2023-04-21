#include <iostream>
#include <fstream>

using namespace std;

int partition(int *arr, int lo, int hi, int &counter){
    int pivot = arr[hi];
    int indx = lo-1;

    for(int i=lo; i<hi; ++i){
        counter++;
        if(arr[i] <= pivot){
            indx++;
            int tmp = arr[i];
            arr[i] = arr[indx];
            arr[indx] = tmp; 
        }
    }
    indx++;
    arr[hi] = arr[indx];
    arr[indx] = pivot;
    return indx;
}
void qs(int *arr, int lo, int hi, int &counter){
    if(lo >= hi){
        return;
    }
    int pivotIndx = partition(arr, lo, hi, counter);
    qs(arr, lo, pivotIndx-1, counter);
    qs(arr, pivotIndx+1, hi, counter);
}

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
float func_statistics(int size, void (*sort_function)(int *array, int lo, int hi, int &counter), int iterations) {
    int counter = 0;
    for(int i=0; i<iterations; i++){
        int*arr = randArray(size, INT_MIN, INT_MAX, 0);
        sort_function(arr, 0, size-1, counter);
        delete[] arr;
    }
    return (float)counter/iterations;
}
float** test_run(
    int start_size, int stop_size, int step, void (*sort_function)(int *, int, int, int &), int iterations){
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

int main(){
    srand(time(NULL));
    int start = 10;
    int stop = 10000;
    int step = 5;
    int rows = (stop-start)/step + 1;

    float **results = test_run(start, stop, step, qs, 10);
    
    saveCSV(results, rows, "results.csv");

    /* for(int i=0; i<rows; i++){
        cout << results[i][0] << " " << results[i][1] << "\n";
    } */
    
    /* int const size = 100;
    int *arr = randArray(size, 0, 100, 0);

    cout << "Original array:\n";
    for(int i=0; i<size; i++){
        cout << arr[i] << " ";
    }
    cout << "\n\n";
    //
    qs(arr, 0, size-1);

    for(int i=0; i<size; i++){
        cout << arr[i] << " ";
    } */

    //      {3}
    //{5,6,7} {2,4,1}
    //{5} {7} {2}  {1}





    return 0;
}