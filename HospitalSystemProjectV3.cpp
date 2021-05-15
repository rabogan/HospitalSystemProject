#include<iostream>
#include<deque>
#include<queue>
#include<string>
using namespace std;

const int MAX_DEPTS = 21;
const int MAX_PATIENTS = 5;  //This is relegated to a bit-part role in this version of the hospital system.

int dept_choice(int high, int low)
{
	cout << "That's [" << low << "-" << high << "]: ";
	int choice = 0;
	cin >> choice;
	if (choice >= high && choice <= low)
		return choice;
	else
		cout << "Invalid entry!\n";

	return dept_choice(high, low);
}

struct hospital_queue
{
	deque<pair<string, int>>que;
	int department_number;

	hospital_queue()
	{
		department_number = -1;
	}
	hospital_queue(int _dept)
	{
		department_number = _dept;
	}
	bool add_end(string name, int stats)
	{
		int size = que.size();
		if (size >= MAX_PATIENTS)
		{
			cout << "We can't accept any more patients in this department\n";
			return false;
		}
		auto item = make_pair(name, stats);
		que.push_back(item);
		return true;
	}
	bool add_front(string name, int stats)
	{
		int size = que.size();
		if (size >= MAX_PATIENTS)
		{
			cout << "We can't accept any more patients in this department\n";
			return false;
		}
		auto item = make_pair(name, stats);
		que.push_front(item);
		return true;
	}
	void remove_front()
	{
		if (que.size() == 0)
		{
			cout << "No patients currently waiting in this department\n";
			return;
		}
		auto item = que.front();
		que.pop_front();
		cout << item.first << " please make your way to the doctor" << endl;
	}
	
	void print() 
	{
		if (que.size() == 0)
			return;

		cout << "There are " << que.size() << " patients in specialization " << department_number << "\n";
		for (auto item : que) {
			cout << item.first << " ";
			if (item.second)
				cout << "urgent\n";
			else
				cout << "regular\n";
		}
		cout << "\n";
	}
};

struct hospital_system
{
	vector<hospital_queue>queues;  //A huge change here...
	hospital_system()
	{
		queues = vector<hospital_queue>(MAX_DEPTS);
		for (int i = 0; i < MAX_DEPTS; ++i)
		{
			queues[i] = hospital_queue(i);
		}
	}

	int menu()
	{
		int choice = -1;
		while (choice == -1)
		{
			cout << "1) Add patient\n2) Print patients\n3) Get patient\n4) Exit\n";
			cin >> choice;
			if (!(choice >= 1 && choice <= 4))
			{
				cout << "You need to enter a value between 1-4\n";
				choice = -1;
			}
		}
		return choice;
	}

	bool add_patient()
	{
		int department_number = 0;
		string patient_name;
		int patient_status = 0;
		cout << "Please enter the department number [1-20]:  ";
		department_number = dept_choice(1, MAX_DEPTS);
		cout << "Please enter the patient name:  ";
		cin >> patient_name;
		cout << "Please enter the patient status (0 = regular, 1 = urgent):  ";
		cin >> patient_status;

		bool success;

		if (patient_status == 0)
			success = queues[department_number].add_end(patient_name, patient_status);
		else
			success = queues[department_number].add_front(patient_name, patient_status);

		if (success = false)
		{
			cout << "We can't add any more patients in this department!\n";
			return false;
		}
		return true;
	}

	void print_patients()
	{
		cout << "PRINTING ****************************************************\n";
		for (int i = 0; i < MAX_DEPTS; ++i)
		{
			queues[i].print();
		}
	}

	void get_patient()
	{
		int dept = 0;
		cout << "Please enter the department for which you'll treat a patient\n";
		cin >> dept;
		queues[dept].remove_front();
	}

	void run()
	{
		while (true)
		{
			int choice = menu();

			if (choice == 1)
				add_patient();
			else if (choice == 2)
				print_patients();
			else if (choice == 3)
				get_patient();
			else
				break;
		}
	}
};

int main()
{
	hospital_system my_hospital;
	my_hospital.run();

	return 0;
}