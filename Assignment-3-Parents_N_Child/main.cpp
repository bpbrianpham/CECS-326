#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

int main(){

    cout << "\n====================Parents and Child Processes a CECS 326 Project===============================\n" << endl;
    cout << "=================================================================================================\n" << endl;
    cout << "==================================A random article===============================================\n" << endl;
    
    ifstream inFile;
    string line;
    inFile.open("randomArticle.txt");

    if(inFile.is_open()){
        while(getline(inFile, line)){
            cout << line << endl;
        }
        inFile.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }

    string target;
    string newWord;
    cout << "Enter the word you would like to replace: ";
    cin >> target;

    cout << "Enter what word you want to replace <" << target << "> with: ";
    cin >> newWord;
    

    return 0;
}

