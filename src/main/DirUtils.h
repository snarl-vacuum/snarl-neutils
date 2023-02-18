#ifndef DIRUTILS_H
#define DIRUTILS_H
//============================================================================
// Name        : DirUtils.h
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include "Common.h"

#include <algorithm>
#include <vector>
#include <string>
#include <experimental/filesystem>

using namespace std;

namespace fs = std::experimental::filesystem;

static const int SEARCH_LINE_MAX = 10;

STRING_VECTOR _dir_recursive(const fs::path&, const EXTS_MAP&);

STRING_VECTOR _dir(const fs::path&, const EXTS_MAP&);

#endif