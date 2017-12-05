/*Note to self:
 * Document and Comment devanagari.h,preeti.h and tools.h
 *Fix the र in the main program
 */
 /**
   *Dependency Chart(For compiling this program)
   *All the dependent files need to be on the same directory as this file
   *unicode2preeti.h->unicode2.h,preeti.h,unicode2.h
   *unicode2.h->iostream and string(both belong to c++ library and hence are not included in the folder)
   *preeti.h->devnagri.h
   *converting_function.h->tools.h,devnagri.h
   */
/**
  *Programmed by: Prashant Subedi
  *For: The software-Nepali Conversion Tool
  *Targeted System:Windows.I love linux, but I don't like the devanagari support in it.
  *The conversion is based on The Unicode Standard Version 7.0
  */
#ifndef UNICODE2PREETI_H
#define UNICODE2PREETI_H
#include"unicode2.h"
/*
 *Contains the class Unicode which I made as C++ has no native support for unicode data
 */
#include"converting_functions.h"
/*
 *This header file contains the Devanagari convert_FixedPosition(Unicode &var,int i)
 */
#include "preeti.h"
/*This is to adjust the converted the data, making small changes.
 *I feel that since preeti also has few 2 bytes characters, it is appropriate for it to have a data type of its own which is able to distinguish caharacters
 */
Devanagari convert_FixedPosition(Unicode &var,int i);
/*
 *The above function carries out the conversion...but the conversion is not complete
 */
std::vector<Pchar> unicode_Converter(std::string raw_data)
{
	Unicode var;
	var=raw_data;
	bool result;
	int i,j=0;
	Devanagari converted;
	Database db;
	/*
	 *I need to  find a way to define this object only once.It has been defined in other functions too and it occupies a lot of space
	 */
	Preeti output(var.length_Unicode());
	/*
	 *The class preeti has a parmeterized constructor which alocates the memory. The length_Unicode() of class Unicode returns the number of unicode characters in
	  in the object. I'm using this number to specify the memory needed to allocated for the output data because-
	 *It is approximates the number of characters that will be outputted.
	 *It is never less than the number of characters that are to be outputted
	 *It does waste a few bytes of memory,but the exact amount of memory required is know only at the end of program...hence it is pointless.
	 */
	for(i=0;i<var.length_Unicode();i++)
	/*
	 *Scan each and every charcter
	 */
	{
		if(var.size_UnicodeChar(i)==3)
		/*
		 *Since the size of Devanageri character is always equal to 3 bytes.
		 */
		{

			result=devanagari_Test((var+i));
			/*
				*(var+i): + is an overloaded operator of class Unicode.It returns the 'i'th unicode character as string.The indexing starts form 0.
				*devanagari_Test() is a function of type bool defined in file tools.h and returns true if the string sent is devanagari
			*/
			if(result==false)
			{
                /*
                 *For the 3 byte characters which are not devanagari, conversion is not required.
                 *But ZWJ and ZWNJ have to be removed..They will create a problem later on,in second scanning in the Preeti class
                 */
				if((var+i)==ZWJ||(var+i)==ZWNJ)
				{
					/*
					 *This step is just necessary to eliminate the two non-printable characters from the output.
					 *This does nothing else
					 */

				}
				else//	if((var+i)==ZWJ||(var+i)==ZWNJ)
				{
					output+=(var+i);

					/*
					*Class Preeti has overloaded operator '+'  which treates data differently depending on whether the parameter is of type devanagari or string.
					*Here the parameter is string
					*/
			 	}
			}
			else
			{
				converted=convert_FixedPosition(var,i);
				i--;
				/*
				 *The function Devanagari convert_FixedPosition(Unicode,int) sometimes reads and coverts more than one unicode character at a time, which is
				  necessary because unicode has many complex characters. Hence incresing the counter by 1 may not be sufficient
				 */
				i+=converted.size_of_dev();
                /*
				 *The size_of_dev() method gives the number of unicode characters which were used to create the devanagari character.
				 */
				output+=converted;
				/*
				 *Here the parameter is Devanagari.
				 */
			}
		}
        else
        {
            /*
             *Some ascii charcters also need to be changed. The are converted here.
             */
            if((var+i)=="?")
            {
				output+=db.return_OtherPreeti(0).return_Dev();
				/*
				 *Here the parameter is string not Devanagari
				 */
            }
            else
			{
				output+=(var+i);
				/*
				 *Here the parameter is string.
				 */
			}
        }
    }
	return output.return_All();

}
std::string unicode_Converter_Direct(std::string raw_data)
{
	std::vector<Pchar> output=unicode_Converter(raw_data);
	std::string return_data;
	for(int i=0;i<output.size();i++)
	{
		return_data+=output[i].preeti_char;
	}
	return return_data;

}
#endif //UNICODE2PREETI_H
