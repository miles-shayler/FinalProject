
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
    int choice = 0;
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


        // menu print
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Find districts" << endl;
        cout << "3. Find shortest path" << endl;
        cout << "4. Find shortest path using Dykstra's Algorithm" << endl;
        cout << "5. Find Closest City to you" << endl;
        cout << "6. Quit" << endl;

        // grab user choice
    while(cin>>choice){
        switch(choice){

        case 1:
            cin.ignore();
           // city.printVertices();
            city.printVert();
            break;

        // Find districts
        case 2:
            cin.ignore();
            city.assignDistricts();
            break;


        // print tree in alphabetical order based off of the root
        case 3:
            //if(//!city.districtsFound()){
               // cout << "Please identify the districts before checking distances" << endl;
            //}
            //else{
            cin.ignore();
            string start;
            string end;
            cout << "Enter a starting city:" << endl;
            getline(cin,start);
            cout << "Enter an ending city:" << endl;
            getline(cin,end);
            city.shortestPath(start,end);
            break;

        case 4:
            cin.ignore();
            string start;
            string end;
            cout << "Enter a starting city:" << endl;
            getline(cin,start);
            cout << "Enter an ending city:" << endl;
            getline(cin,end);
            city.shortestPathDykstra(start,end);
            break;

        case 5:
            cin.ignore();
            string start;
            cout << "Enter the city you are in: " << endl;
            getline(cin,start);
            city.findClosest(start);
            break;

        case 6:
            // exit program
            cout << "Goodbye!" << endl;
            inFile.close();
            return 0;
            break;

        default:
            cout<<"Please Enter a selection 1-6"<<endl;
            break;


        // menu print
        cout << "======Main Menu======" << endl;
        cout << "1. Print vertices" << endl;
        cout << "2. Find districts" << endl;
        cout << "3. Find shortest path" << endl;
        cout << "4. Find shortest path using Dykstra's Algorithm" << endl;
        cout << "5. Find Closest City to you" << endl;
        cout << "6. Quit" << endl;
        }
    }
}

