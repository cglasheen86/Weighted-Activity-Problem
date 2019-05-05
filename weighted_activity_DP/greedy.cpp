#include <iostream>
#include <vector>
#include <fstream>
#include <string>


using namespace std;
struct activity {
	int s_time, f_time;

};

vector<activity> act_profit(vector <activity> a) {
	vector<activity> sol;
	activity temp;
	int j = 0;
	int s, f;
	for (int i = 1; j < a.size(); i++) {
		if (a[i].s_time >= a[j].f_time) {
			temp.s_time = a[j].s_time;
			temp.f_time = a[j].f_time;
			sol.push_back(temp);
			j = i;
		}
	} return sol;

}

int main(int argc, char* argv[]) {
	ifstream input;
	input.open(argv[1]);
	string st, ft;
	vector<activity> act_list;

	activity temp_act;
	int s, e;
	char c;
	while (input >> s >> c >> e ) {
		temp_act.s_time = s;
		temp_act.f_time = e;
		act_list.push_back(temp_act);
	
	}
	vector<activity> sol;
	sol = act_profit(act_list);
	for (int i = 0; i < sol.size(); i++) {
		cout << sol[i].s_time << "," << sol[i].f_time << endl;
	}

	input.close();
	return 0;
}