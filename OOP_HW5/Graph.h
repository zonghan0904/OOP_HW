#ifndef GRAPH_H
#define GRAPH_H

# include <iostream>
# include <fstream>
using namespace std;

# define SIZE 100
struct node{
    int value = 0;
    int d_time = 0;
    int f_time = 0;
    char color = 'w';
    int adj[SIZE];
    int adjcount = 0;
};

class Graph{
public:
    Graph();
    ~Graph();
    void addnode(int);
    node *findnode(int);
    void draw_edge(int, int);
    void DFS();
    void DFS_visit(node &);
    void TP_sort(fstream &);
    void draw_relation();
    void clear();
private:
    int length;
    node vertice[SIZE];
    int time;
};

#endif
