#include "../include/menu.h"


string trimStr(istream &ios, string str) {
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ') + 1);
    return str;
}

bool emptyStream(istream &ios) {
    string bufferContent;
    getline(ios, bufferContent);
    trimStr(ios, bufferContent);
    if (bufferContent.empty())
        return true;
    return false;
}

bool Menu::menuOperationConfirm() {
    char confirm;

    std::cout << "\nConfirm? (Y/N): ";
    std::cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
        return true;
    else
        std::cout << "Canceled. Press any key to continue... ";

    return false;
}


void Menu::mainMenu() {
    char userInput;
    string inputError;

    while (true) {
        int ignoreVar = system(CLEAR);

        if (!inputError.empty())
            cout << inputError;
        inputError = "";


        cout << "=================" << endl;
        cout << "    MAIN MENU     " << endl;
        cout << "=================" << endl;
        cout << "  1)  Create" << endl;
        cout << "  2)  Read" << endl;
        cout << "  3)  Update" << endl;
        cout << "  4)  Delete" << endl;
        cout << "  5)  Others" << endl;
        cout << "  0)  Exit" << endl;
        cout << "================" << endl;
        cout << " > ";


        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "Invalid Input!";
                continue;
            }

            switch (userInput) {
                case '0':
                    exit(0);
                case '1':
                    subMenu("     MENU 1", createFuncs);
                    break;
                case '2':
                    subMenu("     MENU 2", readFuncs);
                    break;
                case '3':
                    subMenu("     MENU 3", updateFuncs);
                    break;
                case '4':
                    subMenu("     MENU 4", deleteFuncs);
                    break;
                default:
                    cout << "Invalid Input!";
                    break;
            }
            continue;

        } else {
            cout << "Invalid Input!";
            continue;
        }
    }
}


void Menu::subMenu(const string &menuTitle, vector<void (Menu::*)()> funcs) {
    char userInput;
    string inputError;

    while (true) {
        int ignoreVar = system(CLEAR);

        if (!inputError.empty())
            cout << inputError;
        inputError = "";

        cout << "=================" << endl;
        cout << menuTitle << endl;
        cout << "=================" << endl;
        cout << "  1)  ..." << endl;
        cout << "  2)  ..." << endl;
        cout << "  3)  ..." << endl;
        cout << "  4)  ..." << endl;
        cout << "  5)  ..." << endl;
        cout << "  6)  Go Back" << endl;
        cout << "  0)  Exit" << endl;
        cout << "================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(std::cin)) {
                cout << "Invalid Input!";
                continue;
            }

            switch (userInput) {
                case '0':
                    exit(0);
                case '1':
                    this->x = funcs[0];
                    ((*this).*(this->x))();
                    break;
                case '2':
                    this->x = funcs[1];
                    ((*this).*(this->x))();
                    break;
                case '3':
                    this->x = funcs[2];
                    ((*this).*(this->x))();
                    break;
                case '4':
                    this->x = funcs[3];
                    ((*this).*(this->x))();
                    break;
                case '5':
                    this->x = funcs[4];
                    ((*this).*(this->x))();
                    break;
                case '6':
                    goto END_MENU;
                default:
                    cout << "Invalid Input!";
                    break;
            }
            continue;
        } else {
            cout << "Invalid Input!";
            continue;
        }
        END_MENU:
        break;
    }
}