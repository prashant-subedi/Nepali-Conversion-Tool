/**
  *Written By: Prashant Subedi
  *For:The software-Nepali Conversion Tool
  *Description:
	*This header contains the definition of the structure Char and class Preeti.
	*See individual class and structure for more info
  */
#ifndef PREETI_H
#define PREETI_H
#include<iostream>
#include "devnagri.h"
#include<vector>
/*
 *It contains the definition of structure Devanagari and also a database of Preeti characters defined in class Database
 */
#define NEPALI true
#define OTHER false
struct Pchar//Preeti Char
{
	///This structure repersents a unit character in Preeti string.
	std::string preeti_char;
	bool type;
};
class Preeti
{
/**
  *Take the newley coverted data
  *Remove zero width joiner and seperator
  */
	private:
		Pchar* single_preeti;
		int unicode_length;
		int preeti_length;
		Database db;
	public:
		Preeti(int);
		~Preeti();
		void operator+=(std::string);
		void operator+=(Devanagari);
        std::vector<Pchar> return_All();

};
Preeti::Preeti(int len)
{
	single_preeti=new Pchar[len];
	unicode_length=len;
	preeti_length=0;
}
Preeti::~Preeti()
{
	delete[] single_preeti;
}
void Preeti::operator+=(std::string character)
{
    single_preeti[preeti_length].preeti_char=character;
    preeti_length++;
    single_preeti[preeti_length].type=OTHER;
}
void Preeti::operator+=(Devanagari character)
{
	single_preeti[preeti_length].preeti_char=character.return_Dev();
	single_preeti[preeti_length].type=NEPALI;
	bool matra=(single_preeti[preeti_length].preeti_char=="L")||(single_preeti[preeti_length].preeti_char=="f]")||(single_preeti[preeti_length].preeti_char=="f")||(single_preeti[preeti_length].preeti_char=="f}");
    if((matra==true)&&single_preeti[preeti_length-1].preeti_char=="{")
    {
		Pchar temp;
        temp=single_preeti[preeti_length-1];
        single_preeti[preeti_length-1]=single_preeti[preeti_length];
        single_preeti[preeti_length]=temp;
    }
    int i;
    for(i=preeti_length;i>(preeti_length-character.change_By());i--)
	{
        Pchar temp;
        temp=single_preeti[i-1];
        single_preeti[i-1]=single_preeti[i];
        single_preeti[i]=temp;

	}
	preeti_length++;
}
std::vector<Pchar> Preeti::return_All()
{
	int i;
	std::vector<Pchar> return_all;
	Pchar p;
	for(i=0;i<preeti_length;i++)
	{
		p.preeti_char=single_preeti[i].preeti_char;
		p.type=single_preeti[i].type;
		return_all.push_back(p);
	}
	return return_all;
}
#endif //PREETI_H

