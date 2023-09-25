#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void parsec_roi_begin() 
{

}

void parsec_roi_end() 
{

}

vector<vector<int>> read(string filename) {
	vector<vector<int>> A, B;
	string line;
	ifstream infile;
	infile.open (filename.c_str());

	int i = 0;
	while (getline(infile, line) && !line.empty()) {
		istringstream iss(line);
		A.resize(A.size() + 1);
		int a, j = 0;
		while (iss >> a) {
			A[i].push_back(a);
			j++;
		}
		i++;
	}
	infile.close();
	return A;
}


vector<int> gather(vector <vector <int> > input, vector <vector <int> > indexes){
    int num_gather = indexes.size();
    vector<int> output(num_gather);
	for(int i = 0; i < num_gather; i++){
		int row = indexes[i][0];
		int col = indexes[i][1];
		output[i] = input[row][col];
	}
    return output;
}

void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it=matrix.begin(); it != matrix.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
			cout << *inner;
			if(inner+1 != it->end()) {
				cout << "\t";
			}
		}
		cout << endl;
	}
}

vector<vector<int>> populateRandomIndexes(vector <vector <int> > indexes, int n){
    vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it=indexes.begin(); it != indexes.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
            *inner = (rand()%n);
		}
	}  

    return indexes;
}

vector<int> populateRandomValues(vector <int> values){
    vector<int>::iterator it;
	for (it=values.begin(); it != values.end(); it++) {
        *it = (rand()%1000);
    }
    return values;
}    


int main (int argc, char* argv[]) {
	string filename;

	cout << argv[0];
	if (argc < 3) {
		filename = "mat_inp_scatter.in";
	} else {
		filename = argv[2];
	}

    int GATHER_SIZE = 1000;
	vector <vector <int> > indexes(GATHER_SIZE, vector<int>(2));
    vector <int> output(GATHER_SIZE);
	vector <vector <int> > A = read(filename);

    srand((unsigned)time(0)); 

    int n = A.size();
    //cout<<"n: "<<n<<endl;
    indexes = populateRandomIndexes(indexes, n);
    //cout<<"Indexes: "<<endl;
    //printMatrix(indexes);
    //cout<<"A: "<<endl;
	//printMatrix(A);
    parsec_roi_begin();
	output = gather(A, indexes);
	parsec_roi_end();
    cout<<"Gather output: "<<endl;
    vector<int>::iterator it;
    for (it=output.begin(); it != output.end(); it++) {
        cout<<*it<<" ";
    }
    cout<<endl;

	return 0;
}