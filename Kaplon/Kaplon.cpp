#include <stdio.h>
#include <fstream>
#include <string>
#include <algorithm>
#include <iostream>  
#include <string>  
#include <vector>  
#include <sstream> 
#include <cstring> 
#include <chrono>
//#include <windows.h>
#include <iomanip>
#include <time.h>
#include <map>
//#include <OpenXLSX.hpp>
using namespace std;


void loadingBar(int progress) {
    const int barWidth = 50;
    int pos = (barWidth * progress) / 100;

    cout << "PROGRESS BAR: [";
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos) {
            cout << "#";
        }
        else {
            cout << "-";
        }
    }
    cout << "] " << progress << " %" << endl;
}

void loadingData(vector<int>& numbers) {
    string STRING;
    string T;

    ifstream infile;
    infile.open("numbers.txt");
    if (!infile.is_open()) {
        cout << "Error: could not open file" << endl;
        return;
    }

    while (getline(infile, STRING)) {
        stringstream X(STRING);
        while (getline(X, T, ',')) {
            numbers.push_back(stoi(T)); // STRING to INT
        }
    }
    infile.close();
}

void saveData(vector<int> numbers, int howManyNumbers) {

    ofstream SAVE("sortedNumbers.txt");
    for (int y = 0; y < howManyNumbers; y++) {
        SAVE << numbers[y] << "\n";
    }
    SAVE.close();
}

void saveTime(int howManyNumbers, int Time) {

    ofstream SAVE("Times.txt", std::ios::app);
    SAVE << howManyNumbers << "," << Time << "\n";
    SAVE.close();

}

void configIni(int* numberOfRepetitions, string* sortName)
{
    ifstream file("config.ini");

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            // Ignore comment lines and blank lines
            if (line[0] == '#' || line.empty()) {
                continue;
            }

            // Find the '=' character in the line
            size_t equal_pos = line.find('=');
            if (equal_pos == string::npos) {
                continue;
            }

            // Get the key and value strings
            string key = line.substr(0, equal_pos);
            string value = line.substr(equal_pos + 1);

            // Remove leading/trailing whitespaces from key and value
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            // Convert the value string to integer
            if (key == "numberOfRepetitions") {
                *numberOfRepetitions = stoi(value);
            }
            else if (key == "sortName") {
                *sortName = value;
            }
        }

        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }

    cout << "numberOfRepetitions: " << *numberOfRepetitions << endl;
    cout << "sortName: " << *sortName << endl;
    //Sleep(500);
}

void sortowanieBabelkowe(vector<int>& vec) {
    int n = vec.size();
    bool swapped = true;
    while (swapped) {
        swapped = false;
        for (int i = 1; i < n; i++) {
            if (vec[i - 1] > vec[i]) {
                swap(vec[i - 1], vec[i]);
                swapped = true;
            }
        }
        n--;
    }
}

void insertionSort(vector<int>& vec) {
    int size = vec.size();
    int temp, j;

    for (int i = 1; i < size; i++) {
        temp = vec[i];
        for (j = i - 1; j >= 0 && vec[j] > temp; j--) {
            vec[j + 1] = vec[j];
        }
        vec[j + 1] = temp;
    }
}

void quicksort(vector<int>& arr, int left, int right) {
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) {
        quicksort(arr, left, j);
    }
    if (i < right) {
        quicksort(arr, i, right);
    }
}


int main()
{
    int numberOfRepetitions = 5;
    string sortName;
    vector <int> instances = { 10, 20, 30, 40, 50, 75, 100, 150, 200, 350, 500, 750, 1000, 1000, 5000, 10000, 12000, 15000, 17000, 20000, 30000, 40000, 50000, 75000, 100000, 150000, 200000, 300000, 400000, 500000, 700000, 800000, 1000000 };
    instances.reserve(instances.size());

    configIni(&numberOfRepetitions, &sortName);

    vector <int> numbers;
    numbers.reserve(1000000);

    loadingData(numbers);

    for (int x = 0; x < instances.size(); x++)
    {
        int instacesInLoop = instances[x];

        //vector<int> copy(numbers.begin(), numbers.begin() + instacesInLoop);

        for (int i = 0; i < numberOfRepetitions; i++) {
            
            vector <int> copy;
            copy.reserve(1000000);

            copy.assign(numbers.begin(), numbers.end());
            copy.resize(instacesInLoop);

            // sort the copy of the array using the bubble sort algorithm
            auto start = chrono::high_resolution_clock::now();
            if (sortName == "Bubble") {
                sortowanieBabelkowe(copy);
            }
            else if (sortName == "Insert") {
                insertionSort(copy);
            }
            else if (sortName == "Quick") {
                quicksort(copy, 0, copy.size() - 1);
            }
            else {
                cout << "Error: WRONG SORT NAME" << endl;
                return 0;
            }

            auto end = chrono::high_resolution_clock::now();

            // measure the execution time
            int time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            // << "Execution time: " << time << "ms" << endl;

            // save the sorted array and the execution time to files
            saveData(copy, instacesInLoop);
            saveTime(instacesInLoop, time);

        }
        loadingBar((float) x / sizeof(instances) * 100);

    }

    return 0;
}