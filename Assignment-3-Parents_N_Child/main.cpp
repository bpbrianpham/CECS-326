#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>
#include <stdio.h>

using namespace std;

void swapWord(string, string);

int main(){

    
    cout << "\n\t\t\tParents and Child Processes a CECS 326 Project\t\t\t\n" << endl;
    cout << "\n\t\t\t==============================================\t\t\t\n" << endl;
    cout << "\n\t\t\t============A random article==================\t\t\t\n" << endl;
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
        
        cout << text << endl << endl;
        cout << "Enter the word you would like to replace (To quit press !wq): ";
        cin >> target;
        if (target == "!wq"){
            cout << "Ending program." << endl;
            exit(0);
        }
        cout << "Enter what word you want to replace <" << target << "> with: ";
        cin >> newWord;

        childID = fork();
        if(childID == 0){
            swapWord(target, newWord);
            exit(0);
        }
        wait(NULL);

    }
    inFile.close();
    return 0;
}

void swapWord(string target, string newWord){
    string text = "";
    int swaps = 0;
    string line;

    ifstream inFile;
    inFile.open("randomArticle.txt");
    if(inFile.is_open()){
        while(swaps == 0){
            while(getline(inFile, line)){
                while (line.find(target) != string::npos){
                    line.replace(line.find(target), target.size(), newWord);
                    swaps++;
                }
                text = text + "\n" + line;
            }
            if(swaps == 0)
                cout << ". . ." << endl;
        }
        inFile.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }

    cout << "\n\t\t\t============The New Article==================\t\t\t\n" << endl;
    cout << text << endl << endl;
    cout << "Number of swaps: " << swaps << endl << endl;
    cout << "\n\t\t\t=============================================\t\t\t\n" << endl;
}
