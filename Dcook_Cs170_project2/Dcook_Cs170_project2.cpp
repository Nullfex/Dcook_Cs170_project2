

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
#include <random>
#include <cmath>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;        //needed for timer

int main()
{

    int algorithm = 3;              //holds what algorithm to use 1 or 2
    while ((algorithm != 1) && (algorithm != 2)) {
    cout << "Forward Selection  (1)\nBackward Elimination  (2)\n\nWhich Algorithm would you like to run?:";
    cin >> algorithm;
    if ((algorithm != 1) && (algorithm != 2)) {
        cout << "invalid input choose 1 or 2\n\n";                  //takes which algorithm to use
    }
}
    cout << fixed;                  //sets how accurate our output values will be .00
    cout << setprecision(1);
    string line;
    double num = 0.0;
    ifstream infile("input_large.txt");             //input file
    vector<vector<double>> data;                    //holds data 2d vector
    while (getline(infile, line)) {                 //fills data with file
        vector<double> row;
        stringstream ss(line);
        while ((ss.peek())!=EOF) {
            ss >> num;
            row.push_back(num);             //pushes number into row
        }
        data.push_back(row);                //pushes row into data
    }

    vector<int> solution = {};              //holds the best solution 
    vector<int> current_set = {};           //holds current chosen set

    if (algorithm == 2) {
        for (int e = 1; e < data[0].size(); e++) {  //fills current_set with all 
            current_set.push_back(e);
        }
    }
    cout << "set = { ";
    for (int i = 0; i < current_set.size(); i++) {  //outputs what the set is at start debugging and whatnot
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

    for (int i = 1; i < size; i++) {                                //goes though whole whole set -- on elimination to avoid breaking vector
        cout << "On the " << i << "th level of search tree\n";
        int feature_to_add;                                         //the location of the feature to add or remove
        double best_so_far = -1;                                    //best choice value

        for (k = 1; k < data[0].size(); k++) {                      //goes though set taking k
           
            bool check;                                             //for forward checks that k is not in set for eliminaiton checks k is in set

            if (algorithm == 1) {
                check = !((find(current_set.begin(), current_set.end(), k) != current_set.end()));
            }
            else {
                check = ((find(current_set.begin(), current_set.end(), k) != current_set.end()));
            }
            

            if (check) {                                            //check
                //cout << "Consider adding " << k << " feature\n";
                int number_correctly_classfied = 0;                 //number that was correct

                for (int c = 0; c < data.size(); c++) {             //calculates accuracy 
                    double nearest_neighbor_distance = 5000000;     //just large number to start
                    int nearest_neighbor_location = 5000000;
                    double nearest_neighbor_label;
                    double lable_object_to_classify = data[c][0];   //type
                    
                    for (int d = 0; d < data.size(); d++) {         //searches for nearest

                        if (c != d) {
                            double distance = 0;            


                            for (int e = 0; e < current_set.size(); e++) {     //calcuates distance from c to d
                                distance += pow((data[c][current_set[e]] - data[d][current_set[e]]), 2);
                            }
                            if (algorithm == 2) {
                                distance -= pow((data[c][k] - data[d][k]), 2);
                            }
                            else {
                                distance += pow((data[c][k] - data[d][k]), 2);
                            }
                            distance = sqrt(abs(distance));                 
                            if (distance < nearest_neighbor_distance) {     //if e is nearest sets variables
                                
                                nearest_neighbor_distance = distance;
                                nearest_neighbor_location = d;
                                nearest_neighbor_label = data[nearest_neighbor_location][0];
                               
                            }
                          
                        }
                    }        
                if (lable_object_to_classify == nearest_neighbor_label) {
                number_correctly_classfied++;}      //if guess is correct ++
                } 
            accuracy = ((double)number_correctly_classfied/(double)((data.size())-1));
                        
                        if (accuracy > best_so_far) {       //if calculated accuracy is best new feature to add
                        best_so_far = accuracy;
                            feature_to_add = k;
                           
                    }
                   
            }

        }
        if (algorithm == 2) {       //algorithm 1 adds feature to add 2 removes feature to add
            cout << "On level " << i << " remove feature " << feature_to_add << " from set\nAccuracy = "<< best_so_far*100 << "%" << endl;
            current_set.erase(find(current_set.begin(), current_set.end(), feature_to_add));    
        }
        else {
            current_set.push_back(feature_to_add);  
            cout << "On level " << i <<  " added feature " <<  feature_to_add << " to set\nAccuracy = " << best_so_far*100 << "%" << endl;
        }
      
        if (best_so_far > bestacc) {
            bestacc = best_so_far;
            bestsetsize = i;
            solution.clear();               //sets solution to current solution
            for (int z = 0; z < current_set.size(); z++) {
                solution.push_back(current_set[z]);
            }
        }
    }



    if (algorithm == 1) {               //outputs
        cout << "Best set = { ";
        for (int i = 0; i < bestsetsize; i++) {
            cout << current_set[i] << " ";
        }

        cout << "}\nwith an accuracy of " << bestacc*100 << "%" << endl;
    }
    else {
        cout << "\nBest set = { ";      //outputs
        for (int i = 0; i < solution.size(); i++) {
            cout << solution[i] << " ";
        }
        cout << "}\nwith an accuracy of " << bestacc*100 << "%" << endl;
    } 

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - start);        //timer stuff
    cout << "Time taken by function: "                          //outputs results
        << duration.count() << " seconds" << endl;

}

