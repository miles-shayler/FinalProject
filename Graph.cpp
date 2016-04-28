#include "Graph.h"

#include <vector>
#include <queue>

using namespace std;
Graph::Graph(){
}
Graph::~Graph(){

}
vertex * Graph::findVertex(std::string name){
    for(int i = 0; i < vertices.size(); i++) if(vertices[i].name == name) return &vertices[i];
    return NULL;
}
void Graph::addEdge(std::string v1, std::string v2, int weight){
    vertex * city1 = findVertex(v1);
    vertex * city2 = findVertex(v2);
    adjVertex adj1;
    adj1.weight = weight;
    adj1.v = city2;
    city1->adj.push_back(adj1);
}
void Graph::addVertex(std::string name){
    vertex vert;
    vert.parent = NULL;
    vert.name = name;
    vert.district = -1;
    vert.distance = 50000000;
    vert.visited = false;
    vertices.push_back(vert);
}
void Graph::assignDistricts(){
    int count = 0;
    std::queue<vertex*> bfs;
    for(int i = 0 ; i < vertices.size() ; i++){
        if(vertices[i].district < 0){
            count ++;
            bfs.push(& vertices[i]);
            while(!bfs.empty()){
                vertex *n = bfs.front();
                n -> district = count;
                bfs.pop();
                for(int x = 0 ; x < n->adj.size() ; x++){
                    if(n -> adj[x].v ->district < 0){
                        bfs.push(n-> adj[x].v);
                    }
                }

            }
        }
    }
}

void Graph::findClosest(std::string starting){
    vertex * vert = findVertex(starting);
    adjVertex * temp;
    for(int i = 0; i < vert->adj.size(); i++)
        if(vert->adj[i].weight < temp->weight){
            temp = &vert->adj[i];
        }
    cout << "Closest City is: " << temp->v->name << " a distance of: " << temp->weight << " away." << endl;
}
void Graph::shortestPathDykstra(std::string starting, std::string destination){
    vector<vertex *> solved;
    vertex * solvedV = NULL;
    vertex * startV = NULL;
    vertex * endV = NULL;
    vertex * temp = NULL;
    vertex * parent = NULL;
    startV = findVertex(starting);
    endV = findVertex(destination);
    for(int i = 0; i < vertices.size(); i ++) vertices[i].visited = false;
    if(startV == NULL || endV == NULL) {
        cout << "one or more cities doesn't exist" << endl;
        return;
    }
    if(startV->district == -1) {
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }
    if(startV->district == endV->district){
        startV->distance = 0;
        startV->visited = true;
        solved.push_back(startV);
        while(!endV->visited){
            int mdist = 500000;
            int dist;
            solvedV = NULL;
            for(int j = 0; j < solved.size(); j++){
                temp = solved[j];
                for(int k = 0; k < temp->adj.size(); k++){
                    if(!temp->adj[k].v->visited){
                        dist = temp->distance + temp->adj[k].weight;
                        if(dist < mdist){
                            solvedV = temp->adj[k].v;
                            mdist = dist;
                            parent = temp;
                        }

                    }
                }
            }
            solvedV->distance = mdist;
            solvedV->visited = true;
            solvedV->parent = parent;
            solved.push_back(solvedV);
        }
        vertex * current = endV;
        vector<vertex *> printV;
        while(current != NULL){
            printV.push_back(current);
            if(current -> parent != NULL) current = current->parent;
            else break;
        }
        cout << printV.size() - 1;
        for(unsigned i = printV.size(); i-- > 0;){
            cout << "," << printV[i]->name;
        }
        cout << endl;
    }else{
        cout << "No safe path between cities" << endl;
    }


}

void Graph::shortestPath(string startS, string endS){
    vertex * start = NULL;
    vertex * end = NULL;
    for(int i = 0 ; i < vertices.size() ; i++){
        if(vertices[i].name == startS) start = &vertices[i];
        if(vertices[i].name == endS) end = &vertices[i];
        vertices[i].visited == false;
    }

    if(start == NULL || end == NULL){
        cout << "One or more cities doesn't exist" << endl;
        return;
    }
    if(start->district == end->district ){
        std::queue<vertex*> bfs;
        start -> visited = true;
        start -> distance = 0;
        bfs.push(start);
        while(!bfs.empty()){
            vertex *n = bfs.front();
            bfs.pop();
            for(int x = 0 ; x < n->adj.size() ; x++){
                if(!n -> adj[x].v->visited){
                    n->adj[x].v->distance = n->distance + 1;
                    n->adj[x].v->parent = n;

                    if(n->adj[x].v->name == end -> name){
                        vertex * travel = end;
                        vector<vertex*> path;
                        while(travel != NULL){
                            path.push_back(travel);
                            travel = travel -> parent;
                        }
                        cout << path.size() - 1;
                        for (int i = path.size() - 1 ; i >= 0 ; i--){
                            cout << "," << path[i]->name;
                        }
                        cout << endl;
                        return;
                    }
                    else{
                        n->adj[x].v->visited = true;
                        bfs.push(n->adj[x].v);

                }
            }

        }
    }

    }else{
        cout << "No safe path between cities" << endl;
        return;
    }
}
void Graph::printVert(){
    for(int i = 0; i < vertices.size(); i++){
    cout<< vertices[i].district <<":"<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1) cout<<"***";
            else cout << endl;
        }
    }
}




