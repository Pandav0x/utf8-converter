#include "functions.hpp"
#include <windows.h>
#include <io.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    clock_t start = clock();
    std::string srcDir, destDir;

    //define default path values if a wrong args number is given
    if(argc != 3)
    {
        srcDir  = ".\\raw";
        destDir = ".\\sanitized";
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

    std::cout << "Processing..." << std::endl;
    counter = 0; //reusing it, global warming stuff..
    copyDir_(srcDir.c_str(), destDir, &counter, &nuof);

    clock_t end = clock();
    std::cout << "\nDone. (" << double(end - start)/CLOCKS_PER_SEC << "s)" << std::endl;

    return 0;
}

