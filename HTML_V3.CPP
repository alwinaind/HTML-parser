#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<conio.h>
#include<ctype.h>
#include<dos.h>
class attribute
{	private:
		char n[15];
		char* name;
		char tags[15][15];
		char *tag[15];
	public:
		void in();
		void out();
		char *rettag();
		char *retname();
};
long l1=sizeof(attribute);
void attribute::in()
{
	cout<<"\n Enter the name of attribute \n";
	cin>>n;
	for(int i=0;i<15;i++)
	{
		cout<<"\n Enter tag "<<i+1<<endl;
		cin>>tags[i];
		if((strcmp(tags[i],"stop"))==0)
		{
			break;
		}
		else if((strcmp(tags[i],"global"))==0)
		{
			strcpy(tags[i+1],"stop");
			break;
		}
	}
	for(int j=0;j<=i;j++)
	tag[j]=tags[j];
	name=n;
}
void attribute::out()
{
	cout<<"\n Attribute name:\t"<<name;
	cout<<"\n Tags:\n";
	for(int i=0;tags[i]!="stop";i++)
	{
		cout<<"\t"<<tags[i];
	}
}
char *attribute::rettag()
{
	return tag[0];
}
char *attribute::retname()
{
	return name;
} 

class tag
{
       char name[20];
       int type;
     public:
       void in();
       void out();
       char *retname();
       int rettype()
       { return type;}
};
void tag::in()
{
   cout<<"\nNew tag\nEnter name of tag: ";
   cin>>name;
   cout<<"\nEnter type of tag (0-Empty;1-Container)";
   cin>>type;
}
void tag::out()
{
   cout<<"\n"<<name<<"\t"<<type;
}
char *tag::retname()
{
     char*p;
     p=name;
     return p;
}

void writ(char filename[])
{
	char str[1000];
	fstream f1, f2;
	f1.open(filename,ios::in|ios::binary);
	if(f1.fail())
	{
		cerr<<"\nError 100(For details go to errors option)";//Error 100
		getch();
		exit(100);
	}
	f2.open("edit.txt",ios::app|ios::binary);
	if(f2.fail())
	{
		cerr<<"\nError 101(For details go to errors option)";//Error 101
		getch();
		exit(100);
	}
	while(!f1.eof())
	{
		f1.getline(str,1000,'\n');
		f2<<str;
	}
	f1.close();
	f2.close();
}

void check_html()
{
	char htmlo[6],htmlc[8],str[1000];
	fstream f;
	int j,i;
	f.open("edit.txt",ios::in|ios::binary);
	if(f.fail())
	{
		cerr<<"\nError 101(For details go to errors option)";//Error 101
		getch();
		exit(100);
	}
	f.getline(str,1000,'>');
	j=strlen(str);
	str[j]='>';
	if(str[0]!='<'||str[1]!='h'||str[2]!='t'||str[3]!='m'||str[4]!='l'||str[5]!='>')
	{
		cout<<"\n <html> tag missing\n";
	}
	f.seekg(-8,ios::end);
	f.getline(htmlc,8,'>');
	j=strlen(htmlc);
	htmlc[j]='>';
	if(htmlc[j-6]!='<'||htmlc[j-5]!='/'||htmlc[j-4]!='h'||htmlc[j-3]!='t'||htmlc[j-2]!='m'||htmlc[j-1]!='l'||htmlc[j]!='>')
	{
		cout<<"\n </html> tag missing\n";
	}
	f.close();
}

