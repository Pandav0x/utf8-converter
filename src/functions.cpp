/********************************
*	
*	
*	
********************************/

// Display a beautiful percentage progression rewriting on the same line
// int number -> current number of files done
// int total -> total number of files to do
// return void
void dispPercentage(int number, int total)
{
    std::cout << "\r"; //return to the beginning of the line
    std::cout << ((100*number)/total) << "%\t" << "(" << number << "/" << total << ")";
    std::cout.fill(' ');
    return;
}

// Check if the given file is a directory
// const char* path -> (almost a string) path to the targeted file
// return bool -> true if is a dir, false otherwise
bool is_dir(const char* path)
{
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

// Check if a file exists or not, avoiding all the process of creating it
// std::string path -> path to check
// return if it can create a stat() structure, meaning if there is a file or not
bool fileExists(std::string path)
{
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
}

int getKeyValue(std::vector<std::tuple<int, int>>haystack, int wantedKey)
{
    std::tuple<int, int> res;
    for(int i = 0; i < haystack.size(); i++)
    {
        if(wantedKey == (int)std::get<0>(haystack[i]))
        {
            return (int)std::get<1>(haystack[i]);
        }
    }
    return -2147483648; //maximum negative value for int
}

// Count the number of files in a given directory
// std::string path to the dir to count from
// int* counter -> pointer to the real counter, we will change it directly in here
// return void
void NuOF(std::string dir, int *counter)
{
    DIR *pDIR;
    struct dirent *entry;
    std::string tmpStr, tmpStrPath, inputDir_str = dir.c_str();

    if(pDIR = opendir(inputDir_str.c_str()))
    {
        while(entry = readdir(pDIR)) //get folders and files names
        {
            tmpStr = entry->d_name;
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                tmpStrPath = inputDir_str;
                tmpStrPath.append("\\");
                tmpStrPath.append(tmpStr);

                if (is_dir(tmpStrPath.c_str()))
                    NuOF(tmpStrPath.c_str(), counter); //recursive if it is a directory
                else
                    *counter = *counter+1; //increment otherwise
            }
        }
        closedir(pDIR);
    }
    return;
}

// Put te corresponding hex value if c in the opened file
// std::wofstream* of -> file to put char in
// char c -> the character to convert in Hex and put in the of file
// return the integer value of c
int putHexValue(std::wofstream* of, char c)
{
    //creating a correspondence dictionary to get the index for the utf8 table defined bellow
    std::vector<std::tuple<int, int>> corespnd;
    for(int i = 0; i <= 127; i++)
        corespnd.push_back(std::tuple<int, int>(i, i));
    for(int i = -128, j = 128; i < 0; i++, j++)
        corespnd.push_back(std::tuple<int, int>(i, j%64));
	
	//first half [0, 127]
	wchar_t utf81stHalf[128] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
		0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
		0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
		0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f,
		0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
		0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
		0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f		
	};

	//second half (is repeated twice, so i didn't bother to write it a second time)
	wchar_t utf82ndHalf[65] = {
		0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 
		0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 
		0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
		0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb,	0xbc, 0xbd, 0xbe, 0xbf
	};

	if((int)c > 0) //in range of ASCII
		*of << (char)utf81stHalf[getKeyValue(corespnd, (int)c)];
	else //Out of range of ANCII, so in Unicode
	{
		if(-(int)c > 65) //in range of the first half
			*of << (char)0xc2;
		else
			*of << (char)0xc3;
		*of << (char)utf82ndHalf[getKeyValue(corespnd, (int)c)];
	}	
    return (int)c;
}

// Create an empty file and put only BOM in it
// std::string inDir -> path to the origin file
// std::string outDir -> path to the new file
// return void
void createFile_(std::string inDir, std::string outDir)
{
    if(fileExists(outDir))
        return;
    std::wifstream src(inDir);
    src.imbue(std::locale(std::locale(), new std::codecvt_utf8<char32_t, 0x10ffff, std::consume_header>));

    std::wofstream dst;
    dst.imbue(std::locale(std::locale(), new std::codecvt_utf8<char32_t, 0x10ffff, std::generate_header>));
    dst.open(outDir);

	//BOM to explicitly specifies that this file is UTF-8 encoded
    dst << (char)0xEF;
    dst << (char)0xBB;
    dst << (char)0xBF;

    dst.close();
    src.close();
    return;
}

