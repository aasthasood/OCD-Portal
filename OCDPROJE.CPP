#include<fstream.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>


char passcheck(char pass[])
{
	char res='y', chk1='n', chk2='n';
	if ( strlen(pass)<6 || strlen(pass)>20 )
	{
		cout<<"Check string length.\n";
		res='n';
	}

	for (int i=0; i<strlen(pass); i++)
	{
		if (pass[i]>='A' && pass[i]<='Z')
			chk1='y';
		if (pass[i]>='0' && pass[i]<='9')
			chk2='y';
	}
	if (chk1=='n')
		{
			cout<<"You need to use an uppercase letter.\n";
			res='n';
		}
	if (chk2=='n')
		{
			cout<<"You need to use a number.\n";
			res='n';
		}

	return res;
}
int quiz()
{
	int ans, total=0, i, j;
	float perc;
	char str[150];
	cout<<"\nTake this six question quiz to find out if you have OCD. Be honest!\n\n";
	ifstream infile("OCDQuiz.txt");
	for (i=1; i<=6; i++)
	{
		for (j=1; j<=6; j++)
		{
			infile.getline(str, 150, '\n');
			cout<<str<<endl;
		}
		cout<<endl;
		cout<<"Answer : ";
		cin>>ans;
		total += (ans-1);
		cout<<endl;
	}
	infile.close();
	perc=(total/24.0)*100;
	return perc;
}
char* medicine_name(int age)
{
	char *medn;
	if (age<18)
		strcpy(medn, "Xanaxe");
	else if (age<40)
		strcpy(medn, "Prozac");
	else
		strcpy(medn, "Valium");
	return medn;
}

int medicine_amt(float bmi)
{
	int amount;
	if (bmi<18.5)
		amount=10;
	else if (bmi<25)
		amount=15;
	else
		amount=20;

	return amount;
}

char* psych_name(float income)
{
	char name[20];
	if (income<20000)
		strcpy(name, "Anjali");
	else if (income<100000)
		strcpy(name, "Aastha");
	else
		strcpy(name, "Ananya");
	return name;
}

class patient
{
	private:
	char name[20], password[20];
	float age, income, bmi;
	int quizres, medamt;
	char psychname[20], medname[20];

	public:
	char input();
	void output();
	char* retname()
	{
		return name;
	}
	int retquiz()
	{
		return quizres;
	}
};

char patient::input()
	{
		char res='y';
		float weight, height;
		clrscr();
		cout<<"Enter your name : ";
		gets(name);
		cout<<"Enter your age : ";
		cin>>age;
		cout<<"Enter your weight (kg) : ";
		cin>>weight;
		cout<<"Enter your height (cm) : ";
		cin>>height;
		cout<<"Enter your monthly income : ";
		cin>>income;
		cout<<"Enter a password.\nThis password must be 6-20 characters long and must contain atleast one uppercase letter and one number.\n";
		gets(password);
		while (passcheck(password)!='y')
		{
			cout<<"Try again!\n";
			cin>>password;
		}


		bmi=weight/(pow(height/100, 2));
		quizres=quiz();
		cout<<"\nOCD percentage based on quiz : "<<quizres<<"%\n";
		if (quizres>=70)
		{
			strcpy (medname, medicine_name(age));
			cout<<"Medicine name : "<<medname<<endl;
			medamt=medicine_amt(bmi);
			cout<<"Medicine amount : "<<medamt<<" g"<<endl;
		}
		if (quizres>=40)
		{
			strcpy (psychname, psych_name(income));
			cout<<"Psychologist name : "<<psychname<<endl;
		}
		else
			res='n';

		return res;
}

void patient::output()
{
	if (quizres>=70)
	{
		char chkpass[20];
		cout<<"\nClassified account belonging to "<<name<<".\n";
		cout<<"Enter password : ";
		gets(chkpass);
		if (strcmp(chkpass, password) != 0)
		{
			cout<<"Access denied.";
			break;
		}
	}
	cout<<"\n******************** Patient Details ********************\n";
	cout<<"Patient name : "<<name<<endl;
	cout<<"Age : "<<age<<endl;
	cout<<"Body Mass Index : "<<bmi<<endl;
	cout<<"Income : "<<income<<endl;
	cout<<"OCD Percentage : "<<quizres<<"%"<<endl;
	cout<<"Psychologist name : "<<psychname<<endl;
	if (quizres>=70)
	{
		cout<<"Medicine name : "<<medname<<endl;
		cout<<"Medicine amount : "<<medamt<<endl;
	}
	cout<<"*********************************************************\n\n";
}

