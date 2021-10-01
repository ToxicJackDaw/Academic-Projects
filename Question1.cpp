//Author j: Kabeer Sheikh

#include <iostream>
using namespace std;

struct Student 
{
   int age;
   double fee;
   string name;

   Student() // no arguement constructor
   {
       age = 0;
       fee = 0.0;
       name = " ";
   }

   Student (int Age, double Fee, string Name) // constructor with arguements
   {
       age = Age;
       fee = Fee;
       name = Name;
   }
};

struct Node 
{
    Student datum;
    Node* pNext;
    Node* pPrev;

    Node() // no arguement constructor
    {
        datum.age = 0;
        datum.fee = 0;
        datum.name = " ";
        pNext = nullptr;
        pPrev = nullptr;
    }

    Node (Student student, Node* Next, Node* Prev) // constructor with arguements 
    {
        datum = student;
        pNext = Next;
        pPrev = Prev;
    }
};

struct sortedLinkedList // contains data for pHead and pTail which will be required later in the code
{
    Node* pHead; // for the head of node
    Node* pTail; // for the tail of the node

    sortedLinkedList() // no arguement constructor
    {
        pHead = nullptr;
        pTail = nullptr;
    }

    // create a function that helps create list in the code
    void createList() 
    {
        cout << "Enter the number of nodes that you want to have in the list: " << endl; // first to ask the user for the numbr of nodes in the list
        int numberOfNodes;
        cin >> numberOfNodes; // input from the user for the total number of nodes. In our case this is 5

        Node* pNewNode; // this helps in filling in values for our items that are created in the list and store their respective addresses
        cout << "Enter your Name, Age and Fees in the 0th node: " << endl;
        int inputage; // declaring input values that helps in creating multiple user inputs according to the number of nodes requested
        double inputfee;
        string inputname;

        cin >> inputname; // asking user input for the following respective values
        cin >> inputage;
        cin >> inputfee;        

        Student student1; 
        student1.name = inputname;
        student1.age = inputage;
        student1.fee = inputfee;

        pNewNode = new Node(student1, nullptr, nullptr); // creating a new space in the heap. This uses the constructor in struct Node.
        pHead = pNewNode;
        pTail = pNewNode;

        int count = 0; // for the while loop

        while (count!= (numberOfNodes-1)) 
        {
            cout << "Enter the value to be inserted in the " << count + 1 << " node: " << endl;
            cin >> inputname;
            cin >> inputage;
            cin >> inputfee;
            pNewNode = new Node (student1, nullptr, nullptr); // this also uses the constructor in the struct node
            pNewNode->pPrev = pTail; // using arrow operator to access it's data component
            pNewNode->pNext = pHead;
            pTail = pNewNode;
            count++;
        }
        pTail->pNext = nullptr;
    }

    // A function that prints from head to tail
     void printLinkedListFromHead() 
        {
            cout << "The list from head is as follows: " << endl;
            for (Node* p = pHead; p != nullptr; p = p->pNext) // this for loop is similar to our traditional for loop 
            { // for (int i = 1; i != 0; i++)
                cout << p->datum.name << " " << p->datum.age << " " << p->datum.fee << endl;
            }
            cout << endl;
        }

    void printLinkedListFromTail()
    {
        cout << "The list from tail is as follows: " << endl;
        for (Node* p = pTail; p != nullptr; p = p->pNext) // similar to the head function but instal of pHead we put in pTail
        {
            cout << p->datum.name << " " << p->datum.age << " " << p->datum.fee << endl;
        }
        cout << endl;
    }

