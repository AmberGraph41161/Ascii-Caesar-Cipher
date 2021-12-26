#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include <conio.h>
#include <windows.h>

///FUNCS
//int main();
void DEFAULTSETTINGS();
void varsetup();
void SETTINGS();
void SETTINGSET(std::string type, std::string replacestring);
int Menu();
void Encrypt();
void Decrypt();
void Auto();
void Manual();
void dupefilereplacetext(std::string filename, int line, std::string replacetext);
std::string getfilename();
int getshiftnum();
int getnum(std::string displaytext);
bool isnum(std::string input);
bool FileExtension(std::string input);
void Credits();
void pause();
void cls(bool tf);

///GLOBAL VARS DEFAULT SETTINGS SETUP
bool CLEARSCREEN = true;
bool AUTOSPEED = false;
int WORDCOUNT = 5;
int AUTOSHIFTMIN = -500;
int AUTOSHIFTMAX = 500;
int READLINELENGTH = 100;


int main()
{
    //probably a windows native app cuz can't find alternative to "system("cls");"
    system("color 2"); //set console output color to green cuz it looks cooler
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED); //max out window size

    varsetup(); //setup settings;
    Credits(); //gotta show dem credits ya know?

    while(true)
    {
        switch(Menu())
        {
        case 1:
            Encrypt();
            break;
        case 2:
            Decrypt();
            break;
        case 3:
            Auto();
            break;
        case 4:
            Manual();
            break;
        case 5:
            SETTINGS();
            break;
        case 6:
            cls(CLEARSCREEN);
            std::cout << "EXITING PROGRAM..." << std::endl;
            exit(-1);
            break;
        default:
            cls(CLEARSCREEN);
            std::cerr << "ERROR" << std::endl;
            std::cerr << "Terminating process..." << std::endl;
            exit(-1);
        }
    }

}

void DEFAULTSETTINGS()
{
    std::fstream write;
    write.open("resources\\USER_SETTINGS.txt", std::ios::out | std::ios::trunc);

    write << "CLEARSCREEN"    << "=" << "true" << "\n";
    write << "AUTOSPEED"      << "=" << "false" << "\n";
    write << "WORDCOUNT"      << "=" << "5" << "\n";
    write << "AUTOSHIFTMIN"   << "=" << "-500" << "\n";
    write << "AUTOSHIFTMAX"   << "=" << "500" << "\n";
    write << "READLINELENGTH" << "=" << "100" << "\n";

    std::cout << "CLEARSCREEN"    << "=" << "true" << "\n";
    std::cout << "AUTOSPEED"      << "=" << "false" << "\n";
    std::cout << "WORDCOUNT"      << "=" << "5" << "\n";
    std::cout << "AUTOSHIFTMIN"   << "=" << "-500" << "\n";
    std::cout << "AUTOSHIFTMAX"   << "=" << "500" << "\n";
    std::cout << "READLINELENGTH" << "=" << "100" << "\n";

    write.close();

    std::cout << "Restored settings to default" << std::endl;
    pause();
    cls(CLEARSCREEN);
}

void varsetup()
{
    std::string outstring;

    std::fstream setup;
    setup.open("resources\\USER_SETTINGS.txt", std::ios::in);
    if(setup.fail())
    {
        cls(CLEARSCREEN);
        std::cerr << "Something went wrong while trying to open \"resources\\USER_SETTINGS.txt\"" << std::endl;
        std::cerr << "Terminating program..." << std::endl;
        pause();
        exit(-1);
    }

    try ///IF varsetup fail (something wrong in USER_SETTINGS.txt), reset to default;
    {
        //CLEARSCREEN
        std::getline(setup, outstring, '=');
        std::getline(setup, outstring);
        if(outstring == "true")
        {
            CLEARSCREEN = true;
        } else if(outstring == "false")
        {
            CLEARSCREEN = false;
        } else
        {
            CLEARSCREEN = false;
        }
        //AUTOSPEED
        std::getline(setup, outstring, '=');
        std::getline(setup, outstring);
        if(outstring == "true")
        {
            AUTOSPEED = true;
        } else if(outstring == "false")
        {
            AUTOSPEED = false;
        } else
        {
            AUTOSPEED = false;
        }
        //WORDCOUNT
        std::getline(setup, outstring, '=');
        std::getline(setup, outstring);
        WORDCOUNT = std::stoi(outstring);
        //AUTOSHIFTMIN
        std::getline(setup, outstring, '=');
        std::getline(setup, outstring);
        AUTOSHIFTMIN = std::stoi(outstring);
        //AUTOSHIFTMAX
        std::getline(setup, outstring, '=');
        std::getline(setup, outstring);
        AUTOSHIFTMAX = std::stoi(outstring);
        //READLINELENGTH
        std::getline(setup, outstring, '=');
        std::getline(setup, outstring);
        READLINELENGTH = std::stoi(outstring);
    } catch (...) //if any errors caught, reset to default settings
    {
        DEFAULTSETTINGS();
    }

    setup.close();
}

