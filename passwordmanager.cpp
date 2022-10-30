#include "filemanagment.h"
#include "randomizer.h"
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////
// passwordmanager.cpp class creates strong passwords and prints them out to a file 	//
// ver 2.0          								    	//
//                                                                             		//
// Language:    Visual C++, ver 7.1                                           		//
// Platfrom:    Linux, WindowsXP                                                       	//
// Author:      Wael Krdi Arizona state University	                        	//
//              wkrdi@asu.edu				                                //
//////////////////////////////////////////////////////////////////////////////////////////
void menu(); // method declarations
void menu2();
void managermenu(loginmanager *logins);
void noarguments();
int main(int argc, char *argv[])
{
    srand(time(NULL));
    if (argc == 1)
    { // runs the passwordmanager application
        noarguments();
        return 0;
    }
    else
    {
        string argument = argv[1];
        if (argument.compare("-decrypt") == 0)
        {
            string filename;
            if (argc == 2)
            {
                cout << "you did not enter the file name you want to decrypt, please enter it now: ";
                getline(cin, filename);
            }
            else
            {
                filename = argv[2];
            }
            cout << "enter a pin the file was encrypted with\n";
            int key;
            cin >> key;
            loginmanager *logins = readfromfilewithpin(filename, key);
            managermenu(logins);
        }
        else if (argument.compare("-read") == 0)
        {
            string filename;
            if (argc == 2)
            {
                cout << "you did not enter the file name you want to read, please enter it now: ";
                string filename;
                getline(cin, filename);
            }
            else
            {
                string filename = argv[2];
            }
            loginmanager *logins = readfromfile(filename);
            if (logins == NULL){
                return 0;
            }
            managermenu(logins);
        }
        else
        {
            cout << "argument not implemented, please try again later." << endl;
        }
    }
    return 0;
}
void noarguments()
{ // no arugments from command line, runs the program normally
    cout << "welcome to password manager, this program can creates random passwords, a login manager which \n"
            "which takes your logins, and can store your logins into a file. the file can be encrypted with a password \n"
            "or left unencrypted, depending on your choice. if you want to get your logins from the file, you  would use \n"
            "this usage: <exe> -read <filename>/ <exe> -decrypt <filename>. you are currently running this program with \n"
            "just the executable if you would like to decrypt a file and add more on to it, please rerun the program.\n";
    char input = 'Z';
    do
    {
        menu();
        cout << "please enter the action that you want to perform" << endl;
        cin.get(input);
        input = toupper(input);
        cin.ignore(20, '\n');
        switch (input)
        {
        case 'C':
        {
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
    } while (input != 'D');
    loginmanager *logins = new loginmanager();
    login templogin;
    managermenu(logins);
}
void managermenu(loginmanager *logins)
{ // lets user manipulate the login manager
    login templogin;
    char input = 'Z';
    string page, user, pass;
    char y_n = 'Z';
    do
    {
        menu2();
        cout << "please enter the action that you want to perform" << endl;
        cin.get(input);
        input = toupper(input);
        cin.ignore(20, '\n');
        switch (input)
        {
        case 'C':
        {
            cout << "generating a strong passowrd" << endl;
            pass = random_pass_generator();
            cout << "your password is " << pass << endl;
            break;
        }
        case 'E':
            cout << "Enter the page you want to add a login to: ";
            cin >> page;
            cout << "\nEnter the username: ";
            cin >> user;
            cout << "would you like a strong passowrd created (y/n)?\n";
            cin >> y_n;
            y_n = toupper(y_n);
            cin.ignore(20, '\n');
            if (y_n == 'Y')
            {
                pass = random_pass_generator();
                if (logins->insert(page, user, pass))
                {
                    cout << "new login created" << endl;
                }
                else
                {
                    cout << "login to this page alrdy existed, your logins are listed below" << endl;
                    logins->printlogins();
                }
            }
            else if (y_n == 'N')
            {
                cout << "enter the password you want for this login: ";
                cin >> pass;
                if (logins->insert(page, user, pass))
                {
                    cout << "new login created" << endl;
                }
                else
                {
                    cout << "login to this page alrdy existed, your logins are listed below" << endl;
                    logins->printlogins();
                }
            }
            else
            {
                cout << "invalid input" << endl;
            }
            break;
        case 'F':
        {
            cout << "enter the page you want a login for" << endl;
            cin >> page;
            templogin = logins->getlogin(page);
            if (templogin.user == "")
            {
                cout << "page not in your manager" << endl;
                break;
            }
            cout << "-----------------------------" << endl;
            cout << page << ":" << endl;
            cout << "username: " << setw(8) << templogin.user << "\t\tpassword: " << templogin.pass << endl;
            cout << "-----------------------------" << endl;
            break;
        }
        case 'I':
            cout << "enter page you want to remove a login for: " << endl;
            cin >> page;
            templogin = logins->getlogin(page);
            if (templogin.user != "")
            {
                cout << "deleting login: " << endl;
                cout << page << ":" << endl;
                cout << "username: " << setw(8) << templogin.user << "password: " << templogin.pass << endl;
                logins->deletelogin(page);
            }
            else
            {
                cout << "login couldn't be found, no logins were deleted." << endl;
            }
            break;
        case 'K':
            cout << "enter the page of the login you want to find: ";
            cin >> page;
            if (logins->isFound(page))
            {
                cout << "login was found!" << endl;
                cout << "-----------------------------" << endl;
                templogin = logins->getlogin(page);
                cout << page << ":" << endl;
                cout << "username: " << setw(8) << templogin.user << "\t\tpassword: " << templogin.pass << endl;
                cout << "-----------------------------" << endl;
                break;
            }
            else
            {
                cout << "page could not be found" << endl;
                break;
            }
        case 'M':
            char inputM;
            cout << "enter the page which you would like to change the logins for: ";
            cin >> page;
            if (logins->isFound(page))
            {
                continue;
            }
            else
            {
                cout << "page was not found" << endl;
                break;
            }
            cout << "if you would like to change username enter \'U\', to change password enter \'P\', and for both enter \'B\': ";
            cin.get(inputM);
            inputM = toupper(inputM);
            cin.ignore(20, '\n');
            if (inputM == 'U')
            {
                cout << "enter the new username: ";
                cin >> user;
                logins->changeuser(page, user);
                cout << "new login information:" << endl;
                cout << "-----------------------------" << endl;
                templogin = logins->getlogin(page);
                cout << page << ":" << endl;
                cout << "username: " << setw(8) << templogin.user << "\t\tpassword: " << templogin.pass << endl;
                cout << "-----------------------------" << endl;
                break;
            }
            else if (inputM == 'P')
            {
                cout << "enter the new password: ";
                cin >> pass;
                logins->changepass(page, pass);
                cout << "new login information:" << endl;
                cout << "-----------------------------" << endl;
                templogin = logins->getlogin(page);
                cout << page << ":" << endl;
                cout << "username: " << setw(8) << templogin.user << "\t\tpassword: " << templogin.pass << endl;
                cout << "-----------------------------" << endl;
            }
            else if (inputM == 'B')
            {
                cout << "enter the new username: ";
                cin >> user;
                cout << "enter the new password: ";
                cin >> pass;
                logins->changeuser(page, user);
                logins->changepass(page, pass);
                cout << "new login information:" << endl;
                cout << "-----------------------------" << endl;
                templogin = logins->getlogin(page);
                cout << page << ":" << endl;
                cout << "username: " << setw(8) << templogin.user << "\t\tpassword: " << templogin.pass << endl;
                cout << "-----------------------------" << endl;
            }
            else
            {
                cout << "invalid input" << endl;
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
    } while (input != 'Q');
    char fileinputq;
    cout << "would you like a file of your logins?(y/n)" << endl;
    cin >> fileinputq;
    fileinputq = toupper(fileinputq);
    if (fileinputq == 'Y')
    {
        string filename;
        cout << "would you like your file to be locked with a password?\n";
        cin >> fileinputq;
        fileinputq = toupper(fileinputq);
        if (fileinputq == 'Y')
        {
            cout << "enter a password to encrypt your file (tip: use a simple password you can always remember)\n";
            string pass;
            cin >> pass;
            int hashedkey = hashkey(pass);
            cout << "enter the file name which you want to write the passwords to" << endl;
            cin >> filename;
            writetofilewithpass(filename, logins, hashedkey);
        }
        else
        {
            cout << "enter the file name which you want to write the passwords to" << endl;
            cin >> filename;
            writetofile(filename, logins);
        }
        delete logins;
    }
}
void menu()
{ // menu for just getting a strong password or creating a login manager
    cout << "Choice\t\tAction\n";
    cout << "------\t\t------\n";
    cout << "C\t\tget a strong password\n";
    cout << "D\t\tcreate a logins manager\n";
    cout << "Q\t\tQuit\n";
}
void menu2()
{ // menu for creating a login manager
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