    Node* searchLinkedList(Node* pHead, Node* pTail, int x) // function that helps us search our list and identify places 
    {
        Node* pPrevious = nullptr; // this gives us the node that comes before our inserted node
        Node* pCurrent = pHead; // our current node is set to pHead considering it is on the top of the list

        if (pCurrent == nullptr) // Case 1. If our pCurrent is nullptr we just return pPrevious
        {
            return pPrevious;
        }
        else // if Case 1 is not our conditoin then...
        {
            if (pHead->datum.age >=x) // our age in the list if it is >=x then we return pPrevious
            {
                return pPrevious;
            }
            else if (pTail->datum.age <= x) // or if our x is <= to the value at the end of tail
            {
                return pPrevious; // we return 
            }
            else 
            { // this loop starts from the beginning of our list and stops until our value is < x
                while (pCurrent->datum.age < x)
                {
                    pPrevious = pCurrent;
                    pCurrent = pCurrent->pNext;
                }
                return pPrevious;
            }
        }
    }

    void insertNode(int x) // insert function that helps us insert age in our list
    {
        Node* pPrevious = searchLinkedList(pHead, pTail, x); // this also works on our struct node constructor
        Node* pCurrent = new Node; // creting new memory in the heap or space
        pCurrent->datum.age = x; // intializing our pCurrent value so thare is no confusion with string or double

        if (pPrevious == nullptr)
        {
            if (pHead == nullptr)
            {
                pCurrent->datum.age = x;
                pHead = pCurrent; // here both head and tail are storing the address...
                pTail = pCurrent; // ...but they are not equal because we are just storing address
            }
            else if (pHead->datum.age>=x) // Case: if our datum value for pHead is >= x
            {
                pCurrent->pNext = pHead;
                pHead->pPrev = pCurrent;
                pHead = pCurrent;
            }
            else if (pTail->datum.age <= x) // Case: if our datum value for pTail is <= x
            {
                pCurrent->pNext = pTail;
                pTail->pNext = pCurrent;
                pTail = pCurrent;
            }
        }
        else
        {
            pCurrent->pNext = pPrevious->pNext;
            pPrevious->pNext->pPrev = pCurrent; // making the connection

            pCurrent->pPrev = pPrevious;
            pPrevious->pNext = pCurrent;
        }
    }

    // A function that helps us to remove node from our list and link the respective other notes accordingly
    void removeNode(int x)
    {   // this function helps us find the address of the previous and the next node between our x so that we can make the connection
        Node* pPrevious = searchLinkedList(pHead, pTail, x); // constructor from the struct node
        if (pPrevious == nullptr) // this will only happen when our while loop above is not satisfied
        {
            if (pHead->datum.age == x)
            {
                Node* pToRemove = pHead;
                pToRemove->pNext->pPrev = nullptr;
                pHead = pToRemove->pNext;
                delete pToRemove;
            }
            else if (pTail->datum.age == x)
            {
                Node* pToRemove = pTail;
                pToRemove->pPrev->pNext = nullptr;
                pTail = pToRemove->pPrev;
                delete pToRemove; // delete the node in the end after linking previous and next nodes together
            }
        }
        else  // if the list is empty and the body of search link is not executed we have to consider the following code
        {
            if (pPrevious->pNext == nullptr || pPrevious->pNext->datum.age != x)
            {
                return;
            }

            Node* pToRemove = pPrevious->pNext;
            pPrevious->pNext = pToRemove->pNext;
            pToRemove->pNext->pPrev = pPrevious;
            delete pToRemove;
        }
    }

    int number_of_elements_from_head() // this functions counts the number of elements in our list in top to bottom direction
    {
        int length = 0;

        for (Node* p = pHead; p != nullptr; p = p->pNext)
        {
            length++;
        }
        return length;
    }

    // A function that tells us wehter the node belongs to the list or not.
    bool isMember(int x)
    {
        Node* pPrevious = searchLinkedList(pHead, pTail, x);
        
        if (pPrevious == nullptr) 
        {
            if (pHead->datum.age == x)
            {
                return true;
            }
            else if (pTail->datum.age == x) 
            {
                return false;
            }
        }
        else // if (PPrevious != nullptr) 
         {
            return (pPrevious->pNext!=nullptr && pPrevious->pNext->datum.age == x);
         }
    }    
};

int main()
{
    
}
