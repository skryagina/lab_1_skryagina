#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Pipe
{
	string pipe_name = "None";
	double pipe_length = 0.0;
	int pipe_diameter = 0;
	bool pipe_repair = false;
};

struct Station
{
	string station_name = "None";
	int station_workshops = 0;
	int station_act_workshops = 0;
	double station_efficiency = 0.0;
};

int check_int(int& int_data)
{
	cin >> int_data;
	while (cin.fail() || cin.peek() != '\n' || int_data <= 0)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nPlease, enter an integer data type greater than 0\n";
		cin >> int_data;
	}
	return int_data;
}

int check_input(int& input_data)
{
	cin >> input_data;
	while (cin.fail() || cin.peek() != '\n' || input_data < 0 || input_data > 7)
	{
		cin.clear();
		cin.ignore(10000, '\n');
		cout << "\nError of data input! Please, try again: ";
		cin >> input_data;
	}
	return input_data;
}

double check_double(double& double_data)
{
	cin >> double_data;
	while (cin.fail() || cin.peek() != '\n' || double_data <= 0)
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nPlease, enter a double data type greater than 0\n";
		cin >> double_data;
	}
	return double_data;
}

double check2_double(double& efficiency_data)
{
	cin >> efficiency_data;
	while (cin.fail() || cin.peek() != '\n' || (efficiency_data < 0.0) || (efficiency_data > 1.0))
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nPlease, enter a efficiency data from 0.0 to 1.0\n";
		cin >> efficiency_data;
	}
	return efficiency_data;
}

bool check_bool(bool& bool_data)
{
	cin >> bool_data;
	while (cin.fail() || cin.peek() != '\n')
	{
		cin.clear();
		cin.ignore(100000, '\n');
		cout << "\nPlease, enter a boolean data type\n";
		cin >> bool_data;
	}
	return bool_data;
}

Pipe AddPipe()
{
	Pipe new_pipe;
	cout << endl << "Adding a new pipe..." << endl;
	cout << "Enter the name of the pipe: ";
	cin.ignore();
	getline(cin, new_pipe.pipe_name);
	cout << "Enter the length of the pipe (in metres): ";
	check_double(new_pipe.pipe_length);
	cout << "Enter the pipe diameter (in millimetres): ";
	check_int(new_pipe.pipe_diameter);
	cout << "Enter the repair status: ";
	check_bool(new_pipe.pipe_repair);
	return new_pipe;
}

void PrintAddPipe(Pipe& new_pipe)
{
	cout << endl << "Info about your pipe..." << endl;
	if (new_pipe.pipe_name == "None")
	{
		cout << "No pipes available!\n";
	}
	else
	{
		cout << "Name: " << new_pipe.pipe_name << "\tLength: " << new_pipe.pipe_length
			<< "\tDiameter: " << new_pipe.pipe_diameter << "\tRepair: " << new_pipe.pipe_repair << endl;
	}
}

void RepairPipe(Pipe& new_pipe)
{
	if (new_pipe.pipe_name == "None")
	{
		cout << "No pipes available!\n";
	}
	else
	{
		new_pipe.pipe_repair = !new_pipe.pipe_repair;
		cout << endl << "You have changed repair status!";
		PrintAddPipe(new_pipe);
	}
}

Station AddStation()
{
	Station new_station;
	cout << endl << "Adding a new CS..." << endl;
	cout << "Enter the station name: ";
	cin.ignore();
	getline(cin, new_station.station_name);
	cout << "Enter the number of workshops: ";
	check_int(new_station.station_workshops);
	cout << "Enter the number of active workshops: ";
	check_int(new_station.station_act_workshops);
	while (new_station.station_act_workshops > new_station.station_workshops)
	{
		cout << "The number of active workshops cannot be greater than those available!\n";
		cout << "Enter the number of active workshops: ";
		check_int(new_station.station_act_workshops);
	}
	cout << "Enter the station efficiency indicator (from 0 to 1 with tenths): ";
	check2_double(new_station.station_efficiency);
	return new_station;
}

void PrintAddStation(Station& new_station)
{
	cout << endl << "Info about your CS..." << endl;
	if (new_station.station_name == "None")
	{
		cout << "No stations available!\n";
	}
	else
	{
		cout << "Name: " << new_station.station_name << "\tWorkshops: " << new_station.station_workshops
			<< "\tActive workshops: " << new_station.station_act_workshops << "\tEfficiency: "
			<< new_station.station_efficiency << endl;
	}
}

void EditStation(Station& new_station)
{
	if (new_station.station_name == "None")
	{
		cout << "No stations available!\n";
	}
	else
	{
		cout << "Enter the number of active workshops: ";
		check_int(new_station.station_act_workshops);
		while (new_station.station_act_workshops > new_station.station_workshops)
		{
			cout << "The number of active workshops cannot be greater than those available!\n";
			cout << "Enter the number of active workshops: ";
			check_int(new_station.station_act_workshops);
		}
	}
	PrintAddStation(new_station);
}

