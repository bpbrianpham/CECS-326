#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <fstream>

using namespace std;

string swapWord(string, string, string);

int main(){

    
    cout << "\n====================Parents and Child Processes a CECS 326 Project===============================\n" << endl;
    cout << "=================================================================================================\n" << endl;
    cout << "==================================A random article===============================================\n" << endl;
    long childID;
    ifstream inFile;
    string line;
    string text;
    string target;
    string newWord;
    inFile.open("randomArticle.txt");

    if(inFile.is_open()){
        while(getline(inFile, line)){
            text = text + "\n" + line;
        }
        inFile.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }

    while(true){
        cout << text;
        cout << "Enter the word you would like to replace (To quit press !q): ";
        cin >> target;
        if (target == "!q"){
            cout << "Ending program." << endl;
            exit(1);
        }
        cout << "Enter what word you want to replace <" << target << "> with: ";
        cin >> newWord;

        text = swapWord(text, target, newWord);
        cout << text;
    }
    inFile.close();
    return 0;
}

string swapWord(string text, string target, string newWord){
    
}
