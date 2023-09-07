#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include<iostream>
#include <fstream>
#include "Coordinates.h"
using namespace std;


class Points
{
private:
    string file_path;
    vector<Coordinates> points;
    unordered_map<int, vector<int>> vertexAndAdjacents;
    static int unique_id;
    void readPtsFile();
    void createAdjacentPairs();
public:
    Points(string file_path);

    void prettyPrint();
};

