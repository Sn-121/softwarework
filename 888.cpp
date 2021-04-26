#include <iostream>
#include <fstream>
#include<windows.h>
#include <string.h>
#include <conio.h>  //��getch()
using namespace std;
int number;
class Supermarket
{
public:
	char name[20];
	char Num[20];
	int Cnum; //��������
	int Mnum; //������Ŀ
	int Enum; //ʣ������Ŀ
	double Price; //����
	char Add[20];  //����
	double Sum; //���۶�
	Supermarket* Next;
	void Input()
	{
		cout << "\t\t��������Ʒ����";
		cin >> name;
		cout << "\t\t��������Ʒ��ţ�";
		cin >> Num;
		cout << "\t\t��������Ʒ����������";
		cin >> Cnum;
		cout << "\t\t��������Ʒ������Ŀ��";
		cin >> Mnum;
		cout << "\t\t��������Ʒʣ������Ŀ��";
		cin >> Enum;
		cout << "\t\t��������Ʒ���أ�";
		cin >> Add;
		cout << "\t\t��������Ʒ����:";
		cin >> Price;
		Sum = Mnum * Price;
	}
	void ReadFile(istream& in) //�ļ�ָ��
	{
		in >> name >> Num >> Cnum >> Mnum >> Enum >> Add >> Price >> Sum;
	}
	void Show()
	{
		cout << "��Ʒ��:" << name << endl
			<< "��Ʒ���:" << Num << endl
			<< "��������:" << Cnum << endl
			<< "������Ŀ:" << Mnum << endl
			<< "ʣ����:" << Enum << endl
			<< "����:" << Add << endl
			<< "����:" << Price << endl
			<< "���۶�:" << Sum << endl
			<< endl;
	}
	void Show1()
	{
		cout << "��Ʒ��:" << name << endl

			<< "��Ʒ���:" << Num << endl
			<< "��������:" << Cnum << endl
			<< "������Ŀ:" << Mnum << endl
			<< "ʣ����:" << Enum - number << endl
			<< "����:" << Add << endl
			<< "����:" << Price << endl
			<< "���۶�:" << Sum << endl
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
	void sale();   //���ۺ���
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
		cout << "���������ַ�����������";
		getch();
	}
	void AddItem()
	{
		End->Input();
		End->Next = new Supermarket;
		End = End->Next;
		cout << "��ӳɹ�!" << endl;
		cout << "���������ַ�����������";
		getch();
	}
private:
	Supermarket* Head, * End;
	ifstream in;
	ofstream out;
	Supermarket* FindItem(char* name)
	{
		for (Supermarket* p = Head; p->Next != End; p = p->Next)//ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
			if (!strcmp(p->Next->name, name))
				return p;
		return NULL;
	}
	Supermarket* FindNum(char* Num)
	{
		for (Supermarket* p = Head; p->Next != End; p = p->Next)//ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
			if (!strcmp(p->Next->Num, Num))
				return p;
		return NULL;
	}
	Supermarket* FindAdd(char* Add)
	{
		for (Supermarket* p = Head; p->Next != End; p = p->Next)//ƥ��ɹ��򷵻���һ��ָ�룬���ɹ��ͷ��ؿ�
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
		cout << "����һ����ϵͳ������Ʒ��Ϣ���������롣" << endl;
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
		cout << "\t\t��ȡ��Ʒ��Ϣ�ɹ�!" << endl;
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
	cout << "��������������������  ��   �� �� �� Ʒ �� �� ϵ  ͳ     ��  ��������������������" << endl;
	cout << "��������������������         ���������       �����﨓 ������������" << endl;
	cout << "��������������������  ��          1.������Ʒ��Ϣ        ��  �﨓���� ������������" << endl;
	cout << "��������������������  ��          2.��ʾ��Ʒ��Ϣ        ��  �﨓���� ������������" << endl;
	cout << "��������������������  ��          3.����ͳ����Ʒ        ��  �﨓���� ������������" << endl;
	cout << "��������������������  ��          4.������Ʒ��Ϣ        ��  �﨓����������������" << endl;
	cout << "��������������������  ��          5.ɾ����Ʒ��Ϣ        ��  �﨓���� ������������" << endl;
	cout << "��������������������  ��          6.�޸���Ʒ��Ϣ        ��  �﨓���� ������������" << endl;
	cout << "��������������������  ��          7.���۳�����Ʒ        ��  �﨓���� ������������" << endl;
	cout << "��������������������  ��          0.��ȫ�˳�ϵͳ        ��  �﨓���� ������������" << endl;
	cout << "\n\t\t\n\t\t��ѡ��";
}
void Supermarketmassage::Find()
{
	char name[20], Num[10];
	int x;
	Supermarket* p = NULL;
	cout << "\n\t\t*********************************\n";
	cout << "\t\t�� 1.����Ʒ�����Ʋ���\n\t\t�� 2.����Ʒ��Ų���";
	cout << "\n\t\t*********************************\n��ѡ��";
	cin >> x;
	switch (x)
	{
	case 1:
	{
		cout << "\t\t������Ҫ���ҵ���Ʒ�����ƣ�";
		cin >> name;
		if (p = FindItem(name))
		{
			p->Next->Show();
			cout << "���������ַ�����������";
			getch();
		}
		else
		{
			cout << "\t\tû���ҵ�����Ʒ��Ϣ��" << '\n' << endl;
			cout << "���������ַ�����������";
			getch();
		}
	}
	break;
	case 2:
	{
		cout << "\t\t������Ҫ���ҵ���Ʒ��ţ�";
		cin >> Num;
		if (p = FindNum(Num))
		{
			p->Next->Show();
			cout << "���������ַ�����������";
			getch();
		}
		else
		{
			cout << "\t\tû���ҵ��ñ�ŵ���Ʒ��" << '\n' << endl;
			cout << "���������ַ�����������";
			getch();
		}
	}
	break;
	}
}
void Supermarketmassage::ModifyItem()//�޸���Ϣ
{
	char name[20];
	Supermarket* p = NULL;
	cout << "\t\t������Ҫ�޸ĵ���Ʒ��:";
	cin >> name;
	if (p = FindItem(name))
	{
		cout << "\t\t���ҵ���Ʒ����Ϣ���������µ���Ϣ!" << endl;
		p->Next->Input();
		cout << "�޸ĳɹ���" << endl;
		cout << "���������ַ�����������";
		getch();
	}
	else
	{
		cout << "\t\tû���ҵ�!" << endl;
		cout << "���������ַ�����������";
		getch();
	}
}
void Supermarketmassage::RemoveItem()// ɾ����Ϣ
{
	int date(int&, int&, int&);
	int year1, month1, day1, year2, month2, day2, sum1, sum2, SUM;
	cout << "��������Ʒ�Ľ�������ڣ�(�ꡢ�¡���)";
	cin >> year1 >> month1 >> day1;
	sum1 = date(year1, month1, day1);
	cout << "��������Ʒ�Ľ�ֹ���ڣ�(�ꡢ�¡���)";
	cin >> year2 >> month2 >> day2;
	sum2 = date(year2, month2, day2);
	SUM = sum2 - sum1;
	if (SUM >= 30)
	{
		cout << "����Ʒ���ڰ�ȫ�ڣ����ô���~" << endl;
	}
	else
	{
		char name[20];
		Supermarket* p = NULL, * temp = NULL;
		cout << "\t\t������Ҫɾ������Ʒ��:" << endl;
		cin >> name;
		if (p = FindItem(name))
		{
			temp = p->Next;
			p->Next = p->Next->Next;
			delete temp;
			cout << "\t\tɾ���ɹ�!" << endl;
			cout << "���������ַ�����������";
			getch();
		}
		else
		{
			cout << "\t\tû���ҵ�!" << endl;
			cout << "���������ַ�����������";
			getch();
		}
	}
}
int date(int& day, int& month, int& year)   //���ں���
{
	int sum, leap;
	switch (month)                     		//�ȼ���ĳ����ǰ�·ݵ�������
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
	sum = sum + day; //�ټ���ĳ�������
	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))//�ж��ǲ�������
		leap = 1;
	else
		leap = 0;
	if (leap == 1 && month > 2)    			//������������·ݴ���2��������Ӧ�ü�һ��
		sum++;
	return sum;
}
void Supermarketmassage::sale()  //���ۺ���
{
	Supermarket a;
	Supermarket* p = NULL;
	int m;
	char name[20], Num[10];
	cout << "��������Ҫ���۵���Ʒ��Ϣ��" << endl;
	cout << "\n\t\t*********************************\n";
	cout << "\t\t�� 1.����Ʒ�����Ʋ���\n\t\t�� 2.����Ʒ��Ų���";
	cout << "\n\t\t*********************************\n��ѡ��";
	cin >> m;
	switch (m)
	{
	case 1:
	{
		cout << "\t\t������Ҫ���ҵ���Ʒ�����ƣ�";
		cin >> name;
		if (p = FindItem(name))
		{
			cout << "������Ҫ���۵�������";
			cin >> number;
			if (number <= Enum1)
			{
				cout << "���۳ɹ�!" << endl;
				cout << "���������ַ�����������";
				getch();
			}
			else
			{
				cout << "��治�㣬����������!" << endl;
				cout << "���������ַ�����������";
				getch();
			}
		}
		else
		{
			cout << "\t\tû���ҵ�!" << endl;
			cout << "���������ַ�����������";
			getch();
		}

	}
	break;
	case 2:
	{cout << "\t\t������Ҫ���ҵ���Ʒ�ı�ţ�";
	cin >> Num;
	if (p = FindNum(Num))
	{
		cout << "������Ҫ���۵�������";
		cin >> number;
		if (number <= Enum1)
		{
			cout << "���۳ɹ�!" << endl;
			cout << "���������ַ�����������";
			getch();
		}
		else
		{
			cout << "��治�㣬����������!" << endl;
			cout << "���������ַ�����������";
			getch();
		}
	}
	else
	{
		cout << "\t\tû���ҵ�!" << endl;
		cout << "���������ַ�����������";
		getch();
	}
	}
	break;
	}
}

