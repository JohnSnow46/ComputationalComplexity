#include <iostream>
using namespace std;
#include <fstream>
#include<windows.h>

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

int main()
{
    loadingBar(10);
}
