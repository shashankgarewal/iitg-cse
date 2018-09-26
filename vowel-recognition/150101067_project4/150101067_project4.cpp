// 150101067_project1.cpp :  Speech Processing Program 1
// Submitted By : Shashank Garewal
// The one/six recognition program
// read read_me.txt for process of running 

#define _USE_MATH_DEFINES

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <cmath>

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

vector< vector<double> > HammingWindow(istream& fileS, int rangeF, int rangeL, double dc_offset, double max){
	vector<double> hamming_signal(320), signal;
	vector< vector<double> > hamming_signals;
	ifstream fs;
	int count = 0;
	double val = 0;
	while (fileS >> val) {
		count++;
		if (count >= rangeF * 100 && count <= rangeL * 100){
			val -= dc_offset;
			val = (val * 5000) / max;
			signal.push_back(val);
		}
	}
	for (int i = 0; i < signal.size() - 3 * 80; i++){
		// cout << i << " ";
		if (i % 80 == 0 && i != 0){
			for (int j = i; j < i + 240; j++){
				// cout << "80 + (i % 80) + j - i " << 80 + (i % 80) + j - i << endl;
				hamming_signal[80 + (i % 80) + j - i] = signal[j] * (0.54 - 0.46*cos((2 * 3.14 * ((i % 80) + j - i)) / 319));
				// cout << 80 + (i % 80) + j - i << " " << hamming_signal[80 + (i % 80) + j - i] << endl;
			}
			hamming_signals.push_back(hamming_signal);
			// hamming_signal.clear();
			hamming_signal[i % 80] = signal[i] * (0.54 - 0.46 * cos((2 * 3.14 * (i % 80)) / 319));
		}
		else{
			hamming_signal[i % 80] = signal[i] * (0.54 - 0.46 * cos((2 * 3.14 * (i % 80)) / 319));
			// cout << hamming_signal[i % 80] << " " << i % 80 << endl;
		}
	}
	return hamming_signals;
}

vector< vector<double> > PreProcesssing(istream& fileS, int& rangeF, int& rangeL, vector<double>& energy, vector<double>& zcr) {
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
		if (count > 700){
			val -= dc_offset;
			val = (val * 5000) / max;
			// removed dc_shift and normalized;
			count++;
			temp += val*val;
			if (count % 100 == 0){
				// cout << count << " - " << temp << endl;
				energy.push_back(temp);
				temp = 0;
			}
		}
		else count++;
	}
	// ignoring first 6*100 sample for energy and calculate noise threshold from later 32*100 sample
	int x = 0, y = 31;
	// mean energy of noise 
	double energy_mean = 0, energy_sd = 0;
	for (int i = x; i <= y; i++)
		energy_mean += energy[i];
	energy_mean /= y - x + 1;

	// zcr standard deviation
	for (int i = x; i <= y; i++)
		energy_sd += pow(energy[i] - energy_mean, 2);
	energy_sd = sqrt(energy_sd / (y - x + 1));

	cout << energy_mean + 3 * energy_sd << endl;

	// voiced sound detection via energy
	for (int i = 2; i < energy.size() - 2; i++) {
		int test = 0;
		if (energy[i] > energy_mean + 3 * energy_sd) {
			if (energy[i + 1] > energy_mean + 3 * energy_sd) test++;
			if (energy[i + 2] > energy_mean + 3 * energy_sd) test++;
			if (energy[i - 1] > energy_mean + 3 * energy_sd) test++;
			if (energy[i - 2] > energy_mean + 3 * energy_sd) test++;
			if (rangeF == 0){
				if (test > 3)
					rangeF = i;
			}
			else if (rangeF < i){
				if (test > 3)
					rangeL = i;
			}
		}
	}
	cout << "voiced range : " << float(rangeF) * 100 / 16000 + .03 << " sec - " << float(rangeL) * 100 / 16000 + .03 << " sec" << endl;
	// shift 500 sample right on both end
	rangeF += 5;
	rangeL += 5;

	fileS.clear();
	fileS.seekg(0, std::ios::beg);
	return HammingWindow(fileS, rangeF, rangeL, dc_offset, max);
}

