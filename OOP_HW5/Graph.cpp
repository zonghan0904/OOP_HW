# include "Graph.h"
Graph::Graph(){
    length = 0;
    time = 0;
}

Graph::~Graph(){
    for (int i = 0; i < length; i++){
        node *node = &vertice[i];
        delete node;
    }
}

void Graph::addnode(int num){
    vertice[length++].value = num;
}

node *Graph::findnode(int num){
    node *ptr;
    for (int i = 0; i < length; i++){
        ptr = &vertice[i];
        if (ptr -> value == num){
            return ptr;
        }
    }
}

void Graph::draw_edge(int above, int below){
    node *down;
    for (int i = 0; i < length; i++){
        node *ptr = &vertice[i];
        if (ptr -> value == below) down = ptr;
    }
    down -> adj[(down->adjcount)++] = above;
}

void Graph::DFS(){
    for (int i = 0; i < length; i++){
        vertice[i].color = 'w';
    }
    time = 0;
    for (int i = 0; i < length; i++){
        if (vertice[i].color == 'w'){
            DFS_visit(vertice[i]);
        }
    }
}

void Graph::DFS_visit(node &visit){
    visit.color = 'g';
    time++;
    visit.d_time = time;
    int counter = visit.adjcount;
    for (int i = 0; i < counter; i++){
        node *nextnode = findnode(visit.adj[i]);
        if (nextnode -> color == 'w'){
            DFS_visit(*nextnode);
        }
    }
    visit.color = 'b';
    time++;
    visit.f_time = time;
}

void Graph::TP_sort(fstream &output){
    int counter = 0;
    int maxtime = 2*length;
    while (counter < length){
        for (int i = 0; i < length; i++){
            if (vertice[i].f_time == maxtime){
                output << vertice[i].value << " ";
                counter++;
            }
        }
        maxtime--;
    }
    output << "\n";
}

void Graph::draw_relation(){
    for (int i = 0; i < length; i++){
        node *ptr = &vertice[i];
        cout << "[" << i << "] : ";
        cout << ptr -> value << "(" << ptr -> d_time
             << "/" << ptr -> f_time << ")\n";
    }
}

void Graph::clear(){
    for (int i = 0; i < length; i++){
        vertice[i].value = 0;
        vertice[i].d_time = 0;
        vertice[i].f_time = 0;
        vertice[i].color = 'w';
        vertice[i].adjcount = 0;
    }
    length = 0;
    time = 0;
}
