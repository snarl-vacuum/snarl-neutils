//============================================================================
// Name        : FileUtils.cpp
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include "FileUtils.h"

string getNoPathFileNameWithExt(const string& fromPathFileName) {
    string fileName = "";
    if(fs::is_directory(fromPathFileName)) {
        // DIRECTORY!!
        // DO NOTHING!
    } else {
        // ASSUME FILE!
        size_t b = fromPathFileName.rfind(DIR_CHAR);    // LINUX
        if(b == string::npos) {
            fileName = string(fromPathFileName);
        } else {
            fileName = fromPathFileName.substr(b+1);
        }
    }
    return fileName;
} // getNoPathFileNameWithExt()

FN_ENCODING getFileNameEncoding(const string pathFileName) {
    string fileName = getNoPathFileNameWithExt(pathFileName);
    if(fileName.compare("") == 0) {
        return FN_ENCODING::UNKNOWN;
    }
    {
        size_t posi = fileName.find(FN_IMG_);
        size_t posd = fileName.find(FN_DSC_);
        size_t posf = fileName.find(FN_FB_IMG_);
        if((posi != string::npos && posi == 0/*zero index*/) ||
           (posd != string::npos && posd == 0/*zero index*/) ||
           (posf != string::npos && posf == 0/*zero index*/)) {

            STRING_VECTOR sv;
            split(fileName, "_", sv);

            string date = "";
            string time = "";
            if(posi == 0) {
                // IMG_2964.JPG
                // IMG_20150111_105448.JPG
                // IMG_20150111_105448_1.JPG
                if(sv.size() == 2) {
                    // IMG_2964.JPG
                    return FN_ENCODING::FILE_MODIFIED_DATE;
                    } else if(sv.size() == 3 || sv.size() == 4) {
                    sv[2] = sv[2].substr(0, sv[2].rfind("."));
                    // IMG_20150111_105448.JPG
                    // IMG_20150111_105448_1.JPG
                    if(sv[1].size() == FN_DATE.size() && sv[2].size() == FN_TIME.size()) {
                        date = sv[1];
                        time = sv[2];
                    } else {
                        return FN_ENCODING::UNKNOWN;
                    }
                }
            } else if(posf == 0) {
                // FB_IMG_20150111_105448.JPG
                // FB_IMG_20150111_105448_1.JPG
                if(sv.size() == 4 || sv.size() == 5) {
                    sv[3] = sv[3].substr(0, sv[3].rfind("."));
                    // FB_IMG_20150111_105448.JPG
                    // FB_IMG_20150111_105448_1.JPG
                    if(sv[2].size() == FN_DATE.size() && sv[3].size() == FN_TIME.size()) {
                        date = sv[2];
                        time = sv[3];
                    } else {
                        return FN_ENCODING::UNKNOWN;
                    }
                }
            } else if(posd == 0) {
                // DSC_1234.JPG
                return FN_ENCODING::FILE_MODIFIED_DATE;
            }

            if(!isDateGood(date) || !isTimeGood(time)) {
                return FN_ENCODING::UNKNOWN;
            }

            return FN_ENCODING::ENCODED_NAME;
        } // if
    }
    {
        size_t posu = fileName.find("_");
        if(posu != string::npos && posu == FILE_NAME2_TEMPLATE.find("_") && (fileName.size() - (fileName.size() - fileName.rfind("."))) == FILE_NAME2_TEMPLATE.size()) {
            // 20220313_132024.jpg
            STRING_VECTOR sv;
            split(fileName, "_", sv);
            sv[1] = sv[1].substr(0, sv[1].rfind("."));

            string date = "";
            string time = "";
            if(sv.size() <=0 || sv.size() > 2) {
                return FN_ENCODING::UNKNOWN;
            } else if(sv[0].size() == FN_DATE.size() && sv[1].size() == FN_TIME.size()) {
                date = sv[0];
                time = sv[1];
            } else {
                return FN_ENCODING::UNKNOWN;
            }
            if(!isDateGood(date) || !isTimeGood(time)) {
                return FN_ENCODING::UNKNOWN;
            }
            // 20220313_132024.jpg
            return FN_ENCODING::ENCODE_NAME2;
        }
    }
    return FN_ENCODING::UNKNOWN;
    
} // getFileNameEncoding()

int handleFile(const string& fromPathFileName, const string& year, const string& month, const string& day, const string& hour, const string& minute, const string& second, const string& outputDir) {
    // NOT NEEDED! validation made in getFileNameEncoding()
    // {
    //     string d(year+month+day);
    //     string t(hour+minute+second);
    //     if(!isDateGood(d) || !isTimeGood(t)) {
    //         cout << "BAD date and or time, ignoring file: " << fromPathFileName << endl;
    //         return 1;
    //     }
    // }
    {
        string pathOutputFolder(outputDir);
        if (!fs::is_directory(pathOutputFolder) || !fs::exists(pathOutputFolder)) {
            cout << "Creating folder: " << pathOutputFolder << endl;
            fs::create_directory(pathOutputFolder);
        }
    }
    {
        string yearFolder(year);
        string pathYearFolder(outputDir+DIR_CHAR+yearFolder);
        if (!fs::is_directory(pathYearFolder) || !fs::exists(pathYearFolder)) {
            cout << "Creating folder: " << pathYearFolder << endl;
            fs::create_directory(pathYearFolder);
        }
    }
    {
        string toFolder(year+DIR_CHAR+year+"."+month+day);
        string toPathFolder(outputDir+DIR_CHAR+toFolder);
        if (!fs::is_directory(toPathFolder) || !fs::exists(toPathFolder)) {
            cout << "Creating folder: " << toPathFolder << endl;
            fs::create_directory(toPathFolder);
        }

        string fileName = getNoPathFileNameWithExt(fromPathFileName);
        if(fileName.compare("") != 0) {
            string toPathFileName(toPathFolder+DIR_CHAR+fileName);
            if(!fs::exists(toPathFileName)) {
                cout << "Copying file from: " << fromPathFileName << " to: " << toPathFolder << " ";
                fs::copy(/*FROM*/fromPathFileName, /*TO*/toPathFileName);

                char command[50];
                // -a = accessed
                // -m = modified
                // -t = timestamp - use [[CC]YY]MMDDhhmm[.ss] time format
                string dtf(year+month+day+hour+minute+"."+second);
                sprintf(command, "touch -a -m -t %s %s", dtf.c_str(), toPathFileName.c_str());
                system(command);

                if(fs::file_size(fromPathFileName) != fs::file_size(toPathFileName)) {
                    cout << "ERROR!";
                    cout << " Mismatching file sizes: " << fs::file_size(fromPathFileName) << " " << fs::file_size(toPathFileName);
                } else {
                    cout << "OK";
                }
                cout << endl;
            }
        }
    }
    return 0;
} // handleFile()

