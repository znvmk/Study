#include"DynamicWebPage1.0.h"

//顺序文件读写
void WriteOrderFile(int r, int g, int b,int l)
{
	ofstream myFile;
	myFile.open("T1.html", ios::out);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	myFile << "<html>" << endl;
	myFile << " <head>" << endl;
	myFile << "  <title>" << endl;
	myFile << "  第一张动态网页" << endl;
	myFile << "  </title>" << endl;
	
	//myFile << "  <meta charset=\"utf-8\">"<< endl;
	myFile << "  <meta http-equiv = \"refresh\" content = \"1\" name = \"keywords\" >"<< endl;
	myFile << " </head>" << endl;
	myFile << " <body bgcolor=\"#"<<ColorConvert(r, g, b)<<"\" background=\"1.jpg\" topmargin=10 leftmargin=10 rightmargin=10 bottommargin=10>" << endl;
	myFile << "<p align = \"center\">欢迎光临我的主页!</p>" << endl;
	myFile << "  <font face = \"楷体\" size = \"5\" color =\"#" << ColorConvert(5, 5, 5)<<"\">" << endl;
	myFile <<"    首页<br><br>" << endl;


	for (int i = 0;i < l;i++) 
	{
		myFile << " <p>" << endl;
		myFile << " <font face = \"楷体\" size = \"3\" color = \"#"<< ColorConvert(i*20, i * 20, i * 20)<<"\">" << endl;
		myFile << " <table>" << endl;
		myFile << " <tr bgcolor=\"#" << ColorConvert(i*r, i *g, i *b) << "\">" << endl;
		myFile << "  <td>北大儿童英语" << i + 1 << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" << "</td>";
		myFile<< "	<td> <img src = \"./music.jpg\" width = \"50\" height = \"50\">" <<"&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"<< "</td>" << endl;
		myFile << "	<td> <img src = \"./mail.jpg\" width = \"50\" height = \"50\">" << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" << "</td>" << endl;
		myFile << "	<td> <img src = \"./download.jpg\" width = \"50\" height = \"50\">" << "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;" << "</td>" << endl;
		myFile << " </tr>" << endl;
		myFile << " </table>" << endl;
		myFile << " </font>" << endl;
		myFile << " </p>" << endl;
	}

	myFile << "  </font>" << endl;
	myFile << "  </font>" << endl;
	myFile << "  <a href=\"file:///D:/znpr/C++/DynamicWebPage1.0/DynamicWebPage1.0/天空之城.mp3\">天空之城</a>"<<endl;
	myFile << " <br><br><br><br><br><br><br><br>" << endl;
	myFile << " <hr with=\"%100\" size=\"1\" color=\"#00FFFF\">" << endl;
	myFile << "  版权&copy;:版权所有，违者必究!" << endl;
	
	myFile << " </body>" << endl;

	myFile << "</html>" << endl;


	myFile.close();

	cout << endl << "写T1.html文件";

}




string ColorConvert(int r, int g, int b)
{
	string color;
	r %= 256;
	g %= 256;
	b %= 256;
	char convert[7] = {};
	char ox[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	convert[0] = ox[r / 16];
	convert[1] = ox[r % 16];
	convert[2] = ox[g / 16];
	convert[3] = ox[g % 16];
	convert[4] = ox[b / 16];
	convert[5] = ox[b % 16];
	convert[6] = '\0';
	color=convert;
	//color = "aoe";
	return color;
}



void ReadOrderFile()
{
	ifstream myFile;
	myFile.open("dataOrder.txt", ios::in);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	cout << endl << "读取dataOrder.txt文件内容如下所示：" << endl;
	int value;
	while ((value = myFile.get()) != EOF)
	{
		cout << (char)value;
	}
	myFile.close();
}


//随机文件读写
struct Record
{
	char value[10];
};

void WriteRandomFile()
{
	Record record[3] = { "01-张三","02-李四","03-王五" };


	ofstream myFile;
	myFile.open("dataRandom.txt", ios::out | ios::binary);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}
	for (int i = 0;i < 3;i++)
	{
		myFile.write((const char*)&record[i], sizeof(Record));

	}



	myFile.close();

	cout << endl << "写dataRandom.txt文件";

}

void ReadRandomFile()
{

	ifstream myFile;
	myFile.open("dataRandom.txt", ios::in | ios::binary);
	if (!myFile)
	{
		cout << "打开文件错误" << endl;
		return;
	}

	cout << endl << "读dataRandom.txt文件" << endl;
	//定义存放获取记录的变量
	Record record;
	//把文件的写指针从文件的开头向后移一条记录
	myFile.seekg(sizeof(Record), ios::beg);
	//读取文件第二条记录
	myFile.read((char*)&record, sizeof(record));
	cout << (char*)&record;

	myFile.close();



}





void main()
{
	int a;
	a = 20;
	cout << a;
	int r, g, b;
	r = 255;g = 255;b = 255;
	cout << ColorConvert(r, g, b) << endl;
	
	int lines;
	lines = 9;

	

	//ReadOrderFile();


	//WriteRandomFile();

	//ReadRandomFile();
	
	while (1)
	{
		Sleep(1000);
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;
		cout << r << " " << g << " " << b<<endl;
		WriteOrderFile( r, g, b,lines);
	}
	
	system("pause");
}