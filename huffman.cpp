#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>


class Symbol
{
public:
	string symbl;
   int frequency;
   char code;
   char bits;

   Symbol() : frequency(1), code(0), bits(0)
   {}
};

class LinkNode
{
public:
	int data;
   LinkNode* Next;
   LinkNode* Pre;

   LinkNode() : Next(NULL), Pre(NULL)
   {}
};

class LinkList
{
private:
	LinkNode* First;
   LinkNode* Last;
public:

	LinkList()
   {
     First=Last=NULL;
   }
   void addItem(int d)
   {
   	LinkNode* newnd = new LinkNode();
      newnd->data = d;
      if(First==NULL)
      {
      	First = newnd;
         Last = newnd;
      }
      else
		{
      	Last->Next = newnd;
         newnd->Pre=Last;
         Last = newnd;
      }
   }
	void delItem()
   {
      if(Last == First)
	   {
		   delete Last;
		   First = Last = NULL;
	   }
	   else
	   {
      Last = Last->Pre;
      Last->Next = NULL;
      delete Last->Next;
      }
	}

   void writeOndisk()
   {
   	ofstream codes("codes.dsa",ios::out | ios::binary);
      for(LinkNode* temp=First;temp!=NULL;temp=temp->Next)
      {
           codes.write(reinterpret_cast <char*> (&temp->data),sizeof(int));
      }
   }

   void displayList()
   {
   	for(LinkNode* temp=First;temp!=NULL;temp=temp->Next)
      {
      	cout<<temp->data<<endl;
      }
 	}

};

class Node
{
public:
	Symbol data;
   Node* left;
   Node* right;
   Node* father;
};

class MinQueue
{

	int MAX;
   Node** A;
   int nItems;

public:

   MinQueue(int m)
   {
   	MAX=m;
   	A=new Node*[MAX];
		nItems=0;
   }
	int isFull()
   {
   	return (nItems==MAX);
   }
   int isEmpty()
   {
   	return !(nItems);
   }
   void AddSorted(Node* x)
   {
   	if(!isFull())
      {
   		 int N=nItems-1;
    	 	 while(N>=0 && x->data.frequency>A[N]->data.frequency)
     	 	{
      	  	A[N+1]=A[N];
       	   N--;
     	 	}
			A[N+1]=x;
    	   nItems++;
      }
   	else
      	cout<<"Queue FUll";
   }

   void Add(Node* x)
   {
	if(!isFull())
      {
   		 A[nItems++] = x;
      }
   	else
      	cout<<"Queue FUll";
   }
   Node* Delete()
   {
   	return A[--nItems];
   }
   Node* peek()
   {
   	return A[nItems-1];
   }

   int getnItems()
   {
   	return nItems;
   }

   void display()
   {
   	for(int n=0;n<nItems;n++)
      {
      	cout<<A[n]->data.symbl<<endl<<A[n]->data.frequency<<endl;
      }
   }

};


class FrequencyTable
{
public:
	Node** nodes;
   int nItems;

   FrequencyTable(int size)
   {
   	nodes = new Node*[size];
      nItems = 0;
   }

   void add(Node* newnd)
   {
		nodes[nItems++] = newnd;
   }

   int isInFreqTable(string msg)
	{
	for(int n=0;n<nItems;n++)
   	{
   		if(nodes[n]->data.symbl == msg )
      		return n;
   	}
   	return -1;
	}

	void incrementFreq(int index)
   {
   	nodes[index]->data.frequency++;
   }

	char getCode(string c)
	{
		for(int n=0;n<nItems;n++)
   		{
   			if(nodes[n]->data.symbl == c )
				return nodes[n]->data.code;
   		}
	}

   int isEmpty()
   {
   	return (nItems == 0);
   }
   Node* delNode()
   {
   	return nodes[--nItems];
   }

   void display()
   {
   	for(int n=0;n<nItems;n++)
      {
      	cout<<nodes[n]->data.symbl<<endl<<nodes[n]->data.frequency<<endl<<nodes[n]->data.code<<endl;
      }
   }


};


