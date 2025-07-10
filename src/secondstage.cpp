#include <iostream> //base cout, cin etc.
#include <string>
#include <vector> // adding multiple value the varible
#include <cstdlib> //for system and other things
#include "stages.hpp" // header file
using namespace std;

vector<string> paketler;
string usbpath;

void secondstage(){
    //Varibles
    string diskpath; //usb mount path
    string cp_packs; //command
    int cpresult; //command result
    int forresult; //command result
    int pacresult; //command result



    //Warnings
    cout << "\033[31m WARNING\033[0m second stage \033[31m dont \033[0mmount usb you need \033[31mmount \033[0mand than give usb \033[32mmounted path\033[0m" << endl;
    cout << "if you dont know how to mount usb pls follow instractions" << endl;
    cout << "Enter your\033[32m mounted disk's path.\033[0m(Example: /mnt/pacofstrap)." << endl;
    cout << "\033[32m>>\033[0m";
    
    //Geting usb mount path
    cin >> diskpath;

    //Info
    cout << "\033[32mPacofstrap, now calling pacstrap...\033[0m" << endl;
    
    //command
    cp_packs = "cp "+ diskpath +"/ofpkgs/*.zst /mnt/var/cache/pacman/pkg/";
    
    // Command AND results
    cpresult = system(cp_packs.c_str()) ;
    forresult = system("for f in /mnt/var/cache/pacman/pkg/*.zst; do pacman -Qp \\\"$f\\\" | awk '{print $1}'; done > pkglist.txt");
    pacresult = system("pacstrap -K /mnt $(cat pkglist.txt) --cachedir=/mnt/var/cache/pacman/pkg") ;
    
    //Error checks
    if (cpresult !=0){
        cout << "\033[31m Package copy opeartion failed \033[0m." << endl; //ERROR CHECK
    }
    else if(forresult !=0){
        cout << "\033[31mTaking package names failed. \033[0m" << endl; //ERROR CHECK
    }
    else if(pacresult !=0){
        cout << "\033[31m Pacstrap failed. \033[0m" << endl; //ERROR CHECK
    }
    else{
        //Info
         cout << "CONGRATS! YOUR OFFLINE INSTALLATION COMPLETED!" << endl;
    }
}

