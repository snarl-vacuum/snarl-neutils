#ifndef FILEUTILS_H
#define FILEUTILS_H
//============================================================================
// Name        : FileUtils.h
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include <stdio.h>  // printf
#include <iostream> // std::cout

#include <vector>
#include <string>
#include <experimental/filesystem>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include "DirUtils.h"
#include "StringUtils.h"

using namespace std;

namespace fs = std::experimental::filesystem;

static const string DIR_CHAR = "/"; // Linux

// IMG_20150111_105448.JPG
static const string FN_IMG_("IMG_");
static const string FN_YEAR("YYYY");
static const string FN_MONTH("MM");
static const string FN_DAY("DD");
static const string FN_HOUR("hh");
static const string FN_MINUTE("mm");
static const string FN_SECOND("ss");
static const string FN_TIME(FN_HOUR+FN_MINUTE+FN_SECOND);
static const string FN_DATE(FN_YEAR+FN_MONTH+FN_DAY);
static const string FILE_NAME_TEMPLATE(FN_IMG_+FN_DATE+"_"+FN_TIME);

static const string FN_DSC_("DSC_");
static const string FN_FB_("FB_");
static const string FN_FB_IMG_(FN_FB_+FN_IMG_);

static const string EXT_JPG(".jpg");
static const string EXT_MOV(".mov");
static const string EXT_HEIC(".heic");
static const string EXT_HEVC(".hevc");

static const string DIR_OF_FILES_TO_GO_BASE("y:\\");
static const string DIR_OF_FILES_TO_GO_FOLDER(DIR_OF_FILES_TO_GO_BASE+"output");

static const string FN2_YEAR("YYYY");
static const string FN2_MONTH("MM");
static const string FN2_DAY("DD");
static const string FN2_HOUR("HH");
static const string FN2_MINUTE("MM");
static const string FN2_SECOND("SS");
static const string FN2_TIME(FN2_HOUR+FN2_MINUTE+FN2_SECOND);
static const string FILE_NAME2_TEMPLATE(FN2_YEAR+FN2_MONTH+FN2_DAY+"_"+FN2_TIME);

enum FN_ENCODING {
    FILE_MODIFIED_DATE, ENCODED_NAME, ENCODE_NAME2, UNKNOWN
};

string getNoPathFileNameWithExt(const string&);

FN_ENCODING getFileNameEncoding(const string);

int handleFile(const string&, const string&, const string&, const string&, const string&, const string&, const string&, const string&);

int processEncodedName1(const string, const string);
int processEncodedName2(const string, const string);
string getFileDateTime(const string&);
int processFileModifiedDate1(const string, const string);

#endif