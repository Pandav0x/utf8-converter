# UTF-8 converter

This project aims to convert all the files in a folder with mixed encoding into UTF-8 encoding. As file encoding is uncertain and is more a "right guess" than anything, I can't say with certitude that your files will all be in UTF-8.

Also, if your non converted file does not contains any **UTF-8** character (meaning no `é`, `ñ`, `€`, or any other 'exotic char'), you may find it as an **ANSI** encoded file in the sanitized version.

I've setted up the program to only find **php** and **html** files, for the moment it is hard coded in the **function.cpp** file, but will be extracted in a **config.json** file in future commits.

There is some part of the code I'll not be able to explain as it is sometime a magic trick and

## Installation

I'm working on the import of all the libraries used in this project, and will commit then in the future so it can be compiled easily. For the moment, if you want to compile it, you will have to fix the dependencies yourself. 

    $git clone
    $cd utf8-converter
    $mkdir raw
    $mkdir sanitized
    $g++ src/main.cpp -o converter

You then have to move your files in the **raw** folder, then run the **converter** command. The converted files will be in the **sanitized** folder.

I recommend you to backup your files and not **Ctrl+X** them in the **raw** folder, as it might corrupt yout files. 

## TODO

A lot of work is still needed to refactorize the code and to make it more... C++. I'll try to split the code into classes and not only as a bunch of functions. 

- Import all needed DLLs
- Create the Makefile
- Extract file inclusion (php and html) in a **config.json** file
- Refactorize the code
- Create classes & stuff
- Try to reduce the complexity and the memory consumption

## Ressources

(This section is mainly for the controls characters)

1) http://www.fileformat.info/ and search for the character corresponding to the unicode code (U+XXXX)
Then take the character in the **Java code** block, and copy the right one (upper or lower case)
2) https://www.compart.com/en/ and search for the char in the clipboard.
You'll get the exact hex code of the given character.
