

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <random>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;        //needed for timer

int main()
{

    int algorithm = 3;
    while ((algorithm != 1) && (algorithm != 2)) {
    cout << "Forward Selection  (1)\nBackward Elimination  (2)\n\nWhich Algorithm would you like to run?:";
    cin >> algorithm;
    if ((algorithm != 1) && (algorithm != 2)) {
        cout << "invalid input choose 1 or 2\n\n";
    }
}
    string line;
    double num = 0.0;
    ifstream infile("input_large.txt");
    vector<vector<double>> data;
    while (getline(infile, line)) {
        vector<double> row;
        stringstream ss(line);
        while ((ss.peek())!=EOF) {
            ss >> num;
            row.push_back(num);             //pushes number into row
        }
        data.push_back(row);                //pushes row into data
    }

    vector<int> solution = {};
    vector<int> current_set = {};

    if (algorithm == 2) {
        for (int e = 1; e < data[0].size(); e++) {
            current_set.push_back(e);
        }
    }
    cout << "set = { ";
    for (int i = 0; i < current_set.size(); i++) {
        cout << current_set[i] << " ";
    }
    cout << " }\n";
    
    int bestsetsize = 0;
    double bestacc = 0;
    double accuracy;
    int k = 0;
    int size = data[0].size();
    if (algorithm == 2)
        size--;

    auto start = high_resolution_clock::now();                       //starts timer

    for (int i = 1; i < size; i++) {
        cout << "On the " << i << "th level of search tree\n";
        int feature_to_add;
        double best_so_far = -1;

        for (k = 1; k < data[0].size(); k++) {
           
            bool check;

            if (algorithm == 1) {
                check = !((find(current_set.begin(), current_set.end(), k) != current_set.end()));
            }
            else {
                check = ((find(current_set.begin(), current_set.end(), k) != current_set.end()));
            }
            

            if (check) { 
                //cout << "Consider adding " << k << " feature\n";
                int number_correctly_classfied = 0;

                for (int c = 0; c < data.size(); c++) {
                    double nearest_neighbor_distance = 5000000;
                    int nearest_neighbor_location = 5000000;
                    double nearest_neighbor_label;
                    double lable_object_to_classify = data[c][0];
                    
                    for (int d = 0; d < data.size(); d++) {

                        if (c != d) {
                            double distance = 0;


                            for (int e = 0; e < current_set.size(); e++) {
                                distance += pow((data[c][current_set[e]] - data[d][current_set[e]]), 2);
                            }
                            if (algorithm == 2) {
                                distance -= pow((data[c][k] - data[d][k]), 2);
                            }
                            else {
                                distance += pow((data[c][k] - data[d][k]), 2);
                            }
                            distance = sqrt(abs(distance));
                           //cout << "Distance = " << distance << endl;

                            

                            if (distance < nearest_neighbor_distance) {
                                //cout << "new nearest = " << d << endl;
                                nearest_neighbor_distance = distance;
                                nearest_neighbor_location = d;
                                nearest_neighbor_label = data[nearest_neighbor_location][0];
                               //cout << "label = " << lable_object_to_classify <<   " nearest = " << nearest_neighbor_label << endl;
                            }
                           // cout << "Ask if " << c << " = " << lable_object_to_classify << " is nearest neigbour with " << d << endl;
                        }

                    }        
                if (lable_object_to_classify == nearest_neighbor_label) {
                number_correctly_classfied++;}
                   
                }

            //cout << "number correct = " << number_correctly_classfied << " number checked = " << data.size() << endl;
            accuracy = ((double)number_correctly_classfied/(double)((data.size())-1));
           // cout << "Accuracy = " << accuracy << endl;
                    if (accuracy > best_so_far) {
                        best_so_far = accuracy;
                            feature_to_add = k;
                            solution.clear();
                            for (int z = 0; z < current_set.size(); z++) {
                                solution.push_back(current_set[z]);
                        }
                    }
                   
            }

        }
        if (algorithm == 2) {
            cout << "On level " << i << " remove feature " << feature_to_add << " from set\nAccuracy = "<< best_so_far << endl;
            //vector<int>::iterator it = find(current_set.begin(), current_set.end(), feature_to_add);
            //cout << "Erase " << *it << endl;

            current_set.erase(find(current_set.begin(), current_set.end(), feature_to_add));
            //cout << "set = { ";
            //for (int i = 0; i < current_set.size(); i++) {
            //    cout << current_set[i] << " ";
            //}
            //cout << " }\n";
        }
        else {
            current_set.push_back(feature_to_add);  
            cout << "On level " << i <<  " added feature " <<  feature_to_add << " to set\nAccuracy = " << best_so_far << endl;
        }
      
        if (best_so_far > bestacc) {
            bestacc = best_so_far;
            bestsetsize = i;
        }
    }



    if (algorithm == 1) {
        cout << "set = { ";
        for (int i = 0; i < bestsetsize; i++) {
            cout << current_set[i] << " ";
        }

        cout << "}\nwith an accuracy of " << bestacc << endl;
    }
    else {
        cout << "\nBest set = { ";
        for (int i = 0; i < solution.size(); i++) {
            cout << solution[i] << " ";
        }
        cout << "}\nwith an accuracy of " << bestacc << endl;
    } 

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);        //timer stuff
    cout << "Time taken by function: "                          //outputs results
        << duration.count() << " seconds" << endl;

}

