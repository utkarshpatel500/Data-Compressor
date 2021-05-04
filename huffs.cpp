#include <bits/stdc++.h>
#include<fstream>
using namespace std;
struct node
{
	int freq;
	char c;
	struct node *left,*right;
};
struct node* root=NULL;
std::vector<pair<int,pair<char,struct node*>>>v;
std::map<char, string> mp1;
void huffcodes(struct node* root,int ve[],int i)
{
	if(root->left)
	{
		ve[i]=0;
		huffcodes(root->left,ve,i+1);
	}
	if(root->right)
	{
		ve[i]=1;
		huffcodes(root->right,ve,i+1);
	}
	if(root->left==NULL&&root->right==NULL)
	{
		string st="";
		//cout<<root->c<<" : ";
		for(int it=0;it<i;it++)
		{
		//	cout<<ve[it];
			if(ve[it]==1)
				st+='1';
			else
				st+='0';
		}
		//cout<<"\n";
		mp1[root->c]=st;
	}
}
void buildhofftree()
{
	while(v.size()>1)
	{
		sort(v.begin(), v.end()); 
		if(v[0].second.first!='*'&&v[1].second.first!='*')
		{
			int a=v[0].first;int b=v[1].first;
			struct node* temp=(struct node*)malloc(sizeof(struct node));
			temp->left=NULL;
			temp->right=NULL;
			temp->freq=v[0].first;
			temp->c=v[0].second.first;

			struct node* temp1=(struct node*)malloc(sizeof(struct node));
			temp1->left=NULL;
			temp1->right=NULL;
			temp1->freq=v[1].first;
			temp1->c=v[1].second.first;

			struct node* temp2=(struct node*)malloc(sizeof(struct node));
			temp2->left=temp;
			temp2->right=temp1;
			temp2->freq=v[0].first+v[1].first;
			temp2->c='*';

			v.erase(v.begin());
			v.erase(v.begin());
			v.push_back({a+b,{'*',temp2}});
		}
		else if(v[0].second.first=='*'&&v[1].second.first!='*')
		{
			int a=v[0].first;int b=v[1].first;
			
			struct node* temp1=(struct node*)malloc(sizeof(struct node));
			temp1->left=NULL;
			temp1->right=NULL;
			temp1->freq=v[1].first;
			temp1->c=v[1].second.first;

			struct node* temp2=(struct node*)malloc(sizeof(struct node));
			temp2->left=v[0].second.second;
			temp2->right=temp1;
			temp2->freq=v[0].first+v[1].first;
			temp2->c='*';

			v.erase(v.begin());
			v.erase(v.begin());
			v.push_back({a+b,{'*',temp2}});
		}
		else if(v[0].second.first!='*'&&v[1].second.first=='*')
		{
			int a=v[0].first;int b=v[1].first;
			
			struct node* temp=(struct node*)malloc(sizeof(struct node));
			temp->left=NULL;
			temp->right=NULL;
			temp->freq=v[0].first;
			temp->c=v[0].second.first;

			struct node* temp2=(struct node*)malloc(sizeof(struct node));
			temp2->left=temp;
			temp2->right=v[1].second.second;
			temp2->freq=v[0].first+v[1].first;
			temp2->c='*';

			v.erase(v.begin());
			v.erase(v.begin());
			v.push_back({a+b,{'*',temp2}});
		}
		else
		{
			int a=v[0].first;int b=v[1].first;
			struct node* temp2=(struct node*)malloc(sizeof(struct node));
			temp2->left=v[0].second.second;
			temp2->right=v[1].second.second;
			temp2->freq=v[0].first+v[1].first;
			temp2->c='*';

			v.erase(v.begin());
			v.erase(v.begin());
			v.push_back({a+b,{'*',temp2}});
		}
	}
	root=v[0].second.second;
	//cout<<root->freq;
	int ve[100];
	huffcodes(root,ve,0);
}
int main()
{
	std::map<char, int> mp;
	ifstream fin;
	string line;
	fin.open("input.txt",ios::binary);
	while(fin)
	{
		getline(fin,line);
		for(int j=0;j<line.length();j++)
			mp[line[j]]++;
	}
	fin.close();
	int i;
	//char arr[]={'*','e','b','c','f','a','d'};
	//int fre[]={0,16,9,12,45,5,13};
	for(auto it=mp.begin();it!=mp.end();it++)
	{
		v.push_back({it->second,{it->first,0}});
	}
	
	/*for(i=0;i<=6;i++)
	{
		cout<<v[i].first<<" "<<v[i].second.first<<" "<<v[i].second.second<<"\n";
	}*/
	buildhofftree();
	for(auto it=mp1.begin();it!=mp1.end();it++)
	{
		cout<<it->first<<" "<<it->second<<'\n';
	}
	char ch;
	ofstream fout;
	fin.open("input.txt",ios::binary);
	fout.open("hufcode.bin",ios::binary);
	while(!fin.eof())
	{
		fin.get(ch);
			fout<<mp1[ch];
	}
	fin.close();
	fout.close();
	fin.open("hufcode.bin",ios::binary);
	
	fout.open("hufdecode.txt",ios::binary);
	struct node* tr=root;
	while(!fin.eof())
    {
        fin.get(ch);
        if(ch=='0')
        	tr=tr->left;
        else if(ch=='1')
        	tr=tr->right;
        if(tr->left==NULL&&tr->right==NULL)
        {
        	fout<<tr->c;
        	tr=root;
        }
    }
    fout.close();
    fin.close();
}