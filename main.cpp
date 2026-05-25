#include <exception>
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <algorithm>

struct Student {
	int id;
	std::string name;
	std::string email;
	std::string NIM;
};

int get_int_input(const std::string &prompt) {
  bool is_valid = false;
  int input;

  while(!is_valid) {
    std::cout << prompt;

    std::string tmp;
    std::cin >> tmp;

    try {
      input = std::stoi(tmp);
    } catch(std::exception e) {
      std::cout << "invalid input.\n";
      continue;
    }

    if(!std::cin) {
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "invalid input.\n";
      continue;
    }

    is_valid = true;
  }

  std::cin.clear(); 
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return input;
}

std::string get_str_input(const std::string &prompt) {
  bool is_valid = false;
  std::string input = "";

  while(!is_valid) {
    std::cout << prompt;
    std::getline(std::cin, input);

    if(!std::cin) {
      std::cin.clear(); 
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "invalid input.\n";
      continue;
    }

    is_valid = true;
    std::cin.clear(); 
  }

  return input;
}

void swap(Student &a, Student &b) {
    Student tmp;
    tmp = a;
    a=b;
    b=tmp;
}

int partition(Student array[], int low, int high) {
    std::string pivot = array[high].NIM; 
    int cnt = low-1;

    for(int i=low; i<high; i++) {
        if(array[i].NIM < pivot) {
            cnt++;
            swap(array[i], array[cnt]);
        }
    }

    swap(array[cnt+1], array[high]);
    return cnt+1;
}

void quickSort_by_nim(Student array[], int low, int high) {
    if(low<high) {
        int p = partition(array, low, high);

        quickSort_by_nim(array, low, p-1);
        quickSort_by_nim(array, p+1, high);
    }
}

void sort_by_nim(Student array[], size_t size){
	Student temp;

	for (int i=0; i < (int)size-1; i++) {
		for (int j=0; j < (int)size-i-1; j++) {
			if (array[j].NIM > array[j+1].NIM) {
				temp = array[j];
				array[j] = array[j+1];
				array[j+1] = temp;
			}
		}
	}
}

int digits(int x) {
    int ans = 0;
    if(x==0) {
        return 1;
    }
    while(x>0) {
        ans++;
        x = x/10;
    }
    return ans;
}

void coout(char c, int x) {
    if(x < 0) {
        x=0;
    }
    for(int i=0; i<x; i++) {
        std :: cout << c;
    }
}

int maxStudentName(Student s[], int studentSize) {
  int x=4;
  for(int i=0; i<studentSize; i++) {
      int length = s[i].name.length();
      if(x<length) {
          x = length;
      }
  }
  return x;
}

int maxEmailName(Student s[], int studentSize) {
  int x=5;
  for(int i=0; i<studentSize; i++) {
      int length = s[i].email.length();
      if(x<length) {
          x = length;
      }
  }
  return x;
}

int maxID(Student s[], int studentSize) {
  int x = 2;
  for(int i=0; i<studentSize; i++) {
    if(x<s[i].id) {
      x=s[i].id;
    }
  }
  return x;
}

int maxStudentNim(Student s[], int studentSize) {
  int x=3;
  for(int i=0; i<studentSize; i++) {
      int length = s[i].NIM.length();
      if(x<length) {
          x = length;
      }
  }
  return x;
}

void print_students(Student students[], size_t size) {
  int maxid = maxID(students, (int)size) +1;
  int maxName = maxStudentName(students, (int)size)+1;
  int maxEmail = maxEmailName(students, int(size))+1;
  int maxNim = maxStudentNim(students, int(size))+1;

	std::cout << "ID"; coout(' ', std::max(0,maxid-2));
  std::cout << "|Name"; coout(' ', std::max(0,maxName-4));
  std::cout << "|Email"; coout(' ', std::max(0,maxEmail-5));
  std::cout << "|NIM"; coout(' ', std::max(0,maxNim-3));
  std::cout << "\n";

	for (size_t i = 0; i < size; i++) {
    auto student = students[i];

    std::cout << student.id; coout(' ', maxid-digits(student.id)+1);
    std::cout << student.name; coout(' ', maxName-student.name.length()+1);
    std::cout << student.email; coout(' ', maxEmail-student.email.length()+1);
    std::cout << student.NIM; coout(' ', maxNim-student.email.length());
    std::cout << "\n";
  }
}

Student* find_students(Student students[], int students_size, int target_id) {
   for (int i = 0; i < students_size; i++) {
     Student student = students[i];

     if (student.id == target_id) {
       return &students[i];
     }
   }

   return NULL;
}

void delete_student(Student students[], size_t &students_size, int target_id) {
  for(int i = 0; i < students_size; i++) {
    Student student = students[i];
    if (student.id == target_id) {

      students_size--;

      for(int j = i; j < students_size; j++) {
        students[j] = students[j+1]; // shift elements to the left 
      }
    }
  }
}

std::ifstream i_file("data.csv");