char ans;
patient p1, p2;
fstream file, temp;


void create()
{
	file.open("ocd.dat", ios::out| ios::binary);
	do
	{
		char res = p1.input();
		if (res == 'y')
			file.write((char*)&p1,sizeof(p1));
		else
			cout<<"You're OCD free. Enjoy your life! :)\n";
		cout<<"Do you wanna write another record? y/n ";
		cin>>ans;
		clrscr();
	}while (ans=='y' || ans=='Y');
	file.close();
}

void show()
{
	file.open("ocd.dat", ios::in | ios::binary);
	while (file.read((char*)&p1, sizeof(p1)))
	{
		p1.output();
	}
	file.close();
}

void append()
{
	file.open("ocd.dat", ios::app | ios::binary);
	do
	{
		cout<<endl;
		p1.input();
		file.write((char*)&p1, sizeof(p1));
		cout<<"Do you want to enter another record? y/n ";
		cin>>ans;
	}while (ans=='y' || ans=='Y');
	file.close();
}

void search()
{
	file.open("ocd.dat", ios::in | ios::binary);
	char pname[20];
	int flag=0;
	cout<<"Enter name to be searched for : ";
	gets(pname);
	while (file.read((char*)&p1, sizeof(p1)))
	{
		if (strcmp(pname, p1.retname())==0)
		{
			p1.output();
			flag=1;
			break;
		}
	}
	if (flag==0)
		cout<<"Name not found.\n";
	file.close();
}

void editrec()
{
	file.open("ocd.dat", ios::in | ios::binary);
	temp.open("new.dat", ios::out| ios::binary);
	int r=0, er;
	cout<<"Enter record number to be edited : ";
	cin>>er;
	file.seekg(0);
	while (file.read((char*)&p2, sizeof(p2)))
	{
		r++;
		if (r==er)
		{
			cout<<"Enter new details :\n";
			p1.input();
			temp.write((char*)&p1, sizeof(p1));
		}
		else
			temp.write((char*)&p2, sizeof(p2));
	}
	temp.close();
	file.close();
	remove("ocd.dat");
	rename("new.dat", "ocd.dat");
}

void editname()
{
	file.open("ocd.dat", ios::in | ios::binary);
	temp.open("new.dat", ios::out| ios::binary);
	char pname[20];
	cout<<"Enter name of account to be edited : ";
	gets(pname);
	file.seekg(0);
	while (file.read((char*)&p2, sizeof(p2)))
	{
		if (strcmp(pname, p2.retname())==0)
		{
			cout<<"Enter the new details :\n";
			p1.input();
			temp.write((char*)&p1, sizeof(p1));
		}
		else
			temp.write((char*)&p2, sizeof(p2));
	}
	temp.close();
	file.close();
	remove("ocd.dat");
	rename("new.dat", "ocd.dat");
}

void countrec()
{
	int r=0;
	file.open("ocd.dat", ios::in | ios::binary);
	while (file.read((char*)&p1, sizeof(p1)))
	{
		++r;
	}
	file.close();
	cout<<"The total number of records are : "<<r<<endl;
}

void countmod()
{
	int r=0;
	file.open("ocd.dat", ios::in | ios::binary);
	while (file.read((char*)&p1, sizeof(p1)))
	{
		if (p1.retquiz()<70 && p1.retquiz()>=40)
		++r;
		p1.output();
	}
	file.close();
	cout<<"The total number of account holders with moderate OCD are : "<<r<<endl;
}

void deletelast()
{
	file.open("ocd.dat", ios::in | ios::binary);
	temp.open("new.dat", ios::out| ios::binary);
	file.seekg(0, ios::end);

	int lp=file.tellg();
	int s=sizeof(p1);
	int lr=lp/s;
	int r=1;

	file.seekg(0);

	while (file.read((char*)&p2, sizeof(p2)))
	{
		if (r!=lr)
			temp.write((char*)&p2, sizeof(p2));
		r++;
	}
	cout<<"Record deleted.\n";
	temp.close();
	file.close();
	remove("ocd.dat");
	rename("new.dat", "ocd.dat");
}

