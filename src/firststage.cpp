//libs
#include <iostream> //cout, cin etc.
#include <string>
#include <vector> // adding multiple value the varible
#include <cstdlib> //for system and etc
#include "stages.hpp" // header file
using namespace std;


//set color 
void setcolor(int textcolor)
{
    cout << "\033[" << 
    textcolor << "m";
}

//clear color
void cleacolor(){
    cout << "\033[0m";
}

//main function in first stage
void firststage() {
    
    //Varibles
    string usb; //device path
    std::string usbuuid; // usb UUID
    char buffer[128]; //Pipe configration
    int copy_main_files_id; //command result
    int create_connect_point_id; //command result
    vector<string> pkgs; //pkg list
    string input; //pkg input
    int mresult; //command result

    //commands
    std::string uuid_command = "blkid -o value -s UUID /dev/"; //Get UUID command
    uuid_command  += usb; //combine UUID command and usb (sdxy) 
    string mcmd = "mount UUID=" + usbuuid + " /mnt/pacofstrap" ; //mount command
    string umcmd = "umount UUID=" +usbuuid + " /mnt/pacofstrap" ; //umount command
    string pacman_command = "pacman -Sw --cachedir /mnt/pacofstrap/ofpkgs --noconfirm"; //pacman command


    //Warnings and infos
    setcolor(31);
    
    cout << "WARNING YOU NEED \033[0m \033[32m USB \033[0m HAVE \033[33m Difrent PARTITION \033[0m IN FAT32 OR XFAT YOU \033[31m CAN'T \033[0m USE MAIN PARTITION BECOUSE YOU \033[31m CAN'T MOUNT IT IN ARCH ISO \033[0m" << endl;
    
    cleacolor();

    cout << "Enter your USB \033[32m your-usb-partition \033[0m (WITH OUT '/dev/')." << endl;

    cout << "if  You need to learn \033[32m *your-usb-partition* \033[0m with \033[32m lsblk \033[0m command." << endl;
    setcolor(32);

    cout << ">> ";
    cleacolor();
    
    cin >> usb;

    //Info
    cout << "\033[32m geting usb_UUID\033[0m" << endl;

    

    //Creating pipe
    FILE* pipe = popen(uuid_command.c_str(), "r");
    if (!pipe) {
        std::cerr << "\033[31m get UUID command can't. runned" << std::endl; //ERROR CHECK
        return;
    }

    //geting pipe result
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        usbuuid += buffer;
    }

    //closing pipe
    pclose(pipe);

    //Removing \n
    if (!usbuuid.empty() && usbuuid.back() == '\n') {
        usbuuid.pop_back();
    }




        cout << "\033[32m creating a connection point ... \033[0m" << endl;

        create_connect_point_id=system("mkdir /mnt/pacofstrap");
        if (create_connect_point_id !=0){ //ERROR CHECK
            cout << "\033[31m Failed to create a connection point \033[0m" << endl;
            return;
        }

        else{
            cout << "\033[32m Mounting USB... \033[0m" << endl;

            //geting mount result 
            mresult = system(mcmd.c_str());

            if (mresult !=0){ //ERROR CHECK
                cout << "\033[31m Failed to mount USB. \033[0m" << endl;
                cout << mcmd << endl;
                //umount usb
                system(umcmd.c_str());

                //remove useless dir
                system("rm -rf /mnt/pacofstrap");
                return ;
            }

            else {
                //Info
                cout << "\033[32m creating packages folder... \033[0m" << endl;

                //make dir for packgs
                system("mkdir /mnt/pacofstrap/ofpkgs");

                //Info
                cout << "copying main files.." << endl;
                copy_main_files_id = system("cp pacofstrap /mnt/pacofstrap/");

                if (copy_main_files_id !=0){ //ERROR CHECK
                cout << "\033[31m Failed to copy main files. \033[0m" << endl;
                //umount usb
                system(umcmd.c_str());

                //remove useless dir
                system("rm -rf /mnt/pacofstrap");
                return ;
                }

                
                cout << "Enter packages you want to install order by order. Enter 'break' to end installing packages." << endl;

    while (true) {
            //geting packages
            cout << "\033[32m >> \033[0m";
            getline(cin, input);

            //ender
            if (input == "break")
                break;
            
            //error check
            if (input.empty() || input.find_first_not_of(" \t") == string::npos) {
                cout << "Space is no a package!" << endl; //ERROR CHECK
                continue;
            }
                pkgs.push_back(input);
            }

            //error check
            if (pkgs.empty()) {
                cout << "No packages given." << endl; //ERROR CHECK
                return ;
            }
            
            //Combine pack list and pacman_command
            for (const auto& pkg : pkgs) {
                pacman_command += " " + pkg;
            }

            //pacman command result 
            int pacman_command_return_id = system(pacman_command.c_str());

            if (pacman_command_return_id != 0) { //ERROR CHECK
                    cout << "\033[31m Failed to install packages. \033[0m" << endl; //ERROR CHECK
                    //umount usb
                    system(umcmd.c_str());

                    //remove useless dir
                    system("rm -rf /mnt/pacofstrap");
                    return ;
                    
                }

                else{
                cout << "\033[32m 1st stage: Succesfully ended! \033[0m" << endl;

                //umount usb
                system(umcmd.c_str());

                //remove useless dir
                system("rm -rf /mnt/pacofstrap");
                return ;
                
            }

            }
        }
}