void check_name_attribute()
{
	int c=0,i,j,k,m,s1,s2,s3,at,atcount,f=0,g1,g2,g3,n;
	char tagname[10],str[1000],tag[10],attri1[20],attri2[20],attri3[20];
	char* p;char* name;
	fstream f1,f2,f3;
	f1.open("edit.txt",ios::in|ios::binary);
	if(f1.fail())
	{
		cerr<<"\nError 101(For details go to errors option)";//Error 101
		getch();
		exit(100);
	}
	f2.open("tag.txt",ios::in|ios::binary);
	if(f2.fail())
	{
		cerr<<"\nError 102(For details go to errors option)";//Error 102
		getch();
		exit(100);
	}
	f3.open("attribute.txt",ios::in|ios::binary);
	if(f2.fail())
	{
		cerr<<"\nError 103(For details go to errors option)";//Error 103
		getch();
		exit(100);
	}
	while(!f1.eof())
	{
		attribute a;
		f1.getline(str,1000,'\0');
		for(i=0;str[i]!='\0';i++)
		{
			f=0;
			at=0;
			atcount=0;
			g1=g2=g3=0;
			if(str[i]=='<')
			{
				c=0;
				for(j=i+1,k=0;str[j]!='\0'&&str[j]!='>';j++)
				{	at=0;
					tagname[k++]=str[j];
					if(str[j]==' ')
					{
						at++;
						f=1;
						break;
					}
				}
				tagname[k]='\0';
				if(at)
				{
					for(n=0;str[j]!='=';n++)
					{
						j++;
						attri1[n]=str[j];
					}
					atcount++;
					while(str[j]!=' ')
					{
						if(str[j]=='>')
						{
							at--;
							break;
						}
					}
					if(at)
					{
						for(n=0;str[j]!='=';n++)
						{
							j++;
							if(str[j]=='>')
							{
								at--;
								break;
							}
							attri2[n]=str[j];
						}
						attri2[n]='\0';
						atcount++;
					}
					if(at)
					{
						for(n=0;str[j]!='=';n++)
						{
							j++;
							if(str[j]=='>')
							{
								at--;
								break;
							}
							attri3[n]=str[j];
						}
						attri3[n]='\0';
						atcount++;
					}
				}
				while(f2.read((char*)&tag,10))
					{
						if(strcmp(tag,tagname)==0)
						c++;
					}
					f2.clear();
					f2.seekg(0,ios::beg);
				if(c==0)
				{
					cout<<"\n Illegal tagname "<<tagname<<endl;
					break;
				}
				if(f)
				{
					if(atcount==1)			//when there is only one attribute
					{
						while(f3.read((char*)&a,l1))
						{
							name=a.retname();
							if((strcmp(name,attri1))==0)
							{
								s1=0;
								p=a.rettag();
								for(m=0;m<16;m++)
								{	
									char *n=p;
									if((strcmp(n,"global"))==0)
									{
										s1=1;
										break;
									}
									if((strcmp(n,tagname))==0)
									{
										s1=1;
										break;
									}
									if((strcmp(n,"stop"))==0)
									{
										break;
									}
									p++;
								}
								if(s1)
								{
									break;
								}
								g1++;
							}
						}
						f3.clear();
						f3.seekg(0,ios::beg);
					}
					if(atcount==2)				//when there are 2 attributes
					{
						while(f3.read((char*)&a,l1))
						{
							name=a.retname();
							if((strcmp(name,attri1))==0)
							{
								s1=0;
								p=a.rettag();
								for(m=0;m<16;m++)
								{
									char *n=p;
									if((strcmp(n,"global"))==0)
									{
										s1=1;
										break;
									}
									if((strcmp(n,"stop"))==0)
									{
										break;
									}
									if((strcmp(n,tagname))==0)
									{
										s1=1;
										break;
									}
									p++;
								}
								if(s1)
								{
									break;
								}
								g1++;
							}
						}
						f3.clear();
						f3.seekg(0,ios::beg);
						while(f3.read((char*)&a,l1))
						{
							name=a.retname();
							if((strcmp(name,attri2))==0)
							{
								s2=0;
								p=a.rettag();
								for(m=0;m<16;m++)
								{
									char *n=p;
									if((strcmp(n,"global"))==0)
									{
										s2=1;
										break;
									}
									if((strcmp(n,tagname))==0)
									{
										s2=1;
										break;
									}
									if((strcmp(n,"stop"))==0)
									{
										break;
									}
									p++;
								}
								if(s2)
								{
									break;
								}
								g2++;
							}
						}
						f3.clear();
						f3.seekg(0,ios::beg);
					}
					if(atcount==3)
					{
						while(f3.read((char*)&a,l1))
						{
							name=a.retname();
							if((strcmp(name,attri1))==0)
							{
								s1=0;
								p=a.rettag();
								for(m=0;m<16;m++)
								{
									char *n=p;
									if((strcmp(n,"global"))==0)
									{
										s1=1;
										break;
									}
									if((strcmp(n,tagname))==0)
									{
										s1=1;
										break;
									}
									if((strcmp(n,"stop"))==0)
									{
										break;
									}
									p++;
								}
								if(s1)
								{
									break;
								}
								g1++;
							}
						}
						f3.clear();
						f3.seekg(0,ios::beg);
						while(f3.read((char*)&a,l1))
						{
							name=a.retname();
							if((strcmp(name,attri2))==0)
							{
								s2=0;
								p=a.rettag();
								for(m=0;m<16;m++)
								{
									char *n=p;
									if((strcmp(n,"global"))==0)
									{
										s2=1;
										break;
									}
									if((strcmp(n,"stop"))==0)
									{
										break;
									}

									if((strcmp(n,tagname))==0)
									{
										s2=1;
										break;
									}
									p++;
								}
								if(s2)
								{
									break;
								}
								g2++;
							}
						}
						f3.clear();
						f3.seekg(0,ios::beg);
						while(f3.read((char*)&a,l1))
						{
							name=a.retname();
							if((strcmp(name,attri3))==0)
							{
								s3=0;
								p=a.rettag();
								for(m=0;m<16;m++)
								{
									char *n=p;
									if((strcmp(n,"global"))==0)
									{
										s3=1;
										break;
									}
									if((strcmp(n,"stop"))==0)
									{
										break;
									}
									if((strcmp(n,tagname))==0)
									{
										s3=1;
										break;
									}
									p++;
								}
								if(s3)
								{
									break;
								}
								g3++;
							}
						}
						f3.clear();
						f3.seekg(0,ios::beg);

					}

				if(atcount==3)
				{
					if(g1)
					{
						if(g2)
						{
							if(g3)
							{		//the tag doesn't belong to any of the attributes
								
									cout<<"\n Illegal use of "<<attri1<<" attribute";
									cout<<"\n Illegal use of "<<attri2<<" attribute";
									cout<<"\n Illegal use of "<<attri3<<" attribute";
							}
							else
							{	//the tag belongd to the third attribute
								
									cout<<"\n Illegal use of "<<attri1<<" attribute";
									cout<<"\n Illegal use of "<<attri2<<" attribute";
							}
						}
						else
						{	//atrri1 wrong attri2 right
							cout<<"\n Illegal attribute name "<<attri1;
							if(s3==0)
								{	//attri3 wrong
									cout<<"\n Illegal use of "<<attri3<<" attribute";
								}
						}
					}
					else
					{
						//attri1 right
						if(g2)
						{	//atrri2 wrong attri1 right
							if(g3)
							{		//attri1 right attri2 and attri3 wrong
							
									cout<<"\n Illegal use of "<<attri2<<" attribute";
									cout<<"\n Illegal use of "<<attri3<<" attribute";
							}
							else
							{	//attri1 and attri3 right attri2 wrong
								if(s2==0)
								{
									cout<<"\n Illegal use of "<<attri2<<" attribute";
								}
							}
						}
						else
						{		//attri1 and attri2 right 
								if(s3==0) 
								{	//attri3 wrong
									cout<<"\n Illegal use of "<<attri3<<" attribute";
								}// if<if> not occured then alright ma nigga
						}

					}
				}
				if(atcount==2)
				{
					if(g1)
					{
						if(g2)
						{	//the tag doesn't belong to any of the attributes
							cout<<"\n Illegal use of "<<attri1<<" attribute";
							cout<<"\n Illegal use of "<<attri2<<" attribute";
						}
						else
						{
							//attri2 right and attri1 wrong
								cout<<"\n Illegal use of "<<attri1<<" attribute";
						}

					}
					else
					{
						if(g2)
						{	//attri1 right attri2 wrong
								cout<<"\n Illegal use of "<<attri2<<" attribute";
						}
						// if<if> not occured then alright ma nigga
					}
				}
				if(atcount==1)
				{
					if(g1)
					{	//attri1 wrong
						cout<<"\n Illegal use of "<<attri1<<" attribute";
					}
				}
			}

		}
	}
	f1.close();
	f2.close();
	f3.close();
}
 }
