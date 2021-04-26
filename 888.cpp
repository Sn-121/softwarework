#include <iostream>
#include <fstream>
#include<windows.h>
#include <string.h>
#include <conio.h>  //用getch()
using namespace std;
int number;
class Supermarket
{
public:
	char name[20];
	char Num[20];
	int Cnum; //进货总数
	int Mnum; //销售数目
	int Enum; //剩余库存数目
	double Price; //单价
	char Add[20];  //产地
	double Sum; //销售额
	Supermarket* Next;
	void Input()
	{
		cout << "\t\t请输入商品名：";
		cin >> name;
		cout << "\t\t请输入商品编号：";
		cin >> Num;
		cout << "\t\t请输入商品进货总数：";
		cin >> Cnum;
		cout << "\t\t请输入商品销售数目：";
		cin >> Mnum;
		cout << "\t\t请输入商品剩余库存数目：";
		cin >> Enum;
		cout << "\t\t请输入商品产地：";
		cin >> Add;
		cout << "\t\t请输入商品单价:";
		cin >> Price;
		Sum = Mnum * Price;
	}
	void ReadFile(istream& in) //文件指针
	{
		in >> name >> Num >> Cnum >> Mnum >> Enum >> Add >> Price >> Sum;
	}
	void Show()
	{
		cout << "商品名:" << name << endl
			<< "商品编号:" << Num << endl
			<< "进货总数:" << Cnum << endl
			<< "销售数目:" << Mnum << endl
			<< "剩余库存:" << Enum << endl
			<< "产地:" << Add << endl
			<< "单价:" << Price << endl
			<< "销售额:" << Sum << endl
			<< endl;
	}
	void Show1()
	{
		cout << "商品名:" << name << endl

			<< "商品编号:" << Num << endl
			<< "进货总数:" << Cnum << endl
			<< "销售数目:" << Mnum << endl
			<< "剩余库存:" << Enum - number << endl
			<< "产地:" << Add << endl
			<< "单价:" << Price << endl
			<< "销售额:" << Sum << endl
			<< endl;
	}
};
class Supermarketmassage
{
public:
	Supermarketmassage();
	~Supermarketmassage();
	void ShowMenu();
	void Find();
	void Save();
	void ModifyItem();
	void RemoveItem();
	void sale();   //销售函数
	void Swap(Supermarket*, Supermarket*);
	void Sort();   //void Unpass();
	int ListCount();   //void Average();
	void Display()
	{
		int i = 1;
		for (Supermarket* p = Head->Next; p != End; p = p->Next, i++)
		{
			if (i == 2)
				p->Show1();
			else p->Show();
		}
		cout << "输入任意字符！继续……";
		getch();
	}
	void AddItem()
	{
		End->Input();
		End->Next = new Supermarket;
		End = End->Next;
		cout << "添加成功!" << endl;
		cout << "输入任意字符！继续……";
		getch();
	}
private:
	Supermarket* Head, * End;
	ifstream in;
	ofstream out;
	Supermarket* FindItem(char* name)
	{
		for (Supermarket* p = Head; p->Next != End; p = p->Next)//匹配成功则返回上一个指针，不成功就返回空
			if (!strcmp(p->Next->name, name))
				return p;
		return NULL;
	}
	Supermarket* FindNum(char* Num)
	{
		for (Supermarket* p = Head; p->Next != End; p = p->Next)//匹配成功则返回上一个指针，不成功就返回空
			if (!strcmp(p->Next->Num, Num))
				return p;
		return NULL;
	}
	Supermarket* FindAdd(char* Add)
	{
		for (Supermarket* p = Head; p->Next != End; p = p->Next)//匹配成功则返回上一个指针，不成功就返回空
			if (!strcmp(p->Next->Add, Add))
				return p;
		return NULL;
	}
};
Supermarketmassage::Supermarketmassage()
{
	Head = new Supermarket;
	Head->Next = new Supermarket;
	End = Head->Next;
	in.open("sort.txt");
	if (!in)
		cout << "这是一个新系统，无商品信息。请先输入。" << endl;
	else
	{
		while (!in.eof())
		{
			End->ReadFile(in);
			if (End->name[0] == '\0')
				break;
			End->Next = new Supermarket;
			End = End->Next;
		}
		in.close();
		cout << "\t\t读取商品信息成功!" << endl;
	}
}
Supermarketmassage::~Supermarketmassage()
{
	Save();
	for (Supermarket* temp; Head->Next != End;)
	{
		temp = Head->Next;
		Head->Next = Head->Next->Next;
		delete temp;
	}
	delete Head, End;
}int Enum1 = 100;
void Supermarketmassage::ShowMenu()
{
	cout << "〒〒〒〒〒〒〒〒〒〒  ☆   超 市 商 品 管 理 系  统     ☆  〒〒〒〒〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒★★★★★         ★★★★★★★★       ★★★★★〒 〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒〒〒★  ☆          1.增加商品信息        ☆  ★〒〒〒 〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒〒〒★  ☆          2.显示商品信息        ☆  ★〒〒〒 〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒〒〒★  ☆          3.排序统计商品        ☆  ★〒〒〒 〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒〒〒★  ☆          4.查找商品信息        ☆  ★〒〒〒〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒〒〒★  ☆          5.删除商品信息        ☆  ★〒〒〒 〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒〒〒★  ☆          6.修改商品信息        ☆  ★〒〒〒 〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒〒〒★  ☆          7.销售超市商品        ☆  ★〒〒〒 〒〒〒〒〒〒" << endl;
	cout << "〒〒〒〒〒〒〒〒〒★  ☆          0.安全退出系统        ☆  ★〒〒〒 〒〒〒〒〒〒" << endl;
	cout << "\n\t\t\n\t\t请选择：";
}
void Supermarketmassage::Find()
{
	char name[20], Num[10];
	int x;
	Supermarket* p = NULL;
	cout << "\n\t\t*********************************\n";
	cout << "\t\t※ 1.按商品的名称查找\n\t\t※ 2.按商品编号查找";
	cout << "\n\t\t*********************************\n请选择：";
	cin >> x;
	switch (x)
	{
	case 1:
	{
		cout << "\t\t请输入要查找的商品的名称：";
		cin >> name;
		if (p = FindItem(name))
		{
			p->Next->Show();
			cout << "输入任意字符！继续……";
			getch();
		}
		else
		{
			cout << "\t\t没有找到该商品信息！" << '\n' << endl;
			cout << "输入任意字符！继续……";
			getch();
		}
	}
	break;
	case 2:
	{
		cout << "\t\t请输入要查找的商品编号：";
		cin >> Num;
		if (p = FindNum(Num))
		{
			p->Next->Show();
			cout << "输入任意字符！继续……";
			getch();
		}
		else
		{
			cout << "\t\t没有找到该编号的商品！" << '\n' << endl;
			cout << "输入任意字符！继续……";
			getch();
		}
	}
	break;
	}
}
void Supermarketmassage::ModifyItem()//修改信息
{
	char name[20];
	Supermarket* p = NULL;
	cout << "\t\t请输入要修改的商品名:";
	cin >> name;
	if (p = FindItem(name))
	{
		cout << "\t\t已找到商品的信息，请输入新的信息!" << endl;
		p->Next->Input();
		cout << "修改成功！" << endl;
		cout << "输入任意字符！继续……";
		getch();
	}
	else
	{
		cout << "\t\t没有找到!" << endl;
		cout << "输入任意字符！继续……";
		getch();
	}
}
void Supermarketmassage::RemoveItem()// 删除信息
{
	int date(int&, int&, int&);
	int year1, month1, day1, year2, month2, day2, sum1, sum2, SUM;
	cout << "请输入商品的今天的日期：(年、月、日)";
	cin >> year1 >> month1 >> day1;
	sum1 = date(year1, month1, day1);
	cout << "请输入商品的截止日期：(年、月、日)";
	cin >> year2 >> month2 >> day2;
	sum2 = date(year2, month2, day2);
	SUM = sum2 - sum1;
	if (SUM >= 30)
	{
		cout << "该商品处于安全期，不用处理~" << endl;
	}
	else
	{
		char name[20];
		Supermarket* p = NULL, * temp = NULL;
		cout << "\t\t请输入要删除的商品名:" << endl;
		cin >> name;
		if (p = FindItem(name))
		{
			temp = p->Next;
			p->Next = p->Next->Next;
			delete temp;
			cout << "\t\t删除成功!" << endl;
			cout << "输入任意字符！继续……";
			getch();
		}
		else
		{
			cout << "\t\t没有找到!" << endl;
			cout << "输入任意字符！继续……";
			getch();
		}
	}
}
int date(int& day, int& month, int& year)   //日期函数
{
	int sum, leap;
	switch (month)                     		//先计算某月以前月份的总天数
	{
	case 1:sum = 0; break;
	case 2:sum = 31; break;
	case 3:sum = 59; break;
	case 4:sum = 90; break;
	case 5:sum = 120; break;
	case 6:sum = 151; break;
	case 7:sum = 181; break;
	case 8:sum = 212; break;
	case 9:sum = 243; break;
	case 10:sum = 273; break;
	case 11:sum = 304; break;
	case 12:sum = 334; break;
	default:cout << "data error"; break;
	}
	sum = sum + day; //再加上某天的天数
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))//判断是不是闰年
		leap = 1;
	else
		leap = 0;
	if (leap == 1 && month > 2)    			//如果是闰年且月份大于2，总天数应该加一天
		sum++;
	return sum;
}
void Supermarketmassage::sale()  //销售函数
{
	Supermarket a;
	Supermarket* p = NULL;
	int m;
	char name[20], Num[10];
	cout << "请输入想要销售的商品信息：" << endl;
	cout << "\n\t\t*********************************\n";
	cout << "\t\t※ 1.按商品的名称查找\n\t\t※ 2.按商品编号查找";
	cout << "\n\t\t*********************************\n请选择：";
	cin >> m;
	switch (m)
	{
	case 1:
	{
		cout << "\t\t请输入要查找的商品的名称：";
		cin >> name;
		if (p = FindItem(name))
		{
			cout << "请输入要销售的数量：";
			cin >> number;
			if (number <= Enum1)
			{
				cout << "销售成功!" << endl;
				cout << "输入任意字符！继续……";
				getch();
			}
			else
			{
				cout << "库存不足，请重新输入!" << endl;
				cout << "输入任意字符！继续……";
				getch();
			}
		}
		else
		{
			cout << "\t\t没有找到!" << endl;
			cout << "输入任意字符！继续……";
			getch();
		}

	}
	break;
	case 2:
	{cout << "\t\t请输入要查找的商品的编号：";
	cin >> Num;
	if (p = FindNum(Num))
	{
		cout << "请输入要销售的数量：";
		cin >> number;
		if (number <= Enum1)
		{
			cout << "销售成功!" << endl;
			cout << "输入任意字符！继续……";
			getch();
		}
		else
		{
			cout << "库存不足，请重新输入!" << endl;
			cout << "输入任意字符！继续……";
			getch();
		}
	}
	else
	{
		cout << "\t\t没有找到!" << endl;
		cout << "输入任意字符！继续……";
		getch();
	}
	}
	break;
	}
}