vector< vector<double> > AutoCorrelation(vector< vector<double> > hamming_signals){
	vector< vector<double> > R;
	vector <double> Rn(13, 0);
	double sum = 0;
	for (int n = 0; n < hamming_signals.size(); n++){
		for (int k = 0; k < 13; k++){
			for(int m = 0; m < 320 - k; m++){
				sum += hamming_signals[n][m]*hamming_signals[n][m+k];
			}
			Rn[k] = sum;
			sum = 0;
		}
		R.push_back(Rn);
	}
	return R;
}

vector< vector<double> > Durbin(vector< vector<double> > R){
	double sum = 0;
	vector<double> E(13, 0), Atemp(12,0), K(12,0);
	vector< vector<double> > A, alphaTemp(12,Atemp);
	for(int n = 0; n<R.size(); n++){
		E[0] = R[n][0];
		for(int i = 1; i < R[n].size(); i++){
			for(int j = 1; j < i; j++){
				sum += 	alphaTemp[j][i-1-1]*R[n][i-j];
			}
			K[i-1] = (R[n][i] - sum)/E[i-1];
			sum = 0;
			alphaTemp[i-1][i-1] = K[i-1];
			for(int j = 1; j <= i-1; j++)
				alphaTemp[j-1][i-1] = alphaTemp[j-1][i-1-1] - K[i-1]*alphaTemp[i-j][i-1-1];
			E[i] = ( 1-K[i-1]*K[i-1] ) * E[i-1];
		}
		for(int i =0; i<12; i++){
			Atemp[i] = alphaTemp[i][11];
		}
		A.push_back(Atemp);
	}
	return A;
}

vector< vector<double> > Cepstral(vector< vector<double> > R, vector< vector<double> > A){
	double sum = 0;
	vector<double> Ctemp(13,0), temp(12,0);
	vector< vector<double> > C;
	for(int n = 0; n < R.size(); n++){
		Ctemp[0] = log2(R[n][0]);
		for(int i=1; i<Ctemp.size(); i++){
			for(int k = 1; k < i; k++){
				// cout << "(k/i) * Ctemp[k]*A[n][i-k]; " << ((float)k / (float)i) * Ctemp[k] * A[n][i - k] << endl;
				sum += ((float)k /(float)i) * Ctemp[k] * A[n][i - k];
			}
			// cout << sum << " " << i << endl;
			Ctemp[i] = A[n][i-1] + sum;
			sum = 0;
			for(int i = 0; i < 12; i++){
				temp[i] = Ctemp[i+1];
			}
		}
		C.push_back(Ctemp);
	}
	return C;
}

