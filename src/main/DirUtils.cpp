//============================================================================
// Name        : DirUtils.cpp
// Author      : kjn
// Copyright   : Copyright 2022 neurohr.us.com
//============================================================================

#include "DirUtils.h"

STRING_VECTOR _dir_recursive(const fs::path& path, const EXTS_MAP& extsMap) {
    STRING_VECTOR fileNames;
    int nn = 0;
    int n = 0;
    for(const auto& p: fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
        if(!fs::is_directory(p)) {
            string origfileName = p.path().string();
            string fileName(origfileName);
            size_t dotPos = fileName.rfind(".");
            // HANDLE ALL name CASES by transforming to lower (ONLY EXTENSION)!!!
            transform(fileName.begin()+dotPos, fileName.end(), fileName.begin()+dotPos, ::tolower);
            for(auto it : extsMap) {
                string ext = it.first;
                bool isActive = it.second;
                if(isActive) {
                    bool isExt = fileName.rfind(ext) != std::string::npos;
                    if(isExt) {
                        fileNames.push_back(origfileName);
                        ++nn;
                        ++n;
                        if(n == SEARCH_LINE_MAX) {
                            n = 0;
                            cout << ".";
                        }
                    }
                }
            } // for
        }
    }
    if(nn<SEARCH_LINE_MAX) {
        cout << ".";
    }
    cout << endl;
    return fileNames;
} // _dir_recursive()

STRING_VECTOR _dir(const fs::path& path, const EXTS_MAP& extsMap) {
    STRING_VECTOR fileNames;
    int nn = 0;
    int n = 0;
    for(const auto& p: fs::directory_iterator(path)) {
        if(!fs::is_directory(p)) {
            string origfileName = p.path().string();
            string fileName(origfileName);
            size_t dotPos = fileName.rfind(".");
            // HANDLE ALL name CASES by transforming to lower (ONLY EXTENSION)!!!
            transform(fileName.begin()+dotPos, fileName.end(), fileName.begin()+dotPos, ::tolower);
            for(auto it : extsMap) {
                string ext = it.first;
                bool isActive = it.second;
                if(isActive) {
                    bool isExt = fileName.rfind(ext) != std::string::npos;
                    if(isExt) {
                        fileNames.push_back(origfileName);
                        ++nn;
                        ++n;
                        if(n == SEARCH_LINE_MAX) {
                            n = 0;
                            cout << ".";
                        }
                    }
                }
            } // for
        }
    }
    if(nn<SEARCH_LINE_MAX) {
        cout << ".";
    }
    cout << endl;
    return fileNames;
} // _dir()
