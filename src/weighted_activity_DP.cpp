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

int weighted_activity_DP(int num_items, vector<activity> activities);
int find_conflict_index(vector<activity> activities);
void print_optimal_activities(vector<activity> activities, int dp_array[], int max_index);

int main(int argc, char** argv){
    if(argc < 2){
	cout << "Error: no input file specified" << endl;
	return 0;
    }
    string input_line;
    string input_file = argv[1];
    string output_file = argv[2];
    ifstream infile1(input_file);
    ofstream outfile(output_file);
    cout.rdbuf(outfile.rdbuf());
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
    //for(int i = 0; i < activities.size(); i++){
        //cout << activities[i].start_time << ", " << activities[i].end_time << ", " << activities[i].weight << endl;
    //}
    cout << weighted_activity_DP(activities.size(), activities) << endl;
}

int weighted_activity_DP(int num_items, vector<activity> activities){
    int dp_table[num_items + 1] = { 0 };
    activity empty_activity;
    activities.insert(activities.begin(), empty_activity);
    for(int i = 1; i < num_items + 1; i++){
	int x = find_conflict_index(activities);
	dp_table[i] = max(activities[i].weight + dp_table[x], dp_table[i-1]);
    }
    print_optimal_activities(activities, dp_table, num_items);
    return dp_table[num_items];
}

int find_conflict_index(vector<activity> activities){
    int current_index = activities.size()-1;
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

void print_optimal_activities(vector<activity> activities, int dp_table[], int max_index){
    int optimal_value = dp_table[max_index];
    for(int i = 1; i <= max_index; i++){
	if(dp_table[i] == optimal_value){
	    cout << "item " << i << endl;
	    optimal_value -= activities[i].weight;
	    max_index = i-1;
	    i = 1;
	}
    }
}