void Supermarketmassage::Swap(Supermarket* p1, Supermarket* p2)//��������combox������������
{
	Supermarket* temp = new Supermarket;
	strcpy(temp->name, p1->name);  //�ַ���name����
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
int Supermarketmassage::ListCount()//ͳ�Ƶ�ǰ����ļ�¼����������һ������
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
void Supermarketmassage::Sort()//�Ե�ǰ�����������
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
	cout << "������ɣ�" << endl;
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
void xinxing()   //ϵͳ��ʼ������ͼ��
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
void logo()    //����ϵͳ�Ŀ�ͷ
{
	int i;
	cout << "\t\t���������������������������" << endl;
	for (i = 0; i < 3; i++)
		cout << "\t\t��\t\t\t\t\t\t  ��" << endl;
	cout << "\t\t����  ��ӭ����У԰������Ʒ����ϵͳ  �������" << endl;
	for (i = 0; i < 3; i++)
		cout << "\t\t��\t\t\t\t\t\t  ��" << endl;
	cout << "\t\t���������������������������\n" << endl;
}
int mai()
{
	system("color E");
	int x;
	bool quit = false;
	xinxing();
	logo();
	Supermarketmassage Grade;
	cout << "���������ʼ����";
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
			cout << "��ӭ�´�ʹ��~" << endl;
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