//****************************************************************************/
//        NAME: Youssif M
//       CLASS: CSCE-2110
//  ASSIGNMENT: Program 2
// DESCRIPTION: This program creates 2 open hash table with function x^2%7.
//		 		These table are used to store student and grade information.
//	 	 		All table functions such as add, delete, search, and show have
//	 	 		been incorperated.
//
// REQUIRED SOURCE FILES:
//      1. Student Gradebook Hash Table.cpp
//
// OTHER FILES:
//      None
//
// SPECIAL INSTRUCTIONS:
//      None
//****************************************************************************/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <limits>
#include <math.h>

#define NUM_BUCKETS     7

using namespace std;

//Node structure
struct node {
	int idNum;
};

struct student: node {
        student *parentNode;
        student	 *childNode;

	string fName, lName, className;
	char letterGrade;
};

struct grade: node {
        grade *parentNode;
        grade *childNode;

	string fName, lName, className;
	char letterGrade;
};

class table {
	public:
                // Function prototypes
                int calc_Key(int);

		template<typename T>
		void add(T*&, T*&, int);

		template<typename T, typename R>
                void del(T, R, bool, int, string);

		template<typename T, typename R>
                bool search(T, R, bool, int, string);

		template<typename T, typename R>
		void show(T, R, bool);
};

class students: public table {
	public:
                student *roots;
                student *dataSet[NUM_BUCKETS];
		students();
		void add_details(int, int, string, string);
};

class grades: public table {
	public:
                grade *roots;
                grade *dataSet[NUM_BUCKETS];
		grades();
		void add_details(int, int, string, char);
};

students::students() { roots = NULL; }
grades::grades() { roots = NULL; }

// Calculate key from hash function.
int table::calc_Key(int data) {
        return((data*data)%NUM_BUCKETS);                // Hash function.
}

// Add value to hash table.
template<typename T>
void table::add(T*& n, T*& n_parent, int data) {
        if(n == NULL) {                                 // If the current node does not exist create one.
                n = new T;
                n->idNum = data;
                n->parentNode = n_parent;
                n->childNode = NULL;
        } else {                                        // If the current node does exist recursivly traverse the list till on do$
                add(n->childNode, n, data);
        }
}


// Delete value from hash table.
template<typename T, typename R>
void table::del(T temp_n, R dataSet, bool studentTableSelected, int idNum, string className) {
        int i;

	for(i = 0; i < NUM_BUCKETS; i++) {              // Run through each linked list of hash table.
                temp_n = dataSet[i];
                while(temp_n != NULL) {                 // For each linked list check elements until specified value is found.
                        if(temp_n->idNum == idNum) {
				if(!studentTableSelected) {
					if(temp_n->className != className) {
		                                temp_n = temp_n->childNode;
						continue;
					}
				}
                                if(temp_n->parentNode != NULL) { // Found node is not a parent node.
                                        temp_n->parentNode->childNode = temp_n->childNode;

                                        if(temp_n->childNode != NULL) {
                                                temp_n->childNode->parentNode = temp_n->parentNode;
                                        }
                                        temp_n = NULL;
                                } else {                // Found node is a parent node.
                                        if(temp_n->childNode != NULL) {
                                                temp_n->childNode->parentNode = temp_n->parentNode;
                                                dataSet[i] = temp_n->childNode;
                                        } else {
                                                dataSet[i] = NULL;
                                        }
                                }
                                break;
                        } else {                        // If current node is not that we are looking for go to next node/
                                temp_n = temp_n->childNode;
                        }
                }
        }
}

// Search for value in the hash table.c
template<typename T, typename R>
bool table::search(T temp_n, R dataSet, bool studentTableSelected, int data, string className) {
        int i;
//        node* temp_n;
        for(i = 0; i < NUM_BUCKETS; i++) {              // Run through each linked list of hash table.
                temp_n = dataSet[i];
                while(temp_n != NULL) {                 // For each linked list out all elements to terminal.
                        if(temp_n->idNum == data) {
                                return(true);
                                break;
                        } else {
                                temp_n = temp_n->childNode;
                        }
                }
        }
        return(false);
}

// Show the hash table.
template<typename T, typename R>
void table::show(T temp_n, R dataSet, bool studentTableSelected) {

        int i;
	bool isEmpty = true;

        for(i = 0; i < NUM_BUCKETS; i++) {              // Run through each linked list of hash table.
                temp_n = dataSet[i];
                while(temp_n != NULL) {                 // For each linked list out all elements to terminal.
			if(studentTableSelected) {
	                        cout << "(" << temp_n->idNum << ", " << temp_n->fName << ", " << temp_n->lName << ")";
			} else {
	                        cout << "(" << temp_n->idNum << ", " << temp_n->className << ", " << temp_n->letterGrade << ")";
			}
                        if(temp_n->childNode != NULL)
                                cout << " - ";
                        temp_n = temp_n->childNode;
                	isEmpty = false;
		}
        }
	if(isEmpty) {
        	cout << "Empty Table";
	}
	cout << endl;
}

