#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int randNum(int minNum, int maxNum);
int* randArray(int size, int minNum, int maxNum, bool unique);
int sequentialSearch(int target, int* arr, int size, int &counter);
float sequentialSearchStatistics(int size, int iterations);
float** testSearch(int start, int stop, int step, int iterations);
void saveCSV(float** arr , int size);

int main(){
    srand(time(NULL));
    int start = 10;
    int stop = 20;
    int step = 5;
    int iterations = 10;
    int rows = (stop-start)/step + 1;

    float** result = testSearch(start, stop, step, iterations);

    saveCSV(result, rows);

    for(int i=0; i<rows; i++){
        //cout << result[i][0] << " " << result[i][1] << "\n";
        delete[] result[i];
     }
    delete[] result;
    result = nullptr;
    cout << "\nDONE!";
    return 0;
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

int* randArray(int size, int minNum=0, int maxNum=INT_MAX, bool unique = true){
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

int sequentialSearch(int target, int* arr, int size, int &counter){
    for(int i=0; i<size; i++){
        counter++;
        if(arr[i] == target){
            return i;
        }
    }
    return -1;
}

float sequentialSearchStatistics(int size, int iterations){
    int counter = 0;
    for(int i=0; i<iterations; i++){
        int* arr = randArray(size, 0 , INT_MAX, true);
        int target = arr[randNum(0, size-1)];
        
        int tmp = counter;
        int target_index = sequentialSearch(target, arr, size, counter);
        delete[] arr;
     }
    return (float)counter/iterations;
}

float** testSearch(int start, int stop, int step, int iterations){
    int rows = (stop-start)/step + 1;
    float** result = new float*[rows];
    for(int i=0; i<rows; i++){
        result[i] = new float[2];
    }
    int j = 0;
    for(int i=start; i<=stop; i+=step){
        cout << "\nSize: " <<i << "\n" << "\n";
        float avg = sequentialSearchStatistics(i, iterations);
        result[j][0] = i;
        result[j++][1] = avg;
    }
    return result;
}

void saveCSV(float** arr , int size){ 
    ofstream results_file("file.csv"); 
    results_file.precision(5);
    results_file << "sep=,\n" <<"Size" << "," << "Average comparisons" << "\n";
    for (int i = 0; i < size; i++) 
        results_file << arr[i][0] << "," << arr[i][1] << "\n";  
    results_file.close(); 
}
