#include"unicode2.h"
#include"devnagri.h"
#include"tools.h"
#include<string>
#include<vector>
int preeti_Converter(std::string abc)
{
	std::cout<<"Enter a string in preeti"<<std::endl;
	getline(std::cin,abc);
	Unicode separator;
	separator=abc;
	Database db;
	std::vector<std::string> preeti;
	/*
	 *preeti is a smart pointer of type vector<string>
	 *We will use it to store one preeti unit(not one byte or one utf-8 character)
	 */
	for(int i=0; i<separator.length_Unicode();i++)
	{
		std::string temp;
		temp=(separator+i);
		if(test_Compound(temp))
		{
			temp+=(separator+(i+1));
			if(test_DoubleCompound(temp))
			{
				temp+=(separator+(i+2));
				std::string temp2;
				temp2=temp[2];
				if(temp2=="}" || temp2=="]")
				{
					preeti.push_back(temp);
					i+=2;
				}
				else//if(temp2=="}" || temp2=="]")
				{
					preeti.push_back("cf");
					i++;
				}
			}
			else//if(test_DoubleCompound(temp))
			{
				if(confirm_Compound(temp))
					{
						preeti.push_back(temp);
						i++;
					}
				else
					preeti.push_back((separator+i));
			}

		}
		else//if(test_Compound)
		{
			preeti.push_back(separator+i);
		}

	}
	//Here comes the converting algorithm
	std::vector<std::string> converted;
	for(int i=0;i<preeti.size();i++)
	{
		Compare c=db.return_Index(preeti[i]);
		if (c.value==EXCEPTION)
		{
			converted.push_back(preeti[i]);
		}
		else
		{
			if(c.type==1)
			{
                converted.push_back(unicode_Generator(c.value));
			}
			else if(c.type==2)
			{

				std::string temp;
				temp+=unicode_Generator(c.value);
				temp+="्";
				converted.push_back(temp);
			}
			else if(c.type==3)
			{

			}

		}
	}
	std::string return_string;
	for(int i=0;i<converted.size();i++)
	{
		return_string+=converted[i];
	}
	return return_string;
}
