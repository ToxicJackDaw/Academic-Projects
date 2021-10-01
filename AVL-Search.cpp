//Name: Kabeer Sheikh
//Student ID: 200438835
//Question 1
//Part of this code has been borrowed from professor's notes

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Student 
{
    string name;
    int age;
    double fee;

    Student()
    {   //no arg constructor
        name = " ";
        age = 0;
        fee = 0;
    }
    Student(string Name, int Age, double Fee)
    { //arguement constructor
        name = Name;
        age = Age;
        fee = Fee;
    }
};
struct Node
{   //simlar to doubly linked list
    Student datum;
    Node *pLeft;  //for the left child
    Node *pRight; //for the right child
    int height;   //height of the tree
};

class AVLTree
{
private:
    Node *pRoot;

public:
    AVLTree()
    {
        pRoot = nullptr;
    }

    bool isEmpty()
    {
        return (pRoot = nullptr);
    }

    int heightOfNode(Node *node)
    { //function to find the height of the node
        if (node == nullptr)
            return -1; //height of the node will be set to -1
        else
            return node->height; //else it will return height of the node
    }

    Node *singleLeftRotate(Node *&node)
    { //rotation with the right child or anitclockwise rotation
        Node *rightNode = node->pRight; //auxilary node where we will store the address of the right node
        node->pRight = rightNode->pLeft; //assigning a leftnode to the right side of the tree
        rightNode->pLeft = node;//left node of the right node will be our node
        node->height = max(heightOfNode(node->pLeft), heightOfNode(node->pRight)) + 1;//maximum height of a tree is leftsub tree, right subtree plus 1
        rightNode->height = max(heightOfNode(rightNode->pRight), node->height) + 1; // height of our new head node will be calculated by the height
        //of the right node + 1
        return rightNode;
    }

    Node *singleRightRotate(Node *&node)
    {   //rotation with left child or anitclockwise rotation
        Node *leftNode = node->pLeft; //auxilary node where we will store the address of the left node
        node->pLeft = leftNode->pRight; //assigning a rightNodde to the left side of the tree
        leftNode->pRight = node; //left node of the right node will be our node
        node->height = max(heightOfNode(node->pLeft), heightOfNode(node->pRight)) + 1; //this is similar to our single left rotate function
        leftNode->height = max(heightOfNode(leftNode->pLeft), node->height) + 1; //but here we are dealing with opposite sides
        return leftNode;
    }

    Node *doubleLeftRotate(Node *&node)
    {  //right left rotate
        node->pRight = singleRightRotate(node->pRight); //first we will pass right child to single child
        return singleLeftRotate(node);//this will return new root node
    }

    Node *doubleRightRotate(Node *&node)
    {//left right rotate
        node->pLeft = singleLeftRotate(node->pLeft); //passing left child of the node and then we make conneciton.
        return singleRightRotate(node);//similarly, this will retrun new root node
    }

    Node *insertNode(Node *node, Student student)
    { //if our tree is empty or our node is a nullptrptr then we create a new node
        if (node == nullptr)
        {
            node = new Node;                 //persistant memory
            node->datum.name = student.name; //setting our data compnent to respective values
            node->datum.age = student.age;
            node->datum.fee = student.fee;
            node->height = 0;
            node->pLeft = nullptr;  //both left and right node will be nullptrptr since the tree is
            node->pRight = nullptr; //currently empty
        }
        else if (student.age < node->datum.age)
        { //or when x is smalled than the data component of the node
            // we insert on the left side of the node
            node->pLeft = insertNode(node->pLeft, student);
            if (heightOfNode(node->pLeft) - heightOfNode(node->pRight) == 2)
            {
                if (student.age < node->pLeft->datum.age)
                { //first we consider the case when x is smalled than the data component of left node
                    node = singleRightRotate(node);
                }
                else
                { //Lr path we use double right rotation
                    node = doubleRightRotate(node);
                }
            }
        }
        else if (student.age > node->datum.age)
        { //or when x is bigger than the data component of the node then we change everything to the right side
            //of the tree or when x is bigger than the data component we insert on the right side of the node
            node->pRight = insertNode(node->pRight, student);
            if (heightOfNode(node->pRight) - heightOfNode(node->pLeft) == 2)
            {
                if (student.age > node->pRight->datum.age)
                { //first we caluclate the case when x is bigger than the data component of the right node
                    node = singleLeftRotate(node);
                }
                else
                { //LR path we use double right rotation
                    node = doubleLeftRotate(node);
                }
            }
        } //after doing this we will udpate the height of the node
        node->height = max(heightOfNode(node->pLeft), heightOfNode(node->pRight)) + 1;
        return node; //after updating return this height
    }

