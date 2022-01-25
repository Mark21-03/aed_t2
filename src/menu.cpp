#include <iomanip>
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


Menu::STATE Menu::criteriaMenu() const {
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
                    showGeneratedPath(1);
                    return criteria;
                case '2':
                    showGeneratedPath(2);
                    return criteria;
                case '3':
                    showGeneratedPath(3);
                    return criteria;
                case '4':
                    showGeneratedPath(4);
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

    resetMenuVars();

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
        cout << "    3)  Settings " << endl;
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
                    askLocationStops();
                    return menuConfirmationPrompt() ? criteria : location;
                case '2':
                    askLocationCords();
                    return menuConfirmationPrompt() ? criteria : location;
                case '3':
                    settingsMenu();
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


list<Graph::Edge> Menu::minStops(Graph &graph, int originIndex, int destinyIndex) {

    list<Graph::Edge> path = graph.bfs_path(originIndex, destinyIndex);
    cout << "\nNumber of stops: " << graph.getNode(destinyIndex).dist << endl << endl;

    return path;

}

list<Graph::Edge> Menu::minDistance(Graph &graph, int originIndex, int destinyIndex) {

    graph.dijkstra_distance(originIndex);
    list<Graph::Edge> path = graph.dijkstra_path(originIndex, destinyIndex);
    cout << "\nDistance: " << graph.getNode(destinyIndex).dist << endl << endl;
    return path;

}


list<Graph::Edge> Menu::minZones(Graph &graph, int originIndex, int destinyIndex) {

    graph.dijkstra_zones(originIndex);
    list<Graph::Edge> path = graph.dijkstra_path(originIndex, destinyIndex);
    cout << "\nNumber of Zones: " << graph.getNode(destinyIndex).dist + 1 << endl << endl;
    return path;

}

list<Graph::Edge> Menu::minSwaps(Graph &graph, int originIndex, int destinyIndex) {

    graph.dijkstra_lineSwaps(originIndex);
    list<Graph::Edge> path = graph.dijkstra_path(originIndex, destinyIndex);
    cout << "\nNumber of minimum line swaps: " << graph.getNode(destinyIndex).dist << endl << endl;
    return path;

}

void Menu::askLocationStops() {

    string input;

    cout << "\nStarting stop code: ";
    getline(cin, input);
    if (validStop(input)) {
        stringstream ss(input);
        ss >> codeStart;
    } else cout << "Invalid!";

    cout << "\nDestination stop code: ";
    getline(cin, input);
    if (validStop(input)) {
        stringstream ss(input);
        ss >> codeEnd;
    } else cout << "Invalid!";

}

void Menu::askLocationCords() {

    string input;

    cout << "\nStarting coordinates (latitude, longitude): ";
    getline(cin, input);
    if (!processStoredCords(input, localStart)) {
        stringstream ss(input);
        if (ss >> localStart) {} else { cout << "Invalid!"; }
    }

    cout << "\nDestination coordinates (latitude, longitude): ";
    getline(cin, input);
    if (!processStoredCords(input, localEnd)) {
        stringstream ss(input);
        if (ss >> localEnd) {} else { cout << "Invalid!"; }
    }
}


void Menu::settingsMenu() {

    askUseMLines();


    askFootDistance();

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

void Menu::resetMenuVars() {
    localStart = {}, localEnd = {};
    codeStart = "", codeEnd = "";
}


void Menu::showGeneratedPath(int pathCriteria) const {

    GraphBuilder model = GraphBuilder();
    Graph graph = model.buildGraph(useMLines);
    vector<pair<Line, bool>> lines;
    list<Graph::Edge> path;

    int originIndex, destinyIndex;
    bool isGeo = false;

    if (!codeStart.empty()) {
        originIndex = model.stopToIndex[codeStart];
        destinyIndex = model.stopToIndex[codeEnd];
    } else {
        originIndex = geoStartNode;
        destinyIndex = geoEndNode;
        graph.addGeoStartEndNode(localStart, localEnd, 500);
        isGeo = true;
    }

    switch (pathCriteria) {
        case 1: // min stops
            path = minStops(graph, originIndex, destinyIndex);
            break;
        case 2: // min distance
            path = minDistance(graph, originIndex, destinyIndex);
            break;
        case 3: // min zones
            path = minZones(graph, originIndex, destinyIndex);
            break;
        case 4: // min lines swaps
            path = minSwaps(graph, originIndex, destinyIndex);
            break;
        default:
            break;
    }

    if (isGeo)
        beautifulPrintGeo(graph, model, path);
    else
        beautifulPrintStops(graph, model, path);

}

void Menu::askFootDistance() {
    cout << "\n\nPlease provide the distance (in meters) you are\n"
            "willing to travel on foot to reach your destination\n"
            "(Current is " << footDistance << "m)\n";
    cout << "\n > ";

    int n;
    if (cin >> n) {
        footDistance = n;
        cout << "\nFoot distance was set to " << footDistance << " m\n";
    } else {
        cout << "Invalid input!\n";
    }

    cin.clear();
    cin.ignore(10000, '\n');
    getchar();

}

void Menu::askUseMLines() {
    char confirm;

    cout << "\nDo you want to include M lines (Y / N) ? ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
        useMLines = true;
    else {
        useMLines = false;
        cin.clear();
        cin.ignore(10000, '\n');
    }

}

bool Menu::processStoredCords(const string &input, Location &location) {

    Location temp = location;

    if (input == "CQUEIJO")
        location = geoCQueijo;

    else if (input == "FEUP")
        location = geoFeup;

    else if (input == "FCUP")
        location = geoFcup;

    else if (input == "PASSAL")
        location = geoPassal;

    else if (input == "IKEA")
        location = geoIkea;

    else if (input == "FRANCELOS")
        location = geoFrancelos;

    else if (input == "ALIADOS")
        location = geoAliados;

    else if (input == "BOMSUCESSO")
        location = geoBomSucesso;

    else if (input == "PBOLSA")
        location = geoPalBolsa;

    else if (input == "GSHOP")
        location = geoGaiaShopping;

    else if (input == "NSHOP")
        location = geoNorteShopping;

    else if (input == "CORDOARIA")
        location = geoCordoaria;

    else if (input == "ALFENA")
        location = geoAlfena;

    else if (input == "CAMPANHA")
        location = geoCampanha;

    else if (input == "SOUTO")
        location = geoSouto;

    return (temp.latitude != location.latitude && temp.longitude != location.longitude);


}

string lineDirectionName(const string &name, bool dir) {

    //18 - PASSEIO ALEGRE - CARMO
    stringstream ss(name);

    string codeName, startName, endName;

    getline(ss, codeName, '-');
    getline(ss, startName, '-');
    getline(ss, endName, '-');

    if (dir)
        return codeName + "." + startName + "-" + endName;
    return codeName + "." + endName + "-" + startName;

}

void Menu::fullLinePrint(Graph graph, GraphBuilder model, vector<pair<Line, bool>> lines, const list<int> &path) {

    int i = 0;
    for (int it: path) {
        cout << setw(8) << model.indexToStop[it] << "\t";
        if (i == lines.size()) break;
        cout << lines[i].first.lineDirectionName(lines[i].second) << " ; " << graph.getNode(it).stop.zone << endl;
        i++;
    }
    getchar();

}

void Menu::beautifulPrintGeo(Graph graph, GraphBuilder model, list<Graph::Edge> path) {

    if (path.front().line.name == "__FOOT__") {
        auto it = path.begin();
        advance(it, 1);
        cout << "Walk to " << model.indexToStop[it->dest] << "\n\n";
        path.pop_front();
    }

    string currentLine;

    for (const auto &it: path) {

        string line = lineDirectionName(it.line.name, it.lineDirection);

        if (it.line.name == "__FOOT__") {

            cout << "\nLeave on " << model.indexToStop[it.origin]
                 << " and walk to your destination\n"; // TODO: IS IT RIGHT ?
            break;
        }


        if (currentLine != line) {
            currentLine = line;
            cout << "Take " << currentLine << endl;
        }

        cout << setw(8) << model.indexToStop[it.origin] << "\t" << graph.getNode(it.origin).stop.zone << "\t\t";

        cout << endl;
    }

    getchar();

}


void Menu::beautifulPrintStops(Graph graph, GraphBuilder model, list<Graph::Edge> path) {

    string currentLine;

    cout << "Starting at " << model.indexToStop[path.front().origin] << endl;
    for (const auto &it: path) {
        string line = lineDirectionName(it.line.name, it.lineDirection);

        if (currentLine != line) {
            currentLine = line;
            cout << "Take " << currentLine << endl;
        }

        cout << setw(8) << model.indexToStop[it.dest] << "\t" << graph.getNode(it.dest).stop.zone << "\t\t";

        cout << endl;
    }
    cout << "Arrive at " << model.indexToStop[path.back().dest];

    getchar();

}

bool Menu::validStop(const string &stop) {

    int index = binarySearch(stopsCode, stop);

    return index != -1;
}

