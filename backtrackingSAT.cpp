// takes input in DIMACS; solves satisfiability problem using backtracking search

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int MAX = 1024;
int nbvar = 0; // total number of variables in input file
int nbclauses = 0; // total number of clauses in input file
int current_var_depth = 0;
vector<vector<int> > clause_vector; // vector of clauses

// converts strings to ints
int str_to_int (string str){
	int num = 0;
	stringstream str_to_int_stream(str);
	str_to_int_stream >> num;
	return num;
}

// parses input file into a vector of clauses (vecotrs of string values)
vector<vector<int> > inputReadFunc(vector<vector<int> > &clause_vector){
	string word;
	ifstream inFile;
	vector<int> var_vector;
	int input_index = 0;

    inFile.open("DIMACSfile.txt");
    if(!inFile.is_open()){
        cout << "open failed, word_vector empty" << endl; 
        return clause_vector;
    }

	while (inFile >> word){
		// ignore first two words of DIMACS file
		if (input_index < 2){
			input_index++;
			continue;
		}
		// get number of variables in the file
		if (input_index == 2){
			input_index++;
			nbvar = str_to_int(word);
			continue;
		}
		// get number of clauses in the file  
		if (input_index == 3){
			input_index++;
			nbclauses = str_to_int(word);
			continue;
		}
		if (word == "0"){
			input_index++;
			clause_vector.push_back(var_vector);
			var_vector.clear();
			continue;
		}
		input_index++;
		var_vector.push_back(str_to_int(word));
	}

	inFile.close();
	return clause_vector;
}

//checks sign of a value
int sign(int x){
	if (x>0)
		return 1;
	if (x<0)
		return -1;
	return 0;
}

// checks whether clauses are satisfied
bool clause_check(int val, int current_var_depth){
	return true;
}

// implements backtracking search
vector<int> backtrack(vector<int> var_vector){
	if (var_vector.size() == nbvar){
		return var_vector;
	}
	current_var_depth++;
	for (int i = 1; i>0; i--){
		if (clause_check(i, current_var_depth)){
			var_vector.push_back(i);
			vector<int> res;
			res = backtrack(var_vector);
			if (!res.empty()){
				return res;
			}
			var_vector.pop_back();
		}
	}
	cout << "backtracking failed" << endl;
	var_vector.clear();
	var_vector.push_back(0);
	return var_vector;
}

int main(){
	clause_vector = inputReadFunc(clause_vector);

	//output problem
	for (int i = 0; i<clause_vector.size(); i++){
		for (int j = 0; j<clause_vector[i].size(); j++){
			cout << clause_vector[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "num vars: " << nbvar << endl << "num clauses: " << nbclauses << endl;

	//treat like a constraint satisfaction problem - solution is a list of assigned boolean values, constraint
	//			is the list of clauses
		// v x1 x2 x3 (...)
	// build binary # of size nbvar
	// take a guess
	//		is problem solved?
	// 			yes -> done
	//			no -> continue
	//			contradiction -> backtrack

	vector<int> var_vector; // initialize vector of variables
	var_vector.push_back(0); // give initial guess
	vector<int> solution_vector = backtrack(var_vector);

	// output solution
	cout << "v ";
	for (int i = 0; i<solution_vector.size(); i++){
		cout << solution_vector[i] << " ";
	}
	cout << endl;
	

	return 0;
}