    void insertNode(Student student)
    { //overloading the insert node function so that it takes only one parameter
        pRoot = insertNode(pRoot, student); //once we pass the root node we will update the root node
    }

    void preOrderTraversal(Node *node)
    {
        if (pRoot == nullptr)
        {
            cout << "The tree is empty" << endl;
        } //if the tree is not empty then we will keep printing
        else if (node != nullptr)
        { //we are going to access it's data component that's why we are writing node!= nullptrptr
            cout << node->datum.name << " ";
            cout << node->datum.age << " ";
            cout << node->datum.fee << " ";
            preOrderTraversal(node->pLeft);
            preOrderTraversal(node->pRight);
        }
        cout << endl;
    }
    void printTreeInPreOrderTraversal()
    { //now here we will call the funciton pre order traversal where we will pass the root node
        preOrderTraversal(pRoot);
    }

    void postOrderTraversal(Node *node)
    {
        if (pRoot == nullptr)
        { //this prints the children node first and only after all the children nodes are printed then it print out
            // the other parent nodes respectively
            cout << "The tree is empty" << endl;
        }
        else if (node != nullptr)
        { //if tree is not empty then we will keep printing
            postOrderTraversal(node->pLeft);
            postOrderTraversal(node->pRight);
            cout << node->datum.name << " ";
            cout << node->datum.age << " ";
            cout << node->datum.fee << " "; //in post we print after.
        }
        cout << endl;
    }
    void printTreeInPostOrderTraversal()
    { //calling the preOrderTraversal where we will pass the root node
        postOrderTraversal(pRoot);
    }

    void inOrderTraversal(Node *node)
    {
        if (pRoot == nullptr)
        { //if the tree is empty
            cout << "The tree is empty" << endl;
        }
        else if (node != nullptr)
        { //when the tree is not empty we access it's data component
            inOrderTraversal(node->pLeft);
            cout << node->datum.name << " ";
            cout << node->datum.age << " ";
            cout << node->datum.fee << " ";
            inOrderTraversal(node->pRight); //prints vlaues in order
        }
        cout << endl;
    }
    void printTreeInOrderTraversal()
    { // now here we will call the function preOrderTraversal where we will pass the root node
        inOrderTraversal(pRoot);
        cout << endl;
    }

