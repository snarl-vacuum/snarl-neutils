//============================================================================
// Name        : StringUtils.cpp
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include "StringUtils.h"

/*
 * https://stackoverflow.com/questions/10058606/splitting-a-string-by-a-character
 */
void split(std::string str, std::string splitBy, std::vector<std::string>& tokens) {
    /* Store the original string in the array, so we can loop the rest
     * of the algorithm. */
    tokens.push_back(str);

    // Store the split index in a 'size_t' (unsigned integer) type.
    size_t splitAt;
    // Store the size of what we're splicing out.
    size_t splitLen = splitBy.size();
    // Create a string for temporarily storing the fragment we're processing.
    std::string frag;
    // Loop infinitely - break is internal.
    while(true)
    {
        /* Store the last string in the vector, which is the only logical
         * candidate for processing. */
        frag = tokens.back();
        /* The index where the split is. */
        splitAt = frag.find(splitBy);
        // If we didn't find a new split point...
        if(splitAt == std::string::npos)
        {
            // Break the loop and (implicitly) return.
            break;
        }
        /* Put everything from the left side of the split where the string
         * being processed used to be. */
        tokens.back() = frag.substr(0, splitAt);
        /* Push everything from the right side of the split to the next empty
         * index in the vector. */
        tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
    }
} // split()

pair<int, long double> convStringToLongDouble(const string& value) {
    int retf = 0;
    if(isNumber(value)) {
        try {
            // FOUND that stold does not check non number characters? Added check BEFORE to catch!
            long double v{stold(value)};
            auto ret = make_pair(retf, v);
            return ret;
        // NOT sure if the following catch exceptions actually do anything...
        } catch(const invalid_argument& ia) {
            retf = 1;
        } catch(const out_of_range& oor) {
            retf = 1;
        }
    } else {
        retf = 1;
    }
    auto ret = make_pair(retf, 0);
    return ret;
} // convStringToLongDouble()

int validateStringDateFormat(const string& value, const string& format) {
    struct tm tm;
    // ASSUME format is valid!
    if(strptime(value.c_str(), format.c_str(), &tm)) {
        return 0;
    } else {
        return 1;
    }
} // validateStringDateFormat()

bool isNumber(const string& value) {
    string::difference_type nDecimal = count(value.begin(), value.end(), '.');
    if(nDecimal>1) {
        return false;
    }

    bool isDouble = false;
    for(char const &ch : value) {
        if(isdigit(ch) == 0) {
            // ALLOW decimal numbers!
            if(ch!='.') {
                return false;
            } else {
                isDouble = true;
            }
        }
    }
    // @TODO check for proper format for double number
    return true;
}

// ASSUME format: YYYYMMDD
// NO checks for actual date is real within a calendar!!! (leap year, etc.)
bool isDateGood(const string& date) {
    if(date == "") {
        return 1;
    }
    string year = date.substr(0, sizeof "YYYY"-1);
    string month = date.substr(sizeof "YYYY"-1, sizeof "MM"-1);
    string day = date.substr(sizeof "YYYY"-1+ sizeof "MM"-1, sizeof "SS"-1);
    if(isNumber(year) && isNumber(month) && isNumber(day)) {
        int iyear = atoi(year.c_str());
        if(iyear == 0) {
            return false;
        }
        int imonth = atoi(month.c_str());
        if(imonth == 0 || (imonth < 1 && imonth > 12)) {
            return false;
        }
        int iday = atoi(day.c_str());
        if(iday == 0 || (iday < 1 && iday > 31)) {
            return false;
        }
        return true;
    }
    return false;
} // isDateGood()

// ASSUME format: HH:MM:SS
bool isTimeGood(const string& time) {
    if(time == "") {
        return 1;
    }
    string hour = time.substr(0, sizeof "HH"-1);
    string minute = time.substr(sizeof "HH"-1, sizeof "MM"-1);
    string second = time.substr(sizeof "HH"-1+ sizeof "MM"-1, sizeof "SS"-1);
    if(isNumber(hour) && isNumber(minute) && isNumber(second)) {
        int ihour = atoi(hour.c_str());
        if(ihour == 0) {
            return false;
        }
        int iminute = atoi(minute.c_str());
        if(iminute == 0 || (iminute < 1 && iminute > 59)) {
            return false;
        }
        int isecond = atoi(second.c_str());
        if(isecond == 0 || (isecond < 1 && isecond > 59)) {
            return false;
        }
        return true;
    }
    return false;
} // isTimeGood()
