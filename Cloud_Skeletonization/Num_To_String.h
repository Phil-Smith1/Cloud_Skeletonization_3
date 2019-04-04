#pragma once

#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

string Num_To_String ( int num )
{
	stringstream ss;
	ss << num;
	string str = ss.str();
	return str;
}

string Num_To_String ( double num )
{
	stringstream ss;
	ss << num;
	string str = ss.str();
	return str;
}

string Num_To_String_2 ( int num )
{
    stringstream ss;
    ss << setfill( '0' ) << setw( 4 ) << num;
    string str = ss.str();
    return str;
}
