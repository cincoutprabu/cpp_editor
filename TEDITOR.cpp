// teditor.cpp

# include <iostream.h>
# include <graphics.h>
# include <string.h>
# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>
# include <conio.h>
# include <time.h>
# include <math.h>
# include <dos.h>
# include <dir.h>

# define FALSE 0
# define TRUE  1

// key scancode definition
# define ESCKEY		1
# define ENTERKEY		28
# define BACKSPACEKEY   	14
# define SPACEBARKEY    	57
# define TABKEY	    	15
# define F1KEY			59
# define F2KEY			60
# define F3KEY			61
# define F4KEY			62
# define F5KEY			63
# define F6KEY			64
# define F7KEY			65
# define F8KEY			66
# define F9KEY			67
# define F10KEY		68
# define LTARROWKEY		75
# define RTARROWKEY		77
# define UPARROWKEY		72
# define DNARROWKEY		80
# define INSERTKEY		82
# define DELETEKEY		83
# define HOMEKEY		71
# define ENDKEY		79
# define PGUPKEY        	73
# define PGDNKEY		81
# define CTRLHOMEKEY	119
# define CTRLENDKEY		117
# define CTRLPGUPKEY    	132
# define CTRLPGDNKEY	118

// menustr declaration
# define MAXPADS 5
char menustr[MAXPADS][10][30];
char hlpstr[MAXPADS][10][35];
int  menucol[MAXPADS]={3,9,15,23,31};
int  menurow[MAXPADS]={2,2,2,2,2};
int  menulines[MAXPADS]={10,8,7,4,4};
int	copt[MAXPADS]={1,1,1,1,1};
int  cpad=1;
long CLINE=1,CCOL=1;
void PrintLineCol();
void Edit();
void SetStatusString(char*);
int  SAVED;
void SaveFile();
void SaveFileAs();
void OpenFile();
void PrintFile();
void branch(int,int);
void main();

void Initialize_menustr()
{
	strcpy(menustr[0][0],"File");                       strcpy(hlpstr[0][0],"File operations");
	strcpy(menustr[0][1],"New        ^N");              strcpy(hlpstr[0][1],"Opens a new file");
	strcpy(menustr[0][2],"Open...    ^O");              strcpy(hlpstr[0][2],"Opens an existing file");
	strcpy(menustr[0][3],"-");                          strcpy(hlpstr[0][3],"-");
	strcpy(menustr[0][4],"Save       ^S");              strcpy(hlpstr[0][4],"Saves current file");
	strcpy(menustr[0][5],"Save As");                    strcpy(hlpstr[0][5],"Saves into a new file");
	strcpy(menustr[0][6],"-");                          strcpy(hlpstr[0][6],"-");
	strcpy(menustr[0][7],"Print...   ^P");              strcpy(hlpstr[0][7],"Print contents of current file");
	strcpy(menustr[0][8],"-");                          strcpy(hlpstr[0][8],"-");
	strcpy(menustr[0][9],"Quit       ^Q");              strcpy(hlpstr[0][9],"Quits to system");
	strcpy(menustr[1][0],"Edit");                       strcpy(hlpstr[1][0],"Editing operations");
	strcpy(menustr[1][1],"Cut          Shift+Del");     strcpy(hlpstr[1][1],"Removes and puts it in Clipboard");
	strcpy(menustr[1][2],"Copy          Ctrl+Ins");     strcpy(hlpstr[1][2],"Copies and puts it in Clipboard");
	strcpy(menustr[1][3],"Paste        Shift+Ins");     strcpy(hlpstr[1][3],"Inserts the Clipboard contents");
	strcpy(menustr[1][4],"Delete             Del");     strcpy(hlpstr[1][4],"Deltes the selected text");
	strcpy(menustr[1][5],"-");                          strcpy(hlpstr[1][5],"-");
	strcpy(menustr[1][6],"Select all          ^A");     strcpy(hlpstr[1][6],"Selects the entire text");
	strcpy(menustr[1][7],"Change case...      ^U");     strcpy(hlpstr[1][7],"Changes the case");
	strcpy(menustr[2][0],"Search");                     strcpy(hlpstr[2][0],"Searches for a text");
	strcpy(menustr[2][1],"Find...            ^F");      strcpy(hlpstr[2][1],"To find a text in the file");
	strcpy(menustr[2][2],"Find & Replace...  ^R");      strcpy(hlpstr[2][2],"To find & replace a text");
	strcpy(menustr[2][3],"Find next          ^L");      strcpy(hlpstr[2][3],"Finds the next occurance");
	strcpy(menustr[2][4],"-");                          strcpy(hlpstr[2][4],"-");
	strcpy(menustr[2][5],"Goto...            ^G");      strcpy(hlpstr[2][5],"Goes to a specified location");
	strcpy(menustr[2][6],"Bookmarks...       ^B");      strcpy(hlpstr[2][6],"Defines & restores Bookmarks");
	strcpy(menustr[3][0],"Insert");                     strcpy(hlpstr[3][0],"Inserts specified text");
	strcpy(menustr[3][1],"Auto Text   ");              strcpy(hlpstr[3][1],"Inserts some standard text");
	strcpy(menustr[3][2],"-");                          strcpy(hlpstr[3][2],"-");
	strcpy(menustr[3][3],"Date/Time");                  strcpy(hlpstr[3][3],"Inserts Date/Time into text");
	strcpy(menustr[4][0],"Help");                       strcpy(hlpstr[4][0],"Displays Help");
	strcpy(menustr[4][1],"Help Topics");                strcpy(hlpstr[4][1],"Displays Help Topics");
	strcpy(menustr[4][2],"-");                          strcpy(hlpstr[4][2],"-");
	strcpy(menustr[4][3],"About...");                   strcpy(hlpstr[4][3],"Displays Credits");
}