// Copy the content of the origin file in the new one using putHexValue()
// std::string inDir -> path to the origin file
// std::string outDir -> path to the new file
// return void
void copyFile_(std::string inDir, std::string outDir)
{
    std::wifstream src(inDir);
    src.imbue(std::locale(std::locale(), new std::codecvt_utf8<char32_t, 0x10ffff, std::consume_header>));

    std::wofstream dst;
    dst.open(outDir);
    dst.imbue(std::locale(std::locale(), new std::codecvt_utf8<char32_t, 0x10ffff, std::consume_header>));
	
    //BOM again, to overwrite any encoding if there is one
    dst << (char)0xEF;
    dst << (char)0xBB;
    dst << (char)0xBF;
    
	wchar_t c;

    while(src.get(c))
    {
        putHexValue(&dst, c);
    }
    src.close();
    dst.close();
	
    return;
}

// Remove the first 3 characters of the file (the BOM)
// std::string outDir -> path to the new file
// return void
void removeBOM(std::string outDir)
{
	std::wifstream dst;
	dst.open(outDir);
	int length = dst.tellg();
	dst.seekg(3, dst.beg);
	
	wchar_t c;
	std::wstring content = L"";

    while(dst.get(c))
    {
		content += c;
    }
    dst.close();
	std::wofstream dst2;
	dst2.open(outDir);
	dst2 << content;
	dst2.close();
	
	return;
}

// Checking if there is any UTF8 characters in the file
// std::string path -> path to the file to scan
// return true if an UTF-8 file has been found, false otherwise
bool isAlreadyUTF8(std::string path)
{
	std::wifstream file;
    file.open(path);

	wchar_t c;
	
	while(file.get(c))
    {
        if((int)c == (int)0xc2 || (int)c == (int)0xc3)
		{
			file.close();
			return true;
		}
    }
    file.close();	
	return false;
}

// Basically the main function, it will browse a folder and its sub folder and do something depending on the flag
// const char* inputDir -> path to the origin file (const char* to ease the use of certain functions, but it is really just a string)
// std::string outDir -> path to the new file
// int* counter -> current number of file browsed (used for percentage)
// int* nuof -> number of files to browse (used for percentage)
// int copying -> the flag, 0- Create file / 1- Copy File / 2- Remove BOM 
// return void
void copyDir_(const char* inputDir, std::string outDir, int* counter, int* nuof, int copying)
{
    DIR *pDIR;
    struct dirent *entry;
    std::string tmpStr, tmpStrPath, outStrPath, inputDir_str = inputDir;

    if (is_dir(inputDir) == false)
    {
        std::cout << "This is not a folder " << std::endl;
        return;
    }

    if(pDIR = opendir(inputDir_str.c_str()))
    {
        while(entry = readdir(pDIR))
        {
            tmpStr = entry->d_name;
            if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                tmpStrPath = inputDir_str;
                tmpStrPath.append("\\" + tmpStr);

                if (is_dir(tmpStrPath.c_str()))
                {
                    // Create Folder in the destination path
                    outStrPath = outDir;
                    outStrPath.append("\\" + tmpStr);
                    mkdir(outStrPath.c_str());
					
                    copyDir_(tmpStrPath.c_str(), outStrPath, counter, nuof, false); //recursive creation of files inside new folder
                }
                else
                {
                    *counter = *counter+1;
                    if(tmpStrPath.substr(tmpStrPath.length() - 4, 4) != ".php") //checking only for php files
						goto disp;
					if(isAlreadyUTF8(tmpStrPath))
						goto disp;
                    outStrPath = outDir;
					outStrPath.append("\\" + tmpStr);
					
                    switch(copying)
					{
						case 0:
							createFile_(tmpStrPath.c_str(), outStrPath.c_str());
							break;
						case 1:
							copyFile_(tmpStrPath.c_str(), outStrPath.c_str());
							break;
						case 2:
							removeBOM(outStrPath.c_str());
							break;
						default:
							break;
					}
                }
				disp:
                dispPercentage(*counter, *nuof);
            }
        }
        closedir(pDIR);
    }
    return;
}
