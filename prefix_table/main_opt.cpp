#include "prefix_table_opt.hpp"
#include "fstream"
#include <cmath>
#include <vector>

#define BYTE 8

using namespace std;

//store input row 
void storeData(string& line,string& prefix,string& cmd,char& id)
{ 
    cmd = line.substr(0, line.find(' '));
    int space = line.find(' ');
    prefix = line.substr(space + 1);
    if(cmd != "FIND") id = prefix[prefix.length()-1];
}


//Convert integer to 8 bit representation
vector<int> convert8Bits(int x)
{
	vector<int> v(8);
    int i = 7;
	if(x==0){ for(int i = 0; i < BYTE; i++) v[i] = 0;}
	else
	{
		while(x) 
	    {
	        if(x&1) v[i]=1;
	        else v[i]=0;
	        i--;
	        x>>=1;  
	    }
	}
  	return v;
}


//Convert integer to 8 bit representation
vector<int> convertBinary(string s)
{
	int n = 0;
	for(int i = s.length()-1; i>=0; i--) n += pow(10,s.length()-1-i)*((int)s[i]-48);
	return convert8Bits(n);
}


string convertChar(vector<int> v)
{
    string t = "";
	for(int i = 0; i < v.size(); i++)
	{
	    if(v[i] == 1) t = t + '1';
	    else t = t + '0';
	}
	return t;
}




int main() {

    ifstream f("sample_input.txt");
    string line, ip, cmd;
    char id;
    int depth = 0, per;

    prefix_table_opt::Tree tree;

    while (getline(f, line))
    {
        storeData(line,ip,cmd,id);
        string temp = "",bin = "";
		for(int i = 0; i < ip.length(); i++)
		{
			if(ip[i] == '/')
            {
                per = stoi(ip.substr(i+1,ip.find(' ')));
                break;
            }
			if(ip[i] == '.')
			{
				vector<int> v = convertBinary(temp);
				bin = bin + convertChar(v);
                temp = "";
			}
			else temp = temp + ip[i];
		}
		vector<int> v = convertBinary(temp);
		bin = bin + convertChar(v);

        if(cmd == "ADD")
        {
            tree.add(bin,id,per);
            cout<<"Added "<<ip<<" "<<"max depth "<<per<<" total nodes "<<bin.substr(0,per)<<endl;
        }
        else if(cmd == "FIND")
        {
            id = tree.find(bin);
            cout<<"Found "<<ip<<" "<<id<<" at the depth "<<per<<endl;
        }
        else if(cmd == "REMOVE")
        {
            depth = tree.remove(bin,id,per);
            cout<<"Removed "<<ip<<" "<<"at the depth "<<per<<" total nodes "<<bin.substr(0,per)<<endl;
        }
        else throw string("invalid input");
    }
   
    f.close();
    return 0;
}


