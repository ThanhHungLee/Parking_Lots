
#include <bits/stdc++.h>
using namespace std;

#define DB(X) cerr<<#X<<": "<<X<<endl;
struct CARS
{
	int countPosition;
	int left;
	int right;
	int top;
	int bottom;
	string key;
	CARS(string key) {
		this->key = key;
	}
	CARS() {
		this->left = 0;
		this->right = 0;
		this->top = 0;
		this->bottom = 0;
		this->key = "";
		this->countPosition = 0;
	}
	CARS(int countPostion) {
		this->countPosition = countPosition;
	}
	CARS(int left, int top, int right, int bottom, string key) {
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
		this->key = key;
		this->countPosition = countPosition;
	}
};
CARS *carprs;
CARS *carPst;
struct Node {
	string key;
	int l;
	int r;
	int t;
	int b;
};
//lay gia tri tu file txt
vector<int> getValue(string line) {
	bool check = false;
	vector<int> ans;
	int prevv = -1;
	for (int i = 0; i < line.size(); i++) {
		if (check == true) {
			if (prevv == -1 and line[i] == ' ') {
				prevv = i;
			}
			else if (prevv != -1 and line[i] == ' ') {
				int k = atoi(line.substr(prevv + 1, i - prevv - 1).c_str());
				ans.push_back(k);
				prevv = i;
			}
			else if (prevv != -1 and i == line.size() - 1) {
				int k = atoi(line.substr(prevv + 1, i - prevv).c_str());
				ans.push_back(k);
			}
		}
		if (line[i] == '=') {
			check = true;
		}
	}
	return ans;
}
string getCate(string line) {
	int l = 0;
	for (int i = 0; i < line.size(); i++) {
		if (line[i] == ':') {
			l = i;
			break;
		}
	}
	return line.substr(0, l);
}
//Ham doc file .txt tu Yolo thu duoc
CARS* readfile(string filename) {
	ifstream myfile;
	myfile.open(filename);
	if(myfile.is_open()){
		cout<<filename << "was read"<<endl;
	}
	else{
		cout<<filename<<" Error"<<endl;
	}
	CARS *carprs = new CARS[100];
	Node *node = new Node[100];
	string line;
	int start = 0;
	bool choice = false;
	int cnt_k = 1;
	int cnt_p = 1;
	while (getline(myfile, line)) {
		//	cout << line << endl;
		if (start == 1) {
			if (line.substr(0, 5).compare("Value") == 0) {
				start = 2;
			}
			else {
				if (line.size() > 0) {
					carprs[cnt_k++].key = getCate(line);
				}
			}
		}
		if (start == 2) {
			if (line.size() > 0) {
				//cout << "here" << endl;
				vector<int> p = getValue(line);
				//cout << p[0] << endl;
				carprs[cnt_p] = CARS(p[0], p[1], p[2], p[3], carprs[cnt_p].key);
				cnt_p++;
			}
		}
		if (line.substr(0, 4).compare("data") == 0) {
			start = 1;
		}
	}
	carprs[1].countPosition = cnt_p;
	return carprs;
}
// Ham tinh dien tich
int S = 0;
int S_s = 0;
int W, H;
int left1, left2;
int right1, right2;
int top1, top2;
int bot1, bot2;
double P = 0.0;
int left, top, right, bot;
typedef pair<int, int> ii;

