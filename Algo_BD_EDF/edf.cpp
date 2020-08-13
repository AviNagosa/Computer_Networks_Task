#include "edf.hpp"

//Convert integer to 8 bit representation
int edf::convertToInt(string s)
{
	int n = 0;
	for(int i = s.length()-1; i>=0; i--) n += pow(10,s.length()-1-i)*((int)s[i]-48);
	return n;
}



int edf::decreas(queue<Packet>& v)
{
   int count = 0;     //count the zero
   for (int i = 0; i < v.size(); i++)
   {
       if((v.front().packet_slack - 1) > 0)
       {
            Packet* p = new Packet(v.front().packet_slack - 1,v.front().packet_value);
            v.pop();
            v.push(*p);
       }
       else    //delete the zero
       {
           v.pop();
           count++;
       }
   }
    return count;
}




int edf::arrival_phase(string& line, queue<Packet>& v, int& queue_size,int& arrive)
{
    int drop = 0;
    while (line.size() != 0)
    {
        int amount, p_s, p_v;

        int del = line.find(',');
        amount = convertToInt(line.substr(1, del-1));
        line = line.substr(del+1);
        arrive = arrive + amount;

        del = line.find(',');
        p_s = convertToInt(line.substr(0, del));
        line = line.substr(del+1);

        del = line.find(')');
        p_v = convertToInt(line.substr(0, del));
        line = line.substr(del+1);

        Packet *pack = new Packet(p_s, p_v);
        for (int i = 0; i < amount; i++)
        {
            if (v.size() < queue_size) v.push(*pack);
            else
            {
                drop++;
                //find the min slack
                int min = v.front().packet_slack;
                for(int i = 0; i < v.size(); i++)
                {
                    if(v.front().packet_slack < min) min = v.front().packet_slack;
                    Packet* p = new Packet(v.front().packet_slack,v.front().packet_value);
                    v.pop();
                    v.push(*p);    
                }
                for(int i=0; i<v.size(); i++)
                {
                    if(v.front().packet_slack == min)
                    {
                        v.pop();
                        v.push(*pack);
                        break;
                    }
                    else
                    {
                        Packet* p = new Packet(v.front().packet_slack,v.front().packet_value);
                        v.pop();
                        v.push(*p);
                    }
                }
            }
        }        
    }
    return drop;
}



int edf::processing_phase(queue <Packet>& v)
{
    if(v.size() == 0) return -1;
    
    int val = 0;
    int min = v.front().packet_slack;

    //find the min slack
    for(int i=0;i<v.size();i++)
    {
        if(v.front().packet_slack < min) min = v.front().packet_slack;
        Packet* p = new Packet(v.front().packet_slack,v.front().packet_value);
        v.pop();
        v.push(*p);    
    }

    for(int i=0;i<v.size();i++)
    {
        if(v.front().packet_slack == min)
        {
            val = v.front().packet_value;
            v.pop();
            break;
        }
        else
        {
            Packet* p = new Packet(v.front().packet_slack,v.front().packet_value);
            v.pop();
            v.push(*p);
        }
    }
    return val;
}



void edf::EDF(int queue_size ,string input)
{

    int arrive = 0,drop = 0, transPacket = 0, transValue = 0, temp = 0;
    queue <Packet> q;
    string line;
    ifstream f(input);

    while (getline(f, line))
    {
        drop = drop + arrival_phase(line,q,queue_size,arrive);

        drop = drop + decreas(q);

        temp = processing_phase(q);

        if(temp != -1)
        {
            transValue = transValue + temp;
            transPacket = transPacket + 1;
        }
        cout<<"Total arrived packets "<<arrive<<", total dropped packets "<<drop<<", total transmitted packets "<<transPacket<<" total transmitted value "<<transValue<<endl;
    }

    while(q.size() >= 1)
    {
        drop = drop + decreas(q);  
        temp = processing_phase(q);
        if(temp != -1)
        {
            transValue = transValue + temp;
            transPacket = transPacket + 1;
        }
    }
    
    cout<<"Total arrived packets "<<arrive<<", total dropped packets "<<drop<<", total transmitted packets "<<transPacket<<" total transmitted value "<<transValue<<endl;
}