// SLINKED class declaration & definition
template <class T>
class SLINKED
{
	private:
		struct SNODE
		{
			T     data;
			SNODE *next;
		};
		SNODE *start;
		long  items;
	public:
		SLINKED();
		~SLINKED();
		long nitems();
		void insertnode(T,long);
		void addnode(T);
		void deletenode(long);
		void deleteallnodes();
		T    getnode(long);
		void setnode(T,long);
};
template <class T>
SLINKED<T>::SLINKED()
{
	start=NULL;
	items=0;
}
template <class T>
SLINKED<T>::~SLINKED()
{
	deleteallnodes();
}
template <class T>
long SLINKED<T>::nitems()
{
	return(items);
}
template <class T>
void SLINKED<T>::insertnode(T tdata,long pos)
{
	if(pos<1) tErrorf("pos<1, SLINKED::insertnode()");
	if(pos>items) tErrorf("pos>nitems, SLINKED::insertnode()");
	SNODE *n=new SNODE;
	n->data=tdata;
	SNODE *tmp,*prev;
	int i;
	for(tmp=start,prev=start,i=0;i<pos-1;prev=tmp,tmp=tmp->next,i++);
	n->next=tmp;
	if(tmp==start) start=n;
	else prev->next=n;
	items++;
}
template <class T>
void SLINKED<T>::addnode(T tdata)
{
	SNODE *n=new SNODE;
	n->data=tdata;
	n->next=NULL;
	SNODE *tmp,*prev;
	int i;
	for(tmp=start,prev=start,i=0;i<items;prev=tmp,tmp=tmp->next,i++);
	if(i==0) start=n;
	else prev->next=n;
	items++;
}
template <class T>
void SLINKED<T>::deletenode(long pos)
{
	if(pos<1) tErrorf("pos<1, SLINKED::delnode()");
	if(pos>items) tErrorf("pos>nitems, SLINKED::delnode()");
	SNODE *tmp,*prev;
	int i;
	for(tmp=start,prev=start,i=0;i<pos-1;prev=tmp,tmp=tmp->next,i++);
	prev->next=tmp->next;
	if(tmp==start) start=start->next;
	delete tmp;
	items--;
}
template <class T>
void SLINKED<T>::deleteallnodes()
{
	int titcnt=items;
	for(int i=titcnt;i>=1;i--) deletenode(i);
}
template <class T>
T SLINKED<T>::getnode(long pos)
{
	if(pos<1) tErrorf("pos<1, SLINKED::getnode()");
	if(pos>items) tErrorf("pos>nitems, SLINKED::getnode()");
	SNODE *tmp;
	int i;
	for(tmp=start,i=0;i<pos-1;tmp=tmp->next,i++);
	return(tmp->data);
}
template <class T>
void SLINKED<T>::setnode(T tdata,long pos)
{
	if(pos<1) tErrorf("pos<1, SLINKED::setnode()");
	if(pos>items) tErrorf("pos>nitems, SLINKED::setnode()");
	SNODE *tmp;
	int i;
	for(tmp=start,i=0;i<pos-1;tmp=tmp->next,i++);
	tmp->data=tdata;
}

// STACK class declaration & definition
template <class T>
class STACK
{
	private:
		SLINKED<T> slink;
		long       top;
	public:
		STACK();
		~STACK();
		STACK(T);
		long ntop();
		void pushnode(T);
		void popnode();
		void popallnodes();
		T    getnode(long);
		void setnode(T,long);
};
template <class T>
STACK<T>::STACK()
{
	top=0;
}
template <class T>
STACK<T>::~STACK()
{
	popallnodes();
}
template <class T>
STACK<T>::STACK(T tdata)
{
	pushnode(tdata);
}
template <class T>
long STACK<T>::ntop()
{
	return(top);
}
template <class T>
void STACK<T>::pushnode(T tdata)
{
	slink.addnode(tdata);
	top++;
}
template <class T>
void STACK<T>::popnode()
{
	slink.deletenode(top);
	top--;
}
template <class T>
void STACK<T>::popallnodes()
{
	int ttop=top;
	for(int i=ttop;i>=1;i--) popnode();
}
template <class T>
T STACK<T>::getnode(long pos)
{
	if(pos<1) tErrorf("pos<1, STACK::getnode()");
	if(pos>top) tErrorf("pos>ntop, STACK::getnode()");
	return(slink.getnode(pos));
}
template <class T>
void STACK<T>::setnode(T tdata,long pos)
{
	if(pos<1) tErrorf("pos<1, STACK::getnode()");
	if(pos>top) tErrorf("pos>ntop, STACK::getnode()");
	slink.setnode(tdata,pos);
}

// STR class declaration
class STR
{
	private:	char* str;
	public: 	STR();
			STR(int);
			STR(int,char);
			STR(char*);
			STR(STR&);
			~STR();
			char *getstr();
			void setstr(char*);
			void setstr(STR);
			char getchr(int);
			void setchr(int,char);
			STR  operator=(char*);
			STR& operator=(STR&);
			STR  operator+(STR);
			int  operator==(STR);
			int  operator!=(STR);
};

// STR functions declaration
int  Len(STR);
STR  Space(int);
int  Asc(char);
char Chr(int);
int  IsEmpty(char);
int  IsAlpha(char);
int  IsDigit(char);
int  IsUpper(char);
int  IsLower(char);
char Lower(char);
char Upper(char);
int  IsEmpty(STR);
int  IsAlpha(STR);
int  IsDigit(STR);
int  IsUpper(STR);
int  IsLower(STR);
STR  Lower(STR);
STR  Upper(STR);
STR  Proper(STR);
STR  Left(STR,int);
STR  Right(STR,int);
STR  SubSTR(STR,int,int);
STR  PadL(STR,int,char);
STR  PadL(STR,int);
STR  PadR(STR,int,char);
STR  PadR(STR,int);
STR  PadC(STR,int,char);
STR  PadC(STR,int);
STR  LTrim(STR);
STR  RTrim(STR);
STR  Trim(STR);
STR  AllTrim(STR);
STR  Replicate(char,int);
int  At(STR,STR,int);
int  At(STR,STR);
int  Occurs(STR,STR,int);
int  Occurs(STR,STR);
STR  STRTran(STR,STR,STR,int);
STR  STRTran(STR,STR,STR);
void PrintSTR(STR);
void tXYPrintSTR(int,int,STR,int,int);
void tEditSTR(STR&,int,int,int,int&,int&,int,int,int,int);

// DATE class declaration
STR daySTR[]={ "Sunday","Monday","Tuesday","Wednesday",
			"Thursday","Friday","Saturday" };
STR monthSTR[]={ "January","February","March","April","May","June","July",
			  "August","September","October","November","December" };
int monthdays[]={ 31,28,31,30,31,30,31,31,30,31,30,31 };

int SET_MARK='/';

class DATE
{
	private:	int d,m,y;
	public:	DATE();
			DATE(int,int,int);
			int  getday();
			int  getmonth();
			int  getyear();
			DATE operator+(int);
			DATE operator-(int);
			DATE operator++();
			DATE operator--();
			int  operator-(DATE);
			int  operator==(DATE);
			int  operator!=(DATE);
			int  operator<(DATE);
			int  operator<=(DATE);
			int  operator>(DATE);
			int  operator>=(DATE);
};

// DATE functions declaration
int  IsEmpty(DATE);
int  Day(DATE);
int  Month(DATE);
int  Year(DATE);
int  DOW(DATE);
STR  cDOW(DATE);
STR  cMonth(DATE);
DATE Date();
STR  DToC(DATE);
STR  DToS(DATE);
DATE CToD(STR);
DATE GoMonth(DATE,int);
STR  DMY(DATE);
STR  MDY(DATE);
int  Between(DATE,DATE,DATE);
void PrintDATE(DATE);
void tXYPrintDATE(int,int,DATE,int,int);

