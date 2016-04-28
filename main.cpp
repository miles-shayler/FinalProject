#include <iostream>
#include <fstream>
#include <sstream>
#include "Graph.h"
#include <stdlib.h>
#include <istream>
using namespace std;

int main(char * argv[], int argc) {

    //create graph
    Graph city = Graph();
    ifstream inFile;
    inFile.open("zombieCities.txt");
    string line;
    string element;
    vector<string> cityNames;
    std::string::size_type sz;

    int number;
    int choice;
    if(inFile.good()){

        getline(inFile,line);
        stringstream ss(line);
        while(getline(ss,element,',')){
            if(element != "cities"){
                city.addVertex(element);
                cityNames.push_back(element);
            }
        }
        int counter = 0;
        while(getline(inFile,line)){
            int counter2 = 0;
            //cout << line << endl;
            std::istringstream sd(line);
            getline(sd,element,',');
            while(getline(sd,element,',')){
                istringstream(element) >> number;
                if(number != -1 && number != 0) city.addEdge(cityNames[counter],cityNames[counter2],number);
                counter2 ++;
            }

            counter ++;
        }
    }
    while(choice != 6){

        // menu print
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Find districts" << endl;
        cout << "3. Find shortest path" << endl;
        cout << "4. Find shortest path using Dykstra's Algorithm" << endl;
        cout << "5. Find Closest City to you" << endl;
        cout << "6. Quit" << endl;

        // grab user choice
        cin >> choice;
        cin.ignore();

        if(choice == 1){
           // city.printVertices();
            city.printVert();
        }

        // Find districts
        else if(choice == 2){
           city.assignDistricts();

        }

        // print tree in alphabetical order based off of the root
        else if(choice == 3){
            //if(//!city.districtsFound()){
               // cout << "Please identify the districts before checking distances" << endl;
            //}
            //else{
            string start;
            string end;
            cout << "Enter a starting city:" << endl;
            getline(cin,start);
            cout << "Enter an ending city:" << endl;
            getline(cin,end);
            city.shortestPath(start,end);


        }
        else if(choice == 4){
            string start;
            string end;
            cout << "Enter a starting city:" << endl;
            getline(cin,start);
            cout << "Enter an ending city:" << endl;
            getline(cin,end);
            city.shortestPathDykstra(start,end);
        }
        else if(choice == 5){
            string start;
            cout << "Enter the city you are in: " << endl;
            getline(cin,start);
            city.findClosest(start);
        }


    }

    // exit program
    cout << "Goodbye!" << endl;

    return 0;
}

