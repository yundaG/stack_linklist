#include<stdio.h>
#include<stdlib.h> 
#include<math.h>
#include<string.h>
#include<iostream>
#include<string>
#include<stack> 
using namespace std;
#define Maxsize 100
#define OK 1
#define ERROR 0
#define listinitsize 100
#define listincrease 10
#define MAX 100
typedef struct Pnode{
	float coef;
	int exp;
	struct Pnode *link;
}*Linklist;
typedef int ElemType;//int can be changed to other type when needed
typedef int Status;//the type of function
typedef struct{
	ElemType *elem;
	int length;//当前长度 
	int listsize;//当前分配的存储容量 
}Sqlist; 
typedef struct node{
	int *coef;
	int order; 
}Polynominal;
typedef struct 
{
	int  data[MAX];
	int  top;
} Stack;
int Judge(char c1,char c2)
{
	int a1,a2;
	if('+'==c1||'-'==c1) a1 = 3;
	if('*'==c1||'/'==c1)a1 = 5;
	if('^'==c1) a1= 7;
	if('('==c1) a1 = 1;
	if(')'==c1) a1 = 9;
	if('#'==c1) a1 = 0; 
	if('+'==c2||'-'==c2)a2 = 2;
	if('*'==c2||'/'==c2)a2 = 4;
	if('^'==c2) a2=6;
	if('('==c2) a2 = 8;
	if(')'==c2) a2 = 1;
	if('#'==c2) a2 = 0;
	if(a1>a2) return 1;
	if(a1==a2) return 0;
	if(a1<a2) return -1;
}
//符号运算函数
double run(char c ,double d1,double d2)
{
	double d4=d1;
	int n=d2;
	switch (c)
	{
	case '+':
		return d1+d2;
		break;
	case '-':
		return d1-d2;
		break;
	case'*' :
		return d1*d2;
		break;
	case '/':
		return d1/d2;
		break;
	case '^':
		d4=1;
		for(int i=0;i<n;i++)
		d4*=d1;
		return d4;
		break;
	default:
		return 0.0;
		break;
	}
}
void calculate(string str){
	string str2=str;
	char * op = "+-*/^()#";
	str.append(1,'#');
	stack<char> OPTR;//运算符栈
	stack<double> OPND;//操作数栈
	for(int i=1;i<strlen(str.c_str());i++){
		if(str[i]=='-'&&str[i-1]=='('){
			str.insert(i,1,'0');
		}
	}
	int a = -1;
	//先将#符号入栈

	OPTR.push('#');
	while(true)
	{
	 int b = a+1;
	 a = str.find_first_of(op,a+1);
	 if(a==string::npos) break;
	 if(a!=b)
	 {
	 string ss(str,b,a-b);
	 double d=atof(ss.c_str());
	 //数据先入栈
	 
	 OPND.push(d);
	 }
	 //运算符优先级比较
	 int ju = Judge(OPTR.top(),str[a]);
	 if(-1==ju)//栈外优先级大直接入栈
	 {
	    OPTR.push(str[a]);
	 }
	 if(0==ju)//栈内外优先级相等则出栈
	 {
		OPTR.pop();
	 }
	 if(1==ju)//栈内优先级大,出栈进行运算
	 {
		 double d1 = OPND.top();
		 		 OPND.pop();
		 double d2= OPND.top();
		 		 OPND.pop();
		 d1 = run(OPTR.top(),d2,d1);
		 //运算结果入栈
		 		 OPND.push(d1);
		 		 OPTR.pop();
		 a--;
	 }
	}
	//删除表达式最后的'#'结束标识符

	str.erase(str.length()-1,1);
	cout<<"计算结果："<<endl;
	cout<<str2<<"="<<OPND.top()<<endl;
}
int table[]={0,0,2,1,0,1,0,2};
void init(Stack *s){
	int i;
	for(i=0;i<MAX;i++){
		s->data[i]=0;
	}
	s->top=-1;
}
void intoback(Stack *s,char *in,int* suff,int*length){
	int  i;			
	int  b = 0;			
	int  j = 0;			
	int  pri= 0;
	for(i=0;i<strlen(in);){
		if(in[i]>='0'&&in[i]<='9'){
			b=0;
			while(in[i]>='0'&&in[i]<='9'){
				b=b*10+(in[i]-'0');
				i++;
			}
			suff[j]=b;
			j++;
			continue;
		}
		if(in[i]==40){
			s->top++;
			s->data[s->top]=in[i];
			pri=table[s->data[s->top]%10];
			i++;
			continue;
		}
		if(in[i]==41){
			while(s->data[s->top]!=40){
				suff[j]=s->data[s->top];
				s->data[s->top]=0;
				s->top--;
				j++;
			}
			s->data[s->top]=0;
			s->top--;
			pri=table[s->data[s->top]%10];
			i++;
			continue;
		}
		if(in[i]>=42&&in[i]<=47){
			if(pri>=table[in[i]%10]){
				while(pri>=table[in[i]%10]&&s->data[s->top]!=40){
					suff[j]=s->data[s->top];
					s->data[s->top]=0;
					s->top--;
					pri=table[s->data[s->top]%10];
					j++;
				}
				s->top++;
				s->data[s->top]=in[i];
				pri=table[s->data[s->top]%10];
				i++;
			}
			else 
			{
				if (in[i] == 45 && s->data[s->top] == 40)
				{
					b = 0;
					while (in[i+1] >= '0' && in[i+1] <= '9')
					{
						b = b * 10 + (in[i+1] - '0');
						i++;
					}
					suff[j] = b * -1;
					s->data[s->top] = 0;
					s->top--;
					j++;
					i += 2;
					pri= table[s->data[s->top] % 10];
					continue;
				}
				s->top++;
				s->data[s->top] = in[i];
				pri= table[s->data[s->top] % 10];
				i++;
			}
		}
	}
	while(s->top!=-1){
		suff[j]=s->data[s->top];
		s->top--;
		j++;
	}
	*length=j;
}
int getresult(Stack *s,int*suff,int length){
	int i,j,result=0;
	for(i=0;i<length;i++){
		switch(suff[i]){
			case 42:
				result=s->data[s->top-1]*s->data[s->top];
				s->top-=1;
				s->data[s->top]=result;
				break;
			case 43:
				result=s->data[s->top-1]+s->data[s->top];
				s->top-=1;
				s->data[s->top]=result;
				break;
			case 45:
				result=s->data[s->top-1]-s->data[s->top];
				s->top-=1;
				s->data[s->top]=result;
				break;
			case 47:
				result=s->data[s->top-1]/s->data[s->top];
				s->top-=1;
				s->data[s->top]=result;
				break;
			default:
				s->top++;
				s->data[s->top]=suff[i];
				break;
		}
	}
	return result;
}
Status Initlist(Sqlist &L){//创建一个空的线性表 
	L.elem=(ElemType *)malloc(listinitsize*sizeof(ElemType));
	if(!L.elem) exit(OVERFLOW);
	L.length=0;
	L.listsize=listinitsize;
	return OK;
}
Status Listinsert(Sqlist &L,int i,ElemType e){//在第i个位置前插入新元素e
 	if(i<1||i>L.length+1) return ERROR;
 	if(L.length>=L.listsize){
 		ElemType* newbase=(ElemType*)realloc(L.elem,(L.listsize+listincrease)*sizeof(ElemType));
 		if(!newbase) exit(OVERFLOW);
 		L.elem=newbase;
 		L.listsize+=listincrease;
	 }
	ElemType* q=&(L.elem[i-1]);
	for(ElemType* p=&(L.elem[L.length-1]);p>=q;--p) *(p+1)=*p;
	*q=e;
	++L.length;
	return OK;
} 
Status Getielem(Sqlist &L,int i){//遍历取第i个元素
	if(i<1||i>L.length) return ERROR;
	return L.elem[i-1]; 
}
Status Listdelete(Sqlist &L,int i,ElemType &e){//删除第i个元素，并用e返回其值 
	if(i<1||i>L.length) return ERROR;
	ElemType* p=&(L.elem[i-1]);
	e=*p;
	ElemType* q=L.elem+L.length-1;
	for(++p;p<=q;++p) *(p-1)=*p;  
	--L.length;
	return OK;
} 
Status Clear(Sqlist &L){//清空 
	free(L.elem+1);
}
Status Delete(Sqlist &L){//删除 
	free(L.elem) ;
}
void Plus(){//向量加法
	int n;
	printf("输入向量的维度：\n");
	scanf("%d",&n);
	Sqlist L1, L2;
	L1.elem=(ElemType *)malloc((n+1)*sizeof(ElemType));
	if(!L1.elem) exit(OVERFLOW);
	L2.elem=(ElemType *)malloc((n+1)*sizeof(ElemType));
	if(!L2.elem) exit(OVERFLOW);
	L1.length=n;
	L2.length=n;
	printf("输入第一个向量：\n");
	for(int i=0;i<n;i++){
		scanf("%d",L1.elem+i);
	}
	printf("输入第二个向量：\n");
	for(int i=0;i<n;i++){
		scanf("%d",L2.elem+i);
	}
	printf("向量的和：\n");
	for(int i=0;i<n;i++){
		printf("%d ",L1.elem[i]+L2.elem[i]);
	}
	printf("\n");
	free(L1.elem);
	free(L2.elem);
	return ;
}
void Subtract(){//减法 
	int n;
	printf("输入向量的维度：\n");
	scanf("%d",&n);
	Sqlist L1, L2;
	L1.elem=(ElemType *)malloc((n+1)*sizeof(ElemType));
	if(!L1.elem) exit(OVERFLOW);
	L2.elem=(ElemType *)malloc((n+1)*sizeof(ElemType));
	if(!L2.elem) exit(OVERFLOW);
	L1.length=n;
	L2.length=n;
	printf("输入第一个向量：\n");
	for(int i=0;i<n;i++){
		scanf("%d",L1.elem+i);
	}
	printf("输入第二个向量：\n");
	for(int i=0;i<n;i++){
		scanf("%d",L2.elem+i);
	}
	printf("向量的差：\n");
	for(int i=0;i<n;i++){
		printf("%d ",L1.elem[i]-L2.elem[i]);
	}
	printf("\n");
	free(L1.elem);
	free(L2.elem);
	return ;
}
void Cos(){//计算夹角余弦值 
	int n;
	printf("输入向量的维度：\n");
	scanf("%d",&n);
	Sqlist L1, L2;
	L1.elem=(ElemType *)malloc((n+1)*sizeof(ElemType));
	if(!L1.elem) exit(OVERFLOW);
	L2.elem=(ElemType *)malloc((n+1)*sizeof(ElemType));
	if(!L2.elem) exit(OVERFLOW);
	L1.length=n;
	L2.length=n;
	int sum1=0,sum2=0,multiply=0;
	printf("输入第一个向量：\n");
	for(int i=0;i<n;i++){
		scanf("%d",L1.elem+i);
		sum1+=L1.elem[i]*L1.elem[i];
	}
	printf("输入第二个向量：\n");
	for(int i=0;i<n;i++){
		scanf("%d",L2.elem+i);
		sum2+=L2.elem[i]*L2.elem[i];
		multiply+=L1.elem[i]*L2.elem[i];
	}
	cout<<"向量夹角余弦值：";
	printf("%lf\n",1.0*multiply/sqrt(sum1)/sqrt(sum2));
	free(L1.elem);
	free(L2.elem);
	return ; 
} 
//顺序表实现一元多项式 
void Add(){//加法 
	int size1,size2,i;
	printf("输入两多项式的阶\n");
	scanf("%d %d",&size1,&size2);
	int x=size1>size2?size1:size2;
	Polynominal poly1,poly2,poly3;
	poly1.coef=(int*)malloc((size1+2)*sizeof(int));
	poly2.coef=(int*)malloc((size2+2)*sizeof(int));
	poly3.coef=(int*)malloc((x+2)*sizeof(int));
	poly1.order=size1;
	poly2.order=size2;
	printf("输入多项式1的系数：\n");
	for( i=0;i<=size1;i++)
		scanf("%d",&poly1.coef[i]);
	printf("输入多项式2的系数：\n");
	for( i=0;i<=size2;i++)
		scanf("%d",&poly2.coef[i]);
	for( i=0;i<=size1&&i<=size2;i++){
		poly3.coef[i]=poly1.coef[i]+poly2.coef[i];
	}
	while(i<=size1) poly3.coef[i]=poly1.coef[i];
	while(i<=size2) poly3.coef[i]=poly2.coef[i];
	//两个循环只执行一个
	poly3.order=x;
	printf("和："); 
	for(i=x;i>0;i--){
		printf("%dx^%d+",poly3.coef[i],i);
	} 
	printf("%d\n",poly3.coef[0]);
	free(poly1.coef);
	free(poly2.coef);
	free(poly3.coef);
	return ;
} 
void sub(){//减法 
	int size1,size2,i;
	printf("输入两多项式的阶\n");
	scanf("%d %d",&size1,&size2);
	int x=size1>size2?size1:size2;
	Polynominal poly1,poly2,poly3;
	poly1.coef=(int*)malloc((size1+2)*sizeof(int));
	poly2.coef=(int*)malloc((size2+2)*sizeof(int));
	poly3.coef=(int*)malloc((x+2)*sizeof(int));
	poly1.order=size1;
	poly2.order=size2;
	printf("输入多项式1的系数：\n");
	for( i=0;i<=size1;i++)
		scanf("%d",&poly1.coef[i]);
	printf("输入多项式2的系数：\n");
	for( i=0;i<=size2;i++)
		scanf("%d",&poly2.coef[i]);
	for( i=0;i<=size1&&i<=size2;i++){
		poly3.coef[i]=poly1.coef[i]-poly2.coef[i];
	}
	while(i<=size1) poly3.coef[i]=poly1.coef[i];
	while(i<=size2) poly3.coef[i]=-poly2.coef[i];
	//两个循环只执行一个
	poly3.order=x;
	printf("和："); 
	for(i=x;i>0;i--){
		printf("%dx^%d+",poly3.coef[i],i);
	} 
	printf("%d\n",poly3.coef[0]);
	free(poly1.coef);
	free(poly2.coef);
	free(poly3.coef);
	return ;
}
void Mul(){//乘法 
	int size1,size2,i,j;
	printf("输入两多项式的阶\n");
	scanf("%d %d",&size1,&size2);
	int x=size1+size2;
	Polynominal poly1,poly2,poly3;
	poly1.coef=(int*)malloc((size1+2)*sizeof(int));
	poly2.coef=(int*)malloc((size2+2)*sizeof(int));
	poly3.coef=(int*)malloc((x+2)*sizeof(int));
	poly1.order=size1;
	poly2.order=size2;
	printf("输入多项式1的系数：\n");
	for( i=0;i<=size1;i++)
		scanf("%d",&poly1.coef[i]);
	printf("输入多项式2的系数：\n");
	for( i=0;i<=size2;i++)
		scanf("%d",&poly2.coef[i]);
	for(i=0;i<=size1+size2;i++)
		poly3.coef[i]=0; 
	for(i=0;i<=size1;i++){
		for(j=0;j<=size2;j++)
			poly3.coef[i+j]+=poly1.coef[i]*poly2.coef[j];
	}
	poly3.order=x;
	for(i=x;i>0;i--){
		printf("%dx^%d+",poly3.coef[i],i);
	} 
	printf("%d\n",poly3.coef[0]);
	int n,sum;
	printf("多项式求值请输入：（输入0结束）\n");
	scanf("%d",&n);
	if(!n){
		free(poly1.coef);
		free(poly2.coef);
		free(poly3.coef);
		return;
	}
	for(i=0;i<=x;i++){
		sum+=poly3.coef[i]*pow(n,i);
	}
	printf("%d",sum);
	free(poly1.coef);
	free(poly2.coef);
	free(poly3.coef);
	return;
}
//链表实现一元多项式 
void Createpoly(Linklist &L){//创建多项式单链表
	Pnode *p,*pre,*s;
	float c;
	int e,i=0;
	cout<<"创建一个多项式单链表"<<endl;
	L=new Pnode;
	L->exp=-1;
	L->link=NULL;
	while (1){
		cout<<"输入第"<<++i<<"个项：";
		cin>>c>>e;
		if(c==0)break;
		s=new Pnode;
		if(s==NULL)
		cout<<"分配失败！";
		s->coef=c;
		s->exp=e;
		//插入排序，按降幂插入 
		//当再次输入同一指数时会忽略此输入 
		pre=L;p=L->link;
		while (p!=NULL&&p->exp>e){
			pre=p;p=p->link;
		}
		if(p!=NULL&&p->exp==e)
			cout<<"输入项指数重复，无效输入"<<endl;
		else{
			s->link=p;pre->link=s;
		}
	} 
}
void Insert(Linklist& L,float c,int e){//多项式链表的插入 
	Pnode *pre=L,*p=L->link;
	while(p!=NULL&&p->exp>e){
		pre=p;p=p->link;
	}
	if(p!=NULL&&p->exp==e){//指数相同即合并 
		if(p->coef+c!=0)
			p->coef+=c;
		else{
			pre->link=p->link;
			free(p);
		}
	}
	else{//创建新节点插入 
		Pnode *pc=new Pnode;
		if(pc==NULL)
		cout<<"分配失败！";
		pc->exp=e;pc->coef=c;
		pre->link=pc;
		pc->link=p;
	}
	
}
void  Add2(){//多项式的加法，遍历b的节点，插入a中实现加法计算 
	Linklist a,b;
	Createpoly(a);
	Createpoly(b);
	Pnode* q=b->link;
	for(;q!=NULL;q=q->link){
		Insert(a,q->coef,q->exp);
	}
	Pnode* p=a->link;
	cout<<"多项式的和:"<<endl; 
	for(;p->link!=NULL;p=p->link){
		cout<<p->coef<<"x^"<<p->exp<<"+ ";
	}
	cout<<p->coef<<"x^"<<p->exp<<endl;
	free(a);free(b);free(p);free(q);
	return;
}
void Sub(){//减法相当于加一个负数，算法思想同上面的加法 
	Linklist a,b;
	Createpoly(a);
	Createpoly(b);
	Pnode* q=b->link;
	for(;q!=NULL;q=q->link){
		Insert(a,-q->coef,q->exp);
	}
	Pnode* p=a->link;
	cout<<"多项式的差："<<endl;
	for(;p->link!=NULL;p=p->link){
		cout<<p->coef<<"x^"<<p->exp<<"+ ";
	}
	cout<<p->coef<<"x^"<<p->exp<<endl;
	free(a);free(b);free(p);free(q);
	return ;
}
void Mul2(){//多项式乘法 
	Linklist a,b;
	Createpoly(a);
	Createpoly(b);
	Pnode *pa,*pb;
	Pnode *c=new Pnode;
	c->link=NULL;
	pa=a->link;
	while(pa!=NULL){
		pb=b->link;
		while(pb!=NULL){
			Insert(c,pa->coef*pb->coef,pa->exp+pb->exp);
			pb=pb->link;
		}
		pa=pa->link;
	}//算法思想：遍历，计算后插入第一个多项式得到结果 
	Pnode* p=c->link;
	cout<<"多项式的积："<<endl;
	for(;p->link!=NULL;p=p->link){
		cout<<p->coef<<"x^"<<p->exp<<"+ ";
	}
	cout<<p->coef<<"x^"<<p->exp<<endl;
	free(a);free(b);free(p);delete(c);free(pa);free(pb);
	return ;
}
void derivative(int n){//计算n阶导数 
	Linklist a;
	Createpoly(a);
	Pnode* p=a->link;
	while(p!=NULL){
		for(int i=0;i<n;i++)
		p->coef*=p->exp-i;
		p->exp-=n;
		p=p->link;
	} 
	cout<<"求导：";
	for(p=a->link;p->link!=NULL;p=p->link){
		cout<<p->coef<<"x^"<<p->exp<<"+ ";
	}
	cout<<p->coef<<"x^"<<p->exp<<endl;
	free(a);free(p);
	return ;
}
void qiuzhi2(){
	cout<<"输入变量"<<endl;
	char x;
	cin>>x;
	char xx;
	cout<<"输入算式"<<endl;
	char ss[MAX];
	cin>>ss;
	cout<<"变量的值"<<endl;
	cin>>xx;
	int l=strlen(ss);
	for(int i=0;i<l;i++){
		if(ss[i]==x){
			ss[i]=xx;
		}
	}
	Stack s;
	int length,result;
	int back[MAX];
	char in[MAX];
	for(int i=0;i<l;i++){
		in[i]=ss[i]; 
	}
	init(&s);
	intoback(&s,in,back,&length);
	init(&s);
	result=getresult(&s,back,length);
	printf("%d",result);
}
void findone(char a[],char b[]){
	int la=0,lb=0,i;
	la=strlen(a);
	lb=strlen(b);
	for(i=0;i<la;i++){
		if(a[i]==b[0]&&lb==1)
			break;
		if(a[i]==b[0]&&i+1!=la&&a[i+1]==b[1])
			break;	
	}
	a[i]='x';//把变量统一设置为x 
	for(i++;i<la;i++){
		a[i]=a[i+lb-1];
	}
}
void findall(char a[],char b[]){
	int la=strlen(a);
	for(int i=0;i<la;i++){
		if(a[i]==b[0]){
			findone(a,b);
		}
	}
}
void newfunction(string def,string run){
	int i,j;
	for(i=0;def[i]!='(';i++);
	for(j=i;def[j]!=')';j++);
	string var=def.substr(i+1,j-i-1);
	//cout<<var<<endl;
	string str(def,j+2);
	//cout<<str<<endl;
	for(i=0;run[i]!='(';i++);
	for(j=i;run[j]!=')';j++);
	string n=run.substr(i+1,j-i-1);
	//cout<<n<<endl;
	findall((char*)str.c_str(),(char*)var.c_str());
	//cout<<str<<endl;
	for(int i=0;i<strlen(str.c_str());i++){
				if(str[i]=='x')
				str.replace(i,1,n);
			}
			calculate(str);
} 
/*void newfunctions(){
	int count;
	cout<<"输入保留函数的数量"<<endl;
	cin>>count;
	char fs[count][100];
	
	for(int i=0;i<count;i++){
		cin>>fs[i];
	}
	string run;
	cout<<"输入运行表达式"<<endl;
	cin>>run;
	char x=run[3];
	for(int i=0;i<count;i++){
		if(x==fs[i][3]){
			newfunction(fs[i],run);
			break;
		}
	}
}*/
/*void singlevar(){
	char n;
	string str;
	cout<<"输入含单变量的表达式"<<endl;
			cin>>str;
			char q;
			for(int i=0;i<str.length();i++)
			{
				if((str.at(i)<='z'&&str.at(i)>='a')||(str.at(i)>='A'&&str.at(i)<='Z'))
				{
					q=str.at(i);
					break;
				}
			}
			cout<<"输入变量 "<<q<<" 的值: ";
			cin>>n;
			int j;
			for(int i=0;i<str.length();i++)
			{	
				if(str.at(i)==q){	str.at(i)=n; j=i;} 
			}
			calculate(str);
}*/
void newfunctions(){
	int count;
	cout<<"输入保留函数的数量"<<endl;
	cin>>count;
	char fs[count][100];
	cout<<"输入函数"<<endl;
	for(int i=0;i<count;i++){
		cin>>fs[i];
	}
	string run;
	cout<<"输入运行表达式"<<endl;
	cin>>run;
	char x=run[3];
	for(int i=0;i<count;i++){
		if(x==fs[i][3]){
			string fsi=(string)fs[i];
			int a=fsi.find_first_of('(',6);//cout<<a<<endl;
			if(a!=string::npos){
				int j;
				for(j=0;j<count;j++){
					if(fs[j][3]==fsi[a-1])
					break;
				}//cout<<j<<endl;cout<<((string)fs[j]).substr(8)<<endl;
				fsi.replace(a+1,1,((string)fs[j]).substr(8));//cout<<fsi<<endl;
				fsi.erase(a-1,1);//cout<<fsi<<endl;
			}
			newfunction(fsi,run);
			break;
		}
	}
}
void matrixadd(){
	cout<<"输入矩阵的行列数"<<endl;
	int m,n;
	cin>>m; 
	cin>>n;
	double a[m][n],b[m][n],c[m][n];
	cout<<"输入矩阵1"<<endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
		cin>>a[i][j];
	}
	cout<<"输入矩阵2"<<endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
		cin>>b[i][j];
	}
	cout<<"两矩阵的和："<<endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
		c[i][j]=a[i][j]+b[i][j];
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<c[i][j]<<ends;
		}
		cout<<endl;
	}
}
void matrixsub(){
	cout<<"输入矩阵的行列数"<<endl;
	int m,n;
	cin>>m; 
	cin>>n;
	double a[m][n],b[m][n],c[m][n];
	cout<<"输入矩阵1"<<endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
		cin>>a[i][j];
	}
	cout<<"输入矩阵2"<<endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
		cin>>b[i][j];
	}
	cout<<"两矩阵的差："<<endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++)
		c[i][j]=a[i][j]-b[i][j];
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
			cout<<c[i][j]<<ends;
		}
		cout<<endl;
	}
}

