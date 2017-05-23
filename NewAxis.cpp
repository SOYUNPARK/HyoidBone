#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>   //getline()
#include <cmath>
using namespace std;
int main(int argc, char *argv[]) {
	string line;
	int frameNum = 0;
	ifstream file_sample;
	ofstream file_new;
	double timeInterval = 0;

	string uri = argv[1];  //text file path

	file_sample.open(uri);   //check if file was successfully opened  
	if (file_sample.fail()) {
		cout << "Failed to load sample file" << endl;
		return 0;
	}
	///////to get frameNumber
	for (int i = 0; i < 9; i++) {
		getline(file_sample, line);
		if (strncmp(line.c_str(), "% Total frame number", 20) == 0) { //to find 'frame number' row 
			stringstream fnst(line);
			string fncontext;
			for (int j = 0; j < 6; j++) {   //the frame number is 6th item
				getline(fnst, fncontext, ' ');
			}
			frameNum = stoi(fncontext);  //stoi() : convert frameNumber string to int
		}
		else if (strncmp(line.c_str(), "% Time interval", 8) == 0) {
			stringstream tist(line);  //to get time interval for HMMD
			string ticontext;
			for (int k = 0; k < 5; k++) {
				getline(tist, ticontext, ' ');
			}
			timeInterval = stod(ticontext); //stod() : convert frameNumber string to double
		}
	}

	int *fn = new int[frameNum];   //allocate dynamic memory with new-delete
	double *h_x = new double[frameNum];
	double *h_y = new double[frameNum];
	double *dis = new double[frameNum];

	for (int i = 0; i < frameNum; i++) {
		getline(file_sample, line);
		if (strncmp(line.c_str(), "%", 1) == 0) {     //skip unnecessary comments
			continue;
		}
		else {
			stringstream st(line);
			string context;

			for (int j = 0; j < 4; j++) {
				getline(st, context, ',');
				switch (j) {
				case 0:
					fn[i] = stoi(context);
					break;
				case 1:
					h_x[i] = stod(context);
					break;
				case 2:
					h_y[i] = stod(context);
					break;
				case 3:
					dis[i] = stod(context);
					break;
				}
			}
		}
	}

	double HMD;//hyoid movement duration = the resting position ~ Burst end position
	double HMP_X;//hyoid maximum posiition x-axis
	double HMP_Y;//hyoid maximum posiition y-axis
	double HMP_XY;//hyoid maximum posiition x-axis, y-axis = burst end position

	double HMD_A;//hyoid maximum displacement Anterior
	double HMD_S;//hyoid maximum displacement superior
	double HMD_H;//hyoid maximum displacement hypotenuse

	double HAV_A;//hyoid average velocity anterior = HMD_A / HMD
	double HAV_S;//hyoid average velocity superior = HMD_S / HMD
	double HAV_H;//hyoid average velocity hypotenuse = HMD_H / HMD

	double MAX_V;//hyoid maximum velocity(velocity of each frame)

	double restingPos;
	int rest_frameNum;
	restingPos = h_y[0];
	rest_frameNum = fn[0];

	double burstEnd;  //to get the Burst end position
	int max_frameNum;
	burstEnd = dis[0];
	for (int i = 0; i < frameNum; i++) {   //the Burst end position = maximum of dis
		if (burstEnd < dis[i]) {
			burstEnd = dis[i];
			max_frameNum = fn[i];
		}
		else {
			continue;
		}
	}

	double max_x;  //to get maximum anterior displacement = HMD_A
	int max_frameNum2;
	max_x = h_x[0];
	for (int i = 0; i < frameNum; i++) {
		if (max_x < h_x[i]) {
			max_x = h_x[i];
			max_frameNum2 = fn[i];
		}
		else {
			continue;
		}
	}
	double max_y;   //to get maximum superior displacement = HMD_S
	int max_frameNum3;
	max_y = h_y[0];
	for (int i = 0; i < frameNum; i++) {
		if (max_y < h_y[i]) {
			max_y = h_y[i];
			max_frameNum3 = fn[i];
		}
		else {
			continue;
		}
	}


	HMD = abs(max_frameNum - rest_frameNum) * timeInterval;

	HMP_X = h_x[max_frameNum - 1];
	HMP_Y = h_y[max_frameNum - 1];
	HMP_XY = burstEnd;  //Burst end position

	HMD_A = h_x[max_frameNum - 1] - h_x[rest_frameNum - 1];
	HMD_S = h_y[max_frameNum - 1] - restingPos;  // = max_y - h_y[rest_frameNum]
	HMD_H = sqrt(pow(HMP_X - h_x[rest_frameNum - 1], 2) + (pow(HMP_Y - h_y[rest_frameNum - 1], 2)));

	HAV_A = HMD_A / HMD;
	HAV_S = HMD_S / HMD;
	HAV_H = HMD_H / HMD;

	double * vofh = new double[frameNum];   //
	for (int i = 0; i < frameNum; i++) {
		if (i < (frameNum - 1)) {
			vofh[i] = sqrt(pow(h_x[i + 1] - h_x[i], 2) + pow(h_y[i + 1] - h_y[i], 2)) / timeInterval;  //calculate velocity of hyoid bone for MAX
		}
		else {
			vofh[i] = -9999;
		}
	}

	//to get maximum velocity of hyoid bone for MAX
	int max_frameNumV;
	MAX_V = vofh[0];
	for (int i = 0; i < frameNum; i++) {
		if (MAX_V < dis[i]) {
			MAX_V = dis[i];
			max_frameNumV = fn[i];
		}
		else {
			continue;
		}
	}

	file_new.open("new_file.txt");
	if (!file_new.is_open()) {       //check if new file was successfully opened 
		cout << "open() error" << endl;
		return -1;
	}
	ifstream file_sample2;
	string line2;
	file_sample2.open(uri);       //check if original file was successfully opened  
	if (file_sample2.fail()) {
		cout << "Failed to load sample file" << endl;
		return 0;
	}
	for (int i = 0; i < 8; i++) {
		getline(file_sample2, line2);
		file_new << line2 << endl;
	}
	file_new << "% Resting Position Frame number : " << rest_frameNum << endl; //add Resting position frame number under the original comments
	file_new << "% Burst End Position Frame number : " << max_frameNum << endl;  //add Burst ending frame number under the original comments
	file_new << "% Data order : Frame number / Velocity of HyoidBone / velocity of Hyoid Bone (x-axis) / average velocity of 3 Hyoid Bone (x-axis)" << endl;
	file_new << "1, Hyoid Movement Duration, " << HMD << endl;
	file_new << "2, Hyoid Maximum Position (X), " << HMP_X << endl;
	file_new << "3, Hyoid Maximum Position (Y), " << HMP_Y << endl;
	file_new << "4, Hyoid Maximum Position (XY), " << HMP_XY << endl;
	file_new << "	4.1, Hyoid Maximum position (X-axis), " << max_x << endl;
	file_new << "	4.2, Hyoid Maximum position (Y-axis), " << max_y << endl;
	file_new << "5, Hyoid Maximum Displacement (Anterior), " << HMD_A << endl;
	file_new << "6, Hyoid Maximum Displacement (Superior)" << HMD_S << endl;
	file_new << "7, Hyoid Maximum Displacement (Hypotenuse)" << HMD_H << endl;
	file_new << "8, Hyoid Average Velocity (Anterior), " << HAV_A << endl;
	file_new << "9, Hyoid Average Velocity (Superior), " << HAV_S << endl;
	file_new << "10, Hyoid Average Velocity (Hypotenuse), " << HAV_H << endl;
	file_new << "11, Hyoid Maximum Velocity = Max (Velocity_of_eachframe), " << MAX_V << endl;


	file_new.close();

	delete[] fn;
	delete[] h_x;
	delete[] h_y;
	delete[] dis;
	delete[] vofh;
	return 0;
}