void read_students_from_csv(Student *students, size_t &student_size) {
  std::string tmp_line;
  std::vector<std::vector<std::string>> rows = {};


  // TODO: skip reading the header
  while (std::getline(i_file, tmp_line)) {
    std::vector<std::string> row = {};
    std::stringstream line_stream(tmp_line);
    std::string cell;

    /** cols (0-indexed) in the .csv file are:
    * id
    * name
    * email
    * nim
    */
    while(std::getline(line_stream, cell, ',')) {
      row.push_back(cell);
    }

    rows.push_back(row);
    row.clear();
  }

  for (int i = 0; i < rows.size(); i++ ) {
    auto row = rows.at(i);
    Student new_student;
    
    new_student.id = std::stoi(row.at(0));
    new_student.name = row.at(1);
    new_student.email = row.at(2);
    new_student.NIM = row.at(3);

    students[i] = new_student;
    student_size++;
  }
};

void write_students_to_csv(Student students[], size_t &students_size) {
  std::ofstream file("data.csv");

  for (int i = 0; i < students_size; i++) {
    Student student = students[i];
    std::string row = std::to_string(student.id) + "," + student.name + "," + student.email + "," + student.NIM;
    file << row;

    file << "\n";
  }
};

int main () {
	int input;
  int student_size_total = 0;

  std::ifstream size_file("total.txt");
  std::string tmp_line;
  std::getline(size_file, tmp_line);
  student_size_total = std::stoi(tmp_line);

	size_t students_size = 0;
	const int MAX_STUDENTS_SIZE = 100;
	Student students[MAX_STUDENTS_SIZE] = {};

  read_students_from_csv(students, students_size);

	do {
		std::cout << "=========================\n";
		std::cout << "Student Management System\n";
		std::cout << "=========================\n";
		std::cout << "1. View Student List\n";
		std::cout << "2. Create Student\n";
		std::cout << "3. Update Student\n";
		std::cout << "4. Delete Student\n";
		std::cout << "5. Exit\n";

		input = get_int_input("Enter Input (1-5): ");
		
		switch (input) {
			case 1:{
				if (students_size == 0){
					std::cout << "No Student Data Found" << "\n\n";
          break;
				}

        int option;
        bool is_looping = true;

        do {
          std::cout << "View Student Option\n";
          std::cout << "1. Sort by NIM\n";
          std::cout << "2. Don't sort\n";
          option = get_int_input( "Enter Input (1-2): ");
          
          switch(option) {
            case 1: {
              Student temp[MAX_STUDENTS_SIZE];
              for (size_t i = 0; i < students_size; i++){
                temp[i] = students[i];
              }
                
              //sort_by_nim(temp, students_size);
              quickSort_by_nim(temp, 0, (int)students_size - 1);

              std::cout << "Displaying Student Data Sorted by NIM:\n";
              print_students(temp, students_size);
              is_looping = 0;
              break;
            }

            case 2: {
              std::cout << "Displaying Student Data:\n";
              print_students(students, students_size);
              is_looping = 0;
              break;
            }

            default: {
              std::cout <<"Invalid Input\n";
            }
          }

        } while (is_looping);

				break;
			}

			case 2: {
				std::cout << "Adding new students..." << "\n";

				Student student;

				student.id = ++student_size_total;
        student.name = get_str_input("name: ");
				student.email = get_str_input("email: ");
        student.NIM = get_str_input("student NIM: ");

        std::cout << "before this?\n";
				students[students_size] = student;
        std::cout << "after this.\n";

				students_size++;

        write_students_to_csv(students, students_size);
        std::ofstream size_file("total.txt");
        size_file << student_size_total;

				break;
			}

			case 3: {
        if (students_size == 0){
					std::cout << "No Student Data Found" << "\n\n";
          break;
				}

				std::cout << "Update student" << "\n";

        print_students(students, students_size);

        int target_id = get_int_input( "input id of student to update: ");
        Student* student = find_students(students, students_size, target_id);
        std::string tmp = get_str_input("input student new name (leave empty to keep): ");

        if(!tmp.empty()) {
          student->name = tmp;
        }

        tmp.clear();

        tmp = get_str_input("input student new email (leave empty to keep): ");
        if(!tmp.empty()) {
          student->email = tmp;
        }

        tmp.clear();

        tmp = get_str_input("input student new NIM (leave empty to keep): ");
        if(!tmp.empty()) {
          student->NIM = tmp;
        }

        tmp.clear();

        write_students_to_csv(students, students_size);

        std::cout << "successfully updated student!\n";
				break;
			}

			case 4: {
        if (students_size == 0){
					std::cout << "No Student Data Found" << "\n\n";
          break;
				}

				std::cout << "Delete student" << "\n";
        print_students(students, students_size);

        int target_id = get_int_input( "choose student to delete (id): ");

        delete_student(students, students_size, target_id);
        write_students_to_csv(students, students_size);

        std::cout << "successfully deleted student with id " << target_id << ".\n";
        
				break;
			}

			case 5: {
				std::cout << "Goodbye, Admin!";
				break;
			}

			default: {
				std::cout << "Invalid Input\n";
				break;
			}
		}

	} while (input != 5);
}