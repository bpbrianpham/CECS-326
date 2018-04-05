#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>

using namespace std;

void swapWord(string, string);

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
        
        cout << text << endl << endl;
        cout << "Enter the word you would like to replace (To quit press !q): ";
        cin >> target;
        if (target == "!q"){
            cout << "Ending program." << endl;
            exit(1);
        }
        cout << "Enter what word you want to replace <" << target << "> with: ";
        cin >> newWord;

        swapWord(target, newWord);
        /*
        childID = fork();
        if(childID == 0){
            swapWord(target, newWord);
            exit(1);
        }
        wait(0);
*/
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
        while(getline(inFile, line)){
            while (line.find(target) != string::npos){
                line.replace(line.find(target), target.size(), newWord);
            }
            text = text + "\n" + line;
        }
        inFile.close();
    }
    else{
        cout << "Unable to open file" << endl;
    }

    cout << "\n==================================The new article===============================================\n" << endl;
    cout << text << endl << endl;
    cout << "Number of swaps: " << swaps << endl << endl;
    cout << "=================================================================================================\n" << endl;
}
