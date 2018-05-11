/*
 * =========================================================================================
 * Name        : eventLib.cpp
 * Author      : Duc Dung Nguyen
 * Email       : nddung@hcmut.edu.vn
 * Copyright   : Faculty of Computer Science and Engineering - Bach Khoa University
 * Description : library for Assignment 2 - Data structures and Algorithms - Fall 2017
 *               This library contains functions used for event management
 * =========================================================================================
 */

#include "requestLib.h"


void loadRequests(char* fName, L1List<VM_Request> &rList) {
	// TODO: write your code to load requests. Each request is separated by a whitespace
	fstream file(fName);
	//fstream file("rq1.txt");

	if (!file)
	{
		cout << "The file is not found!";
		return;
	}
	string str;
	while (file >> str)
	{
		if (str[str.length() - 1] == ';')
			str.pop_back();
		VM_Request vm;
		strcpy(vm.code, str.data());
		rList.push_back(vm);
	}
	return;
}
