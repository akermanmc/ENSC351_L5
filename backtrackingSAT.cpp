// takes input in DIMACS; solves satisfiability problem using backtracking search

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int nbvar = 0; // total number of variables in input file
int nbclauses = 0; // total number of clauses in input file

int str_to_int (string str){
	int num = 0;
	stringstream str_to_int_stream(str);
	str_to_int_stream >> num;
	return num;
}

vector<vector<string> > inputReadFunc(vector<vector<string> > &clause_vector){
	string word;
	ifstream inFile;
	vector<string> word_vector;
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
			clause_vector.push_back(word_vector);
			word_vector.clear();
			continue;
		}
		input_index++;
		word_vector.push_back(word);
	}

	inFile.close();
	return clause_vector;
}

int main(){
	vector<vector<string> > clause_vector; // vector of clauses
	clause_vector = inputReadFunc(clause_vector);

	//output test
	for (int i = 0; i<clause_vector.size(); i++){
		for (int j = 0; j<clause_vector[i].size(); j++){
			cout << clause_vector[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << nbvar << endl << nbclauses << endl;

	return 0;
}