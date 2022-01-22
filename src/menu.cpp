#include <iomanip>
#include "../include/menu.h"
#include "../include/GraphBuilder.h"

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

bool Menu::menuConfirmationPrompt() {
    char confirm;

    cout << "\nConfirm? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
        return true;
    else {
        cout << "Canceled. Press any key to continue...";
        cin.clear();
        cin.ignore(10000, '\n');
        getchar();
    }


    return false;
}


Menu::STATE Menu::criteriaMenu() {
    char userInput;
    string inputError;

    while (true) {
        system(CLEAR);

        if (!inputError.empty())
            cout << inputError;
        inputError = "";

        cout << "========================" << endl;
        cout << "    Minimum Criteria   " << endl;
        cout << "========================" << endl;
        cout << "  1)  Stops " << endl;
        cout << "  2)  Distance" << endl;
        cout << "  3)  Zones" << endl;
        cout << "  4)  Line Changes" << endl;
        cout << "  5)  Go back  " << endl;
        cout << "  0)  Exit" << endl;
        cout << "========================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "Invalid Input!\n";
                continue;
            }

            switch (userInput) {
                case '0':
                    return close;
                case '1':
                    minStops();
                    return criteria;
                case '2':
                    minDistance();
                    return criteria;
                case '3':
                    minZones();
                    return criteria;
                case '4':
                    minSwaps();
                    return criteria;
                case '5':
                    return location;
                default:
                    cout << "Invalid Input!\n";
                    break;
            }
            continue;

        } else {
            cout << "Invalid Input!\n";
            continue;
        }
    }
}

Menu::STATE Menu::locationMenu() {
    char userInput;
    string inputError;

    while (true) {
        system(CLEAR);

        if (!inputError.empty())
            cout << inputError;
        inputError = "";


        cout << "===========================" << endl;
        cout << "        Location  " << endl;
        cout << "===========================" << endl;
        cout << "    1)  Stops " << endl;
        cout << "    2)  Coordinates" << endl;
        cout << "    3)  Set Foot Distance" << endl;
        cout << "    0)  Exit" << endl;
        cout << "===========================" << endl;
        cout << " > ";

        if ((cin >> userInput)) {
            if (!emptyStream(cin)) {
                cout << "Invalid Input!\n";
                cin.clear();
                cin.ignore(10000, '\n');
                continue;
            }

            switch (userInput) {
                case '0':
                    return close;
                case '1':
                    locationStops();
                    return menuConfirmationPrompt() ? criteria : location;
                case '2':
                    locationCords();
                    return menuConfirmationPrompt() ? criteria : location;
                case '3':
                    askFootDistance();
                    return location;
                default:
                    cout << "Invalid Input!\n";
                    cin.clear();
                    cin.ignore(10000, '\n');
                    getchar();
                    break;
            }
            continue;

        } else {
            cout << "Invalid Input!\n";
            cin.clear();
            cin.ignore(10000, '\n');
            getchar();
            continue;
        }
    }
}


void Menu::minStops() {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    //A melhor combinacao para testar é PSL2 CQ10  e o inverso CQ10 PSL1 porque atravessa o porto por comleto (muito longe)
    string origin = codeStart;
    string destiny = codeEnd;

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<pair<Line, bool>> lines;

    list<int> path = graph.bfs_path(originIndex, destinyIndex, lines);
    cout << "\nNumber of stops: " << graph.getNode(destinyIndex).dist << endl << endl;

    int i = 0;
    for (int &it: path) {
        cout << setw(8) << model.indexToStop[it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].first.name << endl;

        i++;
    }
    getchar();
}

void Menu::minDistance() { // TODO: Repetitive
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = codeStart;
    string destiny = codeEnd;

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<pair<Line, bool>> lines;

    graph.dijkstra_distance(originIndex);
    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines);
    cout << "\nDistance: " << graph.getNode(destinyIndex).dist << endl << endl;

    int i = 0;
    for (int &it: path) {
        cout << setw(8) << model.indexToStop[it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].first.name << endl;

        i++;
    }

    getchar();
}

void Menu::minZones() {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = codeStart;
    string destiny = codeEnd;

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<pair<Line, bool>> lines;

    graph.dijkstra_zones(originIndex);
    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines);
    cout << "\nNumber of Zones: " << graph.getNode(destinyIndex).dist << endl << endl;

    int i = 0;
    for (int &it: path) {
        cout << setw(8) << model.indexToStop[it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].first.name << endl;

        i++;
    }

    getchar();
}

void Menu::minSwaps() {
    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph();

    string origin = codeStart;
    string destiny = codeEnd;

    int originIndex = model.stopToIndex[origin];
    int destinyIndex = model.stopToIndex[destiny];

    vector<pair<Line, bool>> lines;

    graph.dijkstra_lineSwaps(originIndex);
    list<int> path = graph.dijkstra_path(originIndex, destinyIndex, lines);
    cout << "\nNumber of minimum line swaps: " << graph.getNode(destinyIndex).dist << endl << endl;

    int i = 0;
    for (int &it: path) {
        cout << setw(8) << model.indexToStop[it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].first.name << endl;

        i++;
    }

    getchar();
}

void Menu::locationStops() {

    //TODO test if they exist
    cout << "\nStarting stop code: ";
    cin >> codeStart;
    cout << "\nDestination stop code: ";
    cin >> codeEnd;

}

void Menu::locationCords() {

    //TODO test if given inputs are valid
    cout << "\nStarting coordinates (latitude, longitude): ";
    cin >> localStart;
    cout << "\nDestination coordinates (latitude, longitude): ";
    cin >> localEnd;
}


void Menu::askFootDistance() {


    cout << "\nPlease provide the bfsDistance (in meters) you are\n"
            "willing to travel on foot to reach your destination\n"
            "(Current is " << footDistance << "m)\n";
    cout << "\n > ";

    int n;
    if (cin >> n) {
        footDistance = n;
        cout << "\nFoot bfsDistance was set to " << footDistance << " m\n";
    } else {
        cout << "Invalid input!\n";
    }

    cin.clear();
    cin.ignore(10000, '\n');
    getchar();

}

void Menu::start() {

    STATE state = location;

    while (true) {

        system(CLEAR);

        switch (state) {

            case location:
                state = locationMenu();
                break;
            case criteria:
                state = criteriaMenu();
                break;
            case close:
                return;
        }
    }

}