void matrixmul(){
	cout<<"输入矩阵1的行列数"<<endl;
	int m1,n1,m2,n2;
	cin>>m1;
	cin>>n1;
	cout<<"输入矩阵2的行列数"<<endl;
	cin>>m2;
	cin>>n2;
	if(n1!=m2){ 
	cout<<"无法计算"<<endl;
	return ;
	} 
	double a[m1][n1],b[m2][n2],c[m1][n2]={0};
	cout<<"输入矩阵1"<<endl;
	for(int i=0;i<m1;i++){
		for(int j=0;j<n1;j++)
		cin>>a[i][j];
	}
	cout<<"输入矩阵2"<<endl;
	for(int i=0;i<m2;i++){
		for(int j=0;j<n2;j++)
		cin>>b[i][j];
	}
	cout<<"两矩阵的乘积："<<endl;
	for(int i=0;i<m1;i++){
		for(int j=0;j<n2;j++){
			for(int k=0;k<n1;k++)
			c[i][j]+=a[i][k]*b[k][j];
		}
	}
	for(int i=0;i<m1;i++){
		for(int j=0;j<n2;j++){
			cout<<c[i][j]<<ends;
		}
		cout<<endl;
	}
}
void matrixdet()
{
	int N;
	cout<<"输入阶数"<<endl;
	cin>>N;
	double matrix[N][N];
	cout<<"输入矩阵"<<endl;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++)
		cin>>matrix[i][j];
	}
    int sign=0;
    long ans=1;
    for(int i=0;i<N;i++)//当前行
    {
        for(int j=i+1;j<N;j++)//当前之后的每一行，因为每一行的当前第一个数要转化成0
        {
            int x=i,y=j;
            while(matrix[y][i])//利用gcd的方法，不停地进行辗转相除
            {
                double t=matrix[x][i]/matrix[y][i];
                for(int k=i;k<N;k++)
                    matrix[x][k]=(matrix[x][k]-matrix[y][k]*t);
                swap(x,y);
            }
            if(x!=i)//奇数次交换，则D=-D'整行交换
            {
                for(int k=0;k<N;k++)
                    swap(matrix[i][k],matrix[x][k]);
                sign^=1;
            }
        }
        if(matrix[i][i]==0)//斜对角中有一个0，则结果为0
        {
            cout<<0<<endl;
            return ;
        }
        else
            ans=ans*matrix[i][i];
    }
    if(sign!=0)
        ans*=-1;
    cout<<(ans)<<endl;
}	
void matrixtran(){
	cout<<"输入矩阵的行列数"<<endl;
	int m,n;
	cin>>m; 
	cin>>n;
	double a[m][n],b[n][m];
	cout<<"输入矩阵"<<endl;
	for(int i=0;i<m;i++){
		for(int j=0;j<n;j++){
		cin>>a[i][j];
		b[j][i]=a[i][j];
		}
	}
	cout<<"转置矩阵："<<endl;
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			cout<<b[i][j]<<ends;
		}
		cout<<endl;
	}
}
int main(){
	cout<<"请选择计算对象："<<endl;
	cout<<"1.向量"<<endl;
	cout<<"2.多项式"<<endl;
	cout<<"3.表达式计算"<<endl;
	cout<<"4.矩阵"<<endl;
	int s1,s2;
	cin>>s1;
	string n;
	string str,var; 
	char def[100],run[100];
	if(s1==1){
		cout<<"1.向量加法"<<endl;
		cout<<"2.向量减法"<<endl;
		cout<<"3.向量夹角余弦值"<<endl;
		cin>>s2;
		if(s2==1) Plus();
		if(s2==2) Subtract();
		if(s2==3) Cos();
	}
	else if(s1==2){
		cout<<"1.多项式加法"<<endl;
		cout<<"2.多项式减法"<<endl;
		cout<<"3.多项式乘法"<<endl;
		cout<<"4.多项式求导"<<endl;	
		cin>>s2;
		if(s2==1) Add2();
		if(s2==2) Sub();
		if(s2==3) Mul2();
		if(s2==4){
			cout<<"请输入阶数："<<endl;
			int x;
			cin>>x;
			derivative(x);
		}
	}
	else if(s1==3){
		cout<<"1.四则运算表达式求值"<<endl; 
		cout<<"2.含单变量表达式求值"<<endl; 
		cout<<"3.定义新函数并求值"<<endl;
		cout<<"4.保留历史函数的求值"<<endl;
		cin>>s2;
		if(s2==1){
			cout<<"输入四则运算表达式"<<endl; 
			cin>>str;
			calculate(str);
		}
		if(s2==2){
			cout<<"输入变量"<<endl;
			cin>>var;
			cout<<"输入表达式"<<endl;
			cin>>str;
			cout<<"输入变量的值"<<endl;
			cin>>n;
			findall((char*)str.c_str(),(char*)var.c_str());
			for(int i=0;i<strlen(str.c_str());i++){
				if(str[i]=='x')
				str.replace(i,1,n);
			}
			calculate(str);
		}
		if(s2==3){
			cout<<"输入定义"<<endl; 
			cin>>def;
			cin>>run;
			newfunction(def,run);
		}
		if(s2==4)
		newfunctions();
	}
	else if(s1==4){
		cout<<"1.矩阵加法"<<endl;
		cout<<"2.矩阵减法"<<endl;
		cout<<"3.矩阵乘法"<<endl;
		cout<<"4.矩阵转置"<<endl;
		cout<<"5.矩阵的行列式"<<endl;
		cin>>s2;
		if(s2==1)
		matrixadd();
		if(s2==2)
		matrixsub();
		if(s2==3)
		matrixmul();
		if(s2==4)
		matrixtran();
		if(s2==5)
		matrixdet();
	}
}
