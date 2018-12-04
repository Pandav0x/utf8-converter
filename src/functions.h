#ifndef FUNCTIONS_H
#define FUNCTIONS_H

	//some are used, some not
	#include <iostream>
	#include <dirent.h>
	#include <string.h>
	#include <sys/stat.h>
	#include <windows.h>
	#include <iomanip>
	#include <codecvt>
	#include <fstream>
	#include <locale>
	#include <vector>
	#include <cstdint>

	bool is_dir(const char* path); //check if a given path is a directory or a file
	void copyDir_(const char *inputDir, std::string outDir, int *counter, int *nuof, int copying); //Copy all files in a directory
	void createFile_(std::string inDir, std::string outDir); //create the files, but it does not copy the content
	bool fileExists(std::string path); //check if a file exists or not
	void copyFile_(std::string inDir, std::string outDir); //copy a given file to a given directory
	void NuOF(std::string dir, int *counter); //get the total number of files in a folder and its sub folders
	bool isAlreadyUTF8(std::string path); //check if a file contains UTF8 characters meaning that the conversion will fail
	void dispPercentage(int number, int total); //display the percentage of work done
	int getKeyValue(std::vector<std::tuple<int, int>>haystack, int wantedKey); //get value from a given vector of tuples for a given key
	int putHexValue(std::wofstream* of, char c); //return the Hexadecimal value of a given character, assuming it is part of the UTF-8 table
	void removeBOM(std::string outDir); //remove the BOM characters a t the begining of the file

	#include "functions.cpp"
	
#endif