void dispPercentage(int number, int total)
{
    std::cout << "\r"; //return to the beginning of the line
    std::cout << ((100*number)/total) << "%\t" << "(" << number << "/" << total << ")";
    std::cout.fill(' ');
    return;
}

// Check if the given file is a directory
bool isDir(const char* path)
{
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
}

// Check if a file exists or not, avoiding all the process of creating it
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

                if (isDir(tmpStrPath.c_str()))
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
int putHexValue(std::wofstream* of, wchar_t c)
{
    std::vector<std::tuple<int, int>> corespnd;
    for(int i = 0; i <= 255; i++)
        corespnd.push_back(std::tuple<int, int>(i, i));
	
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
	wchar_t utf82ndHalf[64] = {
		0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 
		0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f, 
		0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
		0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7, 0xb8, 0xb9, 0xba, 0xbb,	0xbc, 0xbd, 0xbe, 0xbf
	};

    //all the control character (range [0xc280 - 0x2c9f])
    std::map<int, std::vector<int>> unassigned;
        unassigned[0xc280] = {0xe2, 0x82, 0xac};    //PAD
        unassigned[0xc281] = {0xc2, 0xa0};          //HOP
        unassigned[0xc282] = {0xe2, 0x80, 0x9a};    //BPH
        unassigned[0xc283] = {0xc6, 0x92};          //NBH
        unassigned[0xc284] = {0xe2, 0x80, 0x9e};    //IND
        unassigned[0xc285] = {0xe2, 0x80, 0xa6};    //NEL
        unassigned[0xc286] = {0xe2, 0x80, 0xa0};    //SSA
        unassigned[0xc287] = {0xe2, 0x80, 0xa1};    //ESA
        unassigned[0xc288] = {0xcb, 0x86};          //HTS
        unassigned[0xc289] = {0xe2, 0x80, 0xb0};    //HTJ
        unassigned[0xc28a] = {0xc5, 0xa0};          //LTS
        unassigned[0xc28b] = {0xe2, 0x80, 0xb9};    //PLD
        unassigned[0xc28c] = {0xc5, 0x92};          //PLU
        unassigned[0xc28d] = {0xc2, 0xa0};          //RI
        unassigned[0xc28e] = {0xc5, 0xbd};          //SS2
        unassigned[0xc28f] = {0xc2, 0xa0};          //SS3
        unassigned[0xc290] = {0xc2, 0xa0};          //DCS
        unassigned[0xc291] = {0xe2, 0x80, 0x98};    //PU1
        unassigned[0xc292] = {0xe2, 0x80, 0x99};    //PU2
        unassigned[0xc293] = {0xe2, 0x80, 0x9c};    //STS
        unassigned[0xc294] = {0xe2, 0x80, 0x9d};    //CCH
        unassigned[0xc295] = {0xe2, 0x80, 0xa2};    //MW
        unassigned[0xc296] = {0xe2, 0x80, 0x93};    //SPA
        unassigned[0xc297] = {0xe2, 0x80, 0x94};    //EPA
        unassigned[0xc298] = {0xcb, 0x9c};          //SOS
        unassigned[0xc299] = {0xe2, 0x84, 0xa2};    //SGCI
        unassigned[0xc29a] = {0xc5, 0xa1};          //SCI
        unassigned[0xc29b] = {0xe2, 0x80, 0xba};    //CSI
        unassigned[0xc29c] = {0xc5, 0x93};          //ST
        unassigned[0xc29d] = {0xc2, 0xa0};          //OSC
        unassigned[0xc29e] = {0xc5, 0xbe};          //PM
        unassigned[0xc29f] = {0xc5, 0xb8};          //APC 

    int idx = getKeyValue(corespnd, (int)c);

	if((int)c <= 0x7f) //in range of ASCII
    {
		*of << (wchar_t)utf81stHalf[getKeyValue(corespnd, (int)c)];
    }
	else
	{
        int charToInsert, firstByte = (int)NAN, secondByte = (int)NAN, thirdByte = (int)NAN;

		if((int)c < 0xc0) //in range of the first half
			secondByte = 0xc2;
		else
			secondByte = 0xc3;

        firstByte = (int)utf82ndHalf[getKeyValue(corespnd, ((int)c - 0x80)%0x40)];

        if(inArrayKey(unassigned, ((secondByte<<8) | firstByte))) //[0xc280 - 0xc29f] control char c'est chiant wallou
        {
            int newFirst, newSecond, offset = 0;
            if(unassigned.at((secondByte<<8) | firstByte).size() > 2) //handle the cases of [0xcff < char < 0xe20000]
                thirdByte   = unassigned.at((secondByte<<8) | firstByte)[0];
            else 
                offset = 1;
            newFirst    = unassigned.at((secondByte<<8) | firstByte)[2 - offset];
            newSecond   = unassigned.at((secondByte<<8) | firstByte)[1 - offset];
            firstByte   = newFirst;
            secondByte  = newSecond;
        }

        if(!(thirdByte == (int)NAN))
            *of << (wchar_t)thirdByte;
        *of << (wchar_t)secondByte << (wchar_t)firstByte;
    }
    return (int)c;
}

