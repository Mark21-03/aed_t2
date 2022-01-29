#ifndef AED_T2_MENU_H
#define AED_T2_MENU_H


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include<set>

#include "files_reader.h"
#include "graph.h"
#include "GraphBuilder.h"
#include "InverseGraph.h"
#include "GraphInverseBuilder.h"


#ifdef _WIN32
#define CLEAR "cls"
#else //In any other OS
#define CLEAR "clear"
#endif


using namespace std;

/**
 * GUI interface of the program
 */
class Menu {

private:
    vector<string> stopsCode = StopsCodesReader("../dataset/stops.csv");
    set<string> disabledLines;
    set<string> disabledStops;
    GraphBuilder model = GraphBuilder();
    GraphInverseBuilder graphInverseBuilder = GraphInverseBuilder();

public:

    Location localStart, localEnd;
    string codeStart, codeEnd;
    int footDistance = 500;
    int stopRadius = 50;
    bool useMLines = true;

    /**
     * Collection of all possible menu states
     */
    enum STATE {
        location, criteria, close, settings
    };


    /**
     * Start menu states showing all possible options
     * @return next state transition
     */
    STATE locationMenu();

    /**
     * Settings menu state allowing for
     * program configurations
     * @return next state transition
     */
    STATE settingsMenu();

    /**
     * Criteria menu state that asks user for the data they want displayed
     * @return next state transition
     */
    STATE criteriaMenu();

    /**
     * Main method of the Menu class. Starts the menu states
     */
    void start();

    /**
     * Calls the minimum bus stops algorithms and sets the graph values
     * @param graph graph to use in the algorithms
     * @param originIndex starting position/node
     * @param destinyIndex ending position/node
     * @return path list all edges needed to reach destiny starting at the origin
     */
    static list<Graph::Edge> minStops(Graph &graph, int originIndex, int destinyIndex);

    /**
     * Calls the minimum geographic distance algorithms and sets the graph values
     * @param graph graph to use in the algorithms
     * @param originIndex starting position/node
     * @param destinyIndex ending position/node
     * @return path list all edges needed to reach destiny starting at the origin
     */
    static list<Graph::Edge> minDistance(Graph &graph, int originIndex, int destinyIndex);

    /**
     * Calls the minimum different bus zones algorithms and sets the graph values
     * @param graph graph to use in the algorithms
     * @param originIndex starting position/node
     * @param destinyIndex ending position/node
     * @return path list all edges needed to reach destiny starting at the origin
     */
    static list<Graph::Edge> minZones(Graph &graph, int originIndex, int destinyIndex);

    /**
     * Calls the minimum bus line swaps algorithms and sets the graph values
     * @param graph graph to use in the algorithms
     * @param originIndex starting position/node
     * @param destinyIndex ending position/node
     * @return path list all edges needed to reach destiny starting at the origin
     */
    static list<InverseGraph::Edge> minSwaps(InverseGraph &graph, int originIndex, int destinyIndex);

    /**
     * Asks user the start and ending stops of their desired route
     */
    void askLocationStops();

    /**
     * Asks user the start and ending geographic location of their desired route
     */
    void askLocationCords();

    /**
     * Prints the the edges path (program result) of the graph based on user choice
     * @param pathCriteria user's menu option
     */
    void showGeneratedPath(int pathCriteria);

    /**
     * Prints the graph's path in a organized and legible way
     * @param graph graph where the path is
     * @param path path to be printed
     */
    void beautifulPrintStops(Graph &graph, list<Graph::Edge> &path);

    /**
     * Prints the graph's path in a organized and legible way
     * @param graph graph where the path is
     * @param path path to be printed
     */
    void beautifulPrintStopsInverse(InverseGraph &graph, list<InverseGraph::Edge> &path);

};


#endif