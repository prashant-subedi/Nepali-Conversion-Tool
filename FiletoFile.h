/**
  *Author:Prashant Subedi
  *Description:
  	*File To File Conversion Function for Nepali Conversion Tool..Works for Unicode to Preeti,Not vice versa
  	*Hurry Up Ankita!!!!! We need the conversion engine fast!:p
  */
#ifndef FILETOFILE_H
#define FILETOFILE_H
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include "unicode2preeti.h"
/*Prashant's Note:I only know file handling in C...I want to learn native C++ file handling but C is working for me*/
void convert_File_Unicode(std::string file_name)
{
	FILE *raw_file,*converted_file;
	char *nullterminated_filename;
    nullterminated_filename=new char[file_name.length()+1];
    int i;
    for(i=0;i<file_name.length();i++)
    {
		nullterminated_filename[i]=file_name[i];

	}
    nullterminated_filename[i]='\0';
	raw_file=fopen("raw_file.nct","w");
	fprintf(raw_file,"%s %s","Name:",nullterminated_filename);
	fclose(raw_file);
	system("python3 unicode_preeti.py");
	/*
	 *The file has been edited by the above written script
	 */
	raw_file=fopen("raw_file.nct","r");
	char c=fgetc(raw_file);
	std::string whole_string;
	while(c!=EOF)
	{
		whole_string+=c;
		c=fgetc(raw_file);
	}
	std::vector<Pchar> converted=unicode_Converter(whole_string);
	fclose(raw_file);
    converted_file=fopen("converted.nct","w");
	fprintf(converted_file,"%s %s %s","Name:",nullterminated_filename,"\n");
	fprintf(converted_file,"%s","<#!new_run#!>");
	bool nepali=false;
	for(int i=0;i<converted.size();i++)
	{
		Pchar temp=converted[i];
		if(temp.type==NEPALI)
			nepali=true;
		for(int j=0;j<temp.preeti_char.length();j++)
		{
			if(temp.preeti_char[0]=='\0')
			{

				if(nepali==true)
					fputc('1',converted_file);
				else
					fputc('0',converted_file);
				nepali=false;
				fprintf(converted_file,"%s","<#!new_run#!>");
				break;
			}
            fputc(temp.preeti_char[j],converted_file);
		}
	}
	fprintf(converted_file,"%s","\n<#!new_run#!>");
	fclose(converted_file);
	delete[] nullterminated_filename;
	system("python3 make_preeti_docx.py" );

}
#endif //FILETOFILE_H
