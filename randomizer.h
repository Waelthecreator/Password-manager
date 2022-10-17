#include <string>
#include <iostream>
#include <set>
#include <time.h>
#include <algorithm>
using namespace std;
//////////////////////////////////////////////////////////////////////////////////////////
// passwordmanager.cpp class creates strong passwords and prints them out to a file 	//
// ver 1.0          								                                	//
//                                                                          		   	//
// Language:    Visual C++, ver 7.1                                           			//
// Platfrom:    Linux, WindowsXP                                                     	//
// Author:      Wael Krdi Arizona state University	                          			//
//              wkrdi@asu.edu				                                			//
//////////////////////////////////////////////////////////////////////////////////////////

string random_pass_generator(); //method declaration
class randomizer{ //class which keep track of what characters need to be generated
    private:
    int LC, NC, UC, SC;
    set<char> set1 = {'L', 'N', 'U','S'}; 
    public:
    randomizer(int a, int b, int c, int d);
    char getCharall();
    char UCgen();
    char LCgen();
    char NCgen();
    char SCgen();
};
randomizer::randomizer(int a, int b, int c, int d){
    LC = a;
    UC = b;
    SC = c;
    NC = d;
}
char randomizer::getCharall(){
    if (set1.size() == 4){
            int left  = 1 +(rand() %4);
            if(left == 1){
                return LCgen();
            }
            if(left == 2){
                return UCgen();
            }
            if(left == 3){
                return SCgen();
            }
            if(left == 4){
                return NCgen();
            }
        }
        if(set1.size() == 3 && set1.find('L') == set1.end()){
            int left  = 1 +(rand() % 3);
            if(left == 1){
                return UCgen();
            }
            if(left == 2){
                return SCgen();
            }
            if(left == 3){
                return NCgen();
            }
        }
        if(set1.size() == 3 && set1.find('U') == set1.end()){
            int left = 1 +(rand() % 3);
            if(left == 1){
                return LCgen();
            }
            if(left == 2){
                return SCgen();
            }
            if(left == 3){
                return NCgen();
            }
        }
        if(set1.size() == 3 && set1.find('S') == set1.end()){
            int left = 1 +(rand() % 3);
            if(left == 1){
                return LCgen();
            }
            if(left == 2){
                return UCgen();
            }

            if(left == 3){
                return NCgen();
            }
        }
        if(set1.size() == 3 && set1.find('N') == set1.end()){
            int left = 1 +(rand() % 3);
            if(left == 1){
                return LCgen();
            }
            if(left == 2){
                return UCgen();
            }
            if(left == 3){
                return SCgen();
            }
        }
        if(set1.size() == 2){
            if(set1.find('U') == set1.end()){ //CHECKING FOR UC
                if(set1.find('L') == set1.end()){ 
                    int left = 1 + (rand()% 2);
                    if(left == 1){
                        return SCgen();
                    }
                    if(left == 2){
                        return NCgen();
                    }
                }
                if(set1.find('S') == set1.end()){ 
                    int left = 1+(rand()% 2);
                    if(left == 1){
                        return LCgen();
                    }
                    if (left == 2){
                        return NCgen();
                    }
            }
            if(set1.find('N') == set1.end()){
                int left = 1+(rand()% 2);
                    if(left == 1){
                        return LCgen();
                    }
                    if (left == 2){
                        return SCgen();
                    }
                }
            }
            if(set1.find('L') == set1.end()){ //CHECKING FOR LC
                if(set1.find('U') == set1.end()){
                    int left = 1 + (rand()% 2);
                    if(left == 1){
                        return SCgen();
                    }
                    if(left == 2){
                        return NCgen();
                    }
                }
                if(set1.find('S') == set1.end()){
                    int left = 1+(rand()% 2);
                    if(left == 1){
                        return UCgen();
                    }
                    if (left == 2){
                        return NCgen();
                    }
            }
            if(set1.find('N') == set1.end()){
                int left = 1+(rand()% 2);
                    if(left == 1){
                        return UCgen();
                    }
                    if (left == 2){
                        return SCgen();
                    }
                }
            }
            if(set1.find('S') == set1.end()){ //checking for SC
                if(set1.find('U') == set1.end()){
                    int left = 1 + (rand()% 2);
                    if(left == 1){
                        return LCgen();
                    }
                    if(left == 2){
                        return NCgen();
                    }
                }
                if(set1.find('L') == set1.end()){
                    int left = 1+(rand()% 2);
                    if(left == 1){
                        return UCgen();
                    }
                    if (left == 2){
                        return NCgen();
                    }
                }
            if(set1.find('N') == set1.end()){
                int left = 1+(rand()% 2);
                    if(left == 1){
                        return UCgen();
                    }
                    if (left == 2){
                        return LCgen();
                    }
                }
            }
            if(set1.find('N') == set1.end()){ //CHECKING FOR NC
                if(set1.find('U') == set1.end()){
                    int left = 1 + (rand()% 2);
                    if(left == 1){
                        return SCgen();
                    }
                    if(left == 2){
                        return LCgen();
                    }
                }
                if(set1.find('S') == set1.end()){
                    int left = 1+(rand()% 2);
                    if(left == 1){
                        return UCgen();
                    }
                    if (left == 2){
                        return LCgen();
                    }
            }
            if(set1.find('L') == set1.end()){
                int left = 1+(rand()% 2);
                    if(left == 1){
                        return UCgen();
                    }
                    if (left == 2){
                        return SCgen();
                    }
                }
            }
        }
        if(set1.size() == 1){
            if(set1.find('L') != set1.end()){
                return LCgen();
            }
            if (set1.find('U') != set1.end()){
                return UCgen();
            }
            if (set1.find('S') != set1.end()){
                return SCgen();
            }
            if(set1.find('N') != set1.end()){
                return NCgen();
            }
        }
}
char randomizer::UCgen(){
    int random = 97 + (rand() % 26);
        UC = UC-1;
        if(UC == 0){
            set1.erase('U');
        }
        return toupper((char)random);
}
char randomizer::LCgen(){
           int random = 97 + (rand() % 26);
        LC = LC-1;
        if (LC == 0){
            set1.erase('L');
        }
        return (char)random;
}
char randomizer::SCgen(){
           int random = 33 + (rand() % 15);
        SC = SC-1;
        if(SC == 0){
            set1.erase('S');
        }
        return (char)random;
}
char randomizer::NCgen(){
        int random = 48 + (rand() % 10);
        NC = NC-1;
        if(NC == 0){
            set1.erase('N');
        }
        return (char)random;
}
string random_pass_generator(){ //method which generates the random passwords, uses an instance of the randomizer class to get the required special chracters
    string pass  = ""; //guranteed to create strong passwords applicable to most websites.
    int charLC =  4 + (rand() % 4);
    int charUC = 1 + (rand() % 4);
    int charSC = 1 + (rand() % 3);
    int charNC = 2 + (rand() % 3); 
    int totalC = charLC + charUC + charSC + charNC;
    if (totalC <=9){
        charLC += 2;
        totalC += 2;
    }
    else if(totalC > 16){
        string pass  = random_pass_generator();
        return pass;
    }
    randomizer *randpass = new randomizer(charLC, charUC, charSC, charNC);
    for (int i = 0; i < totalC; i++){
        char letterinpass = randpass->getCharall();
        pass.push_back (letterinpass);
    }   
    delete randpass;
    return pass;
}