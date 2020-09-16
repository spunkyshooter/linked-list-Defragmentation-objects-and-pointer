#include "list.h"
#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

//initially we have only free list
list::list(){
	array_size = 99;
	free = 0;
	for(int i = 1; i< array_size-3; i += 3){
		array[i-1] = INT_MIN;
		array[i] = i+2;
	}
	array[array_size -3] = INT_MIN;
	array[array_size-2] = -1;
}

/* for option 1*/
void list::createnewlist(){
	/*inputs*/int m;
            cout<<"The sequence number of the newly created list is: "<<storelisthead.size()+1<<"\n";
            cout<<"Enter key value to be inserted in the newly created list-"<<storelisthead.size()+1<<": ";
            cin>>m;
	//check wheter our array has free space or not.
	if(this->free == -1){ cout<<"FAILURE: MEMORY NOT AVAILABLE\n"; return;}
	//if the array has space then update free to it next attribute
	int temp = free; //store the free index
	free =  array[free + 1]; // now free has updated

	array[temp] = m; //storing the element
	array[temp + 1] = -1;
	array[temp +2] = -1;
	cout<<"SUCCESS\n";
	storelisthead.push_back(temp);
	//temp holds the index of the newly created list
}


/*for option 2*/
void list::insertnewelement(){
 /*inputs*/ int n,m;
            cout<<"List you want to insert in: "; cin>> n;
            cout<<"Enter the key value: "; cin>>m;

//if list number doesn't exists or if we dont have free space then its failure
if(n > this->storelisthead.size() || this->free == -1){ cout<<"FAILURE: MEMORY NOT AVAILABLE\n"; return;}

//now we need to traverse upto last object of the particular list.
int head = this->storelisthead[n-1];// n-1 because internally index starts from 0. so list 1's head will be stored in 0th index
int temp = free;
free = array[free +1]; //updating the free list head
if(head ==  -1){
	//i.e list was first allocated and emptied afterwards.

	storelisthead[n-1] = temp; //free head
	array[temp] = m;
	array[temp + 1 ] = -1;
}
else {
	while(array[head + 1] != -1){
		head = array[head + 1];
	}//now head will be storing the last object hence we can easily link the next object

	array[temp] = m; //storing the element's key
	array[head + 1] = temp; //linking the list to new object. i,e lastobject.next = newobject
	array[temp + 2] = head; //linking the newobject to list. i.e newobject.prev = lastobject
	array[temp + 1] =  -1; //next part of the new object is "/" i.e -1(here) 
}

cout<<"SUCCESS\n";
}
/*for option 3*/
void list::deleteElement(){
	int n,m;
	 cout<<"List you want to delete from: "; cin>>n;
     cout<<"Enter the key value: "; cin>>m;
	if(n > storelisthead.size() || storelisthead[n-1] == -1){cout<<"FAILURE: ELEMENT NOT THERE / LIST EMPTY\n"; return;}
	int head = storelisthead[n-1];
	while(head != -1){
		if(array[head] == m) break;
		head = array[head + 1];
		}
	if(head == -1){ cout<<"FAILURE: ELEMENT NOT THERE / LIST EMPTY\n"; return;}
	//if execution comes to this point then it indicates we have that particular node.
	//int tempfree = free;
	//node at starting position
	if(head == storelisthead[n-1]){
		int next = array[head + 1];
		storelisthead[n-1] = next; //updating the head of the list
		array[next + 2] = -1;//prev of next node is null
		array[head] = INT_MIN;
		array[head + 1] = free; //next part of the found node is updated to free. prev is by default null
		
		free = head;
	}
	else if(array[head + 1] == -1){ //if it is last node
		int prev = array[head + 2];
		array[prev + 1] = -1;
		array[head + 2] = -1; //prev is null
		array[head + 1] = free;
		array[head] = INT_MIN;//key is empty
		free = head;//updated the free
	}
	else{//if node is in middle
		int prev,next;
		prev = array[head + 2];
		next = array[head + 1];
		array[prev + 1] = next;
		array[next + 2] = prev;
		array[head] = INT_MIN; array[head + 1] = free; array[head + 2] = -1;
		free = head;
	}
	
	cout<<"SUCCESS\n";
}

/*for option 4*/
void list::countallele(){

	int count = 0;
	for(int x : storelisthead){ //x has the index of the list head
		int y = x;
		while(y != -1){
			count++;
			y = array[y + 1];
		}
	}
	cout<<"Total number of nodes in all lists are: "<<count<<"\n";
}

/*for option 5*/
void list::totalElementsOfList(){
	int n;
	cout<<"Enter the list number: "; cin>>n;
	int head = this->storelisthead[n-1]; //assuming that always n will be valid
	int count = 0;
	while(head != -1){
			count++;
			head = array[head + 1];
		}
	cout<<"Total number of nodes in all lists are: "<<count<<"\n";
}

/*for option 6*/
void list::displayAllList(){
	int hindex = 1; //to show the list number
	for(int x : storelisthead){ //x has the index of the list head
		cout<<"Elements of list-"<<hindex++<<" are:\n";
		cout<<"key  next  prev"<<"\n";
		int y = x;
		while(y != -1){
			cout<<array[y]<<"  ";
			if(array[y+1] == -1) cout<<"NIL  ";
			else cout<<array[y+1]<<"  ";
			if(array[y+2] == -1) cout<<"NIL\n";
			else cout<<array[y+2]<<"\n";

			y = array[y + 1];
		}
		cout<<"\n";
	}
}

/*for option 7*/
void list::displayfreelist(){
	int temp = free; //storing the head of free list, so that it wont get affected.
	cout<<"[";
	while(temp != -1){
		cout<<temp<<" ,";
		temp = array[temp + 1];
	} 
	cout<<"]\n";
}

/*for option 8*/
void list::defragmentation(){
	std::map<int,int> mvi; //to store number of free objects in from starting to that particular node
	int count = 0;
	for(int i = 0; i<array_size;i += 3){
		if(array[i] == INT_MIN){ count++; }
		else{
			mvi.insert({i,count});
		}
	}
	if(count == 0){cout<<"SUCCESS\n"; return;}// no free spaces

	int nodenumber = 0;//as we traverse, we keep note of the node number
	auto iit = mvi.rbegin(); int ii = iit->first;
	for(int i = 0; i <= ii ; i += 3){
		
		if(array[i] == INT_MIN) continue;//free list nodes
		else {
				int index = nodenumber*3;
				array[index] = array[i];
				int a,b;
				if(array[i+1] == -1){ a = 0;}
				else{
					a = 3*mvi[array[i+1]];
				}
				if(array[i+2] == -1){//in this case i is the head of some list
					//update the storeheadlist
					for(auto x = storelisthead.begin() ; x != storelisthead.end() ; x++){
						if(*x == i){//finding the 
							*x = index; break;
						}
					}
					b = 0;
				}
				else{
					b = 3*mvi[array[i+2]];
				}
				array[index + 1] = array[i+1] - a;
				array[index + 2] = array[i+2] - b;
				nodenumber++;
			}
		}
		free = nodenumber*3;//setting the free head
		while(nodenumber*3 < array_size-3){
			
			int index = nodenumber*3;
			array[index] = INT_MIN;
			array[index + 1] = index + 3;
			nodenumber++;
		}
		array[array_size-3] = INT_MIN;
		array[array_size - 2] = -1;

		//updating the storeheadlist

cout<<"SUCCESS\n";
return;

}
