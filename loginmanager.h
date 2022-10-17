#include <string>
#include <iostream>
#include <utility>
#include <iomanip>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////
// passwordmanager.cpp class creates strong passwords and prints them out to a file 	//
// ver 1.0          		                                                 		   	//
// Language:    Visual C++, ver 7.1                                 			        //
// Platfrom:    Linux, WindowsXP                                                  	    //
// Author:      Wael Krdi Arizona state University	        			                //
//              wkrdi@asu.edu				              			                    //
//////////////////////////////////////////////////////////////////////////////////////////
struct login{ //structure login has a web page name, username and password.
    string page, user, pass;
};
class loginmanager //class loginmanager which stores the login structures in an array, with methods that can add, delete, find, and change logins.
{
    private:
    struct login *loginsArr;
    int size, capacity;
    public:
    loginmanager();
    ~loginmanager();
    int getLogins();
    login *getloginArr();
    bool isFound(string page);
    login getlogin(string page); 
    bool insert(string page, string user, string pass);
    bool changeuser(string page, string newuser);
    bool changepass(string page, string newpass);
    bool deletelogin(string page);
    void printlogins();
};
loginmanager::loginmanager(){
    capacity = 10;
    loginsArr = new login[capacity];
    size = 0;
}
loginmanager::~loginmanager(){
    delete[] loginsArr;
}
int loginmanager::getLogins(){
    return size;
}
login *loginmanager::getloginArr(){
    return loginsArr;
}
bool loginmanager::isFound(string page){
    for (int i = 0; i <size;i++){
        if(loginsArr[i].page == page){
            return true;
        }
    }
    return false;
}
login loginmanager::getlogin(string page){
    for (int i = 0; i< size; i++){
        if(loginsArr[i].page == page){
            login returning = loginsArr[i];
            return returning;
        }
    }
    login empty;
    empty.user = "";
    return empty;
}
bool loginmanager::insert(string page,string user, string pass){
    if(isFound(page)){
        return false;
    }
    login newlogin;
    newlogin.page = page;
    newlogin.user = user;
    newlogin.pass = pass;
    if(size == capacity){
        capacity = capacity*2;
        struct login *tempArr = new login[capacity];
        for(int i = 0; i< size; i++){
            tempArr[i] = loginsArr[i];
        }
        struct login *todeleteArr = loginsArr;
        loginsArr = tempArr;
        delete [] todeleteArr;
    }
    loginsArr[size] = newlogin;
    size += 1;
    return true;
}
bool loginmanager::changeuser(string page, string newuser){
    for (int i =0; i< size; i++){
        if(loginsArr[i].page == page){
            loginsArr[i].user = newuser;
            return true;
        }
    }
    cout << "page entered is not listed, try again" << endl;
    return false;
}
bool loginmanager::changepass(string page, string newpass){
    for (int i =0; i< size; i++){
        if(loginsArr[i].page == page){
            loginsArr[i].pass = newpass;
            return true;
        }
    }
    cout << "page entered is not listed, try again" << endl;
    return false;
}
bool loginmanager::deletelogin(string page){
    for(int i = 0; i <size; i++){
        if(loginsArr[i].page == page){
            login temp;
            temp.page = loginsArr[size-1].page;
            temp.user = loginsArr[size-1].user;
            temp.pass = loginsArr[size-1].pass;
            loginsArr[size-1] = loginsArr[i];
            loginsArr[i] = temp;
            size -= 1;
            return true;
        }
    }
    return false;
}
void loginmanager::printlogins(){
    cout << "you have a total of " << size << " logins available" <<endl;
    cout << "-----------------------------" <<endl;
    for (int i = 0; i <size; i++){
        cout << loginsArr[i].page << ":" <<endl;
        cout << "username: " << setw(8) << loginsArr[i].user << "\t\tpassword: " << loginsArr[i].pass << endl;
        cout << "-----------------------------" << endl;
    }
}