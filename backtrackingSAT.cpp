// takes input in DIMACS; solves satisfiability problem using backtracking search

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

int MAX = 1024;
int nbvar = 0; // total number of variables in input file
int nbclauses = 0; // total number of clauses in input file
int var_depth = 0; // depth of variable backtracking

vector<vector<int> > clause_vector; // vector of clauses
vector<int> var_vector; 			// solution vector
vector<int> temp_vector;			// temp vector of variables

// converts strings to ints
int str_to_int (string str){
	int num = 0;
	stringstream str_to_int_stream(str);
	str_to_int_stream >> num;
	return num;
}

// parses input file into a vector of clauses (vectors of string values)
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

// checks whether a particular clause is satisfied
bool clause_check(vector<int> clause, int val){
	int num_vars_found = 0; // keeps track of whether the given variable (neg or pos) is in the clause
	bool clause_satisfied = false;
	//#pragma omp parallel for
	for (int i = 0; i<(var_depth); i++){
		// if variable is not found in clause at all return true
		if((find(clause.begin(), clause.end(), (i+1)) == clause.end()) && (find(clause.begin(), clause.end(), -(i+1)) == clause.end())){
			continue;
		}
		// if variable is neg and in clause return true
		if(find(clause.begin(), clause.end(), -(i+1)) != clause.end()){
			num_vars_found++;
			if (temp_vector[i] == 0){
				clause_satisfied = true;
				continue;
			}
		}
		// if variable  is pos and in clause return true
		if (find(clause.begin(), clause.end(), (i+1)) != clause.end()){
			num_vars_found++;
			if (temp_vector[i] == 1){
				clause_satisfied = true;
				continue;
			}
		}
	}
	// case when clause is not satisfied:
	//cout << num_vars_found << clause.size() << var_depth << endl;
	if ((num_vars_found == clause.size()) && (clause_satisfied == false)){
		return false;
	}
	return true;
}

// checks whether all clauses are satisfied
bool check_all_clauses(int val){
	bool flag = false;
	#pragma omp parallel for
	for(int i = 0; i < clause_vector.size(); i++){
		if (clause_check(clause_vector[i], val)){
			continue;
		}else{
			//cout << "check_all_clauses returning false" << endl;
			//return false;
			flag = true;
		}
	}
	if (flag == true){
		return false;
	}
	//cout << "check_all_clauses returning true" << endl;
	return true;
}

// implements backtracking search
vector<int> backtrack(vector<int> var_vector){
	if (var_vector.size() == nbvar){
		return var_vector;
	}
	// current variable is equal to var_depth
	var_depth++;

	// for loop determines variable's value
	for (int i = 1; i>(-1); i--){
		temp_vector.push_back(i);
		if (check_all_clauses(i)){
			var_vector.push_back(i);
			vector<int> res;
			res = backtrack(var_vector);
			if (!res.empty()){
				return res;
			}
			var_vector.pop_back();
		}
		temp_vector.pop_back();
	}
	var_depth--;
	//cout << "backtracking" << endl;
	vector<int> empty_vector;
	return empty_vector;
}

int main(){
	clause_vector = inputReadFunc(clause_vector);

	//output problem formulation
	for (int i = 0; i<clause_vector.size(); i++){
		for (int j = 0; j<clause_vector[i].size(); j++){
			cout << clause_vector[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "num vars: " << nbvar << endl << "num clauses: " << nbclauses << endl;

	// call backtracking function
	vector<int> solution_vector = backtrack(var_vector);

	// TO DO: 
// need to "print a progress report on how many backtracks have occurred to date (cumulative) every two seconds"

	// output solution
	cout << endl << "Solution: " << endl;
	cout << "v ";
	for (int i = 0; i<solution_vector.size(); i++){
		if (solution_vector[i] == 0)
			cout << -(i+1);
		if (solution_vector[i] == 1)
			cout << (i+1);
		cout << " ";
	}
	cout << endl;

	return 0;
}