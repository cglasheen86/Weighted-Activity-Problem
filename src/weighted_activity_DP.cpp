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
	//cout << activities.size() << endl;
	//cout << "uh" << endl;
	
    sort(activities.begin(), activities.end(), activityComp);
    for(int i = 0; i < activities.size(); i++){
        cout << activities[i].start_time << ", " << activities[i].end_time << ", " << activities[i].weight << endl;
    }
	
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
    int dp_table[num_items + 1] = { 0 };
	
    activity empty_activity;
	empty_activity.weight = 0;
	activities.insert(activities.begin(), empty_activity);
	//cout << dp_table[0];
	

	for (int i = 1; i < num_items + 1; i++) {
		int x = latest_non_conflict(activities, i);
		int curr_weight = activities[i].weight;
		if (x != -1) { curr_weight += dp_table[x]; }
		
		//cout << "x: " << x << endl;
		dp_table[i] = max(curr_weight, dp_table[i - 1]);
	//	cout << dp_table[i - 1] << endl;
		//cout << activities[i].start_time << "," << activities[i].end_time << endl;
		//cout << " " << dp_table[i] << " "<<endl;
	} cout << endl;
    print_optimal_activities(activities, dp_table, num_items);
    return dp_table[num_items];
}

int find_conflict_index(vector<activity> activities){
    int current_index = activities.size()-2;
	//cout << current_index << endl;
    int beginning = 0;
    int end = activities.size()-2;
	//cout <<"end : "<< end << endl;
    while(beginning <= end){
		int middle = (beginning + end)/2;
		cout << "mid index: " <<middle << endl;
		if (activities[middle].end_time < activities[current_index].start_time) {
			//cout << "middle at " << middle << ": " << activities[middle].start_time << "," << activities[middle].end_time << endl;
			//cout << endl;
			//cout << "current_index: " << activities[current_index].start_time << "," << activities[current_index].end_time << endl;
			if (activities[middle + 1].end_time < activities[current_index].start_time) {
				//cout << "middle: " << middle << "||" << "middle + 1 : " << activities[middle + 1].start_time << "," << activities[middle + 1].end_time << endl;
				//cout << endl;
				//beginning = middle + 1;
				//cout << "beginning" << beginning << endl;
			}
			else { return middle; }
		}
		else end = middle - 1;
	}
    return -1;
}

void print_optimal_activities(vector<activity> activities, int dp_table[], int max_index) {
	int optimal_value = dp_table[max_index];
	//cout << "lol" <<dp_table[max_index] << endl;
	vector<int> sol_idxs;
	int dp_table_size = max_index + 1;

	for (int i = max_index; i >= 0; i--) {
		if (dp_table[i] > dp_table[i - 1]) {
			cout << "Item : " << i << endl;
			sol_idxs.push_back(i);

		}
	}


}
	/*cout <<"opt: " << optimal_value << endl;
    for(int i = 0; i <= max_index; i++){
			if(dp_table[i] == optimal_value){
			cout << "item " << i << endl;
			optimal_value -= activities[i].weight;
			max_index = i-1;
			i = 1;
		}
    }*/
//}
