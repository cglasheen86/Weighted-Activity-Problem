#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv){
    string output_name;
    int time_bound;
    int weight_low_bound;
    int weight_high_bound;
    int total_activities;

    cout << "Enter the name of the output file: ";
    cin >> output_name;
    cout << "Enter the total amount of possible start/end times: ";
    cin >> time_bound;
    cout << "Enter the minimum weight: ";
    cin >> weight_low_bound;
    cout << "Enter the maximum weight: ";
    cin >> weight_high_bound;
    cout << "Enter the number of activities: ";
    cin >> total_activities;

    ofstream outfile(output_name);
    
    for(int i = 0; i < total_activities; i++){
        int start_time = rand() % time_bound;
        int end_time = rand() % (time_bound - start_time) + (start_time + 1);
        int weight = rand() % (weight_high_bound - weight_low_bound + 1) + weight_low_bound;
	outfile << start_time << "," << end_time << "," << weight << endl;
    }
}