int processEncodedName1(const string fromPathFileName, const string outputDir) {
    size_t b = fromPathFileName.rfind(DIR_CHAR);
    size_t b2 = fromPathFileName.rfind(FN_FB_);
    bool startsFB = b2 != string::npos;
    size_t dyb = FILE_NAME_TEMPLATE.find(FN_YEAR) + b + 1;
    size_t dmb = FILE_NAME_TEMPLATE.find(FN_MONTH) + b + 1;
    size_t ddb = FILE_NAME_TEMPLATE.find(FN_DAY) + b + 1;
    size_t thb = FILE_NAME_TEMPLATE.find(FN_HOUR) + b + 1;
    size_t tmb = FILE_NAME_TEMPLATE.find(FN_MINUTE) + b + 1;
    size_t tsb = FILE_NAME_TEMPLATE.find(FN_SECOND) + b + 1;
    if(startsFB) {
        dyb += FN_FB_.size();
        dmb += FN_FB_.size();
        ddb += FN_FB_.size();
        thb += FN_FB_.size();
        tmb += FN_FB_.size();
        tsb += FN_FB_.size();
    }
    string year = fromPathFileName.substr(dyb, FN_YEAR.size());
    string month = fromPathFileName.substr(dmb, FN_MONTH.size());
    string day = fromPathFileName.substr(ddb, FN_DAY.size());
    string hour = fromPathFileName.substr(thb, FN_HOUR.size());
    string minute = fromPathFileName.substr(tmb, FN_MINUTE.size());
    string second = fromPathFileName.substr(tsb, FN_SECOND.size());
    return handleFile(fromPathFileName, year, month, day, hour, minute, second, outputDir);
} // processEncodedName1()

int processEncodedName2(const string fromPathFileName, const string outputDir) {
    size_t b = fromPathFileName.rfind(DIR_CHAR);
    size_t dyb = FILE_NAME2_TEMPLATE.find(FN2_YEAR) + b + 1;
    size_t dmb = FILE_NAME2_TEMPLATE.find(FN2_MONTH) + b + 1;
    size_t ddb = FILE_NAME2_TEMPLATE.find(FN2_DAY) + b + 1;
    size_t thb = FILE_NAME2_TEMPLATE.find(FN2_HOUR) + b + 1;
    size_t tmb = FILE_NAME2_TEMPLATE.find(FN2_MINUTE) + b + 1;
    size_t tsb = FILE_NAME2_TEMPLATE.find(FN2_SECOND) + b + 1;

    string year = fromPathFileName.substr(dyb, FN2_YEAR.size());
    string month = fromPathFileName.substr(dmb, FN2_MONTH.size());
    string day = fromPathFileName.substr(ddb, FN2_DAY.size());
    string hour = fromPathFileName.substr(thb, FN2_HOUR.size());
    string minute = fromPathFileName.substr(tmb, FN2_MINUTE.size());
    string second = fromPathFileName.substr(tsb, FN2_SECOND.size());
    return handleFile(fromPathFileName, year, month, day, hour, minute, second, outputDir);
} // processEncodedName2()

string getFileDateTime(const string& fromPathFileName) {
    struct stat result;
    int ret = stat(fromPathFileName.c_str(), &result); 
    if(ret == 0) {
        time_t mod_time = result.st_mtime;
        struct tm *tm;
        char buf[200];
        /* convert time_t to broken-down time representation */
        tm = localtime(&mod_time);
        /* format time year.month,day hour:minute:seconds */
        strftime(buf, sizeof(buf), "%Y.%m,%d %H:%M:%S", tm);
        //printf("%s\n", buf);
        string datetime(buf);
        return datetime;
    }
    string empty("");
    return empty;
} // getFileDateTime()

int processFileModifiedDate1(const string fromPathFileName, const string outputDir) {
    string datetime = getFileDateTime(fromPathFileName);
    if(datetime == "") {
        return 1;
    }
    string year = datetime.substr(0, datetime.find("."));
    string month = datetime.substr(datetime.find(".")+1, 2);
    string day = datetime.substr(datetime.find(",")+1, 2);
    string hour = datetime.substr(datetime.find(" ")+1, 2);
    string minute = datetime.substr(datetime.find(":")+1, 2);
    string second = datetime.substr(datetime.rfind(":")+1, 2);
    return handleFile(fromPathFileName, year, month, day, hour, minute, second, outputDir);
} // processFileModifiedDate1()
