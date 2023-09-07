#include <iostream>

#include "Points.h"

using namespace std;

int main() {
    string file_path = "C:\\Users\\sez5954\\Downloads\\demo.pts";
    
    Points points(file_path);

    points.prettyPrint();

    return 0;
}