void FileRecord(Pipe& pipe_data, Station& station_data)
{
	ofstream fout("info");
	if (pipe_data.pipe_name == "None")
	{
		cout << "Nothing to record about pipe!\n";
	}
	else
	{
		cout << "Info about the pipe is written to a file!\n";
		if (fout)
		{
			fout << "Info about your pipe...\n";
			fout << pipe_data.pipe_name << endl;
			fout << pipe_data.pipe_length << endl;
			fout << pipe_data.pipe_diameter << endl;
			fout << pipe_data.pipe_repair << endl;
		}
	}
	if (station_data.station_name == "None")
	{
		cout << "Nothing to record about station!\n";
	}
	else
	{
		cout << "Info about the station is written to a file!\n";
		if (fout)
		{
			fout << "Info about your station...\n";
			fout << station_data.station_name << endl;
			fout << station_data.station_workshops << endl;
			fout << station_data.station_act_workshops << endl;
			fout << station_data.station_efficiency << endl;
		}
	}
	fout.close();
}

void FileOutput(Pipe& pipe_data, Station& station_data)
{
	ifstream fin("info");
	if (fin)
	{
		string zero_mean;
		int pipe_flag = 0;
		int station_flag = 0;
		while (getline(fin, zero_mean))
		{
			if (zero_mean == "Info about your pipe...")
			{
				cout << "\nThe pipe data is obtained from the file!" << endl;
				cout << "\nInfo about your pipe..." << endl;
				getline(fin, pipe_data.pipe_name);
				cout << "Name of the pipe: " << pipe_data.pipe_name << endl;
				fin >> pipe_data.pipe_length;
				cout << "Length of the pipe: " << pipe_data.pipe_length << endl;
				fin >> pipe_data.pipe_diameter;
				cout << "Diameter of the diameter: " << pipe_data.pipe_diameter << endl;
				fin >> pipe_data.pipe_repair;
				cout << "Repair status of the pipe: " << pipe_data.pipe_repair << endl;
				pipe_flag += 1;
			}
			if (zero_mean == "Info about your station...")
			{
				cout << "\nThe station data is obtained from the file!" << endl;
				cout << "\nInfo about your station..." << endl;
				getline(fin, station_data.station_name);
				cout << "Name of the station: " << station_data.station_name << endl;
				fin >> station_data.station_workshops;
				cout << "Number of workshops: " << station_data.station_workshops << endl;
				fin >> station_data.station_act_workshops;
				cout << "Number of active workshops: " << station_data.station_act_workshops << endl;
				fin >> station_data.station_efficiency;
				cout << "Station efficiency indicator: " << station_data.station_efficiency << endl;
				station_flag += 1;
			}
		}
		if (pipe_flag == 0)
		{
			cout << "\nNo info about pipe!" << endl;
		}
		if (station_flag == 0)
		{
			cout << "\nNo info about station!" << endl;
		}
		fin.close();
	}
}

int main()
{
	Pipe pipe0;
	Station station0;
	int num = 0;
	while (true) {
		cout << endl << "Menu:" << endl;
		cout << "1) Add pipe" << endl;
		cout << "2) Add a CS" << endl;
		cout << "3) View all objects" << endl;
		cout << "4) Edit pipe" << endl;
		cout << "5) Edit a CS" << endl;
		cout << "6) Save" << endl;
		cout << "7) Download" << endl;
		cout << "0) Exit" << endl;
		cout << endl << "Please, enter the command number: ";
		check_input(num);
		//if (cin.fail() || num < 0 || num > 7)
		//{
		//	cout << "There is no such command, please, try again" << endl;
		//	cin.clear();
		//	cin.ignore(1000, '\n');
		//	continue;
		//}
		switch (num)
		{
		case 1:
		{
			pipe0 = AddPipe();
			PrintAddPipe(pipe0);
			break;
		}
		case 2:
		{
			station0 = AddStation();
			PrintAddStation(station0);
			break;
		}
		case 3:
		{
			PrintAddPipe(pipe0);
			PrintAddStation(station0);
			break;
		}
		case 4:
		{
			RepairPipe(pipe0);
			break;
		}
		case 5:
		{
			EditStation(station0);
			break;
		}
		case 6:
		{
			FileRecord(pipe0, station0);
			break;
		}
		case 7:
		{
			FileOutput(pipe0, station0);
			break;
		}
		case 0:
		{
			return false;
			break;
		}
		default:
		{
			cout << endl << "There is no such command, please, try again" << endl;
			break;
		}
		}
	}
	return 0;
}