void SETTINGS()
{
    int input;
    std::string outstring;

    cls(CLEARSCREEN);
    std::cout << "__________________________________________________\n" << std::endl;
    std::cout << "1. Turn \"CLEARSCREEN\" command ON" << std::endl;
    std::cout << "2. Turn \"CLEARSCREEN\" command OFF" << std::endl;
    std::cout << "4. Optimize AUTO for speed" << std::endl;
    std::cout << "3. Optimize AUTO for readability" << std::endl;
    std::cout << "5. Set required WORDCOUNT(" << WORDCOUNT << ")"  << std::endl;
    std::cout << "6. Set AUTOSHIFT MIN/MAX(" << AUTOSHIFTMIN << ", " << AUTOSHIFTMAX << ")" << std::endl;
    std::cout << "7. Set READLINELENGTH(" << READLINELENGTH << ")" << std::endl;
    std::cout << "8. RESTORE DEFAULT SETTINGS" << std::endl;
    std::cout << "9. EXIT" << std::endl;
    std::cout << "__________________________________________________\n" << std::endl;
    std::cout << "> ";

    std::cin >> input;

    while(!std::cin.good())
    {
        cls(CLEARSCREEN);
        std::cout << "Bad input..." << std::endl;
        pause();
        cls(CLEARSCREEN);

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "__________________________________________________\n" << std::endl;
        std::cout << "1. Turn \"CLEARSCREEN\" command ON" << std::endl;
        std::cout << "2. Turn \"CLEARSCREEN\" command OFF" << std::endl;
        std::cout << "3. Optimize AUTO for speed" << std::endl;
        std::cout << "4. Optimize AUTO for readability" << std::endl;
        std::cout << "5. Set required WORDCOUNT(" << WORDCOUNT << ")"  << std::endl;
        std::cout << "6. Set AUTOSHIFT MIN/MAX(" << AUTOSHIFTMIN << ", " << AUTOSHIFTMAX << ")" << std::endl;
        std::cout << "7. Set READLINELENGTH(" << READLINELENGTH << ")" << std::endl;
        std::cout << "8. RESTORE DEFAULT SETTINGS" << std::endl;
        std::cout << "9. EXIT" << std::endl;
        std::cout << "__________________________________________________\n" << std::endl;
        std::cout << "> ";

        std::cin >> input;
    }
    cls(CLEARSCREEN);

    switch(input)
    {
    case 1:
        //CLEARSCREEN = true;
        SETTINGSET("CLEARSCREEN", "true");
        varsetup();
        break;
    case 2:
        //CLEARSCREEN = false;
        SETTINGSET("CLEARSCREEN", "false");
        varsetup();
        break;
    case 3:
        //AUTOSPEED = true;
        SETTINGSET("AUTOSPEED", "true");
        varsetup();
        break;
    case 4:
        //AUTOSPEED = false;
        SETTINGSET("AUTOSPEED", "false");
        varsetup();
        break;
    case 5:
        //WORDCOUNT = getnum("NEW WORDCOUNT VALUE");
        SETTINGSET("WORDCOUNT", std::to_string(getnum("NEW WORDCOUNT VALUE")));
        varsetup();
        break;
    case 6:
        //AUTOSHIFTMIN = getnum("NEW AUTOSHIFTMIN VALUE");
        //AUTOSHIFTMAX = getnum("NEW AUTOSHIFTMAX VALUE");
        SETTINGSET("AUTOSHIFTMIN", std::to_string(getnum("NEW AUTOSHIFTMIN VALUE")));
        SETTINGSET("AUTOSHIFTMAX", std::to_string(getnum("NEW AUTOSHIFTMAX VALUE")));
        varsetup();
        break;
    case 7:
        //READLINELENGTH = getnum("NEW READLINELENGTH VALUE");
        SETTINGSET("READLINELENGTH", std::to_string(getnum("NEW READLINELENGTH VALUE")));
        varsetup();
        break;
    case 8:
        DEFAULTSETTINGS();
        varsetup();
        break;
    case 9:
        //exit settings
        break;
    default:
        std::cerr << "SOMETHING WENT WRONG..." << std::endl;
        pause();
        exit(-1);
        break;
    }
}

