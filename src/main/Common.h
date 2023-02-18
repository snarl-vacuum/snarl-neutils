#ifndef COMMON_H
#define COMMON_H
//============================================================================
// Name        : Common.h
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include <stdio.h>  // printf
#include <iostream> // std::cout

#include <memory>

#include <string>

#include <vector>
#include <map>

#define STRING_VECTOR vector<string>
#define STRING_VECTOR_PTR unique_ptr<STRING_VECTOR>

#define EXTS_MAP map<string /*key*/, bool /*value*/>
#define EXTS_MAP_PTR unique_ptr<EXTS_MAP>

#endif