// common utils declaration
time_t tim1;
char *tSCROLL_TEXT="IT for Rural India";
int  CTRLFLAG=FALSE,ALTFLAG=FALSE,SHIFTFLAG=FALSE;
int  INSERT=TRUE;

void MakeSound(int,int);
void Beep();
void Quit();
void GetKey();
int  GetSCAN();
int  GetASCII();
int  IntLen(int);
int  Between(int,int,int);
int  Between(long,long,long);
void ToggleINSERT();

// tutils declaration
void InitializeTextScreen();
void tClearScreen();
void tScrollText(int,int,int,int,int);
void tBox(int,int,int,int,int,int,int);
void tBar(int,int,int,int,int,int);
void tHLine(int,int,int,int,int);
void tVLine(int,int,int,int,int);
void TextColor(int,int);
void tCursorOff();
void tCursorOn();
void tMsgBox(STR,STR);
int  tSpin(int,int,int,int,int,int,int,int,int);
int  tGetYesNo(int,int);
void tHMenu();

int  LEFTMOUSE=1,RIGHTMOUSE=2;
int  SINGLE_BORDER=0,DOUBLE_BORDER=1;
int  NORMALLINE=0,EDGEDLINE=1,SOUND_ON=1;
int  ASCIIC,SCANC,ESCC=-1,HELPMSG_LINE=25;

// STR class definition
STR::STR()
{
	str=NULL;
}
STR::STR(int tLen)
{
	str=new char[tLen+1];
	for(int i=0;i<tLen;i++) *(str+i)=32;
	*(str+tLen)='\0';
}
STR::STR(int tLen,char c)
{
	str=new char[tLen+1];
	for(int i=0;i<tLen;i++) *(str+i)=c;
	*(str+tLen)='\0';
}
STR::STR(char* tstr)
{
	str=new char[strlen(tstr)+1];
	strcpy(str,tstr);
}
STR::STR(STR& tstr) // copy constructor
{
	str=new char[strlen(tstr.getstr())+1];
	strcpy(str,tstr.getstr());
}
STR::~STR()
{
	delete str;
}
char* STR::getstr()
{
	return(str);
}
void STR::setstr(char* sstr)
{
	delete str;
	str=new char[strlen(sstr)+1];
	strcpy(str,sstr);
}
void STR::setstr(STR sstr)
{
	delete str;
	str=new char[strlen(sstr.getstr())+1];
	strcpy(str,sstr.getstr());
}
char STR::getchr(int i)
{
	return(*(str+i));
}
void STR::setchr(int i,char c)
{
	*(str+i)=c;
}
STR STR::operator=(char* tstr)
{
	setstr(tstr); //
	STR temp(tstr);
	return(temp);
}
STR& STR::operator=(STR& tstr)
{
	if(this==&tstr) return(*this);
	delete str;
	str=new char[strlen(tstr.getstr())+1];
	strcpy(str,tstr.getstr());
	return(*this);
}
STR STR::operator+(STR tstr)
{
	int l1=strlen(str),l2=strlen(tstr.getstr()),i;
	STR temp(l1+l2);
	for(i=0;i<l1;i++) temp.setchr(i,getchr(i));
	for(i=l1;i<l1+l2;i++) temp.setchr(i,tstr.getchr(i-l1));
	return(temp);
}
int STR::operator==(STR tstr)
{
	int l1=strlen(str),l2=strlen(tstr.getstr()),i;
	if(l1!=l2) return(FALSE);
	for(i=0;i<l1;i++) if(getchr(i)!=tstr.getchr(i)) return(FALSE);
	return(TRUE);
}
int STR::operator!=(STR tstr)
{
	int l1=strlen(str),l2=strlen(tstr.getstr()),i;
	if(l1!=l2) return(TRUE);
	for(i=0;i<l1;i++) if(getchr(i)!=tstr.getchr(i)) return(TRUE);
	return(FALSE);
}

// STR functions definition
int Len(STR tstr)
{
	return(strlen(tstr.getstr()));
}

STR Space(int nspc)
{
	STR temp(nspc);
	return(temp);
}

int Asc(char c)
{
	return(c);
}

char Chr(int n)
{
	return(n);
}

int IsAlpha(char c)
{
	c=c<=90?c+32:c;
	if(c>=97&&c<=122) return(TRUE); else return(FALSE);
}

int IsDigit(char c)
{
	if(c>=48&&c<=57) return(TRUE); else return(FALSE);
}

int IsLower(char c)
{
	if(c>=97&&c<=122) return(TRUE); else return(FALSE);
}

int IsUpper(char c)
{
	if(c>=65&&c<=90) return(TRUE); else return(FALSE);
}

int IsAlpha(STR tstr)
{
	for(int i=0;i<Len(tstr);i++) if(!IsAlpha(tstr.getchr(i))) return(FALSE);
	return(TRUE);
}

int IsDigit(STR tstr)
{
	for(int i=0;i<Len(tstr);i++) if(!IsDigit(tstr.getchr(i))) return(FALSE);
	return(TRUE);
}

int IsLower(STR tstr)
{
	for(int i=0;i<Len(tstr);i++) if(!IsLower(tstr.getchr(i))) return(FALSE);
	return(TRUE);
}

int IsUpper(STR tstr)
{
	for(int i=0;i<Len(tstr);i++) if(!IsUpper(tstr.getchr(i))) return(FALSE);
	return(TRUE);
}

char Lower(char c)
{
	return(IsUpper(c)?c+32:c);
}

char Upper(char c)
{
	return(IsLower(c)?c-32:c);
}

int IsEmpty(char c)
{
	return(c==32?TRUE:FALSE);
}

int IsEmpty(STR tstr)
{
	int i,l=Len(tstr);
	for(i=0;i<l;i++)
	{
		if(!IsEmpty(tstr.getchr(i)))
			return(FALSE);
	}
	return(TRUE);
}

STR Lower(STR tstr)
{
	STR temp=tstr;
	for(int i=0;i<Len(temp);i++) temp.setchr(i,Lower(temp.getchr(i)));
	return(temp);
}

STR Upper(STR tstr)
{
	STR temp=tstr;
	for(int i=0;i<Len(temp);i++) temp.setchr(i,Upper(temp.getchr(i)));
	return(temp);
}

STR Proper(STR tstr)
{
	int i,l1=Len(tstr);
	for(i=0;i<l1;)
	{
		for(;tstr.getchr(i)==32;i++);
		tstr.setchr(i,Upper(tstr.getchr(i)));
		for(;tstr.getchr(i)!=32;i++);
	}
	return(tstr);
}