int Cal_Ss(int left, int top, int right, int bot) {

	W = right - left;
	H = bot - top;
	S_s = W * H;
	return S_s;
}
void calculator(int left1, int left2, int right1, int right2, int top1, int top2, int bot1, int bot2, int &S_s) {
	int left = max(left1, left2);
	int right = min(right1, right2);
	int top = max(top1, top2);
	int bot = min(bot1, bot2);
	S_s = max(0, (right - left))*max((bot - top), 0);
}
int Cal_S1(int left1, int top1, int bot1, int right1) {
	S = (bot1 - top1)*(right1 - left1);
	return S;
}
int Cal_S2(int left2, int top2, int bot2, int right2) {
	S = (bot2 - top2)*(right2 - left2);
	return S;
}
//Creating graph for Dijkstra algrithm
const int N = 1e5 + 7;
typedef pair<int, int> ii;
vector<ii> adj[N];
int dist[N];
int parent[N];
void addEdge(int u, int v, int w) {
	adj[u].push_back(make_pair(w, v));
	adj[v].push_back(make_pair(w, u));
}
void printPath(int parent[], int j) {
	// Base Case : If j is source 
	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);

	printf("%d ", j);
}
void printSolution(int src, int n, int dist[], int parent[]) {
	printf("Vertex\t Distance\tPath");
	for (int i = 1; i <= n; i++)
	{
		printf("\n%d -> %d \t\t %d\t\t%d ",
			src, i, dist[i], src);
		printPath(parent, i);
	}
}
void dijkstra(int src) {
	priority_queue<ii, vector<ii>, greater<ii> > pq;
	pq.push(make_pair(0, src));
	//memset(dist, INT_MAX, sizeof(dist));
	for (int i = 0; i <= 1000; i++) {
		dist[i] = INT_MAX;
	}
	dist[src] = 0;
	parent[src] = -1;
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		for (auto uv : adj[u]) {
			int weight = uv.first;
			int v = uv.second;
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				parent[v] = u;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
}
vector<ii> contains;

int main()
{
	//ii u;
	CARS *mCar1 = new CARS[100];
	CARS *mCar2 = new CARS[100];
	mCar1 = readfile("../Empty.txt");
	mCar2 = readfile("../CarPresent.txt");

	cout << "file name 1: " << endl;
	cout << mCar1[1].countPosition << endl;
	for (int i = 1; i < mCar1[1].countPosition; i++) {
		cout << "K = " << i << " Key = " << mCar1[i].key << ", left = " << mCar1[i].left << ", top = " << mCar1[i].top << ", right = " << mCar1[i].right << ", bot = " << mCar1[i].bottom << endl;
		//cout << mCar1[i].key << endl;
	}
	cout << "=================================" << endl;
	cout << "file name 2: " << endl;
	for (int i = 1; i < mCar2[1].countPosition; i++) {
		cout << "K = " << i << " Key = " << mCar2[i].key << ", left = " << mCar2[i].left << ", top = " << mCar2[i].top << ", right = " << mCar2[i].right << ", bot = " << mCar2[i].bottom << endl;
		//cout << mCar2[i].key << endl;
	}

	//creating graph
	ifstream read;
	read.open("../Graph.txt");

	int u, v, w;
	int cnt = 1;
	while (read >> u >> v >> w) {
		addEdge(u, v, w);
		if (u == -1) {
			break;
		}

	}
	contains.clear();
	cout << "Car Packing: " << endl;

	while (read >> u) {
		cout << u << endl;
		contains.push_back(make_pair(u, 0));
	}
	dijkstra(1);
	int choose[7] = { 0, 9,10,8,13,15,14 };
	//Tinh xac suat trung nhau cua 2 box
	for (int i = 1; i < mCar1[1].countPosition; i++) {

		left1 = mCar1[i].left;
		right1 = mCar1[i].right;
		top1 = mCar1[i].top;
		bot1 = mCar1[i].bottom;
		bool check = false;

		for (int j = 1; j < mCar2[1].countPosition; j++) {
			left2 = mCar2[j].left;
			right2 = mCar2[j].right;
			top2 = mCar2[j].top;
			bot2 = mCar2[j].bottom;
			calculator(left1, left2, right1, right2, top1, top2, bot1, bot2, S_s);
			Cal_S1(left1, top1, bot1, right1);
			P = (double)S_s * 1.0 / S;
			if (P > 0.8) {
				check = true;
				cout << "Position " << i << " has Car " << choose[i]<< endl;
				for (int k = 0; k < contains.size(); k++) {
					if (choose[i] == contains[k].first) {
						contains[k].second = 1;
					}
				}
			}


		}
	}

	int minindex = INT_MAX;
	int minval = INT_MAX;
	
	for (int i = 0; i < contains.size(); i++) {
			if (contains[i].second == 0) {
				if (minval > dist[contains[i].first]) {
					minval = dist[contains[i].first];
					minindex = contains[i].first;
					
				}
			}
	
	}
	
	if (minindex == INT_MAX) {
		cout << "FULL CAR";
		//break;
	}
	else {
		cout << endl;
		cout << "1 ";
		printPath(parent, minindex);
		cout << endl;
	}

	/*if (check) {
		cout << "nothing" << endl;

	}*/
}







