#include <iostream>
#include <fstream>
#include <string>
using namespace std;


string display_menu() {
	string choice;
	cout << "Choose an option" << endl << "Check(1) / Write(2) / Delete(3): ";
	cin >> choice;
	return choice;
}


void check_funct() {
	ifstream myfile;
	string line;
	myfile.open("Data.txt");
	while (getline(myfile, line)) {
		cout << line << endl;
	}
	myfile.close();
}

void write_funct(string Info, int line_count) {
	ofstream outfile("Data.txt", std::ofstream::app);
	outfile << line_count << ") " << Info << "\n";
	outfile.close();
}

int line_count_function() {
	ifstream myfile;
	string line;
	int line_count = 1;
	myfile.open("Data.txt");
	while (getline(myfile, line)) {
		line_count += 1;
	}
	return line_count;
}
/* Reads information at myfile, then writes all of them to a tempfile except the line we removed, then saves the tempfile as the "Data.txt" (old file's name) */

void delete_funct(char line_number) {
	ifstream myfile;
	ofstream updated_file;
	string line;
	string line_to_be_deleted;
	myfile.open("Data.txt");
	while (getline(myfile, line)) {
		if (line[0] == line_number) {
			line_to_be_deleted = line;
			break;
		}
	}

	cout << line_to_be_deleted << " - ";
	myfile.seekg(0, ios::beg);
	updated_file.open("Updated_Data.txt");
	while (getline(myfile, line)) {
		if (line != line_to_be_deleted) {
			updated_file << line << endl;
		}
	}

	updated_file.close();
	myfile.close();

	remove("Data.txt");
	rename("Updated_Data.txt", "Data.txt");
}


int main() {
	string choice;
	int line_count;
	char line_number;
	cout << "Welcome to To-Do list motherfucker" << endl;
	choice = display_menu();
	while (choice != "exit") {

		if (choice == "1") {
			check_funct();
		}

		else if (choice == "2") {
			string Info;
			cout << "Write down the information you want to save: ";
			cin.ignore();
			getline(cin, Info);
			line_count = line_count_function();
			write_funct(Info, line_count);
		}

		else if (choice == "3") {
			cout << "Write down the line number of the line that you want to delete: ";
			cin >> line_number;
			delete_funct(line_number);
		}
		
		else if (choice == "exit") {
			break;
			return 0;
		}

		choice = display_menu();
	}
}