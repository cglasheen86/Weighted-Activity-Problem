#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

struct activity{
    bool operator()(activity a1, activity a2){
	return(a1.end_time < a2.end_time);
    }
    int start_time;
    int end_time;
    int weight;
}activityComp;

int weighted_activity_Recursion(int num_items, vector<activity> activities);
int weighted_activity_Recursion_Helper(int num_items, vector<activity> activities);
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
    sort(activities.begin(), activities.end(), activityComp);
    for(int i = 0; i < activities.size(); i++){
        cout << activities[i].start_time << ", " << activities[i].end_time << ", " << activities[i].weight << endl;
    }
    weighted_activity_Recursion(activities.size(), activities);
}

int weighted_activity_Recursion(int num_items, vector<activity> activities){
    cout << weighted_activity_Recursion_Helper(activities.size(), activities) << endl;
}

int weighted_activity_Recursion_Helper(int num_items, vector<activity> activities){
    if(num_items == 1) return activities[0].weight;
    int weight_if_included = activities[num_items - 1].weight;
    int i = find_conflict_index(activities,num_items);
    if(i != -1) weight_if_included += weighted_activity_Recursion_Helper(i+1, activities);
    int weight_if_excluded = weighted_activity_Recursion_Helper(num_items - 1, activities);
    return max(weight_if_included, weight_if_excluded);
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

void print_optimal_activities(vector<activity> activities, int max_index){
}