void main()
{
	cout<<"enter choice: ";
   int choice;
   cin>>choice;
   if(choice==1)
   {

	FrequencyTable ft(26);
	int endbit;
	
	Symbol fsymb;
	char fcode;
	string fsymbl;
	ifstream file("codes.dsa",ios::in | ios::binary);
	ifstream ftable("ftable.dsa",ios::in | ios::binary);
	ofstream output("abc.dsa",ios::out);
	
	ftable>>endbit;
	
	while(!ftable.eof())
	{
  	 	ftable>>fcode>>fsymbl;

		fsymb.code = fcode;
		fsymb.symbl = fsymbl;
		Node* fnode = new Node();
		fnode->data = fsymb;
		ft.add(fnode);
	}

   int Integer = 0;
   int Intcount = 0;
   unsigned int MSB=0;
   int LSB=0;
   int bit = 0;
	while(file.read(reinterpret_cast <char*> (&Integer),sizeof(int)))
	{
      MSB = 2147483648;

      Intcount = 0;

   	while(Intcount<=32 && Intcount<endbit)
      {

      	if(Integer & MSB)
         {
         	bit = bit << 1;
            bit = bit | 1;
            MSB = MSB >> 1;
         }
         else
         {
            bit = bit << 1;
            MSB = MSB >> 1;
         }

		for(int n=0;n<ft.nItems;n++)
		{
			if(ft.nodes[n]->data.code == bit)
			{
				output<<ft.nodes[n]->data.symbl;
            bit = 0;
            break;
			}
		}
      Intcount++;

      }
	}

	}
   else
   {
	
	FrequencyTable ft(26);
   int symbIndex;
	string charsymbl;
	//cout<<"Enter the message: ";
	char* f = "abc.txt";
   string msg;
  // cin>>msg;
   ifstream file(f,ios::in);



   // *-----------(Input and make nodes, then add in frequency table)-----------*


   while(!file.eof())
   {
   file>>msg;
   for(int n=0;n<msg.length();n++)
   {
   	charsymbl = msg[n];

   	symbIndex = ft.isInFreqTable(charsymbl);

   	if(symbIndex >= 0)
      {
		  ft.incrementFreq(symbIndex);
      }
      else
      {
      	Node* newItem = new Node();
         newItem->data.symbl = charsymbl;
      	ft.add(newItem);
      }
   }
  }
  file.close();


   // *-----------(Add nodes from frequency table to Min Priority Queue)--------------*

	MinQueue queue(150);

   for(int n=0;n<ft.nItems;n++)
   {
   	queue.AddSorted(ft.nodes[n]);
   }
   Node* Root;

   while(queue.getnItems()>1)
   {
   	Node* node1;
      node1 = queue.Delete();
   	Node* node2;
      node2 = queue.Delete();

   	Node* Pnode = new Node();

   	Pnode->data.symbl = node2->data.symbl + node1->data.symbl;
  	 	Pnode->data.frequency = node1->data.frequency + node2->data.frequency;

   	Pnode->left = node2;
   	Pnode->right = node1;
      node1->father = node2->father = Pnode;

      Root = Pnode;

   	queue.Add(Pnode);
   }


	for(int n=0;n<ft.nItems;n++)
	{
     		Node* t = ft.nodes[n];
		Node* leaf = t;
		  while(t != Root)
		  {
      		if(t == t->father->left)
      		{
      			leaf->data.bits++;
      		}
      		else
      		{
      			if(leaf->data.bits!= 0)
         		{
         			leaf->data.code = leaf->data.code | (1<<leaf->data.bits);
            		leaf->data.bits++;
         		}
				else
         		{
					leaf->data.code = 1;
            		leaf->data.bits++;
         		}
      		}
			t = t->father;
   		}
   }


   LinkList* List = new LinkList();

   int Intcount = 0, Integer = 0;
	file.open(f,ios::in);
	while(!file.eof())
   {
		file>>msg;
   for(int n=0;n<msg.length();n++)
   {
   	charsymbl = msg[n];

   	symbIndex = ft.isInFreqTable(charsymbl);

   	if(symbIndex >= 0)
      {

   //	Intcount = Intcount+(ft.nodes[symbIndex]->data.bits);
      if(Intcount<=32)
      {
      	Integer = Integer <<(ft.nodes[symbIndex]->data.bits);
         Integer = Integer | ft.nodes[symbIndex]->data.code;
         Intcount = Intcount + (ft.nodes[symbIndex]->data.bits);
      }
      else
      {
      	int Outbits = Intcount - 32;
         int Inbits = (ft.nodes[symbIndex]->data.bits) - Outbits;
         Integer = Integer << Inbits;
         ft.nodes[symbIndex]->data.code = ft.nodes[symbIndex]->data.code >> Outbits;
         int t = 1;
         for(int n=0;n<Inbits;n++)
         {
         	if(t & ft.nodes[symbIndex]->data.code)
            {
            	Integer = Integer | t;
            }
            t = t << 1;
         }
      	List->addItem(Integer);
      	Integer = 0;
      	Intcount = 0;
      	ft.nodes[symbIndex]->data.code = ft.nodes[symbIndex]->data.code << Outbits;
         t = 1;
         for(int n=0;n<Outbits;n++)
         {
         	if(t & ft.nodes[symbIndex]->data.code)
            {
            	Integer = Integer | t;
            }
            t = t << 1;
         }
         Intcount = Outbits;
      }
   }
    else
      {
			cout<<"character not found";
			getch();
      }
   }
   }
	file.close();

	ofstream ftable("ftable.dsa",ios::out | ios::binary);
	ftable<<Intcount<<endl;
	for(int n=0;n<ft.nItems;n++)
	{
		ftable<<ft.nodes[n]->data.code<<endl;
		ftable<<ft.nodes[n]->data.symbl<<endl;
	}

	ftable.close();

   if(Intcount != 32 && Intcount != 0)
   {
   	List->addItem(Integer);
   }

   for(int n=0;n<(32-Intcount);n++)
   {
   	Integer = Integer << 1;
   }
   List->delItem();
   List->addItem(Integer);
   List->writeOndisk();




/*	ofstream codes("codes.dsa",ios::out | ios::binary);
	file.open(f,ios::in);
	while(!file.eof())
   {
		file>>msg;
   for(int n=0;n<msg.length();n++)
   {
   	charsymbl = msg[n];

   	symbIndex = ft.isInFreqTable(charsymbl);

   	if(symbIndex >= 0)
      {
		  codes<<ft.nodes[symbIndex]->data.code;
      }
      else
      {
		cout<<"character not found";
		getch();
      }
   }
   }  */
	cout<<"done";
   getch();
   }

}




