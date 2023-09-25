#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
// #include <bits/stdc++.h>

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


vector<vector<int>> scatter(vector <vector <int> > input, vector <vector <int> > indexes, vector <int> values){
    int num_scatter = values.size();
	for(int i = 0; i < num_scatter; i++){
		int row = indexes[i][0];
		int col = indexes[i][1];

		input[row][col] = values[i];
	}
    return input;
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
    vector<vector<int>>::iterator it;
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

    int SCATTER_SIZE = 100;
	vector <vector <int> > indexes(SCATTER_SIZE, vector<int>(2));
	vector <int> values(SCATTER_SIZE);

    srand((unsigned)time(0)); 

	vector <vector <int> > A = read(filename);
    int n = A.size();
    cout<<"n: "<<n<<endl;
    indexes = populateRandomIndexes(indexes, n);
    values = populateRandomValues(values);
    //cout<<"Indexes: "<<endl;
    //printMatrix(indexes);
    //cout<<"Values:" <<endl;

    /*
   	vector<int>::iterator it;
    for (it=values.begin(); it != values.end(); it++) {
        cout<<*it<<" ";
    }
    cout<<endl;
    */
    //cout<<"A: "<<endl;
	//printMatrix(A);
    parsec_roi_begin();
	A = scatter(A, indexes, values);
	parsec_roi_end();
    cout<<"Input matrix after scatter: "<<endl;
	printMatrix(A);
	return 0;
}