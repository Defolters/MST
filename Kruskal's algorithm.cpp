// Kruskal's algorithm.cpp : Defines the entry point for the console application.
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm> 

struct Edge
{
    int parent;
    int child;
    int weight;
};

struct Graph
{
    int V;
    int E;
    struct Edge* edges;
};

struct Graph* createGraph(int V_, int E_)
{
    struct Graph* graph = new Graph;
    graph->V = V_;
    graph->E = E_;
    graph->edges = new Edge[E_];
    return graph;
}

struct SubSet
{
    int parent;
    int rank;
};

int Find(struct SubSet subSets[], int i)
{
    SubSet a = subSets[i];
    if (subSets[i].parent != i)
    {
        subSets[i].parent = Find(subSets, subSets[i].parent);
    }
    return subSets[i].parent;
}

void Union(SubSet subSets[], int x, int y)
{
    int xRoot = Find(subSets, x);
    int yRoot = Find(subSets, y);
    if (subSets[xRoot].rank < subSets[yRoot].rank)
        subSets[xRoot].parent = yRoot;
    else if (subSets[xRoot].rank > subSets[yRoot].rank)
        subSets[yRoot].parent = xRoot;

    else
    {
        subSets[yRoot].parent = xRoot;
        subSets[xRoot].rank++;
    }

}

int comparing(const void* a, const void* b)
{
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    if (a1->weight - b1->weight < 0)
    {
        return -1;
    }
    if (a1->weight - b1->weight > 0)
    {
        return 1;
    }
    return 0;
}

void Kruskal(Graph* graph)
{
    int V = graph->V;
    Edge* result = new Edge[V];
    int edgesMST = 0;
    int edgesAll = 0;

    SubSet* subsets = new SubSet[V];
    for (int i = 0; i < V; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), comparing);


    while (edgesMST < V - 1)
    {
        struct Edge nextEdge = graph->edges[edgesAll++];

        int x = Find(subsets, nextEdge.parent);
        int y = Find(subsets, nextEdge.child);

        if (x != y)
        {
            result[edgesMST++] = nextEdge;
            Union(subsets, x, y);
        }
    }
    int minWeight = 0;
    for (int i = 0; i < edgesMST; ++i)
    {
        minWeight += result[i].weight;
    }
    std::cout << "Min weight == " << minWeight<< std::endl;
}
int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, start2, end1, end2;
    start = std::chrono::system_clock::now();
    std::ifstream file;
    file.open("mst_input_1000.txt");

    if (file.fail())
    {
        exit(1);
    }
    int V = 0;
    int E = 0;

    std::string temp;
    
    std::getline(file, temp);
    std::size_t found = temp.find(" ");
    V = std::stoi(temp.substr(0, found));
    E = std::stoi(temp.substr(found + 1));
    struct Graph* graph = createGraph(V, E);
    for (int i = 0; i < E; i++)
    {
        int par, chi, wei;
        std::getline(file, temp);
        std::size_t found = temp.find(" ");
        std::size_t foundB = temp.rfind(" ");
        par = std::stoi(temp.substr(0, found));
        chi = std::stoi(temp.substr(found + 1, foundB - found));
        wei = std::stoi(temp.substr(foundB + 1));
        graph->edges[i].parent = par-1;
        graph->edges[i].child = chi-1;
        graph->edges[i].weight = wei;
    }


    start2 = std::chrono::system_clock::now();
    Kruskal(graph);
    

    end1 = std::chrono::system_clock::now();
    end2 = std::chrono::system_clock::now();
    std::cout << "\n\nProgram: " << ((double)std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start).count()) / 1000 << " seconds\n";
    std::cout << "Algorithm: " << ((double)std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count()) / 1000 << " seconds\n";
    std::cin.get();
    return 0;
}