STR Left(STR tstr,int l)
{
	int l1=Len(tstr); l=l>l1?l1:l; l=l1<=0?0:l; STR temp(l);
	for(int i=0;i<l;i++) temp.setchr(i,tstr.getchr(i));
	return(temp);
}

STR Right(STR tstr,int l)
{
	int l1=Len(tstr),i=l>l1?0:l1-l; i=l1<=0?0:i; STR temp(l1-i);
	for(int j=0;i<l1;i++,j++) temp.setchr(j,tstr.getchr(i));
	return(temp);
}

STR SubSTR(STR tstr,int st,int l)
{
	int l1=Len(tstr); if(st>l1||l1<=0||l<=0||st+l<=0) return("");
	l=st+l-1>l1?l1:st+l-1; STR temp(l-st+1);
	for(int i=0;st<=l;st++,i++) temp.setchr(i,tstr.getchr(st-1));
	return(temp);
}

STR PadL(STR tstr,int l,char c)
{
	int ln=Len(tstr),t=ln>l?0:l-ln; STR temp(t,c); return(temp+tstr);
}

STR PadL(STR tstr,int l)
{
	return(PadL(tstr,l,32));
}

STR PadR(STR tstr,int l,char c)
{
	int ln=Len(tstr),t=ln>l?0:l-ln; STR temp(t,c); return(tstr+temp);
}

STR PadR(STR tstr,int l)
{
	return(PadR(tstr,l,32));
}

STR PadC(STR tstr,int l,char c)
{
	int l1=Len(tstr); if(l1>l) return(tstr);
	int t=((l-l1)%2==0?(l-l1)/2:((l-l1)/2)+1);
	STR temp1(t,c),temp2(((t*2)+l1>l?t-1:t),c);
	return(temp1+tstr+temp2);
}

STR PadC(STR tstr,int l)
{
	return(PadC(tstr,l,32));
}

STR LTrim(STR tstr)
{
	for(int i=0;tstr.getchr(i)==32;i++);
	STR temp(tstr.getstr()+i); return(temp);
}

STR RTrim(STR tstr)
{
	int i,j,l1=Len(tstr); for(i=l1-1;tstr.getchr(i)==32;i--); i++;
	STR temp(i); for(j=0;j<i;j++) temp.setchr(j,tstr.getchr(j));
	return(temp);
}

STR Trim(STR tstr)
{
	return(RTrim(tstr));
}

STR AllTrim(STR tstr)
{
	STR temp=LTrim(tstr);
	return(RTrim(temp));
}

STR Replicate(char c,int n)
{
	STR temp(n,c);
	return(temp);
}

int At(STR tstr,STR tf,int nth)
{
	int i,l=Len(tstr),l1=Len(tf),tcnt=1;
	for(i=1;i<=l;i++)
		if(SubSTR(tstr,i,l1)==tf)
		{
			if(tcnt>=nth)
				return(i);
			tcnt++;
		}
	return(-1);
}

int At(STR tstr,STR tf)
{
	return(At(tstr,tf,1));
}

int Occurs(STR tstr,STR tf,int nst)
{
	int i,l=Len(tstr),l1=Len(tf),tcnt=0;
	for(i=nst+1;i<=l;i++)
		if(SubSTR(tstr,i,l1)==tf)
			tcnt++;
	return(tcnt);
}

int Occurs(STR tstr,STR tf)
{
	return(Occurs(tstr,tf,1));
}

STR STRTran(STR tstr,STR tf,STR tr,int nth)
{
	STR tret="";
	int i,l=Len(tstr),l1=Len(tf),tst=1,tcnt=1,replaced=FALSE;
	for(i=1;i<=l;i++)
		if(SubSTR(tstr,i,l1)==tf)
		{
			if(tcnt>=nth)
			{
				tret=tret+SubSTR(tstr,tst,i-tst);
				tst=i+l1;
				tret=tret+tr;
				replaced=TRUE;
			}
			tcnt++;
		}
	if(replaced) tret=tret+SubSTR(tstr,tst,l);
	else if(!replaced) tret=tstr;
	return(tret);
}

STR STRTran(STR tstr,STR tf,STR tr)
{
	return(STRTran(tstr,tf,tr,1));
}

void PrintSTR(STR tstr)
{
	cprintf("%s",tstr.getstr());
}

void tXYPrintSTR(int col,int row,STR tstr,int bgc,int fgc)
{
	TextColor(bgc,fgc);
	gotoxy(col,row);
	PrintSTR(tstr);
}

void ToggleINSERT()
{
	INSERT=INSERT?FALSE:TRUE;
	if(INSERT) tXYPrintSTR(75,25,"INS",7,0);
	else tXYPrintSTR(75,25,"   ",7,0);
}

int tSTRTerminateChars[]={ESCKEY,ENTERKEY,UPARROWKEY,DNARROWKEY,PGUPKEY,PGDNKEY,CTRLHOMEKEY,CTRLENDKEY,CTRLPGUPKEY,CTRLPGDNKEY};

void tEditSTR(STR &srcstr,int maxlen,int displen,int startpos,int &retkey,int &retpos,int col,int row,int bgc,int fgc)
{
	tCursorOn();
	int i,j,strpos=startpos;
	int key,flag;
	if(maxlen<Len(srcstr)) maxlen=Len(srcstr);
	if(displen>maxlen) displen=maxlen;
	if(maxlen-(startpos+1)<displen) startpos=maxlen-displen;
	STR tstr(maxlen);
	for(i=0;i<Len(srcstr);i++) tstr.setchr(i,srcstr.getchr(i));
	do
	{
		CCOL=strpos;
		PrintLineCol();
		TextColor(bgc,fgc);
		for(i=startpos,j=0;j<displen;i++,j++)
		{
			gotoxy(col+j,row);
			cprintf("%c",tstr.getchr(i));
		}
		gotoxy(col+strpos-startpos,row);
		GetKey();
		key=SCANC;
		flag=FALSE;
		for(i=0;i<sizeof(tSTRTerminateChars)/sizeof(int);i++)
		{
			if(key==tSTRTerminateChars[i])
			{
				flag=TRUE;
				break;
			}
		}
		if(flag) break;
		if(key==LTARROWKEY)
		{
			strpos--;
		}
		if(key==RTARROWKEY)
		{
			strpos++;
		}
		else if(key==HOMEKEY)
		{
			strpos=0;
			startpos=0;
		}
		else if(key==ENDKEY)
		{
			int t=maxlen-1;
			while(tstr.getchr(t)==32) t--;
			strpos=t+1;
			if(!Between(t,startpos,startpos+displen-1)) startpos=t;
		}
		else if(key==INSERTKEY)
		{
			ToggleINSERT();
		}
		else if(key==DELETEKEY)
		{
			for(i=strpos;i<maxlen-1;i++) tstr.setchr(i,tstr.getchr(i+1));
			tstr.setchr(maxlen-1,32);
			SAVED=FALSE;
		}
		else if(key==BACKSPACEKEY)
		{
			if(strpos!=0)
			{
				for(i=strpos-1;i<maxlen-1;i++) tstr.setchr(i,tstr.getchr(i+1));
				strpos--;
				tstr.setchr(maxlen-1,32);
			}
			SAVED=FALSE;
		}
		if(isprint(ASCIIC))
		{
			if(INSERT) for(i=maxlen-2;i>=strpos;i--) tstr.setchr(i+1,tstr.getchr(i));
			tstr.setchr(strpos,ASCIIC);
			strpos++;
			SAVED=FALSE;
		}
		if(strpos-startpos<0) startpos--;
		if(strpos-startpos>displen-1) startpos++;
		if(strpos<0) strpos=0;
		if(startpos<0) startpos=0;
		if(strpos>maxlen-1) strpos=maxlen-1;
		if(maxlen-(startpos+1)<displen) startpos=maxlen-displen;
	}while(TRUE);
	retkey=key;
	retpos=strpos;
	srcstr=AllTrim(tstr);
}

