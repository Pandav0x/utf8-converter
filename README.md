# Utf-8 converter

This program aim to convert files within a folder (and its sub folders) in UTF-8.
It can be from any encoding prior to the execution of the program. However, the only encoding tested are mainly ANSI and ISO 8859-1.
Further tests must be done.

## Use

You must compile the program prior to any use. I used Mingw-w64 as compiler as it have some uniqe libraries that I used as includes.

## How does it work

Let Raw be the targeted path which files will be converted from, and Sanitized the folder where the UTF-8 files will be stored afterward.
The program will recreate the files tree in Raw to Sanitized - provided that those files are not already UTF- 8 encoded, only filled with the UTF-8 BOM : `ï»¿` (hex values : `EF BB BF`).
Then it will rewrite all the files character per character. If a character is outside the ANSI table, it will add `c2` or `c3` before the other character (`c2 = Â` and `c3 = Ã`). 
The last step is to remove the 3 BOM character at the begining (which explain why it put the files already UTF-8 encoded aside).