void students::add_details(int bucket, int idNum, string fName, string lName) {
        int i;

	//student*& n, n_parent;
	add(dataSet[bucket], roots, idNum);
        student* temp_n;
        for(i = 0; i < NUM_BUCKETS; i++) {              // Run through each linked list of hash table.
                temp_n = dataSet[i];
                while(temp_n != NULL) {                 // For each linked list out all elements to terminal.
                        if(temp_n->idNum == idNum) {
                                temp_n->fName = fName;
				temp_n->lName = lName;
                        	break;
			} else {
                                temp_n = temp_n->childNode;
                        }
                }
        }
}


void grades::add_details(int bucket, int idNum, string className, char letterGrade) {
        int i;
        grade* temp_n;

	add(dataSet[bucket], roots, idNum);

	for(i = 0; i < NUM_BUCKETS; i++) {              // Run through each linked list of hash table.
                temp_n = dataSet[i];
                while(temp_n != NULL) {                 // For each linked list out all elements to terminal.
                        if(temp_n->idNum == idNum) {
                                if(temp_n->className  == "") {
					temp_n->className = className;
					temp_n->letterGrade = letterGrade;
                                	break;
				} else {
                                	temp_n = temp_n->childNode;
				}
                        } else {
                                temp_n = temp_n->childNode;
                        }
                }
        }
}

int main(void) {

        int i, tempKey, data, choice;
        double test_data;
	bool studentTableSelected;
	string fName, lName, className;
	char letterGrade;

	table *table;
        students *studentTable = new students();
        grades *gradeTable = new grades();
	string input[2];

        while(1) {                                      // Main loop
                cout << "tables> ";

		cin >> input[0];                          // Read data

		if(input[0] == "students") {
			studentTableSelected = true;
			table = studentTable;
		} else if(input[0] == "grades") {
			studentTableSelected = false;
			table = gradeTable;
		} else if(input[0] == "quit") {
			break;
		} else {
			cout << "Error: Please specify either the \"students\" table or \"grades\" table." << endl;
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		cin >> input[1];

		// Check for correct input data
		if(input[1] == "add" || input[1] == "delete" || input[1] == "search") {
			while(1) {
                                try {                   // Input is not a number
                                        cin >> test_data;

                                        if((int)test_data != ceil(test_data)) { // Test for real number.
                                                cout << "Error: Please enter an integer." << endl;
                                                cin.clear();
                                                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                continue;
                                        }

                                        data = (int)test_data;

                                        if(!cin.fail()) { // Test for strings and chars.
                                                break;
                                        } else {
                                                cin.clear();
                                                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                                cout << "Error: Please enter an integer." << endl;
                                        }
                                } catch(int e) {
                                        cin.ignore();
                                        cout << "Error: Please enter an integer." << endl;
                                }
                        }
                }

                if(input[1] == "quit") { break; }

                if(input[1] == "add")    { choice = 1; }
                if(input[1] == "delete") { choice = 2; }
                if(input[1] == "search") { choice = 3; }
                if(input[1] == "display")   { choice = 4; }

		student* s = new student;
		grade* g = new grade;

                switch (choice) {                       // Perform action
                        case (1) : {                    // Add
				tempKey = table->calc_Key(data);
				if(studentTableSelected) {
					if(!studentTable->search(s, studentTable->dataSet, studentTableSelected, data, "")) {
						cin >> fName >> lName;
						studentTable->add_details(tempKey, data, fName, lName);
					} else {
                				cout << "Warning: duplicate input: " << data << endl;
                           		}
				} else {
					cin >> className >> letterGrade;
					gradeTable->add_details(tempKey, data, className, letterGrade);
				}
                                break;
                        }

                        case (2) : {                    // Delete
                                if(studentTableSelected) {
					if(studentTable->search(s, studentTable->dataSet, studentTableSelected, data, "")) {
        	                                studentTable->del(s, studentTable->dataSet, studentTableSelected, data, "");
                	                } else {
                        	                cout << "Warning: target value not found: " << data << endl;
                                	}
				} else {
					if(gradeTable->search(g, gradeTable->dataSet, studentTableSelected, data, className)) {
						cin >> className;
        	                                gradeTable->del(g, gradeTable->dataSet, studentTableSelected, data, className);
                	                } else {
                        	                cout << "Warning: target value not found: " << data << endl;
                                	}
				}
				break;
                        }
                        case (3) : {                    // Search
                                if(studentTable->search(s, studentTable->dataSet, studentTableSelected, data, "") == 1) {
                                        cout << "True" << endl;
                                } else {
                                        cout << "False" << endl;
                                }
                                break;
                        }

                        case (4) : {                    // Show
				if(studentTableSelected) {
        	                        studentTable->show(s, studentTable->dataSet, studentTableSelected);
                	                break;
                        	} else {
					gradeTable->show(g, gradeTable->dataSet, studentTableSelected);
					break;
				}
			}
                       	default : { cout << "Error: Command not found." << endl; break;}
                }

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                input[0] = "";
		input[1] = "";
                choice = 0;
		fName = "";
		lName = "";
		className = "";
		letterGrade = '\n';
        }
	return(0);
}

