// Dcook_Cs170_project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 

using namespace std;

int main()
{

    string line;
    double num = 0.0;
    ifstream infile("input.txt");
    vector<vector<double>> data;
    while (getline(infile, line)) {
        vector<double> row;
        stringstream ss(line);
        while ((ss.peek())!=EOF) {
            ss >> num;
            //cout << num << endl;
            row.push_back(num);             //pushes number into row
        }
        data.push_back(row);                //pushes row into data
    }

    //cout << data.size() << endl;
    //cout << data[0].size() << endl;
    for (int i = 0; i < data.size(); i++) {
        for (int e = 0; e < data[0].size(); e++) {          //assumes that all vectors are same size could cause errors
            cout << data[i][e] << " ";
        }
        cout << endl;
    }


    std::cout << "Hello World!\n";
}