// DATE class definition
DATE::DATE()
{
	d=m=y=0;
}
DATE::DATE(int td,int tm,int ty)
{
	d=td; m=tm; y=ty;
}
int DATE::getday()
{
	return(d);
}
int DATE::getmonth()
{
	return(m);
}
int DATE::getyear()
{
	return(y);
}
DATE DATE::operator+(int t)
{
	int i,td=d,tm=m,ty=y;
	for(i=1;i<=t;i++)
	{
		monthdays[1]=ty%4==0?29:28;
		td++;
		if(td>monthdays[tm-1])
		{
			td=1;
			tm++;
			if(tm>12)
			{
				tm=1;
				ty++;
			}
		}
	}
	DATE tdt(td,tm,ty);
	return(tdt);
}
DATE DATE::operator++()
{
	monthdays[1]=y%4==0?29:28;
	d++;
	if(d>monthdays[m-1])
	{
		d=1;
		m++;
		if(m>12)
		{
			m=1;
			y++;
		}
	}
	DATE tdt(d,m,y);
	return(tdt);
}
DATE DATE::operator-(int t)
{
	int i,td=d,tm=m,ty=y;
	for(i=1;i<=t;i++)
	{
		td--;
		if(td<1)
		{
			tm--;
			if(tm<1)
			{
				tm=12;
				ty--;
			}
			monthdays[1]=ty%4==0?29:28;
			td=monthdays[tm-1];
		}
	}
	DATE tdt(td,tm,ty);
	return(tdt);
}
DATE DATE::operator--()
{
	d--;
	if(d<1)
	{
		m--;
		if(m<1)
		{
			m=12;
			y--;
		}
		monthdays[1]=y%4==0?29:28;
		d=monthdays[m-1];
	}
	DATE tdt(d,m,y);
	return(tdt);
}
int DATE::operator-(DATE tdt)
{
	DATE tdt1(d,m,y),d1,d2;
	d1=tdt1; d2=tdt;
	if(d1==d2) return(0);
	int sgn=1;
	if(d1<d2) { d1=tdt; d2=tdt1; sgn=-1; }
	int tdiff=0;
	while(d2<d1) { tdiff++; ++d2; }
	return(tdiff*sgn);
}
int DATE::operator==(DATE tdt)
{
	int td=tdt.getday(),tm=tdt.getmonth(),ty=tdt.getyear();
	int flag=FALSE;
	if(d==td&&m==tm&&y==ty) flag=TRUE;
	return(flag);
}
int DATE::operator!=(DATE tdt)
{
	int td=tdt.getday(),tm=tdt.getmonth(),ty=tdt.getyear();
	int flag=FALSE;
	if(d==td&&m==tm&&y==ty) flag=TRUE;	flag=!flag;
	return(flag);
}
int DATE::operator<(DATE tdt)
{
	int td=tdt.getday(),tm=tdt.getmonth(),ty=tdt.getyear();
	int flag=FALSE;
	if(y<ty) flag=TRUE;
	else if(y==ty)	{ if(m<tm) flag=TRUE; else if(m==tm&&d<td) flag=TRUE; }
	return(flag);
}
int DATE::operator<=(DATE tdt)
{
	int td=tdt.getday(),tm=tdt.getmonth(),ty=tdt.getyear();
	int flag=FALSE;
	if(y<ty) flag=TRUE;
	else if(y==ty)	{ if(m<tm) flag=TRUE; else if(m==tm&&d<=td) flag=TRUE; }
	return(flag);
}
int DATE::operator>(DATE tdt)
{
	int td=tdt.getday(),tm=tdt.getmonth(),ty=tdt.getyear();
	int flag=FALSE;
	if(y>ty) flag=TRUE;
	else if(y==ty) { if(m>tm) flag=TRUE; else if(m==tm&&d>td) flag=TRUE; }
	return(flag);
}
int DATE::operator>=(DATE tdt)
{
	int td=tdt.getday(),tm=tdt.getmonth(),ty=tdt.getyear();
	int flag=FALSE;
	if(y>ty) flag=TRUE;
	else if(y==ty) { if(m>tm) flag=TRUE; else if(m==tm&&d>=td) flag=TRUE; }
	return(flag);
}

// DATE functions definition
int Day(DATE tdt)
{
	return(tdt.getday());
}

int Month(DATE tdt)
{
	return(tdt.getmonth());
}

int Year(DATE tdt)
{
	return(tdt.getyear());
}

int IsEmpty(DATE tdt)
{
	int flag=FALSE;
	if(Day(tdt)==0&&Month(tdt)==0&&Year(tdt)==0) flag=TRUE;
	return(flag);
}

int DOW(DATE tdt)
{
	int d=Day(tdt),m=Month(tdt),y=Year(tdt);
	int i,j,k,td=1;
	for(i=1;i<y;i++)
	{
		monthdays[1]=i%4==0?29:28;
		for(j=1;j<=12;j++) for(k=1;k<=monthdays[j-1];k++) td=td==7?1:td+1;
	}
	monthdays[1]=y%4==0?29:28;
	for(j=1;j<m;j++) for(k=0;k<monthdays[j-1];k++) td=td==7?1:td+1;
	for(k=1;k<d;k++) td=td==7?1:td+1;
	return(td);
}

STR cDOW(DATE tdt)
{
	STR tstr(daySTR[DOW(tdt)-1]);
	return(tstr);
}

STR cMonth(DATE tdt)
{
	STR tstr(monthSTR[Month(tdt)-1]);
	return(tstr);
}

