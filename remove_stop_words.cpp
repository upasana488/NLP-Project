#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int main()
{
	char str[1000],stopwords[100][10],temp[100],c,line[500],sign,tab;
	int i,j,k,flag,count=0;
	//stopwords.txt contains all the stop words.
	//new.txt contains processed data, i.e. without stop words.
	FILE *sw=fopen("stopwords.txt","a+");
	FILE *newfile=fopen("new.txt","a+");
	
	//Reading All stop words from file.
	for(i=0;fscanf(sw,"%s",stopwords[i])!=-1;i++);
	
	FILE * fp= fopen("NLP.data.set.full.txt","a+");
	while(!feof(fp))
	{
		fscanf(fp,"%c",&sign);
		fscanf(fp,"%c",&tab);
		//cout<<sign;
		fprintf(newfile,"%c ",sign);
		//fscanf(fp,"%c",&c);
		fgets(str,999,fp);
		
		i=0;
		//converting to lower case;
		while(str[i])
		{
			if(str[i]<='Z' && str[i]>='A')
				str[i]=str[i]+32;
			i++;
		}
		
		//processing each line
		for(i=0;str[i]!='\0';i++)
		{
			j=0;
			//reading word by word
			while((str[i]<='z' && str[i]>='a') || str[i]==39)
				temp[j++]=str[i++];
			temp[j]='\0';
			flag=0;
			
			//checking if word is stop word
			for(k=0;k<100;k++)
			{
				if(strcmp(temp,stopwords[k])==0)
				{
					flag=1;
					break;
				}
			}
			//if flag is 0 i.e. word is not stop word.
			if(flag==0)
				fprintf(newfile,"%s ",temp);
		}
		fprintf(newfile,"%c",'\n');
	}
	return 0;
}
