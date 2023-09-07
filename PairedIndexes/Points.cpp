#include "Points.h"


Points::Points(string file_path):file_path(file_path),vertexAndAdjacents() {}
void Points::readPtsFile() {

    ifstream file(file_path);

    if (!file.is_open()) {
        cerr << "Error opening file: " << file_path << endl;
        return;
    }

    int num_points;
    file >> num_points;

    float x, y, z;
    for (int i = 1; i <= num_points; ++i) {
        file >> x >> y >> z;
        points.push_back(Coordinates(x,y,z));
    }

    file.close();
}

void Points::createAdjacentPairs() {
    for (size_t i = 0; i < points.size(); ++i) {
        vector<int> adjacents;
        for (size_t j = i + 1; j < points.size(); ++j) {
            float dx = points[i].getX() - points[j].getX();
            float dy = points[i].getY() - points[j].getY();
            float dz = points[i].getZ() - points[j].getZ();
            float distance = sqrt(dx * dx + dy * dy + dz * dz);

            if (distance <= 1) {
                //cout << "Adjacent Pair: " << points[i].unique_id << " : " << points[j].unique_id << endl;
                adjacents.push_back(j);
            }
        }
        vertexAndAdjacents[i] = adjacents;
    }
}

void Points::prettyPrint() {
    readPtsFile();
    createAdjacentPairs();
    for (const auto& pair : vertexAndAdjacents) {
        int key = pair.first;
        cout << "Point (key) = " << points[key].getX() << ", " << points[key].getY() << ", " << points[key].getZ() << endl;
        cout << "Adjacents(" << key << ") => ";
        for (int val : pair.second) {
            cout << val << " ";
        }
        cout << endl;
    }
}