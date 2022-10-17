#include <fstream>
#include "randomizer.h"
#include "loginmanager.h"
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////
// passwordmanager.cpp class creates strong passwords and prints them out to a file 	//
// ver 1.0          								    	                            //
//                                                                             		   	//
// Language:    Visual C++, ver 7.1                                           			//
// Platfrom:    Linux, WindowsXP                                                       	//
// Author:      Wael Krdi Arizona state University	                        			//
//              wkrdi@asu.edu				                                			//
//////////////////////////////////////////////////////////////////////////////////////////
void menu(); //method declarations
void menu2();
void writetofile(string filename, login *loginArr, int size);
void encrypttofile(string filename, string outputfile, int key); //future methods to be implemented
void noarguments();
// void readloginsfromfile(string filename, login *loginArr);
void decryptfromfile(string filename, string outputfile, int key);
int main(int argc, char *argv[]){
    if(argc == 1){ //runs the passwordmanager application
        noarguments();
        return 0;
    }
    else {
        string argument = argv[1]; //for future method implementations, functionality not yet available
        if(argument.compare("encrypt") == 0){
            cout << "this functionality is not yet added" << endl;
            break;
            string filename;
            cout << "enter the file name which you want to encrypt" << endl;
            cin >>filename;
            cout << "enter a pin to encrypt the file with" <<endl;
            int key;
            cin >> key;
            string outputfile = "encrypted" + filename;
            encrypttofile(filename,outputfile,key);
        }
        else if(argument.compare("decrypt") == 0){
            cout << "this functionality is not yet added" <<endl;
            string filename;
            int key;
            cout << "enter the file name which you want to decrypt" <<endl;
            cin >> filename;
            cout << "enter the pin the file is encrypted with" <<endl;
            cin >>key;
            string outputfile = "decrypted" + filename;
            decryptfromfile(filename, outputfile, key);
        }
        else{
            cout << "argument not implemented, please try again later." << endl;
        }
    }
    return 0;
}
void noarguments(){ //no arugments from command line, runs the program normally
    char input = 'Z';
    srand(time(NULL));
    do {
        menu();
        cout << "please enter the action that you want to perform" <<endl;
        cin.get(input);
        input = toupper(input);
        cin.ignore(20, '\n');
        switch (input){
            case 'C':{
                cout << "generating a strong passowrd" << endl;
                string pass = random_pass_generator();
                cout << "your password is " << pass << endl;
                break;
            }
            case 'Q':
                cout << "program shutting off\n";
                return;
                break;
            default:
                cout << "action not defined\n";
                break;
        }
    } while(input != 'D');
    loginmanager *logins = new loginmanager();
    login templogin;
    string page, user, pass;
    char y_n = 'Z';
    do{
        menu2();
        cout << "please enter the action that you want to perform" << endl;
        cin.get(input);
        input = toupper(input);
        cin.ignore(20,'\n');
        switch(input){
            case 'C':{
                cout << "generating a strong passowrd" << endl;
                pass = random_pass_generator();
                cout << "your password is " << pass <<endl;
                break;
            }
            case 'E':
                cout <<"Enter the page you want to add a login to: ";
                cin >> page;
                cout << "\nEnter the username: ";
                cin >> user;
                cout << "would you like a strong passowrd created (y/n)?\n";
                cin >> y_n;
                y_n = toupper(y_n);
                cin.ignore(20,'\n');
                if(y_n == 'Y'){
                    pass = random_pass_generator();
                    if(logins->insert(page,user,pass)){
                        cout <<"new login created" <<endl;
                    }
                    else{
                        cout <<"login to this page alrdy existed, your logins are listed below" <<endl;
                        logins->printlogins();
                    }
                }
                else if(y_n == 'N'){
                    cout << "enter the password you want for this login: ";
                    cin >> pass;
                    if(logins->insert(page,user,pass)){
                        cout <<"new login created" <<endl;
                    }
                    else{
                        cout <<"login to this page alrdy existed, your logins are listed below" <<endl;
                        logins->printlogins();
                    }
                }
                else{
                    cout << "invalid input" << endl;
                }
                break;
            case 'F':{
                cout << "enter the page you want a login for" << endl;
                cin >> page;
                templogin = logins->getlogin(page);
                if(templogin.user == ""){
                    cout << "page not in your manager" <<endl;
                    break;
                }
                cout << "-----------------------------" <<endl;
                cout << page << ":" << endl;
                cout << "username: " << setw(8) <<templogin.user << "\t\tpassword: " << templogin.pass <<endl;
                cout << "-----------------------------" <<endl;
                break;
            }
            case 'I':
                cout << "enter page you want to remove a login for: " << endl;
                cin >> page;
                templogin = logins->getlogin(page);
                if(templogin.user != ""){
                    cout << "deleting login: " << endl;
                    cout << page << ":" << endl;
                    cout << "username: " << setw(8) <<templogin.user << "password: " << templogin.pass <<endl;
                    logins->deletelogin(page);
                }
                else{
                    cout << "login couldn't be found, no logins were deleted." <<endl;
                }
                break;
            case 'K':
                cout << "enter the page of the login you want to find: ";
                cin >> page;
                if(logins->isFound(page)){
                    cout << "login was found!" <<endl;
                    cout << "-----------------------------" <<endl;
                    templogin = logins->getlogin(page);
                    cout << page << ":" <<endl;
                    cout << "username: " << setw(8) <<templogin.user << "\t\tpassword: " << templogin.pass <<endl;
                    cout << "-----------------------------" <<endl;
                    break;
                }
                else{
                    cout << "page could not be found" << endl;
                    break;
                }
            case 'M':
                char inputM;
                cout << "enter the page which you would like to change the logins for: ";
                cin >>page;
                if(logins->isFound(page)){
                    continue;
                }
                else{
                    cout << "page was not found" << endl;
                    break;
                }
                cout << "if you would like to change username enter \'U\', to change password enter \'P\', and for both enter \'B\': ";
                cin.get(inputM);
                inputM = toupper(inputM);
                cin.ignore(20,'\n');
                if(inputM == 'U'){
                    cout << "enter the new username: ";
                    cin >> user;
                    logins->changeuser(page,user);
                    cout << "new login information:" <<endl;
                    cout << "-----------------------------" <<endl;
                    templogin = logins->getlogin(page);
                    cout << page << ":" <<endl;
                    cout << "username: " << setw(8) <<templogin.user << "\t\tpassword: " << templogin.pass <<endl;
                    cout << "-----------------------------" <<endl;
                    break;
                }
                else if(inputM == 'P'){
                    cout << "enter the new password: ";
                    cin >> pass;
                    logins->changepass(page,pass);
                    cout << "new login information:" <<endl;
                    cout << "-----------------------------" <<endl;
                    templogin = logins->getlogin(page);
                    cout << page << ":" <<endl;
                    cout << "username: " << setw(8) <<templogin.user << "\t\tpassword: " << templogin.pass <<endl;
                    cout << "-----------------------------" <<endl;
                }
                else if (inputM == 'B'){
                    cout << "enter the new username: ";
                    cin >> user;
                    cout << "enter the new password: ";
                    cin >> pass;
                    logins->changeuser(page,user);
                    logins->changepass(page,pass);
                    cout << "new login information:" <<endl;
                    cout << "-----------------------------" <<endl;
                    templogin = logins->getlogin(page);
                    cout << page << ":" <<endl;
                    cout << "username: " << setw(8) <<templogin.user << "\t\tpassword: " << templogin.pass <<endl;
                    cout << "-----------------------------" <<endl;
                }
                else{
                    cout << "invalid input" <<endl;
                }
                break;
            case 'P':
                logins->printlogins();
                break;
            case 'Q':
                cout << "program shutting off" << endl;
                break;
            default:
                cout << "action not defined" << endl;
                break;
        }
    } while(input != 'Q');
    char fileinputq;
    string filename;
    cout << "would you like a file of your logins?(y/n)" <<endl;
    cin >> fileinputq;
    fileinputq = toupper(fileinputq);
    if(fileinputq == 'Y'){
        login *loginArr = logins->getloginArr();
        int size = logins->getLogins();
        cout << "enter the file name which you want to write the passwords to" << endl;
        cin >> filename;
        writetofile(filename, loginArr, size);
        delete logins;
    }
    cout << "if you want this file to be incrypted, rerun the program and type in \'encrypt\' and it will encrypt it with a pin" <<endl;
}
void menu(){ //menu for just getting a strong password or creating a login manager
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tget a strong password\n";
	cout << "D\t\tcreate a logins manager\n";
	cout << "Q\t\tQuit\n";
}
void menu2(){ //menu for creating a login manager
cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tget a strong password\n";
	cout << "E\t\tadd a login\n";
	cout << "F\t\tget a login\n";
	cout << "I\t\tremove a login\n";
	cout << "K\t\tcheck if a login exists\n";
	cout << "M\t\tchange login information\n";
	cout << "P\t\tshow all logins\n";
	cout << "Q\t\tQuit\n";
}
void writetofile(string filename, login *loginArr, int size){ //writes logins to file
    ofstream ofile(filename);
    ofile << "your logins:" <<endl;
    ofile << "-----------------------------" <<endl;
    for(int i = 0; i <size; i++){

        ofile << loginArr[i].page << ":" <<endl;
        ofile << "username: " << loginArr[i].user << "\t\tpassword: " << loginArr[i].pass <<endl;
        ofile << "-----------------------------" <<endl;
    }
    ofile.close();
    cout << "file \"" << filename << "\" has all your logins now" << endl; 
}
void encrypttofile(string filename, string outputfile, int key){ //encrypts data in a file to another file
    ifstream ifile(filename);
    string line;
    getline(ifile, line);
    if(line.compare("your logins:")){
        cout << "this file is not written through this program, if u wish to continue enter 1 else enter 0" << endl;
        int ans;
        cin >> ans;
        if(ans == 0){
            return;
        }
    }
    ofstream ofile(outputfile);
    for(int i = 0; i < line.size(); i++){
        int temp = line.at(i);
        temp = temp+key;
        ofile << (char)temp;
    }
    ofile.close();
    return;
}
void decryptfromfile(string filename, string outputfile, int key){ //decrypts data from a file to another file.
    ifstream ifile(filename);
    string line;
    getline(ifile,line);
    ofstream ofile(outputfile);
    for(int i = 0; i < line.size(); i++){
        int temp = line.at(i);
        temp = temp;
        temp = (key - temp);
        ofile << (char)temp;
    }
    ifile.close();
    ofile.close();
}