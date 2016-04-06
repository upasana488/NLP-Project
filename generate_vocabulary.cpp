#include<bits/stdc++.h>
using namespace std;
char sign;
int totalpos=0,totalneg=0;
FILE *vocab=fopen("vocabulary.txt","a+");
//structure of BST
struct node
{
	char str[100];					//word
	int countpos,countneg;						//occurence of word
	struct node* left,*right;
};
struct node*insert(struct node*root,struct node*temp)
{
		if(root==NULL )
		{
			if(sign=='+')
				temp->countpos++;
			else if(sign=='-')
				temp->countneg++;
			return temp;
		}
		//condition if word already exist in the tree.
		if(strcmp(temp->str,root->str)==0)
		{
			if(sign=='+')
				root->countpos++;
			else if(sign=='-')
				root->countneg++;
			return root;
		}
		if(strcmp(temp->str,root->str)<0)
			root->left= insert(root->left,temp);
		else
			root->right= insert(root->right,temp);
	return root;
}
//fuction to return new node.
struct node*getnode(char *word)
{
	struct node*temp=(struct node*)malloc(sizeof(struct node));
	strcpy(temp->str,word);
	temp->right=temp->left=NULL;
	temp->countpos=temp->countneg=0;
	return temp;
}
//function to perform inorder traversal and inserting the file vocabulary.txt
void inorder(struct node*root)
{
	if(root)
	{
		inorder(root->left);
		//if(root->countpos && root->countneg)
		if(root->countneg+root->countpos>=2)
			fprintf(vocab,"%s %d %d\n",root->str,root->countpos+1,root->countneg+1);
		if(root->countneg)
			totalneg++;
		if(root->countpos)
			totalpos++;
		//cout<<root->str<<root->countpos<<root->countneg<<endl;
		inorder(root->right);
	}
}
int main()
{
	struct node*root=NULL,*temp;
	int i,j,pos=0,neg=0;
	char word[100],str[500];
	FILE *fp=fopen("new.txt","a+");
	//reading words from file and inserting each word in a BST.
	while(!feof(fp))
	{
		fscanf(fp,"%c",&sign);
		if(sign=='+')
			pos++;
		else if(sign=='-')
			neg++;

		//cout<<sign;
		//fscanf(fp,"%s",word);
		//cout<<word;
		fgets(str,499,fp);
		
		i=0;
			
		//processing each line
		for(i=0;str[i]!='\0';i++)
		{
			j=0;
			//reading word by word
			while((str[i]<='z' && str[i]>='a') || str[i]==39)
				word[j++]=str[i++];
			word[j]='\0';
			//cout<<word<<" ";
			if(strlen(word)>1){	
			temp = getnode(word);
		root = insert(root,temp);
		}
		}
	}
	inorder(root);
	
	cout<<pos<<" "<<neg<<endl;
	cout<<totalpos<<" "<<totalneg<<endl;
	return 0;
}
