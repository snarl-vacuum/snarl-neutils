#ifndef STRINGUTILS_H
#define STRINGUTILS_H
//============================================================================
// Name        : StringUtils.h
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include <stdio.h>  // printf
#include <iostream> // std::cout

#include <algorithm>

#include <string>
#include <vector>
#include <ctime>

#include <stdexcept>

using namespace std;

/*
 * https://stackoverflow.com/questions/10058606/splitting-a-string-by-a-character
 */
void split(std::string, std::string, std::vector<std::string>&);

pair<int, long double> convStringToLongDouble(const string&);

int validateStringDateFormat(const string&, const string&);

bool isNumber(const string&);

bool isDateGood(const string&);

bool isTimeGood(const string&);

#endif