DATE Date()
{
	struct date d;
	getdate(&d);
	DATE tdt(d.da_day,d.da_mon,d.da_year);
	return(tdt);
}

STR DToC(DATE tdt)
{
	char tstr[11];
	sprintf(tstr,"%02d%c%02d%c%04d",Day(tdt),SET_MARK,Month(tdt),SET_MARK,Year(tdt));
	STR tstr1(tstr);
	return(tstr1);
}

STR DToS(DATE tdt)
{
	char tstr[9];
	sprintf(tstr,"%04d%02d%02d",Year(tdt),Month(tdt),Day(tdt));
	STR tstr1(tstr);
	return(tstr1);
}

DATE CToD(STR tstr)
{
	int d,m,y;
	sscanf(tstr.getstr(),"%d",&d);
	sscanf(tstr.getstr()+3,"%d",&m);
	sscanf(tstr.getstr()+6,"%d",&y);
	DATE tdt(d,m,y);
	return(tdt);
}

int Between(DATE tdt,DATE tdt1,DATE tdt2)
{
	int flag=FALSE;
	if(tdt>=tdt1 && tdt<=tdt2) flag=TRUE;
	return(flag);
}

DATE GoMonth(DATE tdt,int tmn)
{
	int td=Day(tdt),tm=Month(tdt),ty=Year(tdt);
	for(int i=1;i<=tmn;i++)
	{
		tm++;
		if(tm>12) { tm=1; ty++; }
	}
	monthdays[1]=ty%4==0?29:28;
	if(td>monthdays[tm-1]) td=monthdays[tm-1];
	DATE tdt1(td,tm,ty);
	return(tdt1);
}

STR DMY(DATE tdt)
{
	char tstr[20];
	sprintf(tstr,"%02d %s %04d",Day(tdt),monthSTR[Month(tdt)-1],Year(tdt));
	STR tstr1(tstr);
	return(tstr1);
}

STR MDY(DATE tdt)
{
	char tstr[20];
	sprintf(tstr,"%s, %02d %04d",monthSTR[Month(tdt)-1],Day(tdt),Year(tdt));
	STR tstr1(tstr);
	return(tstr1);
}

void PrintDATE(DATE tdt)
{
	cprintf("%02d%c%02d%c%04d",Day(tdt),SET_MARK,Month(tdt),SET_MARK,Year(tdt));
}

void tXYPrintDATE(int col,int row,DATE tdt,int bgc,int fgc)
{
	TextColor(bgc,fgc);
	gotoxy(col,row);
	PrintDATE(tdt);
}

// common utils definition
void MakeSound(int freq,int time)
{
	sound(freq);
	delay(time);
	nosound();
}

void Beep()
{
	MakeSound(512,120);
}

void Quit()
{
	closegraph();
	tClearScreen();
	tCursorOn();
	exit(0);
}

void GetKey()
{
	char far *scr=(char far*)0x417;
	while(!kbhit())
	{
		CTRLFLAG=FALSE;
		ALTFLAG=FALSE;
		SHIFTFLAG=FALSE;
		if(*scr&1) SHIFTFLAG=TRUE;
		if(*scr&2) SHIFTFLAG=TRUE;
		if(*scr&4) CTRLFLAG=TRUE;
		if(*scr&8) ALTFLAG=TRUE;
	}
	union REGS regs;
	regs.h.ah=0;
	int86(22,&regs,&regs);
	ASCIIC=regs.h.al;
	SCANC=regs.h.ah;
}

int GetSCAN()
{
	char far *scr=(char far*)0x417;
	while(!kbhit())
	{
		CTRLFLAG=FALSE;
		ALTFLAG=FALSE;
		SHIFTFLAG=FALSE;
		if(*scr&1) SHIFTFLAG=TRUE;
		else if(*scr&2) SHIFTFLAG=TRUE;
		else if(*scr&4) CTRLFLAG=TRUE;
		else if(*scr&8) ALTFLAG=TRUE;
	}
	union REGS regs;
	regs.h.ah=0;
	int86(22,&regs,&regs);
	return(regs.h.ah);
}

int GetASCII()
{
	char far *scr=(char far*)0x417;
	while(!kbhit())
	{
		CTRLFLAG=FALSE;
		ALTFLAG=FALSE;
		SHIFTFLAG=FALSE;
		if(*scr&1) SHIFTFLAG=TRUE;
		else if(*scr&2) SHIFTFLAG=TRUE;
		else if(*scr&4) CTRLFLAG=TRUE;
		else if(*scr&8) ALTFLAG=TRUE;
	}
	union REGS regs;
	regs.h.ah=0;
	int86(22,&regs,&regs);
	return(regs.h.al);
}

int Between(int val,int start,int end)
{
	if(val>=start&&val<=end) return(TRUE);
	else return(FALSE);
}

int Between(long val,long start,long end)
{
	if(val>=start&&val<=end) return(TRUE);
	else return(FALSE);
}

// tutils definition
void InitializeTextScreen()
{
	textmode(C80);
	tClearScreen();
}

void tClearScreen()
{
	TextColor(0,7);
	clrscr();
}

int tReadScreenChar(int col,int row)
{
	gotoxy(col,row);
	union REGS regs;
	regs.h.ah=8;
	regs.h.bh=0;
	int86(0x10,&regs,&regs);
	return(regs.h.al);
}

int tReadScreenChar(int page,char *attr)
{
	union REGS regs;
	regs.h.ah=8;
	regs.h.bh=page;
	int86(0x10,&regs,&regs);
	*attr=regs.h.ah;
	return(regs.h.al);
}

STR tReadScreenSTR(int col,int row,int Len)
{
	STR tstr(Len);
	for(int i=0;i<Len;i++) tstr.setchr(i,tReadScreenChar(col+i,row));
	return(tstr);
}

void tScrollText(int row,int lcol,int rcol,int bgc,int fgc)
{
	static int scrlss=0,scrlse=0,xx=rcol+5;
	int i,j,scrlLen=strlen(tSCROLL_TEXT),xt;
	TextColor(bgc,fgc);
	if(xx<=lcol-scrlLen)
	{
		xx=rcol+3;
		scrlss=0;
		scrlse=0;
		gotoxy(lcol,row);
	}
	xx--;
	delay(70);
	if(xx>rcol) return;
	xt=xx>=lcol?xx:lcol;
	for(i=xt,j=scrlss;j<=scrlse;i++,j++)
	{
		gotoxy(i,row);
		cprintf("%c",tSCROLL_TEXT[j]);
	}
	scrlse++;
	if(scrlse>=scrlLen)	scrlse=scrlLen;
	if(xx<=lcol)
	{
		scrlss++;
		if(scrlss>scrlLen)
			scrlss=0;
	}
}

