// 150101067_project1.cpp :  Speech Processing Program 2
// Submitted By : Shashank Garewal
// The one/six recognition program
// read read_me.txt for process of running 

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>

using namespace std;

vector<double> zcrCalculator(istream& fileS, double dc_offset) {
	int count = 1;
	double val1, val2, temp = 0.0;
	vector<double> zcr;
	fileS >> val1;
	val1 -= dc_offset;
	while (fileS >> val2){
		val2 -= dc_offset;
		count++;
		if (val2 > 0 && val1 < 0 || val2 < 0 && val1 > 0)
			temp += 1.0;
		if (count % 100 == 0){
			temp /= 100.0;
			zcr.push_back(temp);
			temp = 0;
		}
		val1 = val2;
	}
	return zcr;
}

void preProcesssing(istream& fileS, int& rangeF, int& rangeL, vector<double>& energy, vector<double>& zcr) {
	// dc offset
	int count = 0;
	double dc_offset = 0.0, val, temp = 0.0, sum = 0.0, max = 0.0;
	//vector<double> energy, zcr;
	while (fileS >> val) {
		count++;
		// ignore 0.04 sec sample
		if (count > 640)
			sum += val;
		// calculate dc offset from 3200 sample
		if (count == 3840) {
			dc_offset = sum / 3200;
			break;
		}
	}
	cout << "dc_offset : " << dc_offset << endl;

	// normalization factor
	while (fileS >> val) {
		if (max < abs(val - dc_offset)) {
			max = abs(val - dc_offset);
		}
	}
	cout << "normalization factor : " << max << endl;

	fileS.clear();
	fileS.seekg(0, std::ios::beg);
	count = 1;

	// noise threshold
	while (fileS >> val) {
		val -= dc_offset;
		val = (val * 5000) / max;
		// removed dc_shift and normalized;
		count++;
		temp += val*val;
		if (count % 100 == 0){
			energy.push_back(temp);
			temp = 0;
		}
	}
	// ignoring first 6*100 sample for energy and calculate noise threshold from later 64*100 sample

	// voiced sound detection via energy
	for (int i = 2; i < energy.size() - 2; i++) {
		if (energy[i] > 1e8) {
			if (rangeF == 0){
				if (energy[i + 1] > 1e8 && energy[i + 2] > 1e8)
					rangeF = i;
			}
			else if (rangeF < i){
				if (energy[i - 1] > 1e8 && energy[i - 2] > 1e8 || energy[i + 1] < 1e8 && energy[i + 2] < 1e8)
					rangeL = i;
			}
		}
	}
	cout << "voiced range : " << float(rangeF) * 100 / 16000 << " sec - " << float(rangeL) * 100 / 16000 << " sec" << endl;

	fileS.clear();
	fileS.seekg(0, std::ios::beg);

	// zcr calculation
	zcr = zcrCalculator(fileS, dc_offset);
}

void zcrMeanSD(vector<double>& zcr, int x, int y, double& zcr_mean, double& zcr_sd){
	// zcr mean
	for (int i = x; i <= y; i++)
		zcr_mean += zcr[i];
	zcr_mean /= y - x + 1;

	// zcr standard deviation
	for (int i = x; i <= y; i++)
		zcr_sd += pow(zcr[i] - zcr_mean, 2);
	zcr_sd = sqrt(zcr_sd / (y - x + 1));
}

int _tmain(int argc, _TCHAR* argv[])
{
	int sum = 0, count = 0, rangeF = 0, rangeL = 0, sec;
	double zcr_noise_mean = 0, zcr_noise_sd = 0, zcr_voiced_mean = 0, zcr_voiced_sd = 0;
	double zcr_left_mean = 0, zcr_left_sd = 0, zcr_right_mean = 0, zcr_right_sd = 0;
	bool fricativeL = 0, fricativeR = 0, noise = 0, nasal = 0;
	char check = 'c';
	string cmd;
	vector<double> energy, zcr;
	ifstream fs;
	do {
		cout << "Enter recording duration in seconds : ";
		cin >> sec;
		cmd = "Recording_Module\\Recording_Module.exe " + to_string(sec) + " output.wav output.txt";
		system(cmd.c_str());

		fs.open("output.txt");
		if (!fs) {
			std::cerr << "Could not open the file! no such record" << std::endl;
			int ch = cin.get();
			continue;
		}
		preProcesssing(fs, rangeF, rangeL, energy, zcr);

		// noise zcr : ignore first 7*100 sample as we did in dc offset
		zcrMeanSD(zcr, 7, 39, zcr_noise_mean, zcr_noise_sd);
		cout << " \t noise : zcr mean and sd : " << zcr_noise_mean << " " << zcr_noise_sd << endl;

		zcrMeanSD(zcr, rangeF, rangeL, zcr_voiced_mean, zcr_voiced_sd);
		cout << " \t voiced : zcr mean and sd : " << zcr_voiced_mean << " " << zcr_voiced_sd << endl;

		// both ends of voiced part for fricative check 
		zcrMeanSD(zcr, rangeF - 32, rangeF - 1, zcr_left_mean, zcr_left_sd);
		zcrMeanSD(zcr, rangeL + 1, rangeL + 32, zcr_right_mean, zcr_right_sd);

		cout << " \t left end : zcr mean and sd : " << zcr_left_mean << " " << zcr_left_sd << endl;
		cout << " \t right end : zcr mean and sd : " << zcr_right_mean << " " << zcr_right_sd << endl;

		if (zcr_left_mean < zcr_noise_mean && zcr_left_mean > zcr_voiced_mean)
			noise = 1;
		else if (zcr_left_mean > zcr_noise_mean && zcr_left_mean - zcr_noise_mean > 0.1)
			fricativeL = 1;
		if (zcr_right_mean < zcr_left_mean && zcr_right_mean > zcr_voiced_mean)
			nasal = 1;
		else if (zcr_right_mean > zcr_noise_mean && zcr_right_mean - zcr_noise_mean > 0.1)
			fricativeR = 1;
		if (zcr_right_mean > zcr_noise_mean && zcr_left_mean > zcr_noise_mean) {
			fricativeL = 1;
			fricativeR = 1;
		}

		// cout << noise << nasal << fricativeL << fricativeR << endl;

		if (fricativeL == 1 || fricativeR == 1)
			cout << "\t \t *******speech signal contain six********" << endl;
		else if (nasal == 1 || noise == 1)
			cout << "\t \t *******speech signal contain one********" << endl;
		// this problem could be solved by taking zcr_sd into consideration 
		else if (fricativeL == 0 && fricativeR == 0 && noise == 0 && nasal == 0)
			cout << endl << "\t \t *******couldn't able to recognized*****" << endl;

		fs.close();

		// reset value for later signals
		sum = 0, count = 0, rangeF = 0, rangeL = 0;
		zcr_noise_mean = 0, zcr_noise_sd = 0, zcr_voiced_mean = 0, zcr_voiced_sd = 0;
		zcr_left_mean = 0, zcr_left_sd = 0, zcr_right_mean = 0, zcr_right_sd = 0;
		fricativeL = 0, fricativeR = 0, noise = 0, nasal = 0;
		energy.erase(energy.begin(), energy.end()), zcr.erase(zcr.begin(), zcr.end());

		cout << endl << "press c to continue elsewise to exit : ";
		cin >> check;
	} while (check == 'c' || check == 'C');
	// int ch = cin.get();
	return 0;
}