void SETTINGSET(std::string type, std::string replacestring)
{
    int line = 0;
    std::string tempstring;
    std::string outstring;

    //read first, find replace instance, and then write
    std::fstream read;
    read.open("resources\\USER_SETTINGS.txt", std::ios::in);
    if(read.fail())
    {
        cls(CLEARSCREEN);
        std::cerr << "Something went wrong while trying to open \"resources\\USER_SETTINGS.txt\"" << std::endl;
        std::cerr << "Terminating program..." << std::endl;
        pause();
        exit(-1);
    }

    //loop for finding the replace instance
    while(!read.eof())
    {
        std::getline(read, tempstring);
        line++;
        if(tempstring.find(type) != std::string::npos)
        {
            break;
        }
    }
    read.close();

    outstring = tempstring.substr(0, tempstring.find("="));
    outstring += "=" + replacestring;
    dupefilereplacetext("resources\\USER_SETTINGS.txt", line, outstring);
}

int Menu()
{
    int input;

    std::cout << "__________________________________________________\n" << std::endl; //50 chars wide
    std::cout << "1. Encrypt" << std::endl;
    std::cout << "2. Decrypt" << std::endl;
    std::cout << "3. Auto" << std::endl;
    std::cout << "4. Manual" << std::endl;
    std::cout << "5. USER_SETTINGS" << std::endl;
    std::cout << "6. EXIT" << std::endl;
    std::cout << "__________________________________________________\n" << std::endl;
    std::cout << "> ";

    std::cin >> std::setw(1) >> input;
    while(!std::cin.good() || input > 6 || input <= 0)
    {
        ///^^^ CHOICES ARE HARDLOCKED TO 6 FOR NOW
        cls(CLEARSCREEN);
        std::cout << "Bad Input..." << std::endl;
        pause();
        cls(CLEARSCREEN);

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "__________________________________________________\n" << std::endl; //50 chars wide
        std::cout << "1. Encrypt" << std::endl;
        std::cout << "2. Decrypt" << std::endl;
        std::cout << "3. Auto" << std::endl;
        std::cout << "4. Manual" << std::endl;
        std::cout << "5. USER_SETTINGS" << std::endl;
        std::cout << "6. EXIT" << std::endl;
        std::cout << "__________________________________________________\n" << std::endl;
        std::cout << "> ";

        std::cin >> std::setw(1) >> input;
    }

    return input;
}

