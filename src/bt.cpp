#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct activity {
	int start, end, weight;
};

struct Node {
	//begin node properties
	vector<int> feasible;
	int weight, bound, index, depth;
	//overwrite comparison operators
	bool operator <(const Node& other_node)const{
		return bound < other_node.bound;
	}
};

//best activity is determined to be the activity with the earliest finish time/ weight ratio. so if there's an activity with earlier finish time but has less weight, we choose the nextone 
//we then backtrack if it exceeds some bound, in which the next activity with high weight cannot be added since the finish time overlaps with its start time
//int find_best_activity(vector<activity> &S, int index, Node previous) {
	//activity p
	//int ratio = (best.end - best.start)/best.weight;
	
//}

int calc_bound(Node n, vector<activity> &S) {
	int weight_so_far = n.weight;
	int node_bound = 0;
	for (int i = n.depth; i < S.size(); i++) {
		weight_so_far += S[i].weight;
	}
	node_bound = weight_so_far - n.weight;
	return node_bound;	
}
	////INCLUDE IN THE FINDING OPTIMAL SOLUTION: if previous node fin time doesn't overlap. but how would we find the prev node? i think it was like -1

bool is_compatible(activity prev, activity curr) {
	if (prev.end < curr.start) { return true; }
	return false;

}
int find_compatible(Node curr, vector<activity> S) {
	int next_act_idx = curr.depth+1;
	int idx = curr.depth;
	for (int i = next_act_idx; i <S.size(); i++) {
		if (is_compatible(S[idx], S[i])) { return i; }
		
	}
	return -1;
}
void find_sol(vector<activity> S, int size) {
	Node root;
	Node child;
	int weight_so_far = 0;
	bool compatible = false;
	root.weight = 0;
	root.depth = 0;


	priority_queue<Node> q;
	q.push(root);
	
	root.bound = calc_bound(root, S);
	//cout << root.bound << endl;
	//cout << "bro" << root.bound << endl;
	
	while (!q.empty()) {
		//cout << "bro" << endl;
		root = q.top();
	//	cout << root.weight << endl;
		q.pop();

		if (root.depth == 0) {

			child.weight = 0;
			compatible = true;


		} 
		cout << root.depth << endl;
		if (child.depth == size) { break; }
		if (!is_compatible(S[root.depth], S[root.depth+1])) {
			cout << "is incompatible!" << endl;
			int next_act_idx = find_compatible(root, S);
			cout << next_act_idx << endl;
			if (next_act_idx != -1) { child.depth = next_act_idx; }

		} 
		child.weight = root.weight + S[child.depth].weight;
	
		if (child.weight > weight_so_far) { 
			weight_so_far = child.weight;
		}
		
		
		child.bound = calc_bound(child, S);
		

		if (child.bound > weight_so_far) {
			q.push(child);
		}

		cout << "child w: " <<child.weight << endl;
		child.weight = root.weight;
		
		cout <<"root w: "<< root.weight << endl;

		child.depth = find_compatible(child, S);
		child.bound = calc_bound(child, S);
	
		if (child.bound > weight_so_far) {
			q.push(child);
		}
	}
	cout <<  weight_so_far << endl;

	


}

int main(int argc, char* argv[]){
	
	ifstream input;
	input.open(argv[1]);
	vector<activity> S;

	activity temp_act;
	int s, e, w;
	char c;
	while (input >> s >> c >> e >> c >> w ) {
		temp_act.start = s;
		temp_act.end = e;
		temp_act.weight = w;
		S.push_back(temp_act);
	
	}
	input.close();
	
	vector<activity> final_schedule;
	//cout << S.size() << endl;
	//int curr_weight = 0;
	//high_resolution_clock::time_point start = high_resolution_clock::now();
	find_sol(S, S.size());
	//cout << "hi" << endl;
	//high_resolution_clock::time_point end = high_resolution_clock::now();
	//auto duration = duration_cast<microseconds>(end - start);

	fstream output_file;
	int total_weight = 0;
	//output_file.open(argv[2], fstream::in | fstream::out | fstream::trunc);
	for (int i = 0; i < final_schedule.size(); i++) {
		total_weight += final_schedule[i].weight;
		//output_file << final_schedule[i].start << "," << final_schedule[i].end << ","<<final_schedule[i].weight << endl;
		//cout<< final_schedule[i].start << "," << final_schedule[i].end << "," <<final_schedule[i].weight << endl;

	}
	//output_file << "Duration: " << duration.count() << "ms || Total Weight:" << total_weight << endl;
	//output_file.close();
	//cout << "Duration: " << duration.count() << "ms || Total Weight:" << total_weight << endl;
	
	
	
	return 0;



}
