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
#include <windows.h>
#include <iomanip>
#include <time.h>
#include <map>
using namespace std;


int loadingBar(int i) {

    int counter = 0;
    string loading[12];
    loading[0] = "<";
    loading[11] = ">";
    
    for (i = 1; i < 11; i++)
    {
        loading[i] = " ";
    }

    
    for (int x = 0;x < 10;x++)
    {
        cout << "PROGRESS BAR: " << endl;
        for (i = 0; i < 12; i++)
        {
            cout << loading[i];
            
        }
        if (counter < 10)
        loading[++counter] = "#";
        Sleep(500);
        system("CLS");
    }
    

    return 0;
}

void loadingData( ) {
    
    int rounds = 0;
    int howManyNumbers = 1000000;
    int* numbers = new int[howManyNumbers];
    string STRING;
    string T;

    ifstream infile;
    infile.open("numbers.txt");
    while (!infile.std::ios::eof()) // To get you all the lines.
    {
        getline(infile, STRING); // Saves the line in STRING.
    }

    stringstream X(STRING);
    while (getline(X, T, ',')) {
        numbers[rounds] = stoi(T); // STRING to INT
        rounds++;
    }

    ofstream SAVE("sortedNumbers.txt");
    for (int y = 0; y < howManyNumbers; y++)
    {
        SAVE << numbers[y] << "\n";
    }
    SAVE.close();
}


void save_config_to_file(const std::map<std::string, std::map<std::string, std::string>>&config, const std::string & filename)
{
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& section : config) {
            file << "[" << section.first << "]" << std::endl;
            for (const auto& key : section.second) {
                file << key.first << "=" << key.second << std::endl;
            }
            file << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Failed to open file " << filename << " for writing." << std::endl;
    }
}



int main()
{
    // Tworzenie przykładowej konfiguracji
    std::map<std::string, std::map<std::string, std::string>> config = {
        {"Section1", {{"key1", "value1"}, {"key2", "value2"}}},
        {"Section2", {{"key3", "value3"}, {"key4", "value4"}}}
    };

    // Zapisanie konfiguracji do pliku "config.ini"
    save_config_to_file(config, "config.ini");

    std::cout << "Konfiguracja została zapisana do pliku config.ini." << std::endl;

    //loadingBar(10);
    loadingData();
    cout << "end" << endl;

    return 0;
}