void deleterec()
{
	file.open("ocd.dat", ios::in | ios::binary);
	temp.open("new.dat", ios::out| ios::binary);
	int r=1, dr;
	cout<<"Enter record number to delete : ";
	cin>>dr;
	file.seekg(0);
	while (file.read((char*)&p1, sizeof(p1)))
	{
		if (r!=dr)
			temp.write((char*)&p1, sizeof(p1));
		r++;
	}
	cout<<"Record deleted.\n";
	temp.close();
	file.close();
	remove("ocd.dat");
	rename("new.dat", "ocd.dat");
}

void insertfirst()
{
	file.open("ocd.dat", ios::in | ios::binary);
	temp.open("new.dat", ios::out| ios::binary);
	cout<<"Enter new details :\n";
	p1.input();
	temp.write((char*)&p1, sizeof(p1));
	while (file.read((char*)&p2, sizeof(p2)))
	{
		temp.write((char*)&p2, sizeof(p2));
	}
	temp.close();
	file.close();
	remove("ocd.dat");
	rename("new.dat", "ocd.dat");
}

void insertname()
{
	file.open("ocd.dat", ios::in | ios::binary);
	temp.open("new.dat", ios::out| ios::binary);
	char pname[20];
	cout<<"Enter new details :\n";
	p1.input();
	cout<<"Enter the name after which a new record is to be inserted : ";
	gets(pname);
	file.seekg(0);
	while (file.read((char*)&p2, sizeof(p2)))
	{
		if (strcmp(p2.retname(), pname)!=0)
			temp.write((char*)&p2, sizeof(p2));
		else
		{
			temp.write((char*)&p2, sizeof(p2));
			temp.write((char*)&p1, sizeof(p1));
		}
	}
	temp.close();
	file.close();
	remove("ocd.dat");
	rename("new.dat", "ocd.dat");
}

void main()
{
	clrscr();
	int ch;
	char ch1;
	cout<<"\nObsessive Compulsive Disorder is an anxiety disorder characterized by persistent, unreasonable thoughts and fears (obsessions) that lead you to perform repetitive behaviours (compulsions).";
	cout<<"\nUse the OCD Portal to manage accounts of persons suffering from OCD.";
	cout<<"\nIf a person has 70% OCD or greater, they may need immediate medical assistance as well as psychological counseling.";
	cout<<"\nIf a person has 40% - 70% OCD, their OCD is considered moderate and can be treated by psychological counseling.";
	cout<<"\nIf a person has less than 40% OCD, they are perfectly normal and will not be registered on the OCD portal.";
	getch();

	do
	{
		clrscr();
		cout<<"********************** OCD Portal **********************\n";
		cout<<"Press 1 to create a new account."<<endl;
		cout<<"Press 2 to show all the accounts' details."<<endl;
		cout<<"Press 3 to append an account to the file."<<endl;
		cout<<"Press 4 to search on the basis of patient name."<<endl;
		cout<<"Press 5 to edit details of the nth account."<<endl;
		cout<<"Press 6 to edit an account having user given name."<<endl;
		cout<<"Press 7 to count the total number of records."<<endl;
		cout<<"Press 8 to count the number of people with moderate OCD."<<endl;
		cout<<"Press 9 to delete the last account."<<endl;
		cout<<"Press 10 to delete the nth account."<<endl;
		cout<<"Press 11 to insert an account as the first account."<<endl;
		cout<<"Press 12 to insert an account at a user given position."<<endl;
		cout<<"Enter your choice : ";
		cin>>ch;

		clrscr();
		switch(ch)
		{
			case 1:	create();
				break;
			case 2: show();
				break;
			case 3: append();
				break;
			case 4: search();
				break;
			case 5: editrec();
				break;
			case 6: editname();
				break;
			case 7: countrec();
				break;
			case 8: countmod();
				break;
			case 9: deletelast();
				break;
			case 10:deleterec();
				break;
			case 11:insertfirst();
				break;
			case 12:insertname();
				break;
		}
		cout<<"Do you want to go back to the OCD Portal? y/n ";
		cin>>ch1;
	}while(ch1=='y');
}









