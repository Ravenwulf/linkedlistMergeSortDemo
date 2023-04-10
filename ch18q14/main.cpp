// This program illustrates the building  
// and traversal of a linked list.
#include <iostream>
#include <fstream>
using namespace std;

struct ListNode
  {
     double value;
     ListNode *next;
     // Constructor
     ListNode(double value1, ListNode *next1 = nullptr)
     {
       value = value1;
       next = next1;
     }
  };

void sort(ListNode* aList) {

    if (aList->next == nullptr)
        return;
    ListNode* temp = aList->next;
    sort(temp);
    if (temp->value < aList->value) {
        double tempVal = aList->value;
        aList->value = temp->value;
        temp->value = tempVal;
        sort(aList);
    }
    return;
}

ListNode* add(ListNode* aList, double value)
{
    if (aList == nullptr)
        return new ListNode(value);
    else
    {
        // add the value to the end of the tail
        aList->next = add(aList->next, value);
        return aList;
    }
}

ListNode* remove(ListNode* aList, double value)
{
    if (aList == nullptr) return nullptr;
    if (aList->value == value)
    {
        ListNode* tail = aList->next;
        delete aList;
        return tail;
    }
    else
    {
        aList->next = remove(aList->next, value);
        return aList;
    }
}



ListNode* merge(ListNode* list1, ListNode* list2) {
    if (!list1) {
        if (!list2)
            return nullptr;
        return list2;
    } else if (!list2) {
        return list1;
    }

    while (list1 != nullptr) {
        list2 = remove(list2, list1->value);
        list2 = add(list2, list1->value);
        list1 = list1->next;
    }
    
    return list2;
}


int main()
{
    double number;                    // Used to read the file
    ListNode* numberList1 = nullptr;   // List of numbers
    ListNode* numberList2 = nullptr;   // List of numbers

    // Open the file
    ifstream numberFile("numberFile.dat");
    if (!numberFile)
    {
        cout << "Error in opening the file of numbers.";
        exit(1);
    }
    // Read the file into a linked list    
    cout << "The contents of list1 are: " << endl;
    while (numberFile >> number && number != -1)
    {
      cout << number << "  ";
      // Create a node to hold this number
      numberList1 = new ListNode(number, numberList1);
    }

    cout << endl << "The contents of list2 are: " << endl;
    while (numberFile >> number && number != -1)
    {
        cout << number << "  ";
        // Create a node to hold this number
        numberList2 = new ListNode(number, numberList2);
    }

   cout << endl << "Sorting list1... ";
   sort(numberList1);
   cout << endl << "The contents of list1 are: " << endl;
   ListNode* ptr = numberList1;
   while (ptr != nullptr)
   {
       cout << ptr->value << "  "; // Process node
       ptr = ptr->next;            // Move to next node
   }

   cout << endl << "Sorting list2... ";
   sort(numberList2);
   cout << endl << "The contents of list2 are: " << endl;
   ptr = numberList2;
   while (ptr != nullptr)
   {
       cout << ptr->value << "  "; // Process node
       ptr = ptr->next;            // Move to next node
   }

   cout << endl << "Merging lists... ";
   ListNode* mergedList = merge(numberList1, numberList2);
   sort(mergedList);
   cout << endl << "The sorted contents of merged list are: " << endl;
   ptr = mergedList;
   while (ptr != nullptr)
   {
       cout << ptr->value << "  "; // Process node
       ptr = ptr->next;            // Move to next node
   }

   return 0;
}