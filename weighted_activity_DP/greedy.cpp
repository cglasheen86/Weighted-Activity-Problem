#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct activity {
	int s_time, f_time, weight;

};

vector<activity> greedy_sol(vector <activity> a) {
	vector<activity> sol;
	activity temp;
	int j = 0;
	for (int i = 1; j < a.size(); i++) {
		if (a[i].s_time >= a[j].f_time) {
			temp.s_time = a[j].s_time;
			temp.f_time = a[j].f_time;
			temp.weight = a[j].weight;
			sol.push_back(temp);
			j = i;
		}
	} 

	return sol;

}

int main(int argc, char* argv[]) {
	ifstream input;
	input.open(argv[1]);
	string st, ft;
	vector<activity> act_list;

	activity temp_act;
	int s, e, w;
	char c;
	while (input >> s >> c >> e >> c >> w ) {
		temp_act.s_time = s;
		temp_act.f_time = e;
		temp_act.weight = w;
		act_list.push_back(temp_act);
	
	}
	input.close();
	
	vector<activity> final_schedule;

	high_resolution_clock::time_point start = high_resolution_clock::now();
	final_schedule = greedy_sol(act_list);
	high_resolution_clock::time_point end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - start);

	fstream output_file;
	int total_weight = 0;
	output_file.open(argv[2], fstream::in | fstream::out | fstream::trunc);
	for (int i = 0; i < final_schedule.size(); i++) {
		total_weight += final_schedule[i].weight;
		output_file << final_schedule[i].s_time << "," << final_schedule[i].f_time << ","<<final_schedule[i].weight << endl;
		cout<< final_schedule[i].s_time << "," << final_schedule[i].f_time << "," <<final_schedule[i].weight << endl;

	}
	output_file << "Duration: " << duration.count() << "ms || Total Weight:" << total_weight << endl;
	output_file.close();
	cout << "Duration: " << duration.count() << "ms || Total Weight:" << total_weight << endl;
	
	
	
	return 0;
}