void tBox(int Left,int top,int Right,int bottom,int border,int bgc,int fgc)
{
	int tl,tr,bl,br,hl,vl;
	int i;
	if(border==SINGLE_BORDER)
	{
		tl=218;
		tr=191;
		bl=192;
		br=217;
		hl=196;
		vl=179;
	}
	else if(border==DOUBLE_BORDER)
	{
		tl=201;
		tr=187;
		bl=200;
		br=188;
		hl=205;
		vl=186;
	}
	else return;
	TextColor(bgc,fgc);
	gotoxy(Left,top);
	cprintf("%c",tl);
	gotoxy(Right,top);
	cprintf("%c",tr);
	gotoxy(Left,bottom);
	cprintf("%c",bl);
	gotoxy(Right,bottom);
	cprintf("%c",br);
	for(i=top+1;i<bottom;i++)
	{
		gotoxy(Left,i);
		cprintf("%c",vl);
		gotoxy(Right,i);
		cprintf("%c",vl);
	}
	for(i=Left+1;i<Right;i++)
	{
		gotoxy(i,top);
		cprintf("%c",hl);
		gotoxy(i,bottom);
		cprintf("%c",hl);
	}
}

void TextColor(int bgc,int fgc)
{
	textbackground(bgc);
	textcolor(fgc);
}

void tCursorOff()
{
	_setcursortype(_NOCURSOR);
}

void tCursorOn()
{
	_setcursortype(_NORMALCURSOR);
}

void tBar(int Left,int top,int Right,int bottom,int bgc,int fgc)
{
	int i;
	TextColor(bgc,fgc);
	for(i=top;i<=bottom;i++)
	{
		gotoxy(Left,i);
		cprintf("%*s",Right-Left+1," ");
	}
}

void tXYPrintChar(int col,int row,char c,int bgc,int fgc)
{
	TextColor(bgc,fgc);
	gotoxy(col,row);
	cprintf("%c",c);
}

void tHLine(int line,int Left,int Right,int border,int type,int bgc,int fgc)
{
	int i;
	char l,r,h;
	TextColor(bgc,fgc);
	if(border==SINGLE_BORDER)
	{
		l=195;
		r=180;
		h=196;
	}
	else if(border==DOUBLE_BORDER)
	{
		l=204;
		r=185;
		h=205;
	}
	for(i=Left;i<=Right;i++)
	{
		gotoxy(i,line);
		cprintf("%c",h);
	}
	if(type==EDGEDLINE)
	{
		gotoxy(Left,line);
		cprintf("%c",l);
		gotoxy(Right,line);
		cprintf("%c",r);
	}
}

void tVLine(int col,int top,int bottom,int border,int type,int bgc,int fgc)
{
	int i;
	char t,b,v;
	TextColor(bgc,fgc);
	if(border==SINGLE_BORDER)
	{
		t=194;
		b=193;
		v=179;
	}
	else if(border==DOUBLE_BORDER)
	{
		t=203;
		b=202;
		v=186;
	}
	for(i=top;i<=bottom;i++)
	{
		gotoxy(col,i);
		cprintf("%c",v);
	}
	if(type==EDGEDLINE)
	{
		gotoxy(col,top);
		cprintf("%c",t);
		gotoxy(col,bottom);
		cprintf("%c",b);
	}
}

void tMsgBox(STR str,STR tit)
{
	int l=Len(str),x=((80-l)/2)-2,y=((25-(l/50))/2)-2,i;
	char buffer[4096];
	gettext(1,1,80,25,buffer);
	tBar(x,y,x+l+4,y+3,0,0);
	tBox(x,y,x+l+5,y+3,DOUBLE_BORDER,0,3);
	for(i=x;i<=x+l+5;i++)
	{
		gotoxy(i,y);
		cprintf("%c",219);
	}
	textbackground(3);
	textcolor(0);
	gotoxy(((80-Len(tit))/2)+1,y);
	cprintf("%s",tit);
	textbackground(0);
	textcolor(15);
	gotoxy(x+3,y+1);
	cprintf("%s",str);
	Beep();
	getch();
	puttext(1,1,80,25,buffer);
}

void tErrorf(STR errstr)
{
	tMsgBox(errstr,"Error");
	Quit();
}

// editor declaration & definition
void tHMenu()
{
	tCursorOff();
	char buffer[4096];
	gettext(1,1,80,25,buffer);
	int i,key=0,maxlen,col,row,n;
	int npad=cpad-1,nlines,flag=TRUE;
	do
	{
		tBar(1,1,80,1,7,0);
		TextColor(7,0);
		for(i=0;i<MAXPADS;i++)
		{
			gotoxy(menucol[i],1);
			cprintf(" %s ",menustr[i][0]);
		}
		TextColor(10,0);
		gotoxy(menucol[npad],1);
		cprintf(" %s ",menustr[npad][0]);
		n=copt[npad];
		do
		{
			maxlen=0;
			for(i=1;i<menulines[npad];i++) if(maxlen<strlen(menustr[npad][i])) maxlen=strlen(menustr[npad][i]);
			col=menucol[npad]-1;
			row=menurow[npad];
			nlines=menulines[npad];
			tBox(col,row,col+3+maxlen,row+nlines,SINGLE_BORDER,7,0);
			TextColor(7,0);
			for(i=1;i<nlines;i++)
			{
				if(!strcmp("-",menustr[npad][i])) tHLine(row+i,col,col+maxlen+3,SINGLE_BORDER,EDGEDLINE,7,0);
				else
				{
					gotoxy(col+1,row+i);
					cprintf(" %-*s ",maxlen,menustr[npad][i]);
				}
			}
			TextColor(10,0);
			gotoxy(col+1,row+n);
			cprintf(" %-*s ",maxlen,menustr[npad][n]);
			SetStatusString(hlpstr[npad][n]);
			GetKey();
			key=SCANC;
			if(key==ESCKEY) { flag=FALSE; break; }
			if(key==UPARROWKEY) n--;
			else if(key==DNARROWKEY) n++;
			else if(key==HOMEKEY) n=1;
			else if(key==ENDKEY) n=menulines[npad]-1;
			else if(key==PGUPKEY) n=1;
			else if(key==PGDNKEY) n=menulines[npad]-1;
			if(!strcmp("-",menustr[npad][n]))
				if(key==UPARROWKEY) n-=1; else n+=1;
			if(n<1) n=nlines-1;
			if(n>nlines-1) n=1;
		}while(key!=LTARROWKEY&&key!=RTARROWKEY&&key!=ENTERKEY&&key!=SPACEBARKEY);
		puttext(1,1,80,25,buffer);
		copt[npad]=n;
		if(!flag) break;
		if(key==ENTERKEY||key==SPACEBARKEY) branch(npad+1,n);
		if(key==LTARROWKEY) npad-=1;
		else if(key==RTARROWKEY) npad+=1;
		if(npad<0) npad=MAXPADS-1;
		if(npad>MAXPADS-1) npad=0;
	}while(key!=ESCKEY);
	cpad=npad+1;
	tCursorOn();
	Edit();
}

