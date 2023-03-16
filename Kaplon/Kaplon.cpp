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

void loadingData(int* numbers, int howManyNumbers) {
    string STRING;
    string T;

    ifstream infile;
    infile.open("numbers.txt");
    if (!infile.is_open()) {
        cout << "Error: could not open file" << endl;
        return;
    }

    int rounds = 0;
    while (getline(infile, STRING)) {
        stringstream X(STRING);
        while (getline(X, T, ',')) {
            if (rounds >= howManyNumbers) {
                cout << "ilosc liczb: " << howManyNumbers << endl;
                return;
            }
            numbers[rounds] = stoi(T); // STRING to INT
            rounds++;
        }
    }
    infile.close();

}

void saveData(int *numbers, int howManyNumbers) {

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

void sortowanieBabelkowe(int tab[], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size - 1; j++)
        {
            if (tab[j] > tab[j + 1])
                swap(tab[j], tab[j + 1]);
        }
    }
}

void sortowanieWstawianie(int tab[], int size)
{
    int temp, j;
    for (int i = 1; i < size; i++)
    {
        temp = tab[i];

        for (j = i - 1; j >= 0 && tab[j] > temp; j--)
            tab[j + 1] = tab[j];

        tab[j + 1] = temp;
    }
}

void sortowanieQuick(int tab[], int left, int right)
{
    int i = left;
    int j = right;
    int x = tab[(left + right) / 2];

    do
    {
        while (tab[i] < x)
            i++;

        while (tab[j] > x)
            j--;

        if (i <= j)
        {
            swap(tab[i], tab[j]);

            i++;
            j--;
        }

        // Calculate progress based on sorted elements on the left side
        int progress = 0;
        for (int k = left; k < i; k++) {
            if (tab[k] <= x) {
                progress++;
            }
        }

    } while (i <= j);

    if (left < j) sortowanieQuick(tab, left, j);

    if (right > i) sortowanieQuick(tab, i, right);
}


int main()
{
    int numberOfRepetitions = 5;
    string sortName;
    int instances[] = { 10, 20, 30, 40, 50, 75, 100, 150, 200, 350, 500, 750, 1000, 1000, 5000, 10000, 12000, 15000, 17000, 20000, 30000, 40000, 50000, 75000, 100000, 150000, 200000, 300000, 400000, 500000, 700000, 900000, 1000000 };
    configIni(&numberOfRepetitions, &sortName);
    //loadingData(numbers, howManyNumbers);

    for (int x = 0; x < sizeof(instances); x++)
    {
        int instacesInLoop = instances[x];
        int* numbers = new int[instacesInLoop];

        for (int i = 0; i < numberOfRepetitions; i++) {
            int* copy = new int[instacesInLoop];
            memcpy(copy, numbers, instacesInLoop * sizeof(int)); // create a copy of numbers

            // sort the copy of the array using the bubble sort algorithm
            auto start = chrono::high_resolution_clock::now();
            sortowanieBabelkowe(copy, instacesInLoop);
            //sortowanieWstawianie(copy, instacesInLoop);
            //sortowanieQuick(copy, 0, instacesInLoop);
            auto end = chrono::high_resolution_clock::now();

            // measure the execution time
            int time = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            // << "Execution time: " << time << "ms" << endl;

            // save the sorted array and the execution time to files
            saveData(copy, instacesInLoop);
            saveTime(instacesInLoop, time);

            
            delete[] copy; // free the memory
        }
        loadingBar((float)x / sizeof(instances) * 100);
        delete[] numbers; // free the memory
    }
    loadingBar(100);

    return 0;
}