vector<double> TokhuraDistance(vector< vector<double> > Ctest, vector< vector<double> > Crefrence){
	double sum = 0;
	vector<double> W{1,3,7,13,19,22,25,33,42,50,56,61}, distance;
	//if(Ctest.size() != Crefrence.size())
		//return {-1};
	for (int n = 0; n < Crefrence.size(); n++){
		for (int i = 1; i < Crefrence[n].size(); i++){
			sum += W[i-1] * (Ctest[n][i] - Crefrence[n][i])*(Ctest[n][i] - Crefrence[n][i]);
		}
		distance.push_back(sum);
		sum = 0;
	}
	return distance;
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
	int sum = 0, count = 0, rangeF = 0, rangeL = 0;
	double zcr_noise_mean = 0, zcr_noise_sd = 0, zcr_voiced_mean = 0, zcr_voiced_sd = 0, max = 0;
	double zcr_left_mean = 0, zcr_left_sd = 0, zcr_right_mean = 0, zcr_right_sd = 0, val = 0;
	bool fricativeL = 0, fricativeR = 0, noise = 0, nasal = 0;
	char check = 'c';
	string fileName;
	const int traningSize = 5 * 5; // 5 for no. of traning signal dataset of vowel and another one is for type of vowels
	double distance[traningSize][10];
	vector<double> energy, zcr, d(10);
	vector< vector<double> > hamming_signals, R, A, C;
	vector< vector<double> > cepstral[traningSize];
	ifstream fs;
	for (int i = 1; i <= traningSize; i++){
		if (i <= 5)
			fileName = "150101067_project3/150101067_a_" + std::to_string(i) + ".txt";
		else if (i >= 5 && i <= 10)
			fileName = "150101067_project3/150101067_e_" + std::to_string(i - 5) + ".txt";
		else if (i >= 10 && i <= 15)
			fileName = "150101067_project3/150101067_i_" + std::to_string(i - 10) + ".txt";
		else if (i >= 15 && i <= 20)
			fileName = "150101067_project3/150101067_o_" + std::to_string(i - 15) + ".txt";
		else
			fileName = "150101067_project3/150101067_u_" + std::to_string(i - 20) + ".txt";

		fs.open(fileName);
		cout << fileName << endl;
		if (!fs) {
			std::cerr << "Could not open the file! no such record" << std::endl;
			int ch = cin.get();
			continue;
		}
		hamming_signals = PreProcesssing(fs, rangeF, rangeL, energy, zcr);
		R = AutoCorrelation(hamming_signals);
		A = Durbin(R);
		C = Cepstral(R, A);
		for (int j = 0; j < 10; j++){
			cepstral[i-1].push_back(C[i]);
		}
		cout << endl;
		fs.close();
		sum = 0, count = 0, rangeF = 0, rangeL = 0;
		energy.erase(energy.begin(), energy.end())/*, zcr.erase(zcr.begin(), zcr.end())*/;
	}
	do {
		cout << "Enter the file name with extension : ";
		cin >> fileName;
		fs.open("150101067_project3/" + fileName);
		if (!fs) {
			std::cerr << "Could not open the file! no such record" << std::endl;
			int ch = cin.get();
			continue;
		}
		// hamming_signals = HammingWindow(fs, 0, 2000, 0, 5000);
		hamming_signals = PreProcesssing(fs, rangeF, rangeL, energy, zcr);
		R = AutoCorrelation(hamming_signals);
		A = Durbin(R);
		C = Cepstral(R, A);
		/*
		for (int i = 0; i < 20; i++){
			for (int j = 0; j < A[i].size(); j++)
				cout << A[i][j] << " , " ;
			cout << endl;
		}
		cout << endl << endl;
		for (int i = 0; i < 20; i++){
			for (int j = 0; j < C[i].size(); j++)
				cout << C[i][j] << " , ";
			cout << endl;
		}
		*/
		fs.close();

		for (int i = 0; i < traningSize; i++){
			TokhuraDistance(C, cepstral[i]).size();
			d = TokhuraDistance(C, cepstral[i]);
			
			for (int j = 0; j < 10; j++){
				distance[i][j] = d[j];
				cout << distance[i][j] << " ";
			}
			cout << endl;
			if ( (i+1) % 5 == 0){
				cout << endl;
			}
		}
		sum = 0;
		double min = 100000;
		int index = -1;
		for (int i = 0; i < traningSize; i++){
			for (int j = 0; j < 10; j++){
				if (distance[i][j] < min){
					index = i;
					min = distance[i][j];
				}
				//sum += distance[i][j];
			}
		}
		index++;
		cout << endl << index << endl;
		if (index <= 5)
			cout << fileName << " contain a" << endl;
		else if (index >= 5 && index <= 10)
			cout << fileName << " contain e" << endl;
		else if (index >= 10 && index <= 15)
			cout << fileName << " contain i" << endl;
		else if (index >= 15 && index <= 20)
			cout << fileName << " contain o" << endl;
		else
			cout << fileName << " contain u" << endl;

		// reset value for later signals
		sum = 0, count = 0, rangeF = 0, rangeL = 0;
		zcr_noise_mean = 0, zcr_noise_sd = 0, zcr_voiced_mean = 0, zcr_voiced_sd = 0;
		zcr_left_mean = 0, zcr_left_sd = 0, zcr_right_mean = 0, zcr_right_sd = 0;
		fricativeL = 0, fricativeR = 0, noise = 0, nasal = 0;
		energy.erase(energy.begin(), energy.end()), zcr.erase(zcr.begin(), zcr.end());

		cout << endl << "press c to continue elsewise to exit : ";
		//cin >> check;
	} while (check == 'c' || check == 'C');
	// int ch = cin.get();
	return 0;
}