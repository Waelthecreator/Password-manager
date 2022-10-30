#include <fstream>
#include <iostream>
#include <string>
#include "loginmanager.h"
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////
// filemangment.h class that manipulates file IO and encryption/decryption           	//
// ver 2.0          								    	                            //
//                                                                             		   	//
// Language:    Visual C++, ver 7.1                                           			//
// Platfrom:    Linux, WindowsXP                                                       	//
// Author:      Wael Krdi Arizona state University	                        			//
//              wkrdi@asu.edu				                                			//
//////////////////////////////////////////////////////////////////////////////////////////
char encryptkey(char letter) // standard ceasar cypher encryption
{
    if (letter == '\n' || letter == '\t' || letter == ' ')
    {
        return letter;
    }
    int ASCII = (int)letter;
    ASCII = (ASCII + 20) % 90;
    ASCII = ASCII + 33;
    return (char)ASCII;
}
char decryptkey(char letter) // ceasar cypher decryption
{
    if (letter == '\t' || letter == ' ')
    {
        return letter;
    }
    else if (letter == '\n')
    {
        return ' ';
    }
    int ASCII = int(letter);
    ASCII = ASCII - 33;
    ASCII = 90 - ((ASCII - 20) * -1);
    if (ASCII > 122)
    {
        ASCII = ASCII % 90;
    }
    return char(ASCII);
}
string filedecrypt(string str) // given a string, applies ceasar cypher dencryption on to it then returns it
{
    string decryptedline = "";
    for (int i = 0; i < str.length(); i++)
    {
        char letter = str[i];
        decryptedline = decryptedline + decryptkey(letter);
    }
    return decryptedline;
}
string fileencrypt(string str) // given a string, applies ceasar cypher on to it then returns it
{
    string encryptedline = "";
    for (int i = 0; i < str.length(); i++)
    {
        char letter = str[i]; 
        encryptedline = encryptedline + encryptkey(letter);
    }
    return encryptedline;
}
void writetofile(string filename, loginmanager *logins)
{ // writes logins to file
    login *loginArr = logins->getloginArr();
    int size = logins->getLogins();
    ofstream ofile(filename);
    ofile << "your logins:\n";
    ofile << "-----------------------------\n";
    for (int i = 0; i < size; i++)
    {

        ofile << loginArr[i].page << ":\n";
        ofile << "username: " << loginArr[i].user << "\t\tpassword: " << loginArr[i].pass << "\n";
        ofile << "-----------------------------\n";
    }
    ofile.close();
    cout << "file \"" << filename << "\" has all your logins now"
         << "\n";
}
void writetofilewithpass(string filename, loginmanager *logins, int hashkey) // given a hashkey, writes logins to a file using the encryption method above
{
    string str;
    login *loginArr = logins->getloginArr();
    int size = logins->getLogins();
    ofstream ofile(filename);
    ofile << hashkey << "\n";
    ofile << "-----------------------------\n";
    for (int i = 0; i < size; i++)
    {
        str = loginArr[i].page + ":";
        cout << str.length() << " " << str[str.length()-1] << endl;
        ofile << fileencrypt(str) << "\n";
        str = "username: " + loginArr[i].user + "\t\tpassword: " + loginArr[i].pass;
        ofile << fileencrypt(str) << "\n";
        ofile << "-----------------------------\n";
    }
    ofile.close();
    cout << "file \"" << filename << "\" has all your logins now"
         << "\n";
}
loginmanager *readfromfilewithpin(string filename, int key) // given a hashkey, if correct writes the logins to a loginmanager class and
{
    ifstream ifile(filename);
    loginmanager *logins = NULL;
    if (!ifile.is_open())
    {
        cout << "Error with opening the file, please try again\n";
        return logins;
    }
    string str = "";
    string hashedkey = to_string(key);
    getline(ifile, str);
    str.erase(str.length() - 2, str.length() - 1);
    if (str.compare(hashedkey) == 0)
    {
        cout << "Wrong password, please try again\n";
        return logins;
    }
    logins = new loginmanager();
    string page, user, pass;
    while (getline(ifile, str))
    {
        if (str.length() != 0)
        {
            str.erase(str.length() - 1, str.length() - 1);
        }
        else
        {
            continue;
        }
        if (str[0] == '-' && str[str.length() - 1 == '-'])
        {
            continue;
        }
        else
        {
            str = filedecrypt(str);
            int pos = str.find(":");
            page = str.substr(0, pos);
            getline(ifile, str);
            str = filedecrypt(str);
            pos = str.find(": ");
            str.erase(0, pos + 2);
            pos = str.find("\t");
            user = str.substr(0, pos);
            pos = str.find(": ");
            str.erase(0, pos + 2);
            pos = str.find("\n");
            pass = str.substr(0, pos);
            logins->insert(page, user, pass);
        }
    }
    ifile.close();
    return logins;
}
loginmanager *readfromfile(string filename) // given a normal file, reads info and returns a loginmanager
{
    ifstream ifile(filename);
    loginmanager *logins = NULL;
    if (!ifile.is_open())
    {
        cout << "Error with opening the file, please try again\n";
        return logins;
    }
    string str = "";
    getline(ifile, str);
    if (str.compare("your logins:") != 0)
    {
        cout << "this file was not written through the program, and therefore can not be processed\n";
        return logins;
    }
    logins = new loginmanager();
    string page, user, pass;
    while (getline(ifile, str))
    {
        str.erase(str.length() - 1, str.length());
        if (str[1] == '-')
        {
            continue;
        }
        int pos = str.find(":");
        page = str.substr(0, pos);
        getline(ifile, str);
        pos = str.find(": ");
        str.erase(0, pos + 2);
        pos = str.find("\t");
        user = str.substr(0, pos);
        pos = str.find(": ");
        str.erase(0, pos + 2);
        pos = str.find("\n");
        pass = str.substr(0, pos);
        logins->insert(page, user, pass);
    }
    ifile.close();
    return logins;
}
int hashkey(string key) // hasking function to make files more secure
{
    int cons = 31;
    int hashkey = 0;
    char letter;
    for (int i = 0; i < key.length(); i++)
    {
        letter = key[i];
        hashkey = hashkey + (cons * (int)letter);
    }
    return hashkey;
}