void Encrypt() //encrypt and decrypt have inverted shift values
{
    std::fstream read;
    std::fstream write;

    std::string readfilename = getfilename();
    std::string writefilename = "ENCRYPTED_" + readfilename;

    int shift = getshiftnum();

    read.open(readfilename, std::ios::in);
    write.open(writefilename, std::ios::out);

    while(read.fail()) //only checking 'read' to make sure file exists and not create new
    {
        cls(CLEARSCREEN);
        std::cerr << "Something went wrong when trying to create/open specified file/file_path" << std::endl;
        std::cerr << "Trying again...\n" << std::endl;
        pause();

        read.close();
        write.close();

        std::string readfilename = getfilename();
        std::string writefilename = "ENCRYPTED_" + readfilename;

        read.open(readfilename, std::ios::in);
        write.open(writefilename, std::ios::out);

        cls(CLEARSCREEN);
    }


    //loops. fun. wow. so cool. we loves loops.
    //I hate loops. loops can go and step on a lego
    //okkkkk here we gooooooo wowwwwwww
    char outchar;

    std::cout << "ENCRYPTING...\n" << std::endl;
    std::cout << "\n__________________________________________________\n";
    read.seekg(std::ios::beg); //return to beginning just in case...?
    write.seekg(std::ios::beg);
    while(!read.eof())
    {
        read.get(outchar);
        if(outchar != '\n')
        {
        outchar += shift;
        }
        write << outchar;
        std::cout << outchar;
    }

    std::cout << "\n__________________________________________________\n";
    std::cout << "ENCRYPTION COMPLETE" << std::endl;
    pause();
    cls(CLEARSCREEN); ///MIGHT NEED TO GET RID OF THIS ONE LATER BUT IDK CUZ PAUSE AND CLEAR ORDER IS WACKY

    read.close();
    write.close();
}
void Decrypt()
{
    std::fstream read;
    std::fstream write;

    std::string readfilename = getfilename();
    std::string writefilename = "DECRYPTED_" + readfilename;

    int shift = getshiftnum();

    read.open(readfilename, std::ios::in);
    write.open(writefilename, std::ios::out);

    while(read.fail()) //only checking 'read' to make sure file exists and not create new
    {
        cls(CLEARSCREEN);
        std::cerr << "Something went wrong when trying to create/open specified file/file_path" << std::endl;
        std::cerr << "Trying again...\n" << std::endl;
        pause();

        read.close();
        write.close();

        std::string readfilename = getfilename();
        std::string writefilename = "DECRYPTED_" + readfilename;

        read.open(readfilename, std::ios::in);
        write.open(writefilename, std::ios::out);

        cls(CLEARSCREEN);
    }

    char outchar;

    std::cout << "DECRYPTING...\n" << std::endl;
    std::cout << "\n__________________________________________________\n";
    read.seekg(std::ios::beg); //return to beginning just in case...?
    write.seekg(std::ios::beg);
    while(!read.eof())
    {
        read.get(outchar);
        if(outchar != '\n')
        {
            outchar -= shift;
        }
        write << outchar;
        std::cout << outchar;
    }

    std::cout << "\n__________________________________________________\n";
    std::cout << "DECRYPTION COMPLETE" << std::endl;
    pause();
    cls(CLEARSCREEN);

    read.close();
    write.close();
}
void Auto()
{
    /*
    Monday, 9:51PM, 12/20/2021
    I feel like this is gonna be the longest part of this project...
    gonna take forever I feel like

    I have to take care of all of the Auto_Word_Detection stuff and what not

    Importing/finding a txt document with just dictionary words seems like a poopy task
    idk why but I feel like nobody has made one yet and if they have, that it would take
    a lot of trying to find it.

    Maybe I can just make my own list as a backup plan.
    I could just search up "most commonly used English words" and paste them into the doc
    but idk. welp, here goes nothing.

    END. Monday, 9:54PM 12/20/2021
    */

    std::fstream read;
    std::fstream write;

    std::string readfilename = getfilename();
    std::string writefilename = "AUTO_" + readfilename;

    read.open(readfilename, std::ios::in);
    write.open(writefilename, std::ios::out);

    while(read.fail()) //only checking 'read' to make sure file exists and not create new
    {
        cls(CLEARSCREEN);
        std::cerr << "Something went wrong when trying to create/open specified file/file_path" << std::endl;
        std::cerr << "Trying again...\n" << std::endl;
        pause();

        read.close();
        write.close();

        std::string readfilename = getfilename();
        std::string writefilename = "AUTO_" + readfilename;

        read.open(readfilename, std::ios::in);
        write.open(writefilename, std::ios::out);

        cls(CLEARSCREEN);
    }
    cls(CLEARSCREEN);


    /*
    Tuesday, 12:02AM, 12/21/2021

    I procrastinated for a while, and now here I am. I just (quite literally just) found a txt files
    that contains almost the entire English dictionary, which is nice.

    The file was made from back in 2012 which is kinda cool, but ye. I'ma use it now, and am super happy
    that I do not have to manually write all of those keywords.

    I also found out that you can use either "strstr" or "find" to find words within a string.
    lets get this started...
    :)


    END. Tuesday, 12:04AM, 12/21/2021
    */



    ///open "1-1000.txt" as main, and "engmix.txt" as backup
    //commonwords
    std::fstream commonwords;
    commonwords.open("resources\\1-1000.txt", std::ios::in);
    if(commonwords.fail())
    {
        cls(CLEARSCREEN);
        std::cerr << "ERROR. CRITICAL FILE MISSING" << std::endl;
        std::cerr << "CANNOT FIND \"resources\\1-1000.txt\"" << std::endl;
        std::cerr << "TERMINATING PROGRAM..." << std::endl;
        exit(-1);
    }
    commonwords.seekg(std::ios::beg);

    //dictionary
    std::fstream dictionary;
    dictionary.open("resources\\engmix.txt", std::ios::in);
    if(dictionary.fail())
    {
        cls(CLEARSCREEN);
        std::cerr << "ERROR. CRITICAL FILE MISSING" << std::endl;
        std::cerr << "CANNOT FIND \"resources\\engmix.txt\"" << std::endl;
        std::cerr << "TERMINATING PROGRAM..." << std::endl;
        exit(-1);
    }
    dictionary.seekg(std::ios::beg);

    /*
    NOTE TO SELF:
    FIX THE AUTO DECRYPT LOOP CRAP WITH THIS:
    https://en.cppreference.com/w/cpp/string/basic_string/getline
    https://www.geeksforgeeks.org/unordered_set-in-cpp-stl/

	ALSO CHALLENGE BY SOME GUY NAMED "eatnumber1":
	https://en.wikipedia.org/wiki/Levenshtein_distance
    */


    /*
    Tuesday, 4:04PM, 12/21/2021

    I just got home, and have eaten 2 chocolate chip cookies from Costco so far...

    While in school today, I came up with the solution to change from reading the entire
    English dictionary to instead just the most commonly used words in the English dict.
    I am really hoping that this solves my loop issues.

    Also, I gotta study up today and not focus so much on this project because I have
    an important math test retake for the end of the semester tomorrow, and if I flunk it,
    I am screwed.

    I also gotta say, making these "journals" within a cpp files is kinda fun. lol.

    END. Tuesday, 4:06PM, 12/21/2021
    */

    ///AUTO WORD SEARCH VARS
    int wordcount = 0;
    int shift = AUTOSHIFTMIN; //start from negatives, go to positives
    std::string tempstring;
    std::string readline;
    std::string wordbank[15];
    char outchar;

    //put words into wordbank
    for(int x = 0; x < 15; x++)
    {
        std::getline(commonwords, tempstring);
        if(tempstring != "a") //making sure to exclude "a" (too common of a word/letter)
        {
            wordbank[x] = tempstring;
        } else
        {
            x--;
        }
    }
    //getline from "read"
    //make sure that the string is at least 100 characters long (short lines == bad/won't work)
    read.seekg(std::ios::beg);
    while(readline.length() < 100)
    {
        std::getline(read, tempstring);
        for(unsigned int x = 0; x < tempstring.length(); x++)
        {
            readline += tempstring[x] + shift;
        }
    }

    std::cout << "AUTO DECRYPTING PROCESS HAS BEGUN..." << std::endl;
    std::cout << "__________________________________________________\n" << std::endl;
    Sleep(500);

    if(AUTOSPEED == false)
    {
        std::cout << "wordcount: " << wordcount << std::endl;
        std::cout << "wordbank: " << wordbank << std::endl;
        std::cout << "readline: " << readline << std::endl;
        std::cout << "shift: " << shift << std::endl;
        std::cout << "tempstring: " << tempstring << std::endl;
        std::cout << "breakcode: ";
    }

    //The actual loop after setup
    while(true)
    {
        ///First option is to try the first 15 most common English words (will not include "a" as a word)
        ///Second option if to try the entire English dictionary
        //compare
        for(int x = 0; x < 15; x++)
        {
            if(readline.find(wordbank[x]) != std::string::npos)
            {
                readline.erase(readline.find(wordbank[x]), wordbank[x].length());
                wordcount++;
                x--;
            }
        }

        if(AUTOSPEED == false)
        {
            cls(CLEARSCREEN);
            std::cout << "wordcount: " << wordcount << std::endl;
            std::cout << "wordbank: " << wordbank << std::endl;
            std::cout << "shift: " << shift << std::endl;
            std::cout << "tempstring: " << tempstring << std::endl;
            std::cout << "readline: " << readline << std::endl;
        } else
        {
            std::cout << wordcount << wordbank << shift << tempstring << readline << std::endl;
        }

        if(wordcount >= WORDCOUNT)
        {
            break;
        }
        if(shift <= AUTOSHIFTMAX)
        {
            shift++;

        } else
        {
            break;
        }
        read.seekg(std::ios::beg);
        readline = "";
        while(readline.length() < READLINELENGTH)
        {
            std::getline(read, tempstring);
            for(unsigned int x = 0; x < tempstring.length(); x++)
            {
                readline += tempstring[x] + shift;
            }
        }
    }

    ///EXPORTING AUTO WORK
    std::cout << "\n\nEXPORTING AUTO WORK..." << std::endl;
    std::cout << "\n__________________________________________________\n";

    read.clear();
    read.seekg(std::ios::beg);
    write.seekg(std::ios::beg);
    while(!read.eof())
    {
        read.get(outchar);
        if(outchar != '\n')
    {
    outchar += shift;
    }
        write << outchar;
        std::cout << outchar;
    }

    std::cout << "\n__________________________________________________\n";
    std::cout << "AUTO WORK has been exported into file successfully" << std::endl;
    pause();
    cls(CLEARSCREEN);

    read.close();
    write.close();
    commonwords.close();
    dictionary.close();

    /*
    Wednesday, 4:00AM, 12/22/2021

    OMGOMG HOLY FREAKING HECK I F*CKING DID IT DUDE!!!

    I AM A FARTING GENIUS BROOOOOOO LETS GOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO

    dude. I am like, actually super happy this worked. wtf. like, I did not think that this would work at all tbh
    lets gooooo.

    cannot wait to finally upload the vid for this one. it's been over a year since my first vid so ye

    also kinda wanna show teacher Lenny. I wonder how he would react

    welp, now I'ma just add a couple more other things, like a settings sections and what not.

    END. Wednesday, 4:03AM, 12/22/2021
    */
}
void Manual()
{
    std::fstream read;
    std::fstream write;

    std::string readfilename = getfilename();
    std::string writefilename = "MANUAL_" + readfilename;

    read.open(readfilename, std::ios::in);
    write.open(writefilename, std::ios::out);

    while(read.fail()) //only checking 'read' to make sure file exists and not create new
    {
        cls(CLEARSCREEN);
        std::cerr << "Something went wrong when trying to create/open specified file/file_path" << std::endl;
        std::cerr << "Trying again...\n" << std::endl;
        pause();

        read.close();
        write.close();

        std::string readfilename = getfilename();
        std::string writefilename = "DECRYPTED_" + readfilename;

        read.open(readfilename, std::ios::in);
        write.open(writefilename, std::ios::out);

        cls(CLEARSCREEN);
    }
    cls(CLEARSCREEN);

    ///MANUAL LOOP
    int shift = 0;
    char outchar;

    std::cout << "ESCAPE KEY to finish\n" << std::endl;
    std::cout << "Use LEFT/RIGHT ARROW_KEYS or A & D keys" << std::endl;
    std::cout << "CURRENT SHIFT VALUE: " << shift << std::endl;
    std::cout << "__________________________________________________\n" << std::endl;
    read.clear();
    read.seekg(std::ios::beg);
    while(!read.eof())
    {
        read.get(outchar);
        outchar += shift;
        outchar == '\n' ? std::cout << "\n" : std::cout << outchar;
    }

    while(true)
    {
        //to the left to the left to the left to the left
        if(GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(0x41)) ///0x41 == "A"
        {
            cls(CLEARSCREEN);
            shift--;

            std::cout << "ESCAPE KEY to export as final\n" << std::endl;
            std::cout << "Use LEFT/RIGHT ARROW_KEYS or A & D keys" << std::endl;
            std::cout << "CURRENT CHAR VALUE: " << +outchar << std::endl;
            std::cout << "CURRENT SHIFT VALUE: " << shift << std::endl;
            if((int)outchar < 0)
            {
                std::cout << "\nWARNING, CURRENT CHAR VALUE IS IN NEGATIVE RANGE" << std::endl;
                std::cout << "(may run into encoding problems)\n" << std::endl;

            }
            std::cout << "__________________________________________________\n" << std::endl;

            read.clear();
            read.seekg(std::ios::beg);
            while(!read.eof())
            {
                read.get(outchar);
                outchar += shift;
                outchar == '\n' ? std::cout << "\n" : std::cout << outchar;
            }
            Sleep(30);
        }
        //to the right to the right to the right to the right
        if(GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState(0x44)) ///0x44 == "D"
        {
            cls(CLEARSCREEN);
            shift++;

            std::cout << "ESCAPE KEY to finish\n" << std::endl;
            std::cout << "Use LEFT/RIGHT ARROW_KEYS or A & D keys" << std::endl;
            std::cout << "CURRENT CHAR VALUE: " << +outchar << std::endl;
            std::cout << "CURRENT SHIFT VALUE: " << shift << std::endl;
            if((int)outchar < 0)
            {
                std::cout << "\nWARNING, CURRENT CHAR VALUE IS IN NEGATIVE RANGE" << std::endl;
                std::cout << "(may run into encoding problems)\n" << std::endl;

            }
            std::cout << "__________________________________________________\n" << std::endl;

            read.clear();
            read.seekg(std::ios::beg);
            while(!read.eof())
            {
                read.get(outchar);
                outchar += shift;
                outchar == '\n' ? std::cout << "\n" : std::cout << outchar;
            }
            Sleep(30);
        }
        //GET ME OUT OF HERE OMG OMG OMG AHHHHHHH!!!!!
        if(GetAsyncKeyState(VK_ESCAPE))
        {
            break;
        }
    }

    ///WRITE TO FILE AFTER BREAKING FROM MANUAL LOOP
    cls(CLEARSCREEN);
    std::cout << "EXPORTING MANUAL WORK...\n" << std::endl;
    std::cout << "\n__________________________________________________\n";

    read.clear();
    read.seekg(std::ios::beg);
    write.seekg(std::ios::beg);
    while(!read.eof())
    {
        read.get(outchar);
        if(outchar != '\n')
        {
        outchar += shift;
        }
        write << outchar;
        std::cout << outchar;
    }

    std::cout << "\n__________________________________________________\n";
    std::cout << "MANUAL WORK has been exported into file successfully" << std::endl;
    pause();
    cls(CLEARSCREEN);

    read.close();
    write.close();
}

