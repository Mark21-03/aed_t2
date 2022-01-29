#include "../include/menu.h"
#include "../include/menuAsks.h"


Menu::STATE Menu::criteriaMenu() const {
    char userInput;
    string inputError;

    while (true) {
        (void) system(CLEAR);

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


Menu::STATE Menu::settingsMenu() {

    char userInput;
    string inputError;

    while (true) {
        (void) system(CLEAR);

        if (!inputError.empty())
            cout << inputError;
        inputError = "";

        cout << "====================================" << endl;
        cout << "        Settings  " << endl;
        cout << "====================================" << endl;
        cout << "    1)  Foot Distance \t( " << footDistance << " )" << endl;
        cout << "    2)  Stop Radius \t( " << stopRadius << " )" << endl;
        cout << "    3)  M Lines \t( " << (useMLines ? "YES" : "NO") << " )" << endl;
        cout << "    4)  Disable Stop \t( " << disabledStops.size() << " )" << endl;
        cout << "    5)  Disable Line \t( " << disabledLines.size() << " )" << endl;
        cout << "    6)  Go Back " << endl;
        cout << "    0)  Exit" << endl;
        cout << "====================================" << endl;
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
                    footDistance = askFootDistance();
                    return settings;
                case '2':
                    stopRadius = askStopRadius();
                    return settings;
                case '3':
                    useMLines = askUseMLines();
                    return settings;
                case '4':
                    askDisableStop(stopsCode, disabledStops);
                    return settings;
                case '5':
                    askDisableLine(disabledLines);
                    return settings;
                case '6':
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


Menu::STATE Menu::locationMenu() {

    codeStart = "", codeEnd = "";
    localStart = {}, localEnd = {};

    char userInput;
    string inputError;

    while (true) {
        (void) system(CLEAR);

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
                    return settings;
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


void Menu::start() {
    STATE state = location;
    while (true) {
        (void) system(CLEAR);
        switch (state) {
            case location:
                state = locationMenu();
                break;
            case criteria:
                state = criteriaMenu();
                break;
            case settings:
                state = settingsMenu();
                break;
            case close:
                return;
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


list<InverseGraph::Edge> Menu::minSwaps(InverseGraph &graph, int originIndex, int destinyIndex) {

    graph.dijkstra(originIndex);
    list<InverseGraph::Edge> path = graph.dijkstra_path(originIndex, destinyIndex);
    cout << "\nNumber of minimum line swaps: " << graph.getNode(destinyIndex).dist << endl << endl;
    return path;

}


void Menu::askLocationStops() {

    string input;

    cout << "\nStarting line code: ";
    getline(cin, input);
    if (validStop(stopsCode, disabledStops, input)) {
        stringstream ss(input);
        ss >> codeStart;
    } else cout << "Invalid!";

    cout << "\nDestination line code: ";
    getline(cin, input);
    if (validStop(stopsCode, disabledStops, input)) {
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


//

//


void Menu::showGeneratedPath(int pathCriteria) const {

    vector<pair<Line, bool>> lines;
    list<Graph::Edge> path;

    GraphBuilder model = GraphBuilder();
    GraphInverseBuilder graphInverseBuilder = GraphInverseBuilder();

    Graph graph;
    InverseGraph graph1;

    int originIndex, destinyIndex;

    if (pathCriteria != 4) {
        graph = model.buildGraph(useMLines, stopRadius, disabledLines, disabledStops);
        if (!codeStart.empty()) {
            originIndex = model.stopToIndex[codeStart];
            destinyIndex = model.stopToIndex[codeEnd];
        } else {
            originIndex = geoStartNode;
            destinyIndex = geoEndNode;
            graph.addGeoStartEndNode(localStart, localEnd, footDistance);
        }
    } else {
        graph1 = graphInverseBuilder.buildGraph(useMLines, stopRadius, disabledLines, disabledStops);
        if (!codeStart.empty()) {
            originIndex = graphInverseBuilder.nodeToIndex[pair<string, string>(codeStart, "")];
            destinyIndex = graphInverseBuilder.nodeToIndex[pair<string, string>(codeEnd, "")];
        } else {
            originIndex = graphInverseBuilder.len + 1;
            destinyIndex = graphInverseBuilder.len + 2;
            graphInverseBuilder.addGeoStartEndNode(localStart, localEnd, footDistance);
        }
    }

    list<Graph::Edge> aux;
    list<InverseGraph::Edge> auxInverse;

    switch (pathCriteria) {
        case 1: // min stops
            aux = minStops(graph, originIndex, destinyIndex);
            beautifulPrintStops(graph, model, aux);
            break;
        case 2: // min distance
            aux = minDistance(graph, originIndex, destinyIndex);
            beautifulPrintStops(graph, model, aux);
            break;
        case 3: // min zones
            aux = minZones(graph, originIndex, destinyIndex);
            beautifulPrintStops(graph, model, aux);
            break;
        case 4: // min lines swaps
            auxInverse = minSwaps(graph1, originIndex, destinyIndex);
            beautifulPrintStopsInverse(graph1, graphInverseBuilder, auxInverse);
            break;
        default:
            break;
    }
}



void Menu::beautifulPrintStops(Graph &graph, GraphBuilder &model, list<Graph::Edge> &path) {
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

void Menu::beautifulPrintStopsInverse(InverseGraph &graph, GraphInverseBuilder &model, list<InverseGraph::Edge> &path) {
    string currentLine;
    if (path.empty()) {
        cout << "There is not a valid path. Sorry for the inconvenience!" << endl;
        getchar();
        return;
    }
    
    cout << "Starting at " << model.indexToNode[path.front().origin].first << endl;
    for (const auto &it: path) {
        //string line = lineDirectionName(, it.lineDirection);
        auto p = model.indexToNode[it.origin];
        string line = p.second;

        if (currentLine != line) {
            currentLine = line;
            cout << "Take " << currentLine << endl;
        }

        cout << setw(8) << p.first << "\t" << graph.zones[p.first] << "\t\t"; // TODO: BUS LINE DIRECTION NAME

        cout << endl;
    }
    cout << "Arrive at " << model.indexToNode[path.back().dest].first;

    getchar();
}



