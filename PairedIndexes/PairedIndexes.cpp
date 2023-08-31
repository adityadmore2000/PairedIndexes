#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include<unordered_map>

using namespace std;


/// <summary>
/// The code reads pts file, and extracts x,y,z coordinates, assigns a unique id to each point
/// Then, it displays adjacent points
/// The adjacent points are stored in an unordered map of <int,vector<int>>
/// 
/// Next, We'd like to display them in x,y,z format
/// </summary>
struct Point3D {
	float x;
	float y;
	float z;
	int unique_id;
};

vector<Point3D> readPtsFile(const std::string& file_path, int& unique_id_counter) {
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
		points.push_back({ x, y, z, unique_id_counter++ }); // Assign the unique number and increment the counter
	}

	file.close();
	return points;
}

void createAdjacentPairs(const vector<Point3D>& points, std::unordered_map<int, vector<int>>& vertexAndAdjacents)
{
	for (size_t i = 0; i < points.size(); ++i)
	{
		vector<int> adjacents;
		for (size_t j = i + 1; j < points.size(); ++j) 
		{
			float dx = points[i].x - points[j].x;
			float dy = points[i].y - points[j].y;
			float dz = points[i].z - points[j].z;
			float distance = sqrt(dx * dx + dy * dy + dz * dz);


			if (distance <= 1) 
			{
				cout << "Adjacent Pair: " << points[i].unique_id << " : " << points[j].unique_id << endl;
				// adjacents are represented as:
				// 0-><1,2>
				adjacents.push_back(j);

			}

		}
		vertexAndAdjacents[i] = adjacents;
	}
}


void prettyPrint(const vector<Point3D>& points, std::unordered_map<int, vector<int>>& vertexAndAdjacents) {

	std::vector<int> keys;
	// store keys of unordered map
	for (const auto& pair : vertexAndAdjacents) {
		keys.push_back(pair.first);
	}

	for (auto key : keys) {
		std::cout <<" Points(key) = "<<points[key].x;
		std::cout << "Adjacents(" << key << ")" << " => ";
		for (auto val : vertexAndAdjacents[key])
		{
			std::cout << val << " ";
		}
		std::cout << std::endl;
	}
}
int main() {
	string folder_path = "C:\\Users\\sez5954\\source\\repos\\projects\\C# tutorials\\PairedIndexes";
	int unique_id_counter = 1; // Start the unique ID from 1

	unordered_map<int, vector<int>> vertexAndAdjacents;
	WIN32_FIND_DATAA find_data;
	HANDLE find_handle = FindFirstFileA((folder_path + "/*.pts").c_str(), &find_data);

	if (find_handle == INVALID_HANDLE_VALUE) {
		cerr << "Error opening directory or no .pts files found: " << folder_path << endl;
		return 1;
	}

	vector<Point3D> points;
	do {
		string file_name = find_data.cFileName;
		string file_path = folder_path + "/" + file_name;

		points = readPtsFile(file_path, unique_id_counter);

		cout << "File: " << file_path << endl;
		for (const auto& point : points) {
			cout << point.unique_id << " Coordinates: (" << point.x << ", " << point.y << ", " << point.z << ")" << endl;
		}

		createAdjacentPairs(points, vertexAndAdjacents);


	} while (FindNextFileA(find_handle, &find_data) != 0);

	//FindClose(find_handle);
	//prettyPrint(points, vertexAndAdjacents);
	return 0;
}