void dupefilereplacetext(std::string filename, int line, std::string replacetext)
{
    std::string outstring;
    std::string dupefilename = "resources\\temp" + filename.substr(filename.find("\\") + 1, std::string::npos);

    std::cout << "filename: " << filename << std::endl;
    std::cout << "dupefilename: " << dupefilename << std::endl;
    std::cout << "line: " << line << std::endl;
    std::cout << "replacetext: " << replacetext << "\n\n" << std::endl;


    std::fstream read;
    std::fstream write;
    read.open(filename, std::ios::in);
    write.open(dupefilename, std::ios::out);

    if(read.fail())
    {
        std::cerr << "\"dupefilereplacetext\" READ.FAIL() == true" << std::endl;
        std::cerr << "Something went wrong..." << std::endl;
        std::cerr << "Terminating program..." << std::endl;
        pause();
        exit(-1);
    }
    if(write.fail())
    {
        std::cerr << "\"dupefilereplacetext\" WRITE.FAIL() == true" << std::endl;
        std::cerr << "Something went wrong..." << std::endl;
        std::cerr << "Terminating program..." << std::endl;
        pause();
        exit(-1);
    }

    for(int x = 1; x < line; x++) //x = 1, because start at line 1 not 0
    {
        std::getline(read, outstring);
        write << outstring << "\n";
    }
    std::getline(read, outstring); //store to move cusor, but don't write, but write replacetext
    write << replacetext << "\n";
    while(!read.eof())
    {
        std::getline(read, outstring);
        write << outstring << "\n";
    }

    read.close();
    write.close();

    remove(filename.c_str());
    rename(dupefilename.c_str(), filename.c_str());

    std::cout << "dupefilereplacetext OPERATION COMPLETE\n" << std::endl;
    pause();
    cls(CLEARSCREEN);
}

