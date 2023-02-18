#include <catch2/catch_test_macros.hpp>

#include "../main/FileUtils.h"

#include <stdio.h>  // printf
#include <iostream> // std::cout

#include <experimental/filesystem>

using namespace std;

namespace fs = std::experimental::filesystem;

TEST_CASE( "FileUtils.getNoPathFileNameWithExt().FILE", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/venus.jpg");
    string fn = getNoPathFileNameWithExt(FILENAME);
    REQUIRE( strcmp("venus.jpg", fn.c_str()) == 0 );
}

TEST_CASE( "FileUtils.getNoPathFileNameWithExt().DIR", "[FileUtils]" ) {
    string DIRNAME("../src/test/resources/venus.dir");
    string fn = getNoPathFileNameWithExt(DIRNAME);
    REQUIRE( strcmp("", fn.c_str()) == 0 );
}

TEST_CASE( "FileUtils.getFileNameEncoding().FILE.FILEMODIFIEDDATE", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/DSC_1234.JPG");
    FN_ENCODING fnenc = getFileNameEncoding(FILENAME);
    REQUIRE( FN_ENCODING::FILE_MODIFIED_DATE == fnenc );
}

TEST_CASE( "FileUtils.getFileNameEncoding().FILE.ENCODEDNAME", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/IMG_20150111_105448.JPG");
    FN_ENCODING fnenc = getFileNameEncoding(FILENAME);
    REQUIRE( FN_ENCODING::ENCODED_NAME == fnenc );
}

TEST_CASE( "FileUtils.getFileNameEncoding().FILE.ENCODEDNAME_1", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/IMG_20150111_105448_1.JPG");
    FN_ENCODING fnenc = getFileNameEncoding(FILENAME);
    REQUIRE( FN_ENCODING::ENCODED_NAME == fnenc );
}

TEST_CASE( "FileUtils.getFileNameEncoding().FILE.ENCODEDNAMEb", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/FB_IMG_20150111_105448.JPG");
    FN_ENCODING fnenc = getFileNameEncoding(FILENAME);
    REQUIRE( FN_ENCODING::ENCODED_NAME == fnenc );
}

TEST_CASE( "FileUtils.getFileNameEncoding().FILE.ENCODEDNAMEb_1", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/FB_IMG_20150111_105448_1.JPG");
    FN_ENCODING fnenc = getFileNameEncoding(FILENAME);
    REQUIRE( FN_ENCODING::ENCODED_NAME == fnenc );
}

TEST_CASE( "FileUtils.getFileNameEncoding().FILE.ENCODEDNAME2", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/20220313_132024.jpg");
    FN_ENCODING fnenc = getFileNameEncoding(FILENAME);
    REQUIRE( FN_ENCODING::ENCODE_NAME2 == fnenc );
}

TEST_CASE( "FileUtils.getFileNameEncoding().FILE.UNKNOWN", "[FileUtils]" ) {
    string DIRNAME("../src/test/resources/venus.jpg");
    FN_ENCODING fnenc = getFileNameEncoding(DIRNAME);
    REQUIRE( FN_ENCODING::UNKNOWN == fnenc );
}

TEST_CASE( "FileUtils.getFileNameEncoding().DIR.UNKNOWN", "[FileUtils]" ) {
    string DIRNAME("../src/test/resources/venus.dir");
    FN_ENCODING fnenc = getFileNameEncoding(DIRNAME);
    REQUIRE( FN_ENCODING::UNKNOWN == fnenc );
}

TEST_CASE( "FileUtils.processEncodedName1()", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/IMG_20150111_105448.JPG");
    string OUTPUTDIR("out/");

    fs::remove_all(OUTPUTDIR);

    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    int ret = processEncodedName1(FILENAME, OUTPUTDIR);
    
    cout.rdbuf(rdbufCout);

    REQUIRE( fs::is_directory(OUTPUTDIR) == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015") == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015"+DIR_CHAR+"2015.0111") == true );
    REQUIRE( fs::is_regular_file(OUTPUTDIR+"2015/2015.0111/IMG_20150111_105448.JPG") == true );
}