void indent()
{
   struct node
   {
	tag info;
	node *next;
   };
   node *top=NULL,*t;
   fstream f1,f2;
   tag ctag;
   int check,check1,i,j;
   long l=sizeof(ctag);
   char str[1000],tagname[20];
   f1.open("edit.txt",ios::in|ios::binary);
   if(f1.fail())
   {
	cerr<<"\nError 101(For details go to errors option)";//Error 101
	getch();
	exit(400);
   }
   f2.open("tag.txt",ios::in|ios::binary);
   if(f2.fail())
   {
	cerr<<"\nError 102(For details go to errors option)";//Error 102
	getch();
	exit(400);
   }
   f1.seekg(0,ios::beg);
   f2.seekg(0,ios::beg);
   while(!f1.eof())
   {    check=0;
	check1=0;
	f1.getline(str,1000,'\0');
	for(i=0;str[i]!='\0';i++)
	{
	    if(str[i]=='<')
	    {    for(j=0;str[i]!=' '&&str[i]!='\0'&&str[i]!='>';j++,i++)
		 tagname[j]=str[i];
	    }
	}
	tagname[j]='\0';
	if(tagname[0]=='/')
	{
	    if(top==NULL)
	    {
		cerr<<"\n No Closing tag in the beginning";
	    }
	    else
	    { for(i=1;tagname[i-1]!='\0';i++)
	     {
		 tagname[i-1]=tagname[i];
	     }   //tag name has /removed from the beginning
		 f2.seekg(0,ios::beg);

	     while(!f2.eof())
	     {
		 f2.read((char*)&ctag,l);
		 if(strcmp(ctag.retname(),tagname)==0)
		 {

		     if(ctag.rettype()==0)
		     {
			cerr<<"\n"<<tagname<<" is not a closing tag";
		     }
		     else
		     {

			 if(strcmp(top->info.retname(),tagname)==0)
			 {
			     t=top->next;
			     delete top;
			     top=t;
			 }
			 else
			 {
			     cerr<<"\n"<<tagname<<" is closed at wrong position (intendation problem)";
			 }
		     }
		 }
		 else
		 {
		    cerr<<"\n"<<tagname<<" is illegal tag";
		 }
	     }
	    }
	     f2.clear();
	     f2.seekg(0,ios::beg);
	}	//end of deleting and check of "close tag"
	else if(isalpha(tagname[0])!=0)
	{  check1=1;
	   f2.seekg(0,ios::beg);
	   while(!f2.eof())
	   {
	       f2.read((char*)&ctag,l);
	      if(strcmp(ctag.retname(),tagname)==0)
	      {
		if(ctag.rettype()==0)
		{
		    check=1;
		}
		else
		{
		    check=1;
		    t=new node;
		    if(t==NULL)
		    {
		       cerr<<"\nError 105(For details go to errors option)";//Error 105
		       break;
		    }
		    t->info=ctag;
		    if(top==NULL)
		    {  t->next=NULL;
		       top=t;
		    }
		    else
		    {
		       t->next=top;
		       top=t;
		    }
		}  //else{type=1} close
	      }//if{tag is legal} close
	   }
	  if(check==0)
	  {
		   cout<<"\n"<<tagname<<" is illegal";
	  }
	}//closing if the tag is "open tag"
       if(check1==0)
       {
	   cerr<<"\n"<<tagname<<" is tag is illegal";
       }
   }//reading of the line from edit.txt ends here
   f1.close();
   f2.close();

}
void check_single_tag()
{
	int title=0,head=0,i=0,body=0,html=0,j=0,k=0;
	char str[100],tagname[100];
	fstream f;
	f.open("edit.txt",ios::in|ios::binary);
	while(!f.eof())
	{
	       f.getline(str,1000,'\0');
		for(i=0;str[i]!='\0';i++)
		{
			if(str[i]=='<')
			{
				for(j=i+1,k=0;str[j]!='\0'&&str[j]!='>';j++)
				{
					tagname[k++]=str[j];
					if(str[j]==' ')
					{
						break;
					}
				}
			       }
		}
	tagname[k]='\0';
	if(tagname[0]=='\\')
	{
	     for(i=1;tagname[i-1]!='\0';i++)
	     {
		 tagname[i-1]=tagname[i];
	     }   //tag name has /removed from the beginning
	}
	     if(strcmp(tagname,"title")==0)
		{title++;}

	     if(strcmp(tagname,"body")==0)
		{body++;}

	     if(strcmp(tagname,"head")==0)
		{head++;}

	     if(strcmp(tagname,"html")==0)
		{html++;}
	}
	if(html!=2)
	{cerr<<"\n <html> position wrong";}
	if(title!=2)
	{cerr<<"\n <title> position wrong";}
	if(body!=2)
	{cerr<<"\n <body> position wrong";}
	if(head!=2)
	{cerr<<"\n <head> positon worng";}
	f.close();
}
void check()
{
	clrscr();
	char file[100];
	cout<<"\n Enter file name \n";
	cin>>file;
	writ(file);
	check_html();
	check_single_tag();
	check_name_attribute();
	indent();
	getch();
	remove("edit.txt");
}
void add()
{	
	tag t;
	long l=sizeof(t);
	fstream f;
	f.open("tag.txt",ios::app,ios::binary);
	if(f.fail())
	{
		cerr<<"\nError 102(For details go to errors option)";//Error 102
		getch();
		exit(19);
	}
	cout<<"\n Enter tag name\n";
	t.in();
	f.write((char*)&t,l);
	f.close();
}
void del()
{
	tag t;
	char tagn[155];
	long l=sizeof(t);
	fstream f1,f2;
	f1.open("tag.txt",ios::in|ios::binary);
	if(f1.fail())
	{	
		cerr<<"\nError 102(For details go to errors option)";//Error 102
		getch();
		exit(19);
	}
	f2.open("temp.txt",ios::out|ios::binary);
	if(f2.fail())
	{
		cerr<<"\nError 104(For details go to errors option)";//Error 104
		getch();
		exit(19);
	}
	cout<<"\n Enter tag name\n";
	cin>>tagn;
	while(f1.read((char*)&t,l))
	{	
		char *p=t.retname();
		if(strcmp(p,tagn))
		{
			f2.write((char*)&t,l);
		}
	}
	f1.close();
	f2.close();
	rename("temp.txt","tag.txt");
	remove("temp.txt");
}
void view()
{
	tag t;
	long l=sizeof(t);
	fstream f;
	f.open("tag.txt",ios::in,ios::binary);
	if(f.fail())
	{
		cerr<<"\nError 102(For details go to errors option)";//Error 102
		getch();
		exit(19);
	}
	while(f.read((char*)&t,l))
	{
		t.out();
		cout<<endl;
	}
	f.close();
}
void tag()
{
	int option;
	char choice;
	do
	{
		clrscr();
		cout<<"\n 1. Add tags";
		cout<<"\n 2. Delete tags";
		cout<<"\n 3. View tags";
		cout<<"\n 4. Exit";
		cout<<"\n Enter the option: ";
		cin>>option;
		switch(option)
		{
			case 1:	add();
				break;
			case 2: del();
				break;
			case 3: view();
				break;
			case 4: exit(100);
				break;
			default: cout<<"\n Wrong choice";
			  	 getch();
		}
		cout<<"\n Would you like to continue? \n";
		cin>>choice;
	}
	while(choice=='y'||choice=='C');
}
void adda()
{
	attribute a;

	fstream f;
	f.open("attribute.txt",ios::app,ios::binary);
	if(f.fail())
	{
		cerr<<"\nError 103(For details go to errors option)";//Error 103
		getch();
		exit(19);
	}
	a.in();
	f.write((char*)&a,l1);
	f.close();
}
void dela()
{
	char att[100];
	attribute a;
	fstream f1,f2;
	f1.open("attribute.txt",ios::in|ios::binary);
	if(f1.fail())
	{
		cerr<<"\nError 103(For details go to errors option)";//Error 103
		getch();
		exit(19);
	}
	f2.open("temp.txt",ios::out|ios::binary);
	if(f2.fail())
	{
		cerr<<"\nError 104(For details go to errors option)";//Error 104
		getch();
		exit(19);
	}
	cout<<"\n Enter attribute to be deleted\n";
	cin>>att;
	while(f1.read((char*)&a,l1))
	{
		if(strcmp(att,a.retname()))
		{
			f2.write((char*)&a,10);
		}
	}
	f1.close();
	f2.close();
	rename("temp.txt","attribute.txt");
	remove("temp.txt");
}
void viewa()
{
	attribute a;
	fstream f;
	f.open("tag.txt",ios::in,ios::binary);
	if(f.fail())
	{
		cerr<<"\nError 103(For details go to errors option)";//Error 103
		getch();
		exit(19);
	}
	while(f.read((char*)&a,l1))
	{
		a.out();
	}
	f.close();
}
void attribute()
{

	int option;
	char choice;
	do
	{
		clrscr();
		cout<<"\n 1. Add attributes";
		cout<<"\n 2. Delete attributes";
		cout<<"\n 3. View attributes";
		cout<<"\n 4. Exit";
		cout<<"\n Enter the option: ";
		cin>>option;
		switch(option)
		{
			case 1:	adda();
				break;
			case 2: dela();
				break;
			case 3: viewa();
				break;
			case 4: exit(100);
				break;
			default: cout<<"\n Wrong choice";
			  	 getch();
		}
		cout<<"\n Would you like to continue? \n";
		cin>>choice;
	}
	while(choice=='y'||choice=='C');

}
void error() 
{
	int code;
	char opt;
	do
	{
		cout<<"\nEnter error code\n";
		cin>>code;
		switch(code)
		{
			case 100: cout<<"\n Given HTML file couldn't be opened";
				  getch();
			  break;
			case 101: cout<<"\n edit.txt file couldn't be opened";
				  getch();
				  break;
			case 102: cout<<"\n tag.txt file couldn't be opened";
				  getch();
				  break;
			case 103: cout<<"\n attribute.txt file couldn't be opened";
				  getch();
				  break;
			case 104: cout<<"\n temporary file for deletion of record couldn't be opened";
				  getch();
				  break;
			case 105: cout<<"\n System ran out of Memory, therefore dynamic allocation not possible";
				  getch();
				  break;
			default:  cout<<"\n Wrong error code";
			 	 getch();
		}
		cout<<"\n Would You Like To Continue?(Y/N)";
	cin>>opt;
	}
	while(opt=='y'||opt=='Y');
}