std::string getfilename()
{
    std::string filename;

    cls(CLEARSCREEN);
    std::cout << "Please enter file path" << std::endl;
    std::cout << "> ";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, filename);

    while(!std::cin.good() || !FileExtension(filename))
    {
        if(!std::cin.good()) //only clear cin buffer if !cin.good()
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } //skip clear if it is a file extension problem instead (stupid, no point)
        cls(CLEARSCREEN);

        std::cout << "One of the following errors have occurred: " << std::endl;
        std::cout << "1. File-Extension not included" << std::endl;
        std::cout << "2. File-Extension is not \".txt\" (not a text file)" << std::endl;
        std::cout << "3. Bad-User-Input" << std::endl;

        std::cout << "Please Try Again..." << std::endl;
        pause();
        cls(CLEARSCREEN);


        std::cout << "Please enter file path" << std::endl;
        std::cout << "> ";
        std::getline(std::cin, filename);
    }

    return filename;
}

int getshiftnum()
{
    /*
    00 == NULL
    01 = SOH (Start Of Header)

    32 == SPACE
    64 == '@'

    64 == 'A'
    90 == 'Z'

    97 == 'a'
    122 == 'z'

    254 == (square lookin thingy)
    255 = NBSP (No Break Space)
    */

    unsigned int shift; ///only positive values

    cls(CLEARSCREEN);
    std::cout << "Please enter a shift number ranging from 1 - 30" << std::endl;
    std::cout << "> ";
    std::cin >> std::setw(1) >> shift;
    while(!std::cin.good() || shift <= 0 || shift > 30)
    {
        cls(CLEARSCREEN);
        std::cout << "One of the following errors have occurred:" << std::endl;
        std::cout << "1. Input value was not a positive" << std::endl;
        std::cout << "2. Bad user input" << std::endl;
        pause();
        cls(CLEARSCREEN);

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Please enter a shift number ranging from 1 - 30" << std::endl;
        std::cout << "> ";
        std::cin >> std::setw(1) >> shift;
    }

    return shift;
}

