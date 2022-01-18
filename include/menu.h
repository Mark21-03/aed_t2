#ifndef AED_T2_MENU_H
#define AED_T2_MENU_H


#include <iostream>
#include <vector>
#include <string>

#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif

using namespace std;


class Menu {

    static bool menuOperationConfirm();

    const vector<void (Menu::*)()> createFuncs = {&Menu::f1};

    const vector<void (Menu::*)()> readFuncs = {&Menu::f1};

    const vector<void (Menu::*)()> updateFuncs = {&Menu::f1};

    const vector<void (Menu::*)()> deleteFuncs = {&Menu::f1};

    void f1(){
        cout<<"To implement..."<<endl;
        getchar();
    }

public:
    void (Menu::*x)(){};
    void mainMenu();
    void subMenu(const string &menuTitle, vector<void (Menu::*)()> funcs);


};

string trimStr(istream &ios, string str);
bool emptyStream(istream &ios);

#endif