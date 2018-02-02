#include <iostream>
#include <stdlib.h>
using namespace std;

int main ()
{
    string mainMenu = "(1) Access a pointer \n(2) List deallocated memory (index) \n(3) Deallocate all memory \n(4) Exit Program";
    bool cont = true;

    int choice;
    while(cont){
        cout << mainMenu << "\n\n Please enter your choice (1-4): ";
        cin >> choice;
        switch (choice){
            case 1: {
                bool cont2 = true;
                while(cont2){
                    cout <<  "\n\n(1) Print the first 10 char of the specified array."
                            << "\n(2) Delete all chars associated to the specified array."
                            << "\n(3) Return to the main menu\n\n";
                    cout << "Please enter your choice (1-3): ";
                    cin >> choice;

                    switch(choice){
                        case 1: {
                            
                        }
                        case 2:{

                        }
                        case 3:{
                            cont2 = false;
                            break;
                        }
                        default:{
                            cout << "Please enter a number 1 through 3.";
                        }
                    }
                }
                break;
            }
            case 2: {
                cout << "2";
                break;
            }
            case 3: {
                cout << "3";
                break;
            }
            case 4: {
                cout << "Ending Program....";
                cont = false;
                break;
            }
            default: {
                cout << "Please enter a number from 1 to 4.\n";
            }
        }
    }
    return 0;
}