    Node *findMin(Node *node)
    {
        // returns the address of the minimum value
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->pLeft == nullptr)
        {
            // it does not have any left node means our node's value is the smallest
            return node;
        }
        else
        {
            // if sub tree does not have any left child and if it has then we will call this function
            return findMin(node->pLeft);
        }
    }

    Node *findMinValue()
    {
        // passing root node so we don't have to pass anything
        return findMin(pRoot);
    }

    Node *findMax(Node *node)
    {
        // returns the address of the minimum value
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->pRight == nullptr)
        {
            // it does not have any right node means our node's value is the smallest
            return node;
        }
        else
        {
            // if sub tree does not have any rightchild and if it has then we will call this function
            return findMax(node->pRight);
        }
    }

    Node *findMaxValue()
    {
        // passing root node so we don't have to pass anything
        return findMax(pRoot);
    }

    Node *removeNode(Node *node, Student student)
    {
        if (node == nullptr)
            return nullptr; //if the tree is empty

        else if (student.age < node->datum.age)
        {  //when the our x is smalled than the data value
            node->pLeft = removeNode(node->pLeft, student); //we remove from the left side
        }
        else if (student.age > node->datum.age)
        {// if our x is greater than the data value
            node->pRight = removeNode(node->pRight, student); //we remove from the right side
        }

        else if (student.age == node->datum.age)
        {
            Node *pToRemove = node;
            if (node->pRight == nullptr)
            {//if node's right child is nullptrptr then we will call the left child as the node itself
                node = node->pLeft; //make connection
                delete pToRemove;   //remove the node
                return node;
            }
            else if (node->pLeft == nullptr)
            {                        // if node's elft child is nullptrptr then we will call the right child as the node itself
                node = node->pRight; //make connection
                delete pToRemove;    //remove the node
                return node;
            }
            else if (node->pLeft != nullptr && node->pRight != nullptr)
            { //when the left and the right nodes have their own children respectively
                //we will find the minValue from the right
                //for the left side we will find the max value
                node->datum = findMin(node->pRight)->datum;//looking for hte min vlaue on the right side
                node->pRight = removeNode(node->pRight, node->datum); //making connection
                return node;
            }
        }

        node->height = max(heightOfNode(node->pLeft), heightOfNode(node->pRight)) + 1;

        if (heightOfNode(node->pLeft) - heightOfNode(node->pRight) == 2)
        { //if the height of the node from the left side - the height of the node from the left side's right child is not equal to 1
            if (heightOfNode(node->pLeft->pLeft) - heightOfNode(node->pLeft->pRight) == 1)
                return singleRightRotate(node); // we return the node from the right rotation
            else
                return doubleRightRotate(node); //if that is not the case then we return the node from the double right rotaiton
        }

        if (heightOfNode(node->pRight) - heightOfNode(node->pLeft) == 2)
        { //similary this is the case for the right side of the node
            if (heightOfNode(node->pRight->pRight) - heightOfNode(node->pRight->pLeft) == 1)
                return singleLeftRotate(node); //if the condition suffice the we return the node obtained from the singe left rotaiton
            else
                return doubleLeftRotate(node); //else the double left rotation
        }
        return node;
    }

    void removeNode(Student student)
    { //calling recursive statement so that it takes only one parameter when called
        pRoot = removeNode(pRoot, student);
    }
};

int main()
{
    AVLTree tree1;

    Student student1, student2, student3;
    cout << "Enter the value for the first student." << endl;
    cin >> student1.name;
    cin >> student1.age;
    cin >> student1.fee;

    cout << endl;
    cout << "Enter the value for the second student." << endl;
    cin >> student2.name;
    cin >> student2.age;
    cin >> student2.fee;

    cout << endl;
    cout << "Enter the value for the third student." << endl;
    cin >> student3.name;
    cin >> student3.age;
    cin >> student3.fee;

    tree1.insertNode(student1);
    tree1.insertNode(student2);
    tree1.insertNode(student3);

    cout << endl;
    cout << "The tree in order is as follows:" << endl;
    tree1.printTreeInOrderTraversal(); //print tree in ordered form

    tree1.removeNode(student2); //remove node
    Node *node1 = tree1.findMinValue();
    cout << "The minimum value is: " << node1->datum.name << " " << node1->datum.age << " " << node1->datum.fee << endl; //find the minimum value

    Node *node2 = tree1.findMaxValue();
    cout << "The maximum value is: " << node2->datum.name << " " << node2->datum.age << " " << node2->datum.fee << endl; //find max value

    cout << endl;
    cout << "Printing tree in pre order: " << endl;
    tree1.printTreeInPreOrderTraversal();
    cout << "Printing tree in post order: " << endl;
    tree1.printTreeInPostOrderTraversal();

    return 0;
}