#ifndef AED_T2_MENU_H
#define AED_T2_MENU_H


#include <iostream>
#include <vector>
#include <string>
#include "files_reader.h"

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;


class Menu {
private:

    Location localStart, localEnd;
    string codeStart, codeEnd;
    int footDistance = 200;

    static bool menuConfirmationPrompt();

public:

    enum STATE {
        location, criteria, result, close
    };

    STATE locationMenu();

    STATE criteriaMenu();

    static STATE resultMenu();

    void start();

    void minStops();

    static void minDistance();

    static void minZones();

    static void minSwaps();

    void locationStops();

    void locationCords();

    void askFootDistance();


};

string trimStr(istream &ios, string str);

bool emptyStream(istream &ios);

#endif