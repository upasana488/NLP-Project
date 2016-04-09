#include<bits/stdc++.h>
using namespace std;
FILE * vocabtraining=fopen("q4.txt","a+");
FILE * train=fopen("train.txt","a+");
FILE * test=fopen("test.txt","a+");
FILE * accu=fopen("accuracy.txt","a+");
struct vocab
{
	char str[100];
	int cp,cn;
	double pp,pn;
}store[5000];
int main()
{
	int i,j,k,len,cp,cn,vocabsize=0,posrev=0,negrev=0,accuracycount=0;			//count pos, count negative 
	double pp,pn,pps,pns,priorpp,priorpn;				//prob pos,  prob negative, s stands for sentance
	char str[5000],sign,word[100],s[5000];
	cout<<"Hello";
	i=0;
	while(!feof(vocabtraining))
	{
		fscanf(vocabtraining,"%s %d %d %lf %lf",s,&cp,&cn,&pp,&pn);
		strcpy(store[i].str,s);
		store[i].cp=cp;
		store[i].cn=cn;
		store[i].pp=pp;
		store[i].pn=pn;
		i++;
	
	}
	
	vocabsize=i;
	/*for(i=0;i<100;i++)
	{
		cout<<store[i].str<<" "<<store[i].pp<<endl;
	}*/
	int posword,negword;
	posword=negword=0;
	while(!feof(train))
	{
		fgets(str,9999,train);
		//cout<<str<<endl;
		if(str[0]=='+')
			posrev++;
		else if(str[0]=='-')
			negrev++;
		len=strlen(str);
		//cout<<len<<" ";
		for(i=2;i<len;i++)
		{
			j=0;
			while((str[i]<='z' && str[i]>='a') || str[i]==39)
				word[j++]=str[i++];
			word[j]='\0';
			if(str[0]=='+')
				posword++;
			else if(str[0]=='-')
				negword++;
			
		}	
	//	cout<<posword<<" "<<negword<<endl;
	}
	cout<<"posword and negwords";
	cout<<posword<<" "<<negword<<endl;
	priorpp=posrev/450.0;
	priorpn=negrev/450.0;
	cout<<"prior probability"<<priorpp<<" "<<priorpn<<endl;
	/*while(!feof(vocabtraining))
	{
		fscanf(vocabtraining,"%s %d %d %lf %lf",s,&cp,&cn,&pp,&pn);
		//vocabsize++;
		cout<<s<<" "<<cp<<" "<<cn<<" "<<pp<<" "<<pn<<endl;
	}*/
	//cout<<posrev<<" "<<negrev<<endl;
	//cout<<"vocabsize is"<<vocabsize<<endl;
	
	while(!feof(test))
	{
		j=0;
		pps=priorpp;
		pns=priorpn;
		//cout<<"priors "<<pps<<" "<<pns<<endl<<endl;
		fgets(str,9990,test);
		len=strlen(str);
		//cout<<str<<endl;
		sign=str[0];
		
		//cout<<str[2];
		for(i=2;i<=len;i++)
		{
			j=0;
			while((str[i]<='z' && str[i]>='a') || str[i]==39)
				word[j++]=str[i++];
			word[j]='\0';
			//cout<<word<<" ";
			//cout<<"a";
			//cout<<feof(vocabtraining)<<endl;
			//cout<<"hello";
			for(k=0;k<vocabsize;k++)
			{

				if(strcmp(store[k].str,word)==0)
				{
					//cout<<"yeah\n";
					pps=(log(1/pps)+log(1/store[k].pp));
					pns=(log(1/pns)+log(1/store[k].pn));
					break;
				}
			}
			
			if(k==vocabsize)
			{
				pps=(log(1/pps)+log(1/posword+vocabsize));
				pns=(log(1/pns)+log(1/negword+vocabsize));
			}
			/*while(!feof(vocabtraining))
			{

				fscanf(vocabtraining,"%s %d %d %lf %lf",s,&cp,&cn,&pp,&pn);
				if(strcmp(s,word))
				{
					pps=pps*pp;
					pns=pns+pn;
				}
				cout<<pps<<" "<<pns<<endl;
				cout<<s<<" "<<cp<<" "<<cn<<" "<<pp<<" "<<pn<<endl;
			}*/
			
		}
//		cout<<pps<<"  "<<pns<<endl;
//		cout<<pps<<" "<<pns<<" "<<sign<<endl;
		if(pps>pns && sign=='-')
	{			accuracycount++;
	//		cout<<"positive"<<sign<<endl;
	}
		else if(pps<pns && sign=='+')
		{
			accuracycount++;
	//		cout<<"negative"<<sign<<endl;
		}
		//else cout<<"abc";	
		//cout<<endl;
	}
	cout<<"Accuracy "<<accuracycount<<endl;
	fprintf(accu, "acc = %d vocabsize=%d\n",accuracycount,vocabsize);
	return 0;
}
