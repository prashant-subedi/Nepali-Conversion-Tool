#ifndef CONVERTING_FUNCTION_H
#define CONVERTING_FUNCTION_H
#include "tools.h"
/*
 *Varrious functions used in the coverting function are defined in this header file
 */
#include "devnagri.h"
/*
 *It contains the definition of structure Devanagari and also a database of Preeti characters defined in class Database
 */
bool devanagari_Test(std::string unicode_char);
std::string unicode_Generator(int);
void main_converter();
bool test_Complex(int* );
int find_ComplexUnicodeMatch(int*);
int find_UnicodeMatch(std::string);
/*
 *All the above functions are defined in tools.h
 */
Devanagari convert_FixedPosition(Unicode &var,int position)
{

    static Database db;
    /*
     *This function is called many times but the Database class object is same for each calling.
     *To avoid unnecessary creation and destruction of the large object , I am making it static.
     */
    int i=0,j=0;
	int numerical_value[6];
	/*
	 *I have found experimently that upto a maximum number of 6 characters need to be read for the purpose of conversion
	 */
	static int half_count=0;
	static int penultimate_halfcount=0;
	static int antepenultimate_halfcount=0;
	/*
	 *The ‌Devanagari UTF-8 has a complex system for handling half characters.
	 *Weather or not a character combination (व्यञ्न वर्ण)‌‌+्+  ...gives half character depends not only one the charcter after ् but also wheather or
	  how many half characters have occured already.
	 *half_count, a static variable is defined because not only do we need a way to store the information about half characters but
	  also a way to  pass that information to next calling of the function.
	  *The half_count value, 2 digits before the ि is required.
	  */
	bool half=false;
	/*
	 *The half variable is used to create a mechanism to increase or reset the half_count.
	 *Its default value is false and the character passed by the function is not half,it remains false.
	 *But if the character passed is half, the value is changed to ture.*/
	static bool reverse_status=false,future_reverse_status=false;
	reverse_status=future_reverse_status;

	 /*
	  *In some cases like रेफ, we need to change the position, forware.
	  *This is not posiible in the current calling
	  *Hence instead , we are going to reverse every character that comes after that one until a condiotion is met
	  */
	static int complex_count=0;
	static int penultimate_complexcount;
	bool complex_status=false;
	static bool penultimate_complex_status=false;
	Devanagari dev;
	for(i=0;i<=5;i++)
	{
		if((var+(position+i))==EOU)
		{
			/*
			 *This condition is to avoid the Index Out of Bound Error,which occurs when the value of integer after var+ is more than length of unicode string
			 *EOU(End Of Unicode) is a string that I have defined to be stored at the end of unicode to mark its end
			 */
			break;
		}
		numerical_value[i]=find_UnicodeMatch(var+(position+i));
		/*
		 *It will be much more easier to match on the basis of the relative postion of devanagari unicode characters than by treating them as strings
		 *The find_UnicodeMatch(string) returns a number corresponding to the character passed. It also returns some other values but they are not used in this case.
		 *If the character is ascii, it will return EXCEPTION macro defined in tools.h
		 *Similarly ZWJ_EXCEPTION and ZWNJ_EXCEPTION are returned for ZWJ and ZWNJ
		 */
	}
	/*
	 *From this point onwards,the actual conversion begins!
	 */
	if(numerical_value[0]>=(0x15)&&numerical_value[0]<=(0x39))
	/*
	 *The chart which I used(published by The Unicode Consortium) has Hexadecimal values hence this program also uses hexadecimal.
	 *Relative postion of क==0x15 and ह=0x39.
	 *All the half and complex characters always begin with व्यञ्न्जन वर्ण
	 *Hence if the character is anything else, it can be directly converted as done in else block.
	 */
		{
			if(numerical_value[1]==0x4d)
			/*
			*Relative position of ् = 0x4d
			*Both half or complex characters need second character to be ्
			*/
			{
			if(half_count<4)
			/*
			 *Half letters can only be chained upto 4 letters at a time.
			 *The 5th letter is a regular letter
			 *There is one way to create a longer chain, it will be adressed later
			 */
			{
				bool a=((numerical_value[2]>=(0x15))&&numerical_value[2]<=(0x39))||numerical_value[2]==ZWJ_EXCEPTION;
				/*
				 *Now for half, the 3rd character has to be ZWJ or a व्यञ्न्जन वर्ण
				 *For complex, the are specific cases.
				 *Hence, we have to first test for complex and then half
				 */
				if(a==true)
				{
					if((test_Complex(numerical_value)==true)&&(half_count<3))
					/*
					 *test_Complex returns true if the 1st 3 of numerical value, in the given order represent a complex character.
					 *1st part of Complex characters are eqivalent to half letters. Hence for the letter to be complex,there can only be upto 3 half letters before it.
					 */
					{
						complex_count++;
						complex_status=true;
						int complex_value=find_ComplexUnicodeMatch(numerical_value);
						/*
						 *find_ComplexUnicodeMatch(int) returns the numerical value of comlex character formed by the combination of 1st 3 characters
						 *The numerical value belongs to the same list as that of regular characters.
						 */
						if(numerical_value[3]==0x4d)
						/*
						 *The condition is-Is the character after the complex character ् ?
						 *This is to test if the complex is a half complex
						 */
						{
							if((numerical_value[4]>=(0x15)&&numerical_value[4]<=(0x39))||(numerical_value[4]==ZWJ_EXCEPTION))
							{
							/*
							 *The condition for the complex character to be half is same as that for regular characters.
							 */
								dev=db.return_HalfPreeti(complex_value);
								/*
								 *return_HalfPreeti(int) of class Database returns a Half Devanagari character of Preeti font corresponding to the int.
								*/
								half_count+=2;
								/*
								 *Since,  half complex is equivalent to 2 half characters
								 */
								half=true;
							}
							else
							{
								dev=db.return_FullPreeti(complex_value);
								/*
								 *return_FullPreeti(int) of class Database returns a Half Devanagari character of Preeti font corresponding to the int.
								 */
							}
						}
						else //if(numerical_value[3]=0x4d)
						{
							/*
							 *For full complex
							 */
							dev=db.return_FullPreeti(complex_value);
						}
					}

					else if(numerical_value[2]==0x30)
					{
						//furter testing required..in windows and linux
						/*
						 *This is for letters such as प्र,क्र etc
						 *0x30== र
						 */
						dev=db.return_FullPreeti(numerical_value[0]);
						dev+=db.return_OtherPreeti(1);
						/*
						 *Other preeti is something I made for special symbols in Preeti
						 */
					}
					else//if ((test_Complex(numerical_value)==true)&&(half_count<3))
					{
						if(numerical_value[0]==0x30)
						//for the 2 of 3 र conditions
						{

							if(numerical_value[2]==ZWJ_EXCEPTION)
							{
								dev=dev+db.return_OtherPreeti(2);
							}
							else//if(numerical_value[2]==ZWJ_EXCEPTION)
							{
								dev=dev+db.return_HalfPreeti(0x30);
								future_reverse_status=true;
								half=true;
								half_count++;
							}

						}
						else
						{
							half_count++;
							half=true;
							dev=db.return_HalfPreeti(numerical_value[0]);
						}
					}
				}
				else //if(a==true) where a=((numerical_value[2]>=(0x15))&&numerical_value[2]<=(0x39))||numerical_value[2]==ZWJ_EXCEPTION
				{
						dev=db.return_FullPreeti(numerical_value[0]);
				}
			}
			else //if(half_count<4)
			{
				if(numerical_value[2]==ZWJ_EXCEPTION)
				{
					/*
					 *Using this method the half can be chained
					 *If before the character after 4th half-letter or equivalent complex letter is ZWJ, the half_count is reset and again further 4 half letters can be chained
					 *I found this experimently, so user testing may bring out other cases as well.
					 */
					dev=db.return_HalfPreeti(numerical_value[0]);

				}
				else//if(numerical_value[2]==ZWJ_EXCEPTION)
				{
					/*
					 *If the chain has been saturated and the above exception is not found, a full preeti will be returned
					 */
					dev=db.return_FullPreeti(numerical_value[0]);
				}
			}
		}
		else// if(numerical_value[1]==0x4d)
		{
			/*
			 *If 2nd character is not ् , 1st character can be diretly mapped.
			 */
			dev=db.return_FullPreeti(numerical_value[0]);
		}
	}
	else //if(numerical_value[0]>=(0x15)&&numerical_value[0]<=(0x39))
	{
		/*
		 *If 1st character is not व्यञ्न्जन वर्ण, it is directly mapped.
		 *But it will be difficult to change the position in second phase with out an indicator
		 */

		if(numerical_value[0]==0x3f)
		{
			/*
			 *0x3f=ह्रस्व चिन्ह
			 *Position of ह्रस्व  चिन्ह has to be adjusted according to the letter before it
			 *This way this symbol is handled in linux is too complex
			 *Not just that but it is also unatural..So I am building this conversion tool based on windows
			 */

			dev=dev+db.return_FullPreeti(0x3f);
			int penultimate_char;
			j=1;
			do
			{
				penultimate_char=find_UnicodeMatch(var+(position-j));
				j++;

			}while(penultimate_char==ZWJ_EXCEPTION||penultimate_char==ZWNJ_EXCEPTION);
			/*
			 *The postition of ह्रस्व  चिन्ह shifts according to the last printable character.
			 *So I am selecting removing ZWJ and ZWNJ.
			 *Relative postion of अ==0x5 and ह=0x39.
			 *For some bizzare reason,ि symols always shifts behind श्वर वर्ण too.
			 */
			 int deduce=penultimate_complexcount;
			 if(penultimate_complex_status==true)
			{

				deduce--;
			}
			if(penultimate_char>=0x5&&penultimate_char<=0x39)
			{
				dev.to_Change(antepenultimate_halfcount+1-deduce);//+1 since if there is no half, shift is by one character
			}
			reverse_status=false;//This case does not need to be reversed
		}
		else//if(numerical_value[0]==0x3f)
		{
			dev=dev+db.return_FullPreeti(numerical_value[0]);
		}
	}
	antepenultimate_halfcount=penultimate_halfcount;
    penultimate_halfcount=half_count;
    /*
     *Now for the reverse :p
	 *when a रेफ is enountered future_reverse_status becomes true
	 *After execution of the if(reverse_status==true) block, the reverse status also becomes true
	 *Hence the next charcter, if it is a consonat,changes position with रेफ
	 *But if its not, reverse_staus becomes false (see else loop for this case)
	 *If it is half...the algrithm below adjusts is postion
	 */
	 if(reverse_status==true)
	 {
		//if(numerical_value[2]!=0x03f)
		dev.to_Change(1);
	 }
	 penultimate_complexcount=complex_count;
	 penultimate_complex_status=complex_status;
	if(half==false)
	{
		/*
		 *resetting the half_count
		*/
		half_count=0;
		complex_count=0;
		future_reverse_status=false;
	}
	return dev;
}
#endif //CONVERTING_FUNCTION_H
