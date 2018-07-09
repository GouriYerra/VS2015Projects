// Homework1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct studentData {
	string username;
	float gpa;
	int age;
};

void addUser(vector<studentData> *gradeList, string name, float _gpa, int _age) {
	//studentData *stu = new studentData;

	studentData user;
	user.age = _age;
	user.username = name;
	user.gpa = _gpa;

	/*stu->username = name;
	stu->age = _age;
	stu->gpa = _gpa;*/

	(*gradeList).push_back(user);
}

void printList(vector<studentData> *gradeList) {
	for (vector<studentData>::iterator it = (*gradeList).begin(); it != (*gradeList).end(); ++it) {
		cout << (*it).username << " [" << (*it).gpa << "] age: " << (*it).age << endl;
	}
}

int main(int argc, char* argv[]) {
	ifstream inFile;
	string data;

	vector<studentData> gradeList;
	int userIndex = 0;

	inFile.open(argv[1]); //Open the file
	if (inFile.is_open()) {
		while (getline(inFile, data)) {
			stringstream ss(data);

			string username1;
			getline(ss, username1, ',');

			string tmp;
			getline(ss, tmp, ',');
			float gpa1;
			gpa1 = stof(tmp);

			getline(ss, tmp, ',');
			int age1;
			age1 = stoi(tmp);

			addUser(&gradeList, username1, gpa1, age1);

			userIndex++;
		}
	}
	else {
		cout << "Unable to open file." << endl;
	}
	printList(&gradeList);
}
