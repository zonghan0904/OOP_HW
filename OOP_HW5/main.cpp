# include <iostream>
# include "Graph.h"
using namespace std;

int main(){
    fstream fin;
    fin.open("sample data.txt", ios_base::in);
    if (!fin){
        cerr << "[ERROR] Could not find \"sample.txt\" file.\n";
        return -1;
    }
    fstream fout;
    fout.open("TP_Sort_0511076.txt", ios_base::out);
    if (!fout){
        fin.close();
        cerr << "[ERROR] Could not create the output file.\n";
        return -1;
    }
    int layers, constrains, vertice, node1, node2;
    char skip;

    Graph graph;
    while (fin >> layers){
        for (int i = 0; i < layers; i++){
            fin >> vertice;
            graph.addnode(vertice);
        }
        fin >> constrains;
        for (int i = 0; i < constrains; i++){
            fin >> node1 >> skip >> node2;
            graph.draw_edge(node1, node2);
        }
        graph.DFS();
        graph.TP_sort(fout);
        graph.clear();
    }

    fin.close();
    fout.close();

    return 0;
}
