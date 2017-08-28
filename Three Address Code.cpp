// Three Address Code Assignment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

std::vector<std::string> myLines;
std::vector<std::string> tempStmt;
int alloCount = 0;
int pos = 0;


int main()
{
	string myfile,lines;
	cout << "File path: ";
	getline(cin, myfile);
	ifstream file(myfile);
	

	while (std::getline(file, lines)) {
		myLines.push_back(lines);
	}

	program(myLines);
	//cout << myLines[myLines.size() - 3] << endl;
    return 0;
}

//program -> program Stmt_list end . end
void program(vector<string>& list) {

	//check to see if it is a program file
	if (list[1] == "program" && list[list.size() - 3] == "end") {
		list.erase(list.begin(), list.begin() + 2);
		list.erase(list.end() - 4, list.end());
	}
	
	//move to stmt_list function
	stmt_list(list);
}

//stmt_list -> stmt ; stmt_list
void stmt_list(vector<string>& list) {

	//vector<string> list2;
	int front = 0, back = 0;

	for (int i = 0; i < list.size(); i++) {
		if (list[i] == "SEMICOLON") {
			back = i;
			std::vector<string> list2(list.begin() + front, list.begin() + back);
			stmt(list2);
			front = back;
			//break;	//delete when we get everything working
		}
		else {
			//cout << list[14] << endl;
		}	
	}
	
}

//stmt -> id = expr {mov}
void stmt(vector<string>& list) {

	
	string st1 = list[0];
	string st2 = list[1];
	string p;
	string mov = "MOV";

	if (list[1] == "ID" && list[2] == "=") {
		list.erase(list.begin(), list.begin() + 4);
		tempStmt = list;
		expr(p);
		quad("mov", st1, p);
	}
	else {
		cout << "Error in stmt" << endl;
	}
}

//expr -> term moreterms
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

//Elist
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

//Tlist
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


//make quad function
void quad(string operation, string operand1, string operand2, string result) {
	cout << operation << " " << operand1 << " " << operand2 << " " << result << "\n" << endl;
}

void quad(string operation, string operand1, string operand2) {
	cout << operation << " " << operand1 << " " << operand2 << "\n" << endl;
}

//make allocator function
string alloc() {

	string t = "t";
	alloCount = alloCount + 1;
	t = t + to_string(alloCount);

	return t;
}