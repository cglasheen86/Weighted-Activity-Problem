#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <string>
#include <chrono>
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
void print_optimal_activities(vector<activity> activities, vector<activity> sol, int dp_array[], int max_index);

int main(int argc, char** argv){
    if(argc < 2){
	cout << "Error: no input file specified" << endl;
	return 0;
    }
    string input_file = argv[1];
   // string output_file = argv[2];
    ifstream infile1(input_file);
	ofstream output_file;
    //cout.rdbuf(outfile.rdbuf());
    vector<activity> activities;
	activity temp_act;		
	int s, e, w;
	char c;
	while (infile1 >> s >> c >> e >> c >> w) {
		temp_act.start_time = s;
		temp_act.end_time = e;
		temp_act.weight = w;
		activities.push_back(temp_act);
	}
	
	output_file.open(argv[2], fstream::in | fstream::out | fstream::trunc);
	
    sort(activities.begin(), activities.end(), activityComp);
   // for(int i = 0; i < activities.size(); i++){
      //  cout << activities[i].start_time << ", " << activities[i].end_time << ", " << activities[i].weight << endl;
   // }
	
	cout << "Total Weight: " << weighted_activity_DP(activities.size(), activities) << endl;
	return 0;
   
}

int latest_non_conflict(vector<activity> a, int num_act) {
	for (int i = num_act - 1; i >= 0; i--) {
		if (a[i].end_time <= a[num_act].start_time) {
			return i;
		}
	} return -1;
}
int weighted_activity_DP(int num_items, vector<activity> activities){
	vector<activity> solution;

    int dp_table[num_items + 1] = { 0 };
	

    activity empty_activity;
	empty_activity.weight = 0;
	activities.insert(activities.begin(), empty_activity);
	

	for (int i = 1; i < num_items + 1; i++) {
		int x = latest_non_conflict(activities, i);
		int curr_weight = activities[i].weight;
		if (x != -1) { curr_weight += dp_table[x]; }
		if (curr_weight > dp_table[i-1]) {
			
		}

		dp_table[i] = max(curr_weight, dp_table[i - 1]);
		solution.push_back(activities[i]);
		//solution.push_back(activities[i]);

		
	}
    print_optimal_activities(activities, solution, dp_table, num_items);
    return dp_table[num_items];
}

void print_optimal_activities(vector<activity> activities, vector<activity> sol, int dp_table[], int max_index) {

	int optimal_value = dp_table[max_index];
	cout << "________________________" << endl;
   	for(int i = 1; i <= max_index; i++){
		
		if(dp_table[i] == optimal_value){
		    cout << "Activity " << i << ": " << endl;
			cout << activities[i].start_time << "," <<activities[i].end_time << "," << activities[i].weight<<endl;
			cout << "________________________" << endl;
		    optimal_value -= activities[i].weight;
	    	max_index = i-1;
	    	i = 1;
		}	
	}
}






	
