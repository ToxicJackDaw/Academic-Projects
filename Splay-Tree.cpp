//Name: Kabeer Sheikh
//Student ID: 200438835
//Question 2
//Part of this code has been borrowed from Professor's notes

#include <iostream>
#include <string> //in case we need it

using namespace std;

struct Student
{
    string name;
    int age;
    double fee;

    Student() 
    {
        name = " ";
        age = 0;
        fee = 0;
    }

    Student(string Name, int Age, double Fee) 
    {
        name = Name;
        age = Age;
        fee = Fee;
    }
};

struct Node
{
    int key;
    string name;
    double fee;
    Node *pLeft; //node for the left pointer
    Node *pRight; //node for the right pointer

    Node()
    { //no arg constructor 
        name = " ";
        key = 0;
        fee = 0.0;
        pLeft = nullptr;
        pRight = nullptr;
    }
};

Node *newNode(Student student1)
{   //node which contains the instances of student with the left and right pointer 
    Node *pNode = new Node();
    pNode->name = student1.name;
    pNode->key = student1.age;
    pNode->fee = student1.fee;
    pNode->pLeft = nullptr;
    pNode->pRight = nullptr;
    return pNode;
}

Node *rightRotation(Node *node)
{   //function to rotate right 
    Node *temp = node->pLeft;
    node->pLeft = temp->pRight;
    temp->pRight = node;
    return temp;
}

Node *leftRotation(Node *node)
{   //function to rotate left 
    Node *temp = node->pRight;
    node->pRight = temp->pLeft;
    temp->pLeft = node;
    return temp;
}

Node *splayTree(Node *root, Student student1)
{   //if this is the case then the node lies on the left side 
    if (root == nullptr || root->key == student1.age)
    {
        return root;
    }

    //now we are going to consider if the node is left child of the sub tree 
    if (root->key > student1.age)
    {   //zig zag situtation 
        if (root->pLeft == nullptr)
        {
            return root;
        }
        if (root->pLeft->key > student1.age)
        {   //we keep searching if this is the case 
            root->pLeft->pLeft = splayTree(root->pLeft->pLeft, student1);

            if (root->pLeft->pLeft != nullptr)
            {
                root = rightRotation(root);
            }
        }
        else if (root->pLeft->key < student1.age)
        {   //same for this case 
            root->pLeft->pRight = splayTree(root->pLeft->pRight, student1);
            if (root->pLeft->pRight != nullptr)
            {
                root->pLeft = leftRotation(root->pLeft);
            }
        }
        return (root->pLeft == nullptr) ? root : rightRotation(root); //if child of the root node lies on the left sub tree
    }
    else
    {
        if (root->pRight == nullptr)
        {
            return root;
        }
        if (root->pRight->key > student1.age)
        {   //now we are going to consideer if the node is right child of the rightSubTree
            root->pRight->pLeft = splayTree(root->pRight->pLeft, student1);
            if (root->pRight->pLeft != nullptr) //zig zag sitatuon.
            {
                root->pRight = rightRotation(root->pRight);
            }
        }
        else if (root->pRight->key < student1.age)
        {
            root->pRight->pRight = splayTree(root->pRight->pRight, student1); //keep searching if this is the case 
            if (root->pRight->pRight != nullptr)
            {
                root = leftRotation(root);
            }
        }
        return (root->pRight == nullptr) ? root : leftRotation(root); //if the chld of the root lies on the rightsubtree
    }
}

Node *searchNode(Node *root, Student student1)
{   //recursive searchfunction that finds the location of our element
    return splayTree(root, student1);
}

void preOrderTraversal(Node *node)
{   //prints the tree in preorder traversal 
    if (node != nullptr)
    {
        cout << node->name << " ";
        cout << node->key << " ";
        cout << node->fee << " ";
        preOrderTraversal(node->pLeft);
        preOrderTraversal(node->pRight);
    }
}

Node *insertNode(Node *root, Student student1)
{
    //function to insert node 
    if (root == nullptr)
    {
        return newNode(student1); //if null then just return
    }
    root = splayTree(root, student1);

    if (root->key == student1.age)
    {
        return root; //if the key is > than our inserted age then just return 
    }

    Node *pNewNode = newNode(student1);

    if (root->key > student1.age)
    {
        pNewNode->pRight = root; //we make a new node and apply these settings 
        pNewNode->pLeft = root->pLeft;
        root->pLeft = nullptr;
    }
    else
    {
        pNewNode->pLeft = root; //if the age is bigger than our key 
        pNewNode->pRight = root->pRight;
        root->pRight = nullptr;
    }
    return pNewNode;
}

Node *deleteNode(Node *root, Student student1)
{   //function to delete a node from our list 
    Node *pToRemove;

    if (root == nullptr)
    {
        return nullptr; //if empty just return 
    }

    if (!root)
    {
        return nullptr; //if is not equal to root it is nullptr 
    }

    root = splayTree(root, student1);

    if (student1.age != root->key)
    {
        return root; //if the age is not equal to our value than just return 
    }

    if (root->pLeft == nullptr)
    {   //if the left side equals to null value we delete it 
        pToRemove = root;
        root = root->pRight;
    }
    else
    {   //similary if it is the right side we delete it 
        pToRemove = root;
        root = splayTree(root->pLeft, student1);
        root->pRight = pToRemove->pRight;
    }

    delete pToRemove;

    return root; //we return the root value 
}

int main()
{

    Student student0("Kabeer", 19, 35.17); //7 instances of struct student 
    Student student1("John", 21, 31.65);
    Student student2("Paul", 25, 33.43);
    Student student3("Kaur", 18, 34.93);
    Student student4("Patel", 23, 36.37);
    Student student5("Alexander", 22, 33.78);
    Student student6("Ramesh", 27, 34.46);

    Node *root = newNode(student0); //giving each of them their place in the tree 
    root->pRight = newNode(student1);
    root->pRight->pRight = newNode(student2);
    root->pLeft = newNode(student3);
    root->pRight->pRight->pLeft = newNode(student4);
    root->pRight->pRight->pLeft->pLeft = newNode(student5);
    root->pRight->pRight->pRight = newNode(student6);

    insertNode(root, student0); //inserting them at the right place in the tree
    insertNode(root->pRight, student1);
    insertNode(root->pRight->pRight, student2);
    insertNode(root->pLeft, student3);
    insertNode(root->pRight->pRight->pLeft, student4);
    insertNode(root->pRight->pRight->pLeft->pLeft, student5);
    insertNode(root->pRight->pRight->pRight, student6);

    preOrderTraversal(root); //prinint in pre order traversal 
    cout << endl;

    root = deleteNode(root, student1); //deleting student 1 
    root = searchNode(root, student5); //searching student 5

    preOrderTraversal(root); //printing afte searching and deleting 
    cout << endl;

    return 0;
}