void PrintLineCol()
{
	char tstr[30];
	sprintf(tstr,"%c  Line: %ld  %c  Col: %ld  %c",179,CLINE,179,CCOL+1,179);
	TextColor(7,0);
	gotoxy(43,25);
	cprintf("%30s",tstr);
}

void SetStatusString(char *tstr)
{
	STR tstr1(35);
	tXYPrintSTR(2,25,tstr1,7,7);
	TextColor(7,0);
	gotoxy(2,25);
	cprintf("%s",tstr);
}

void tScreen()
{
	tClearScreen();
	tBar(1,25,80,25,7,0);		// status bar
	tXYPrintSTR(80,24," ",0,0);
	PrintLineCol();
	SetStatusString("Press F1 for Help");
	ToggleINSERT();
	ToggleINSERT();
	tBar(1,1,80,1,7,0);			// menu
	TextColor(7,0);
	for(int i=0;i<MAXPADS;i++)
	{
		gotoxy(menucol[i],1);
		cprintf(" %s ",menustr[i][0]);
	}
	tVLine(1,3,24,SINGLE_BORDER,NORMALLINE,0,7);
	tHLine(2,2,80,SINGLE_BORDER,NORMALLINE,0,7);
	gotoxy(1,2); cprintf("%c",218);
	gotoxy(80,2); cprintf("%c",191);
	tBar(2,3,79,24,1,15);	  	// edit area
}

long MAXLINES,MAXCOLS=1000;
long DISPLINES,STARTLINE;

SLINKED<STR> contents;

void Edit()
{
	tScreen();
	STR tstr;
	int retkey,retpos,i,j,k,col=2;
	retkey=0;
	retpos=0;
	CLINE=1;
	CCOL=0;
	STARTLINE=1;
	DISPLINES=21;
	while(retkey!=ESCKEY)
	{
		MAXLINES=contents.nitems();
		tBar(2,3,79,24,1,15);	  	// edit area
		TextColor(1,7);
		for(i=STARTLINE,k=1;k<=DISPLINES;i++,k++)
		{
			if(k>MAXLINES) break;
			for(j=0;j<Len(contents.getnode(i))&&j<78;j++)
			{
				gotoxy(col+j,k+2);
				cprintf("%c",contents.getnode(i).getchr(j));
			}
		}
		PrintLineCol();
		CCOL=retpos;
		if(CCOL>Len(contents.getnode(CLINE))) CCOL=Len(contents.getnode(CLINE))-1;
		tstr=contents.getnode(CLINE);
		if(Len(tstr)<1) CCOL=0;
		tEditSTR(tstr,MAXCOLS,78,CCOL,retkey,retpos,2,(CLINE-STARTLINE)+3,1,7);
		contents.setnode(tstr,CLINE);
		if(retkey==ENTERKEY)
		{
			contents.addnode(" ");
			MAXLINES++;
			CLINE++;
		}
		else if(retkey==UPARROWKEY)
		{
			CLINE--;
		}
		else if(retkey==DNARROWKEY)
		{
			CLINE++;
		}
		else if(retkey==CTRLHOMEKEY)
		{
			CLINE=1;
			STARTLINE=1;
			CCOL=0;
		}
		else if(retkey==CTRLENDKEY)
		{
			CLINE=MAXLINES;
			STARTLINE=MAXLINES;
		}
		if(CLINE-STARTLINE<1) STARTLINE--;
		if(CLINE-STARTLINE>DISPLINES) STARTLINE++;
		if(STARTLINE<1) STARTLINE=1;
		if(CLINE<1) CLINE=1;
		if(CLINE>MAXLINES) CLINE=MAXLINES;
		if(MAXLINES<DISPLINES) STARTLINE=1;
	}
	if(retkey==ESCKEY) tHMenu();
}

void SaveFile()
{
	if(!SAVED)
	{
		SetStatusString("");
		tXYPrintSTR(2,25,"Save file [y/n]: ",7,0);
		char c=0;
		tCursorOff();
		do c=toupper(getch()); while(c!='Y'&&c!='N'&&c!=27);
		tCursorOn();
		if(c==27) return;
		if(c=='N') main();
		STR fname(12);
		SetStatusString("Enter file name: ");
		int retkey,retpos;
		tEditSTR(fname,12,12,0,retkey,retpos,20,25,7,0);
		char fnm[15];
		strcpy(fnm,fname.getstr());
		FILE *fpnew;
		fpnew=fopen(fnm,"w");
		if(fpnew==NULL)
		{
			tMsgBox("Error opening file","File Open Error");
			Edit();
		}
		for(int i=1;i<=contents.nitems();i++)
		{
			fprintf(fpnew,"%s\n",contents.getnode(i).getstr());
		}
		fclose(fpnew);
		main();
	}
	else main();
}

void OpenFile()
{
}

void SaveFileAs()
{
}

void PrintFile()
{
	for(int i=1;i<=contents.nitems();i++)
	{
		fprintf(stdprn,"%s\n",contents.getnode(i).getstr());
	}
}

void branch(int tpad,int topt)
{
	switch(tpad)
	{
		case 1:				// file menu
			switch(topt)
			{
				case 1:		// new file
					SaveFile();
					break;
				case 2:		// open file
					OpenFile();
					break;
				case 4:		// save file
					SaveFile();
					break;
				case 5:		// save as file
					SaveFileAs();
					break;
				case 7:		// print file
					PrintFile();
					break;
				case 9:		// quit
//					SaveFile();
					Quit();
					break;
			}
			break;
		case 2:				// edit menu
			switch(topt)
			{
				case 1:		// cut
					break;
				case 2:		// copy
					break;
				case 3:		// paste
					break;
				case 4:		// delete selected text
					break;
				case 6:		// select all
					break;
				case 7:		// change case
					break;
			}
			break;
		case 3:				// search menu
			switch(topt)
			{
				case 1:		// find
					break;
				case 2:		// find & replace
					break;
				case 3:		// find again
					break;
				case 5:		// goto
					break;
				case 6:		// bookmarks
					break;
			}
			break;
		case 4:				// insert menu
			switch(topt)
			{
				case 1:		// autotext
					break;
				case 3:		// date/time
					break;
			}
			break;
		case 5:				// help menu
			switch(topt)
			{
				case 1:		// help topics
					break;
				case 3:		// about
					break;
			}
			break;
	}
}

void main()
{
	InitializeTextScreen();
	Initialize_menustr();
	SAVED=TRUE;
	contents.deleteallnodes();
	contents.addnode("");
	Edit();
}