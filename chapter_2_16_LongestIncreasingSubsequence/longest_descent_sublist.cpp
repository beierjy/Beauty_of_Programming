#include<vector>
#include<iostream>

using namespace std;
int max(int a, int b){
	if (a > b)
		return a;
	else
		return b;
}
vector<int> asc_list(vector<int> vec){
	vector<int> max_len(vec.size(), 0);
	for (int i = 0; i < vec.size(); i++){
		max_len[i] = 1;
		for (int j = 0; j < i; j++){
			if (vec[i]>vec[j])
				max_len[i] = max(max_len[i], max_len[j] + 1);
		}
	}
	return max_len;
}
vector<int> des_list(vector<int> vec){
	vector<int> max_len(vec.size(), 0);
	for (int i = vec.size() - 2; i >= 0; i--){
		max_len[i] = 1;
		for (int j = vec.size() - 1; j > i; j--){
			if (vec[i]>vec[j])
				max_len[i] = max(max_len[i], max_len[j] + 1);
		}
	}
	return max_len;
}

int max_queue(vector<int> vec){
	if (vec.size() <= 0)
		return 0;
	vector<int> asc = asc_list(vec);
	vector<int> des = des_list(vec);
	int max_r = -1;
	for (int i = 0; i < vec.size(); i++){
		max_r = max(max_r, (asc[i] + des[i]) - 1);
	}
	return max_r;
}
int main(){
	int N;
	while (cin >> N){
		vector<int> vec;
		int a;
		while (N>0){
			cin >> a;
			vec.push_back(a);
			N--;
		}
		cout << vec.size() - max_queue(vec) << endl;
	}
}