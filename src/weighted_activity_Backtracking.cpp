//#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
//#include <array>
#include <chrono>
//#include <ctime>
#include <iomanip>
#include <algorithm>
#include <queue>

using namespace std;
using namespace std::chrono;

struct activity{
    bool operator()(activity a1, activity a2){
	return(a1.end_time < a2.end_time);
    }
    int start_time = -1;
    int end_time = -1;
    int weight = -1;
}activityComp;

struct node{
    inline bool operator < (node n1)const{
	return(bound < n1.bound);
    }
    vector<int> included;
    int weight = -1;
    int bound = -1;
    int act = -1;
};

int boundMaker(vector<activity> activities, int tot_weight, int act);

int find_next_activity(vector<activity> activities, int act);

int weighted_activity_Backtrack(int size, vector<activity> activities);

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
    cout << endl;
    high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now(); //Start time of algorithm execution

    sort(activities.begin(), activities.end(), activityComp);
    //for(int i = 0; i < activities.size(); i++){
        //cout << activities[i].start_time << ", " << activities[i].end_time << ", " << activities[i].weight << endl;
	//bool s = activities[i].start_time > activities[i].end_time > activities[i].weight;
	//cout << "";
    //}
    cout << weighted_activity_Backtrack(activities.size(), activities) << endl;
    high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now(); //Start time of algorithm execution
    
    //Calculates the execution time by subtracting the start time from the end time
    double executionTime = duration_cast<nanoseconds>(t2 - t1).count();
    executionTime *= 1e-9;
    cout << executionTime << endl;
}

int weighted_activity_Backtrack(int size, vector<activity> activities){
    priority_queue<node> Q;
    node u,v;
    int max_weight = 0;
    v.weight = 0;
    v.bound = boundMaker(activities, 0, 0);
    //cout << v.bound << endl;
    v.act = 0;
    Q.push(v);
    vector<int> included;
    while(!Q.empty()){
        //cout << "bing" << endl;
	v = Q.top();
	Q.pop();
        if(v.act >= activities.size() || v.act == -1 || activities[v.act].start_time > activities[v.act].end_time) continue;
	if(v.bound >= max_weight){
	    u.included = v.included;
	    //Yes Child
	    u.weight = v.weight + activities[v.act].weight;
	    u.act = find_next_activity(activities, v.act);
	    //cout << "-" << v.act << " --> " << u.act << "-" << endl;
	    u.included.push_back(v.act);
	    if(u.weight > max_weight){
		max_weight = u.weight;
		included = u.included;
	    }
            u.bound = boundMaker(activities, u.weight, u.act+1);
            //cout << u.bound << endl;
	    if(u.bound >= max_weight) Q.push(u);
	
	    //No child
	    u.weight = v.weight;
	    u.act = v.act+1;
	    u.included = v.included;
	    while(u.included.size() >0 && activities[u.act].start_time < activities[u.included[u.included.size()-1]].end_time){
	        u.act++;
		//cout << "inv, " << u.included.size() << endl;
	    }
	    //cout << u.act << endl;
	    u.bound = boundMaker(activities, u.weight, v.act+1);
	    //cout << u.bound << endl;
	    //cout << v.act << endl;
	    if(u.bound >= max_weight && activities[u.act].start_time < activities[u.act].end_time) Q.push(u);
	}
    }
    for(int i = 0; i < included.size(); i++) cout << activities[included[i]].start_time << ", " << activities[included[i]].end_time << ", " << activities[included[i]].weight << endl;
    return max_weight;
}

int boundMaker(vector<activity> activities, int tot_weight, int act){
    int bound = tot_weight;
    for(int i = act; i < activities.size(); i++) bound+=activities[i].weight;
    return bound;
}

int find_next_activity(vector<activity> activities, int act){
    for(int i = act+1; i < activities.size(); i++){
	if(activities[i].start_time >= activities[act].end_time) return i; 
    }
    return -1;
}