#include <iostream>
#include <fstream>
#include "reader_header.h"

using namespace std;

int main(){
	CSV_Data reader;
	ifstream ip("data.csv"); //Give pathe to datefile.csv

	if(!ip.is_open()) std::cout<<"ERROR: Not possible to open file"<< "\n";
	
	
	std::cout << "-------------------------------------------------"<< "\n";
	while (ip.good()){
	
		getline(ip,reader.Date,';');
		getline(ip,reader.Time,';');
		getline(ip,reader.X_position,';');
		getline(ip,reader.Y_position,';');
		getline(ip,reader.Z_position,';');
		getline(ip,reader.X_velocity,';');
		getline(ip,reader.Y_velocity,';');
		getline(ip,reader.Z_velocity,';');
		getline(ip,reader.Temperature,';');
		getline(ip,reader.Rel_humidity,';');
		getline(ip,reader.Light_intensity,'\n');
	
		std::cout << "Date:" << reader.Date << "\n";
		std::cout << "Time:" << reader.Time << "\n";
		std::cout << "X_position:" << reader.X_position << "\n";
		std::cout << "Y_position:" << reader.Y_position << "\n";
		std::cout << "Z_position:" << reader.Z_position << "\n";
		std::cout << "X_velocity:" << reader.X_velocity << "\n";
		std::cout << "Y_velocity:" << reader.Y_velocity << "\n";
		std::cout << "Z_velocity:" << reader.Z_velocity << "\n";
		std::cout << "Temperature:" << reader.Temperature << "\n";
		std::cout << "Rel_humidity:" << reader.Rel_humidity << "\n";
		std::cout << "Light_intensity:" << reader.Light_intensity << "\n";
		std::cout << "-------------------------------------------------"<< "\n";
	}
}

