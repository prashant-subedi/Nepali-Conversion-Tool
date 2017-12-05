#ifndef TOOLS_H
#define TOOLS_H
#include<iostream>
#include<string>
#include<vector>
#define ZWJ "‍"//be extreamely careful...here lies the non printable Zero Width Joiner
#define ZWNJ "‌"//Zero Width Non Joiner..phew.....printed them using binary...
#define ZWJ_EXCEPTION 200
#define ZWNJ_EXCEPTION 201
#define EXCEPTION 202//for ascii and others which are not relevant
bool devanagari_Test(std::string unicode_char)
{
    if((unsigned char)unicode_char[0]==224&&((unsigned char)unicode_char[1]>=164 && (unsigned char)unicode_char[1]<=165))
    {
        return true;
    }
    /*else if((unsigned char)unicode_char[0]==0xE2&&((unsigned char)unicode_char[1]==0x80&& (unsigned char)unicode_char[2]==0x8D))
    {
    //Zero Width Zoiner
        return true;
    }
    else if((unsigned char)unicode_char[0]==0xE2&&((unsigned char)unicode_char[1]==0x80&& (unsigned char)unicode_char[2]==0x8C))
    {
    //Zero Width Non Joiner
        return true;

    }
    else
    {
        return false;
    }*/
    //I realized I don't need to pass them......and i didn't want to delete the code
    return false;
}
std::string unicode_Generator(int position)
{
    //Correct this !!!...corrected!!
    std::string generated;
    char listx[4];
    listx[0]=(unsigned char)224;
    listx[1]=(unsigned char)164;
    listx[2]=(unsigned char)128;
    listx[3]='\0';
    /*Above code initializes the list to store the 1st unicode character*/
    if(position<64)
    {
        listx[2]+=position;

    }
    else if(position<=127)
    {
        listx[1]+=1;
        position-=64;
        listx[2]+=position;
    }
    generated=listx;
    if(position==128)
		generated="क्ष";
	else if(position==129)
		generated="त्र";
	else if(position==130)
		generated="ज्ञ";
	else if(position==131)
		generated="ट्ट";
	else if(position==132)
		generated="ठ्ठ";
	else if(position==133)
		generated="त्त";
	else if(position==134)
		generated="द्द";
	else if(position==135)
		generated="श्र";
	return generated;
}
int find_UnicodeMatch(std::string s)
{
    int i;
     /*for easier comparision, I have decided to use strings rather than arrays of char*/
    for(i=0;i<128;i++)
    {
        if(s==unicode_Generator(i))//there was a semi colon here which made me frustated for half an hour
        return i;
    }
    if(s==ZWJ)
    {
		return ZWJ_EXCEPTION;
    }
    else if(s==ZWNJ)
    {
		return ZWNJ_EXCEPTION;
    }
    else
    {
		return EXCEPTION;
    }

}
bool test_Complex(int* number)
{
    std::string to_test=unicode_Generator(number[0]);
    to_test+=unicode_Generator(number[1]);
    to_test+=unicode_Generator(number[2]);
    int i;
    for(i=128;i<=135;i++)
    {
			if(to_test==unicode_Generator(i))
			{
				return true;
			}
    }
    return false;
}
int find_ComplexUnicodeMatch(int* number)
{
	std::string to_test=unicode_Generator(*(number+0));
    to_test+=unicode_Generator(*(number+1));
    to_test+=unicode_Generator(*(number+2));
	int i;
	for(i=128;i<=135;i++)
    {
		if(to_test==unicode_Generator(i))
		{
			return i;
		}
    }
    return 128;
}
///This part is written by Ankita
bool test_Compound(std::string subject)
{
	std::string test_case="copfek0iI";
	std::string temp;
	for (int i=0; i<test_case.length();i++)
	{
		temp=test_case[i];//Note To Ankita(By Prashant)..Apparently character and a string can't be directly compared..Hence I had to follow this extra step.
		if(temp==subject)
		{
			return true;
		}
	}
	return false;
}
bool test_DoubleCompound(std::string subject)
{
	if(subject=="cf")
		return true;
	else
		return false;
}
bool confirm_Compound(std::string subject)
{
	if(subject=="pm")
		return true;
	else if(subject=="em")
		return true;
	else if(subject=="0f")
		return true;
	else if(subject=="km")
		return true;
	else if(subject=="if")
		return true;
	else if(subject=="f]")
		return true;
	else if(subject=="f}")
		return true;
	else if(subject=="If")
		return true;


	return false;

}
#endif //TOOLS_H
