/****************************************************************
*	This program is intended to convert mixed-encoded files to UTF-8
*	2 args can be provided :
*	    1 - The source path
*	    2 - The destination path
*	It is poorly coded and can be upgraded, but if it works, well...
*****************************************************************/

#include "functions.h"

int main(int argc, char *argv[])
{
    std::string srcDir, destDir;

    //define default path values if a wrong args number is given
    if(argc != 3)
    {
        srcDir  = "C:\\raw";
        destDir = "C:\\sanitized";
    }
    else
    {
        srcDir  = (std::string)argv[1];
        destDir = (std::string)argv[2];
    }
	
    std::cout << "Calculating..." << std::endl;
    int counter = 0;
    NuOF(srcDir, &counter);
    int nuof = counter;
    std::cout << nuof << " files to process." << std::endl << std::endl;

    std::cout << "Creation of empty UTF-8 files" << std::endl;
    counter = 0; //reusing it, global warming stuff..
    copyDir_(srcDir.c_str(), destDir, &counter, &nuof, 0);

    std::cout << std::endl << "Attempting to fill new UTF-8 files with content" << std::endl;
    counter = 0; //again
    copyDir_(srcDir.c_str(), destDir, &counter, &nuof, 1);
	
	std::cout << std::endl << "Removing BOM from copied files" << std::endl;
    counter = 0; //and again
	copyDir_(srcDir.c_str(), destDir, &counter, &nuof, 2);

    std::cout << "\nDone." << std::endl;

    return 0;
}