void main()
{
	clrscr();
	char opt;
	int a;
	int i;
	cout<<"\t\t\t Terms and conditions:\n";
	cout<<"\n1. Checking the HTML file in .txt format only";
	cout<<"\n2. Checks for atmost 3 attributes";
	cout<<"\n3. No spaces between \"<\" and \"tagname\" ";
	cout<<"\n5. Attribute value checking";
	cout<<"\n6. Case of the code should be small";
	cout<<"\n\nPress enter to accept and continue......";
	getch();
	clrscr();
	for(i=1;i<=100;i++)

	{ clrscr();
	  cout<<"\n\n\n\n\n\n\n\n\n\t\t\tLoading...";
	  switch(i%4)
	  {
	     case 0: cout<<"|";
		     break;
	     case 1: cout<<"/";
		     break;
	     case 2: cout<<"\\";
		     break;
	     case 3: cout<<"-";
		     break;
	  }
	  cout<<"  "<<i<<"%";delay(200);
	}
	do
	{	
		clrscr();
		
		cout<<"\n 1. Check HTML Code";
		cout<<"\n 2. Tags";
		cout<<"\n 3. Attributes";
		cout<<"\n 4. Errors";
		cout<<"\n 5. Exit";
		cout<<"\n Enter option: " ;
		cin>>a;
		switch(a)
		{
			case 1: check();
				break;
			case 2:	tag();
				break;
			case 3:	attribute();
				break;
			case 4: error();
				break;
			case 5:	exit(88);
			default: cout<<"\n Wrong choice";
			  	 getch();
		}
	cout<<"\n Would You Like To Continue?(Y/N)";
	cin>>opt;
	}
	while(opt=='y'||opt=='Y');
}