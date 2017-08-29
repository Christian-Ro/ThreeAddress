// Three Address Code.cpp

#include "string"
#include "iomanip"
#include "vector"
#include "fstream"
#include "iterator"
#include "iostream"
#include "algorithm"
using namespace std;

void program(vector<string>& list);
void stmt_list(vector<string>& list);
void stmt(vector<string>& list);
void expr(string &list);
void term(string &p);
void factor(string &p);
void moreterms(string p, string &q);
void morefactors(string p, string &q);
void quad(string operation, string operand1, string operand2, string result);
void quad(string operation, string operand1, string operand2);
string alloc();

vector<string> myLines;
vector<string> tempStmt;
int alloCount = 0;
int pos = 0;

/***************************************************
	Gets the words from a file and stores them 
	into vector string
****************************************************/
int main(){

	string myfile,lines;
	cout << "File path: ";
	getline(cin, myfile);
	ifstream file(myfile);
	
	while (getline(file, lines)) {
		myLines.push_back(lines);
	}

	program(myLines);
	//cout << myLines[myLines.size()-1] << endl;
    return 0;
}

/***************************************************
	program -> program Stmt_list end . end
****************************************************/
void program(vector<string>& list) {

	//check to see if it is a program file
	if (list[1] == "program" && list[list.size() - 3] == "end") {
		list.erase(list.begin(), list.begin() + 2);	//Erease the first two words from the file. (Program, Program). Starts from nest.
		list.erase(list.end() - 4, list.end());	//Erease the last three words including the period at the end. (PERIOD, ., end, end). Ends at SEMICOLON.
	}

	//Start of the stmt_list function
	stmt_list(list);
}

/***************************************************
	This function is to get many statements 
	at the same time. For right now we 
	only focus on one statement per file.

	//stmt_list -> stmt ; stmt_list

****************************************************/
void stmt_list(vector<string>& list) {

	//vector<string> list2;
	int front = 0, back = 0;

	//This for loop is to get the end of each statement which will end with ";", but for right now we only have one statement per file.
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == "SEMICOLON") {
			back = i;
			vector<string> list2(list.begin() + front, list.begin() + back);	//Deletes the identifier "SEMICOLON", we are left with ";"
			stmt(list2);
			front = back;
		}
		else {
			//Let the loop run until it finds the SEMICOLON
		}	
	}
	
}

/***************************************************
	//stmt -> id = expr {mov}
****************************************************/
void stmt(vector<string>& list) {

	
	string st1 = list[0];
	string st2 = list[1];
	string p;
	string mov = "MOV";

	if (list[1] == "ID" && list[2] == "=") {	//CHeck if to see if there is an identifier before the assign operator
		list.erase(list.begin(), list.begin() + 4);	//This is to delete the word "SEMICOLON" and "ASSIGNMENT" identifiers, just be left with the expression that ends at ";".
		tempStmt = list;
		expr(p);
		quad(mov, st1, p);
	}
	else {
		cout << "Error in stmt" << endl;
	}
}

/***************************************************
	expr -> term moreterms
****************************************************/
void expr(string &p) {

	string q;
	
	if (tempStmt[pos] == "(" || tempStmt[pos + 1] == "ID" || tempStmt[pos + 1] == "CONSTANT") {
		term(q); 
		moreterms(q, p);
	}
	else {
		cout << "reject expr" << endl;
	}
	
}

/***************************************************
	Term function
****************************************************/
void term(string &p) {

	string q;

	if (tempStmt[pos] == "(" || tempStmt[pos + 1] == "ID" || tempStmt[pos + 1] == "CONSTANT") {
		factor(p); 
		morefactors(q, p);
	}
	else {
		cout << "Is this showing?" << endl;
	}
}

/***************************************************
	Elist
****************************************************/
void moreterms(string p, string &q) {
	string r, s;

	if (tempStmt[pos + 2] == "+") {
		pos = pos + 4;
		r = tempStmt[pos];
		term(r);
		s = alloc();
		quad("Add", p, r, s);
		moreterms(s, q);
	}
	else if(tempStmt[pos + 2] == "-"){
		pos = pos + 4;
		r = tempStmt[pos];
		term(r);
		s = alloc();
		quad("Sub", p, r, s);
		moreterms(s, q);
	}
	else if (tempStmt[pos + 2] == ";" || tempStmt[pos + 2] == ")") {
		//q = p;
		p = q;
	}
	else {
		cout << "Reject" << endl;
	}
}

/***************************************************
	Factor function

****************************************************/
void factor(string &p) {

	if (tempStmt[pos] == "(") {
		pos = pos + 1;
		string temp = tempStmt[pos + 1];
		expr(temp);
		if (tempStmt[pos] == ")") {
			cout << p << endl;
			pos = pos + 1;
		}
		else {
			expr(temp);
			cout << "nothing to show here2" << endl;
		}
	}
	else if (tempStmt[pos + 1] == "ID" || tempStmt[pos + 1] == "CONSTANT") {
		p = tempStmt[pos];
	}
	else {
		cout << "Npthing to show" << endl;
	}
}

/***************************************************
Tlist
****************************************************/
void morefactors(string p, string &q) {

	string r, s;
	
	if (tempStmt[pos + 2] == "*") {
		pos = pos + 4;
		r = tempStmt[pos];
		factor(r);
		s = alloc();
		quad("Mult", p, r, s);
		morefactors(s, q);
	}
	else if (tempStmt[pos + 2] == "/") {
		pos = pos + 4;
		r = tempStmt[pos];
		factor(r);
		s = alloc();
		quad("Dvd", p, r, s);
		morefactors(s, q);
	}
	else if (tempStmt[pos + 2] == "div") {
		pos = pos + 4;
		r = tempStmt[pos];
		factor(r);
		s = alloc();
		quad("Div", p, r, s);
		morefactors(s, q);
	}
	else if (tempStmt[pos + 2] == "mod") {
		pos = pos + 4;
		r = tempStmt[pos];
		factor(r);
		s = alloc();
		quad("Mod", p, r, s);
		morefactors(s, q);
	}
	else if (tempStmt[pos + 2] == "+" || tempStmt[pos + 2] == ";" || tempStmt[pos + 2] == ")") {
		//q = p;
		p = q;
		//cout << p << endl;
	}
	else {
		cout << "REject" << endl;
	}
}

/***************************************************
make quad function
****************************************************/
void quad(string operation, string operand1, string operand2, string result) {
	cout << operation << " " << operand1 << " " << operand2 << " " << result << "\n" << endl;
}

void quad(string operation, string operand1, string operand2) {
	cout << operation << " " << operand1 << " " << operand2 << "\n" << endl;
}

/***************************************************
//make allocator function
****************************************************/
string alloc() {

	string t = "t";
	alloCount = alloCount + 1;
	t = t + to_string(alloCount);

	return t;
}