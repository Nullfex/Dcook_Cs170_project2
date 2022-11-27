// Dcook_Cs170_project2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <random>


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


    vector<int> current_set = {};
    int bestsetsize = 0;
    double bestacc = 0;
    double accuracy;
    int k = 0;

    for (int i = 1; i < data[0].size(); i++) {
        cout << "On the " << i << "th level of search tree\n";
        int feature_to_add;
        double best_so_far = 0;

        for (k = 1; k < data[0].size(); k++) {
            cout << "Consider adding " << k << " feature\n";

            if (!((find(current_set.begin(), current_set.end(), k) != current_set.end()))) {

                accuracy = (rand()%99);

                    if (accuracy > best_so_far) {
                        best_so_far = accuracy;
                            feature_to_add = k;
                    }
                    cout << "Accuracy = " << accuracy << endl;
            }

        }

        current_set.push_back(feature_to_add);
        cout << "On level " << i <<  " added feature " <<  feature_to_add << " to set\n";
        if (best_so_far > bestacc) {
            bestacc = best_so_far;
            bestsetsize = i;
        }
    }

    cout << "set = { ";
    for (int i = 0; i < bestsetsize; i++) {
        cout << current_set[i] << " ";
    }

    cout << "}\nwih an accuracy of " << bestacc;

    //cout << data.size() << endl;
    //cout << data[0].size() << endl;
    //for (int i = 0; i < data.size(); i++) {
    //    for (int e = 0; e < data[0].size(); e++) {          //assumes that all vectors are same size could cause errors
    //        cout << data[i][e] << " ";
    //    }
    //    cout << endl;
    //}





   
}

