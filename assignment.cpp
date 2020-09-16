#include<iostream>
#include "list.h"
using namespace std;


int main(int argc, char const *argv[])
{
    
    
    int value  = 1;
    list l;//we create the array only one time
    while(value){
        cout<<"Select an option"<<"\n";  
        cout<<"1. Create a new list"<<"\n";
        cout<<"2. Insert a new element in a given list in sorted order"<<"\n";
        cout<<"3. Delete an element from a given list"<<"\n";
        cout<<"4. Count total elements excluding free list"<<"\n";
        cout<<"5. Count total elements of a list"<<"\n";
        cout<<"6. Display all lists"<<"\n";
        cout<<"7. Display free list"<<"\n";
        cout<<"8. Perform defragmentation"<<"\n";
        cout<<"9. Press 0 to exit"<<"\n";

        int option;
        cin>>option;
        switch(option){
            case 0: value = 0;break; //to exit 
            case 1:  l.createnewlist();break;
            case 2: l.insertnewelement(); break;
            case 3: l.deleteElement(); break;
            case 4: l.countallele(); break;
            case 5: l.totalElementsOfList(); break;
            case 6: l.displayAllList();  break;
            case 7: l.displayfreelist(); break;
            case 8: l.defragmentation(); break;
                
        }

    } 

    return 0;
}
