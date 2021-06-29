#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main ()
{
	    string s("The zip code of Hondelage in Germany is 38108.");
	    cout<<"Original: " << s << endl;
	    string sd(s.begin(),s.end()); //构造函数中使用迭代器
	    cout << "Destination: " << sd << endl;
	    transform(sd.begin(),sd.end(),sd.begin(),toupper); //算法中使用迭代器(仿函数)
	     cout << "Destination (All Toupper)): " << sd << endl;
	     string sd1;
	     sd1.append(sd.begin(),(sd.end() -7)); //append()函数中使用迭代器
	     cout << "Destination sd1: " << sd1 << endl;
	     string sd2;
	     string::reverse_iterator iterA;
     	     string temp = "0";
	     for(iterA = sd.rbegin(); iterA != sd.rend(); iterA++) //reverse_iterator
	     {	
		     temp=* iterA;			
		     sd2.append(temp);
	     }
	     cout << "Destination sd2: " << sd2 << endl;
	     sd2.erase (0, 15); //erase()函数中使用迭代器								       
	     cout << "Destination sd2 (Erased 15 chars) : " << sd2 << endl;
	     string::iterator iterB = sd2.begin();
	     string sd3 = string ("12345678");
	     sd2.insert(sd2.begin(), sd3.begin(), sd3.end()); //insert()函数中使用迭代器								
	     cout << "Destination sd2 (Insert 8 chars) : " << sd2 << endl;
	     sd2.replace(sd2.begin (), sd2.end(), "This is an Exarrple of Replace"); //Replace
	     cout <<"Destination sd2 (Replace All): " << sd2 << endl; // replace ()函数中使用迭代器
}
