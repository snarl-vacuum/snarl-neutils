#include <catch2/catch_test_macros.hpp>

#include "../main/DirUtils.h"

#include <stdio.h>  // printf
#include <iostream> // std::cout

#include <string>
#include <map>

using namespace std;

TEST_CASE( "DirUtils._dir_recursive().FILE", "[FileUtils]" ) {
    string INPUTDIR("../src/test/resources/");
    EXTS_MAP extsMap;
    extsMap.insert(make_pair("jpg", true));
    STRING_VECTOR pathFileNames = _dir_recursive(INPUTDIR, extsMap);
    map<string, bool> FILEMAP;
    FILEMAP.insert(make_pair("../src/test/resources/venus.dir/recursive.jpg", true));
    FILEMAP.insert(make_pair("../src/test/resources/IMG_2964.JPG", true));
    FILEMAP.insert(make_pair("../src/test/resources/venus.jpg", true));
    FILEMAP.insert(make_pair("../src/test/resources/DSC_1234.JPG", true));
    FILEMAP.insert(make_pair("../src/test/resources/IMG_20150111_105448.JPG", true));
    FILEMAP.insert(make_pair("../src/test/resources/FB_IMG_20150111_105448.JPG", true));
    FILEMAP.insert(make_pair("../src/test/resources/20220313_132024.jpg", true));
    FILEMAP.insert(make_pair("../src/test/resources/IMG_20150111_105448_1.JPG", true));
    REQUIRE( FILEMAP.size() == pathFileNames.size() );
    REQUIRE( FILEMAP.count(pathFileNames[0]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[1]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[2]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[3]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[4]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[5]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[6]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[7]) == 1 );
}

TEST_CASE( "DirUtils._dir().FILE", "[FileUtils]" ) {
    string INPUTDIR("../src/test/resources/");
    EXTS_MAP extsMap;
    extsMap.insert(make_pair("jpg", true));
    STRING_VECTOR pathFileNames = _dir(INPUTDIR, extsMap);
    map<string, bool> FILEMAP;
    FILEMAP.insert(make_pair("../src/test/resources/IMG_2964.JPG", true));
    FILEMAP.insert(make_pair("../src/test/resources/venus.jpg", true));
    FILEMAP.insert(make_pair("../src/test/resources/DSC_1234.JPG", true));
    FILEMAP.insert(make_pair("../src/test/resources/IMG_20150111_105448.JPG", true));
    FILEMAP.insert(make_pair("../src/test/resources/FB_IMG_20150111_105448.JPG", true));
    FILEMAP.insert(make_pair("../src/test/resources/20220313_132024.jpg", true));
    FILEMAP.insert(make_pair("../src/test/resources/IMG_20150111_105448_1.JPG", true));
    REQUIRE( FILEMAP.size() == pathFileNames.size() );
    REQUIRE( FILEMAP.count(pathFileNames[0]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[1]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[2]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[3]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[4]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[5]) == 1 );
    REQUIRE( FILEMAP.count(pathFileNames[6]) == 1 );
}