int getnum(std::string displaytext)
{
    int num;

    std::cout << displaytext << std::endl;
    std::cout << "> ";
    std::cin >> num;

    while(!std::cin.good())
    {
        cls(CLEARSCREEN);
        std::cout << "Bad input..." << std::endl;
        pause();
        cls(CLEARSCREEN);

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << displaytext << std::endl;
        std::cout << "> ";
        std::cin >> num;
    }
    cls(CLEARSCREEN);
    return num;
}

bool isnum(std::string input)
{
    for(unsigned int x = 0; x < input.length(); x++)
    {
        if(isdigit(input[x] == 0))
        {
            return false;
        }
    }
    return true;
}

bool FileExtension(std::string input)
{
    std::string INPUT = "";
    if(input.length() >= 4) //4 for ".TXT" char checking
    {
        for(unsigned int x = 0; x < input.length(); x++)
        {
            INPUT += std::toupper(input[x]);
        }
        if(INPUT.substr((INPUT.length() - 4), 4) == ".TXT")
        {
            return true;
        }
    }

    return false;
}

void Credits()
{
    cls(CLEARSCREEN);
    std::cout << "______________________CREDITS_____________________\n" << std::endl;
    //^^^50 chars wide, left-22, right 21, mid-7
    std::cout << "ASCII Caesar Cipher" << std::endl;
    std::cout << "Author: AmberGraph41161 (AKA Jinwoo Kim)" << std::endl;
    std::cout << "__________________________________________________" << std::endl;
    //^^^50 chars wide
    pause();
    cls(CLEARSCREEN);
}

void pause()
{
    std::cout << "Press any key to continue...";
    getch();

    //I guess getch() really is the best alternative to "system("pause")"

    /*
    std::cin.get();
    //std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    */
}

void cls(bool tf)
{
    if(tf == true)
    {
        system("cls");
    } else
    {
        std::cout << "\n\n  ||CLEARSCREEN||\n\n" << std::endl;
    }
}