void Supermarketmassage::Swap(Supermarket* p1, Supermarket* p2)//交换两个combox变量的数据域
{
	Supermarket* temp = new Supermarket;
	strcpy(temp->name, p1->name);  //字符串name里面
	strcpy(temp->Num, p1->Num);
	strcpy(temp->Add, p1->Add);
	temp->Cnum = p1->Cnum;
	temp->Mnum = p1->Mnum;
	temp->Enum = p1->Enum;
	temp->Price = p1->Price;
	temp->Sum = p1->Sum;
	strcpy(p1->name, p2->name);
	strcpy(p1->Num, p2->Num);
	strcpy(p1->Add, p2->Add);
	p1->Cnum = p2->Cnum;
	p1->Mnum = p2->Mnum;
	p1->Enum = p2->Enum;
	p1->Price = p2->Price;
	p1->Sum = p2->Sum;
	strcpy(p2->name, temp->name);
	strcpy(p2->Num, temp->Num);
	strcpy(p2->Add, temp->Add);
	p2->Cnum = temp->Cnum;
	p2->Mnum = temp->Mnum;
	p2->Enum = temp->Enum;
	p2->Price = temp->Price;
	p2->Sum = temp->Sum;
}
int Supermarketmassage::ListCount()//统计当前链表的记录总数，返回一个整数
{
	if (!Head)
		return 0;
	int n = 0;
	for (Supermarket* p = Head->Next; p != End; p = p->Next)
	{
		n++;
	}
	return n;
}
void Supermarketmassage::Sort()//对当前链表进行排序
{
	cout << "Sorting..." << endl;
	Supermarket* p = NULL, * p1 = NULL, * k = NULL;
	int n = Supermarketmassage::ListCount();
	if (n < 2)
		return;
	for (p = Head->Next; p != End; p = p->Next)
		for (k = p->Next; k != End; k = k->Next)
		{
			if (p->Add > k->Add)
			{
				Supermarketmassage::Swap(p, k);
			}
		}
	cout << "排序完成！" << endl;
	getch();
	return;
}
void Supermarketmassage::Save()
{
	out.open("sort.txt");
	for (Supermarket* p = Head->Next; p != End; p = p->Next)
		out << p->name << "\t\t"
		<< p->Num << "\t\t"
		<< p->Cnum << "\t\t"
		<< p->Mnum << "\t\t"
		<< p->Enum << "\t\t"
		<< p->Add << "\t\t"
		<< p->Price << "\t\t"
		<< p->Sum << '\n';
	out.close();
}
void xinxing()   //系统开始的心形图形
{
	int i, j, k, l, m;
	char c = 3;
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 32 - 2 * i; j++)
			cout << " ";
		for (k = 1; k <= 4 * i + 1; k++)
			cout << c;
		for (l = 1; l <= 13 - 4 * i; l++)
			cout << " ";
		for (m = 1; m <= 4 * i + 1; m++)
			cout << c;
		cout << endl;
	}
	for (i = 1; i <= 3; i++)
	{
		for (j = 1; j <= 24 + 1; j++)
			cout << " ";
		for (k = 1; k <= 29; k++)
			cout << c;
		cout << endl;
	}
	for (i = 7; i >= 1; i--)
	{
		for (j = 1; j <= 40 - 2 * i; j++)
			cout << " ";
		for (k = 1; k <= 4 * i - 1; k++)
			cout << c;
		cout << endl;
	}
	for (i = 1; i <= 39; i++)
		cout << " ";
	cout << c;
	cout << endl;
}
void logo()    //进入系统的开头
{
	int i;
	cout << "\t\t§§§§§§§§§§§§§§§§§§§§§§§§§§" << endl;
	for (i = 0; i < 3; i++)
		cout << "\t\t◎\t\t\t\t\t\t  ◎" << endl;
	cout << "\t\t◎★★★【  欢迎进入校园超市商品管理系统  】★★★◎" << endl;
	for (i = 0; i < 3; i++)
		cout << "\t\t◎\t\t\t\t\t\t  ◎" << endl;
	cout << "\t\t§§§§§§§§§§§§§§§§§§§§§§§§§§\n" << endl;
}
int mai()
{
	system("color E");
	int x;
	bool quit = false;
	xinxing();
	logo();
	Supermarketmassage Grade;
	cout << "按任意键开始……";
	getch();
	while (!quit)
	{
		system("cls");
		Grade.ShowMenu();
		cin >> x;
		switch (x)
		{
		case 0:
		{
			quit = true;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << endl;
			cout << "欢迎下次使用~" << endl;
			system("color C");
			xinxing();
		}
		break;
		case 1:Grade.AddItem();
			break;
		case 2:Grade.Display();
			break;
		case 3:Grade.Sort();
			break;
		case 4:Grade.Find();
			break;
		case 5:Grade.RemoveItem();
			break;
		case 6:Grade.ModifyItem();
			break;
		case 7:Grade.sale();
			break;
		}
	}
	return 0;
}

void main()
{
	mai();
}