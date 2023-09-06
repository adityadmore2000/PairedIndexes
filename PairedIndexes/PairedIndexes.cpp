#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <cmath>

using namespace std;

struct Point3D {
    float x;
    float y;
    float z;
    int unique_id;
};

vector<Point3D> readPtsFile(const string& file_path, int& unique_id_counter) {
    vector<Point3D> points;
    ifstream file(file_path);

    if (!file.is_open()) {
        cerr << "Error opening file: " << file_path << endl;
        return points;
    }

    int num_points;
    file >> num_points;

    float x, y, z;
    for (int i = 1; i <= num_points; ++i) {
        file >> x >> y >> z;
        points.push_back({ x, y, z, unique_id_counter++ });
    }

    file.close();
    return points;
}

void createAdjacentPairs(const vector<Point3D>& points, unordered_map<int, vector<int>>& vertexAndAdjacents) {
    for (size_t i = 0; i < points.size(); ++i) {
        vector<int> adjacents;
        for (size_t j = i + 1; j < points.size(); ++j) {
            float dx = points[i].x - points[j].x;
            float dy = points[i].y - points[j].y;
            float dz = points[i].z - points[j].z;
            float distance = sqrt(dx * dx + dy * dy + dz * dz);

            if (distance <= 1) {
                cout << "Adjacent Pair: " << points[i].unique_id << " : " << points[j].unique_id << endl;
                adjacents.push_back(j);
            }
        }
        vertexAndAdjacents[i] = adjacents;
    }
}

void prettyPrint(const vector<Point3D>& points, const unordered_map<int, vector<int>>& vertexAndAdjacents) {
    for (const auto& pair : vertexAndAdjacents) {
        int key = pair.first;
        cout << "Point (key) = " << points[key].x << ", " << points[key].y << ", " << points[key].z << endl;
        cout << "Adjacents(" << key << ") => ";
        for (int val : pair.second) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    string file_path = "C:\\path\\to\\your\\file.pts";
    int unique_id_counter = 1;

    unordered_map<int, vector<int>> vertexAndAdjacents;

    vector<Point3D> points = readPtsFile(file_path, unique_id_counter);

    if (!points.empty()) {
        cout << "File: " << file_path << endl;
        for (const auto& point : points) {
            cout << point.unique_id << " Coordinates: (" << point.x << ", " << point.y << ", " << point.z << ")" << endl;
        }

        createAdjacentPairs(points, vertexAndAdjacents);
        prettyPrint(points, vertexAndAdjacents);
    }

    return 0;
}