TEST_CASE( "FileUtils.processEncodedName1()_1", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/IMG_20150111_105448_1.JPG");
    string OUTPUTDIR("out/");

    fs::remove_all(OUTPUTDIR);

    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    int ret = processEncodedName1(FILENAME, OUTPUTDIR);
    
    cout.rdbuf(rdbufCout);

    REQUIRE( fs::is_directory(OUTPUTDIR) == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015") == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015"+DIR_CHAR+"2015.0111") == true );
    REQUIRE( fs::is_regular_file(OUTPUTDIR+"2015/2015.0111/IMG_20150111_105448_1.JPG") == true );
}

TEST_CASE( "FileUtils.processEncodedName1().overwrite", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/IMG_20150111_105448.JPG");
    string OUTPUTDIR("out/");

    fs::remove_all(OUTPUTDIR);

    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    int ret = processEncodedName1(FILENAME, OUTPUTDIR);
    
    cout.rdbuf(rdbufCout);
    
    REQUIRE( fs::is_directory(OUTPUTDIR) == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015") == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015"+DIR_CHAR+"2015.0111") == true );
    REQUIRE( fs::is_regular_file(OUTPUTDIR+"2015/2015.0111/IMG_20150111_105448.JPG") == true );

    ret = processEncodedName1(FILENAME, OUTPUTDIR);
    REQUIRE( fs::is_directory(OUTPUTDIR) == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015") == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015"+DIR_CHAR+"2015.0111") == true );
    REQUIRE( fs::is_regular_file(OUTPUTDIR+"2015/2015.0111/IMG_20150111_105448.JPG") == true );

}

TEST_CASE( "FileUtils.processEncodedName1().FB", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/FB_IMG_20150111_105448.JPG");
    string OUTPUTDIR("out/");

    fs::remove_all(OUTPUTDIR);

    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    int ret = processEncodedName1(FILENAME, OUTPUTDIR);
    
    cout.rdbuf(rdbufCout);
    
    REQUIRE( fs::is_directory(OUTPUTDIR) == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015") == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2015"+DIR_CHAR+"2015.0111") == true );
    REQUIRE( fs::is_regular_file(OUTPUTDIR+"2015/2015.0111/FB_IMG_20150111_105448.JPG") == true );
}

TEST_CASE( "FileUtils.processEncodedName2()", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/20220313_132024.jpg");
    string OUTPUTDIR("out/");

    fs::remove_all(OUTPUTDIR);

    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    int ret = processEncodedName2(FILENAME, OUTPUTDIR);
    
    cout.rdbuf(rdbufCout);

    REQUIRE( fs::is_directory(OUTPUTDIR) == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2022") == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2022"+DIR_CHAR+"2022.0313") == true );
    REQUIRE( fs::is_regular_file(OUTPUTDIR+"2022/2022.0313/20220313_132024.jpg") == true );
}

TEST_CASE( "FileUtils.processFileModifiedDate1()", "[FileUtils]" ) {
    string FILENAME("../src/test/resources/DSC_1234.JPG");
    string OUTPUTDIR("out/");

    fs::remove_all(OUTPUTDIR);

    streambuf* rdbufCout= cout.rdbuf();
    ostringstream ossCout;
    cout.rdbuf(ossCout.rdbuf());

    int ret = processFileModifiedDate1(FILENAME, OUTPUTDIR);
    
    cout.rdbuf(rdbufCout);
    
    REQUIRE( fs::is_directory(OUTPUTDIR) == true );
    REQUIRE( fs::is_directory(OUTPUTDIR+"2022") == true );
    //REQUIRE( fs::is_directory(OUTPUTDIR+"2022"+DIR_CHAR+"2022.1108") == true );
    //REQUIRE( fs::is_regular_file(OUTPUTDIR+"2022/2022.1108/DSC_1234.JPG") == true );
}

