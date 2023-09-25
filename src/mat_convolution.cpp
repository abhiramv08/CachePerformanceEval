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

struct Result {
	vector< vector<int> > A;
	vector< vector<int> > B;
};

vector< vector<int> > read(string filename) {
	vector< vector<int> > A, B;
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

vector< vector<int> > convolution(vector< vector<int> > A,
									vector< vector<int> > K) {
	int n = A.size();
    int m = K.size();
    int p = n-m+1; //Output is of size pxp

	// initialise C with 0s
	vector<int> tmp(p, 0);
	vector< vector<int> > C(p, tmp);

	cout<<"Input A size: "<<n<<"Input B size: "<<m<<"Output size: "<<p<<endl;

	for (int i = 0; i+m <= n; i++) {  //Iterate over rows of A
		for (int j = 0; j+m <= n; j++) { //Iterate over cols of A
			//Do dot product of A[i...i+m-1][j...j+m-1] with K
            int res = 0;
            for (int ai = i, ki = 0; ki < m; ai++, ki++){ //Iterate over rows of K
                for (int aj = j, kj = 0; kj < m; aj++, kj++){ //Iterate over cols of K
                    res+= A[ai][aj] * K[ki][kj];
				}
            }
            C[i][j] = res;
		}
	}
	return C;
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

int main (int argc, char* argv[]) {
	string input_filename;
	if (argc < 3) {
		input_filename = "2000.in";
	} else {
		input_filename = argv[2];
	}
	vector< vector <int>> A = read(input_filename);
	vector< vector <int>> K {
		{1, 2, 9},
		{0, 5, 8},
		{6, 4, 7}
	};
    parsec_roi_begin();
	//printMatrix(A);
	//cout<<endl;
	//printMatrix(K);

	vector<vector<int>> C = convolution(A, K);
    parsec_roi_end();
	cout<<"Result:"<<endl;
	printMatrix(C);
	return 0;
}
