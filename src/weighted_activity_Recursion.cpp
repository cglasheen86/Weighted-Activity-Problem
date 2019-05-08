#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct activity{
    bool operator()(activity a1, activity a2){
	return(a1.end_time < a2.end_time);
    }
    int start_time;
    int end_time;
    int weight;
}activityComp;

struct solution{
    vector<activity> included;
    int max_val = 0;
};

int weighted_activity_Recursion(int num_items, vector<activity> activities);
solution weighted_activity_Recursion_Helper(int num_items, vector<activity> activities, solution &s);
int find_conflict_index(vector<activity> activities, int num_items);
void print_optimal_activities(vector<activity> activities, int max_index);

int main(int argc, char** argv){
    if(argc < 2){
	cout << "Error: no input file specified" << endl;
	return 0;
    }
    string input_line;
    string input_file = argv[1];
    string output_file = argv[2];
    ifstream infile1(input_file);
    //ofstream outfile(output_file);
    //cout.rdbuf(outfile.rdbuf());
    vector<activity> activities;
    while(getline(infile1, input_line)){
	stringstream ss(input_line);
        string line;
        vector<string> splittedStrings;
        while (std::getline(ss, line, ','))
        {
            splittedStrings.push_back(line);
        }
        activity temp_activity;
	temp_activity.start_time = stoi(splittedStrings[0]);
	temp_activity.end_time = stoi(splittedStrings[1]);
	temp_activity.weight = stoi(splittedStrings[2]);
	activities.push_back(temp_activity);
    }
    high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now(); //Start
    sort(activities.begin(), activities.end(), activityComp);
    //for(int i = 0; i < activities.size(); i++){
    //    cout << activities[i].start_time << ", " << activities[i].end_time << ", " << activities[i].weight << endl;
    //}
    weighted_activity_Recursion(activities.size(), activities);
    high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    
    //Calculates the execution time by subtracting the start time from the end time
    double executionTime = duration_cast<nanoseconds>(t2 - t1).count();
    executionTime *= 1e-9;
    cout << executionTime << endl;
}

int weighted_activity_Recursion(int num_items, vector<activity> activities){
    solution s;
    solution x = weighted_activity_Recursion_Helper(activities.size(), activities, s);
    for(int i = 0; i < x.included.size(); i++) cout << x.included[i].start_time << ", " << x.included[i].end_time << ", " << x.included[i].weight << endl;
    cout << x.max_val << endl;
}

solution weighted_activity_Recursion_Helper(int num_items, vector<activity> activities, solution &s){
    if(num_items == 1){
	s.included.push_back(activities[0]);
 	s.max_val = activities[0].weight;
	return s;
    }

    solution weight_if_excluded;
    weight_if_excluded.included = s.included;
    weight_if_excluded.max_val = weighted_activity_Recursion_Helper(num_items - 1, activities, weight_if_excluded).max_val;

    solution weight_if_included;
    s.included.push_back(activities[num_items-1]);
    weight_if_included.included = s.included;
    weight_if_included.max_val = activities[num_items - 1].weight;
    int i = find_conflict_index(activities,num_items);
    if(i != -1) weight_if_included.max_val += weighted_activity_Recursion_Helper(i+1, activities, weight_if_included).max_val;
    
    int opt = max(weight_if_included.max_val, weight_if_excluded.max_val);
    if(opt == weight_if_included.max_val){
	s.included = weight_if_included.included;
        return weight_if_included;
    }
    else{
	s.included = weight_if_excluded.included;
	return weight_if_excluded;
    }
}

int find_conflict_index(vector<activity> activities, int num_items){
    int current_index = num_items-1;
    int beginning = 0;
    int end = activities.size()-2;
    while(beginning <= end){
	int middle = (beginning + end)/2;
	if(activities[middle].end_time <= activities[current_index].start_time){
	    if(activities[middle+1].end_time <= activities[current_index].start_time)
		beginning = middle + 1;
	    else return middle;
	}
	else end = middle - 1;
    }
    return -1;
}