//Copy the content of the origin file in the new one using putHexValue()
void copyFile_(std::string inDir, std::string outDir)
{
    std::wifstream src(inDir);

    std::wofstream dst;
    dst.open(outDir);
    dst.imbue(std::locale(std::locale(), new std::codecvt_utf8<char32_t, 0x10ffff, std::consume_header>));
    
	wchar_t c;
    int counter = 0;

    while(src.get(c))
    {
        counter++;
        putHexValue(&dst, c);
    }
    src.close();
    dst.close();
	
    if(counter == 0)
        remove(outDir.c_str());

    return;
}

//copy all files from inDir remaining in outDir
void copyLeftovers(std::string inDir, std::string outDir)
{
    if(fileExists(outDir))
        return;
    
    std::ifstream  src(inDir, std::ios::binary);
    std::ofstream  dst(outDir,   std::ios::binary);

    dst << src.rdbuf();

    return;
}

//Checking if there is any UTF8 characters in the file
bool isAlreadyUTF8(std::string path)
{
	std::wifstream file; //Detect without openign
    file.open(path);

	wchar_t c;
    bool ans = false;

    wchar_t utf8fingerprint[3] = {0xc2, 0xc3}; //Accentued characters' first byte or badly encoded char
	
	while(file.get(c))
    {
        for(int i = 0; i < (sizeof(utf8fingerprint)/sizeof(utf8fingerprint[0])); i++)
        {
            if(utf8fingerprint[i] == c)
            {
                ans = true;
                goto end;
            }
        }
    }
    end:
    file.close();
	return ans;
}

int findLastIndex(std::string& str, char x) 
{ 
    for (int i = str.length() - 1; i >= 0; i--) 
        if (str[i] == x) 
            return i; 
    return -1; 
}

bool inArray(std::vector<std::string> haystack, std::string needle)
{
    for(int i = 0; i < haystack.size(); i++)
        if(haystack[i] == needle)
            return true;
    return false;
}

bool inArrayKey(std::map<int, std::vector<int>> haystack, int needle)
{
    std::map<int, std::vector<int>>::iterator it = haystack.find(needle);
    if(it != haystack.end())
        return true;
    return false;
}

//Basically the main function, it will browse a folder and its sub folders
void copyDir_(const char* inputDir, std::string outDir, int* counter, int* nuof)
{
    DIR *pDIR;
    struct dirent *entry;
    std::string tmpStr, tmpStrPath, outStrPath, inputDir_str = inputDir;

    std::vector<std::string> extensions = {"php", "html"};

    if (isDir(inputDir) == false)
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

                if(isDir(tmpStrPath.c_str()))
                {
                    //Create Folder in the destination path
                    outStrPath = outDir;
                    outStrPath.append("\\" + tmpStr);
                    mkdir(outStrPath.c_str());
					
                    //recursive creation of files inside new folder
                    copyDir_(tmpStrPath.c_str(), outStrPath, counter, nuof);
                }
                else
                {
                    *counter = *counter + 1;

                    outStrPath = outDir;
                    outStrPath.append("\\" + tmpStr);

                    //-- here
                    bool extMatch = inArray(extensions, tmpStrPath.substr(findLastIndex(tmpStrPath, '.')+1));
                    bool isUTF8 = isAlreadyUTF8(tmpStrPath.c_str());

                    if(extMatch)
                    {
                        if(!isUTF8) //not already UTF8 encoded
                            copyFile_(tmpStrPath.c_str(), outStrPath.c_str());
                        else
                            copyLeftovers(tmpStrPath.c_str(), outStrPath.c_str());
                    }
                    else
                        copyLeftovers(tmpStrPath.c_str(), outStrPath.c_str());
                }
                dispPercentage(*counter, *nuof);
            }
        }
        closedir(pDIR);
    }
    return;
}