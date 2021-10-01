//Name: Kabeer Sheikh
//Student ID: 200438835
// Question 4
// Part of this code has been borrowed from video lectures of professor


#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int age;
    double fee;

    Student() { // no arg constructor
        name = " ";
        age = 0;
        fee = 0.0;
    }
};

struct Node {
    // similar to doubly linked list
    Student datum;
    Node* pLeft;
    Node* pRight;

    Node() { // no arg constructor
        pLeft = nullptr;
        pRight = nullptr;
        datum.name = " ";
        datum.age = 0;
        datum.fee = 0.0;
    }
};

class binarySearchTree { // BST
    Node* pRoot;
    Node* pHead;
    Node* pTail;
    public:
        binarySearchTree() {
            pRoot = nullptr;
        }

        bool isEmpty() {
            // check if the tree is empty
            return (pRoot == nullptr);
        }

        void insertNode (Node* pLeaf, Student student) {   
               
            if (student.age < pLeaf->datum.age) {
                // if inputvalue is smaller than the data component of the leaf value
                // first we will have to check if the node exists or not and then we have to check if there exists another node for our subtree
                if (pLeaf->pLeft != nullptr) {
                    // the left to the node exists we will call it leaf node
                    insertNode(pLeaf->pLeft, student);
                }
                else {
                    // if pLeaf->pleft exists then we will create and assign dynamic memory to it
                    pLeaf->pLeft = new Node;
                    pLeaf->pLeft->datum.name = student.name;
                    pLeaf->pLeft->datum.age = student.age;
                    pLeaf->pLeft->datum.fee = student.fee;
                    // initializing left and right pointer
                    pLeaf->pLeft->pLeft = nullptr;
                    pLeaf->pLeft->pRight = nullptr;
                }
            }
            else if (student.age >= pLeaf->datum.age) {
                if (pLeaf->pRight != nullptr) {
                    // the left to the node exists we will call it leaf node
                    insertNode(pLeaf->pRight, student);
                }
                else {
                     // if pLeaf->pleft exists then we will create and assign dynamic memory to it
                    pLeaf->pRight = new Node;
                    pLeaf->pRight->datum.name = student.name;
                    pLeaf->pRight->datum.age = student.age;
                    pLeaf->pRight->datum.fee = student.fee;
                    // initializing left and right pointer
                    pLeaf->pRight->pLeft = nullptr;
                    pLeaf->pRight->pRight = nullptr;
                }
            }
        };

        void insertNode (Student student) {
            
            if (pRoot != nullptr) {
                insertNode(pRoot, student);
            }
            else {
                pRoot = new Node;
                pRoot->datum.name = student.name;
                pRoot->datum.age = student.age;
                pRoot->datum.fee = student.fee;
                pRoot->pLeft = nullptr;
                pRoot->pRight = nullptr;
            }
        }

        void preOrderTraversal(Node* node) {
            if (pRoot == nullptr) {
                cout << "The tree is empty. " << endl;
            }
            // if p is not empty then we will keep printing 
            else if (node != nullptr) {
                // we are going to access it's data component that's why we are writin node!= nullptr
                cout << node->datum.name << " " << node->datum.age << " " << node->datum.fee << endl;
                preOrderTraversal(node->pLeft);
                preOrderTraversal(node->pRight);
            }
        }

        void printTreeInPreOrderTraversal() {
            // now here we will call the function preOrderTraversal where we will pass the root node
            preOrderTraversal(pRoot);
            cout << endl;
        }

        void postOrderTraversal (Node* node) {
            if (pRoot == nullptr) {
                // this prints the children node first and only after all the children nodes are printed then it prints out
                // the other parent nodes respectively
                cout << "The tree is empty. " << endl;
            }
            // if p is not empty then we will keep printing 
            else if (node != nullptr) {
                // we are going to access it's data component that's why we are writin node!= nullptr
                postOrderTraversal(node->pLeft);
                postOrderTraversal(node->pRight);
                cout << node->datum.name << " " << node->datum.age << " " << node->datum.fee << endl;// in post we print after
            }
        }

        void printTreeInPostOrderTraversal() {
             // now here we will call the function preOrderTraversal where we will pass the root node
            postOrderTraversal(pRoot);
            cout << endl;
        }

        void inOrderTraversal(Node* node) {
            if (pRoot == nullptr) {
                cout << "The tree is empty. " << endl;
            }
             // now here we will call the function preOrderTraversal where we will pass the root node
            else if (node != nullptr) {
                  // we are going to access it's data component that's why we are writin node!= nullptr
                inOrderTraversal(node->pLeft);
                cout << node->datum.name << " " << node->datum.age << " " << node->datum.fee << endl;
                inOrderTraversal(node->pRight);
            }
        }

        void printTreeInOrderTraversal() {
            // now here we will call the function preOrderTraversal where we will pass the root node
            inOrderTraversal(pRoot);
            cout << endl;
        }

         // since we are searching it will give address of the node
        Node* searchNode (Node* pLeaf, Student student) {
            // here we have two case. if leaf node is null or not
            if (pLeaf != nullptr) {
                // then we have
                if (student.age == pLeaf->datum.age) {
                    return pLeaf; // because we found the right node (return)
                }
                if (student.age < pLeaf->datum.age) {
                     // when data component is < then we move to the left
                    return searchNode(pLeaf->pLeft, student);  // we call the original function using recursion 
                }
                else {
                     // we call the original function using recursion 
                    return searchNode(pLeaf->pRight, student);
                }
            }
            else {
                // if any of the cases are not satisfied i.e. no node
                return nullptr;
            }
        }

        Node* searchNode (Student student) {
            return searchNode(pRoot, student);
        }

        Node* findMin (Node* node) {
            // returns the address of the minimum value
            if (node == nullptr) {
                return nullptr;
            }
            if (node->pLeft == nullptr) {
                 // it does not have any left node means our node's value is the smallest
                return node;
            }
            else {
                 // if sub tree does not have any left child and if it has then we will call this function
                return findMin(node->pLeft);
            }
        }

        Node* finMinValue() {
             // passing root node so we don't have to pass anything
            return findMin(pRoot);
        }

        Node* findMax (Node* node) {
            // returns the address of the minimum value
            if (node == nullptr) {
                return nullptr;
            }
            if (node->pRight == nullptr) {
                // it does not have any right node means our node's value is the smallest
                return node;
            }
            else {
                // if sub tree does not have any rightchild and if it has then we will call this function
                return findMax(node->pRight);
            }
        }

        Node* findMaxValue() {
            // passing root node so we don't have to pass anything
            return findMax(pRoot);
        }

        void removeNode (Node* &node, Student &student) {
            if (node == nullptr) {
                return; // if tree is empty return
            }
            if (node->datum.age == student.age) {
                 // we find the value that we want to remove
                Node* pToRemove = node; // assigning the value of the node we want to delete
                if (node->pRight == nullptr) {
                    // if node's right child is nullptr then we will call the left child as the node itself
                    node = node->pLeft;// make connection
                      // now to remove the node 
                    delete pToRemove;
                }
                else if (node->pLeft == nullptr) {
                    // if node's left child is nullptr then we will call the right child as the node itself
                    node = node->pRight; // make connection 
                     // now to remove the node 
                    delete pToRemove;
                }
                else if (node->pLeft != nullptr && node->pRight != nullptr) {
                    // when the left and the right nodes have their own children respectivley
                    // we will find miniVal from the right 
                    // for the left side we will find the max value
                    node->datum.age = findMin(node->pRight)->datum.age; // looking for the min value on the right side of the tree
                    // now we have to remove the node and make connection
                    removeNode(node->pLeft, student);  // looking for data component that we obtained from min and eventually will replace the node
                }
            }
            else if (node->datum.age < student.age) {
                 // it will be passed to the right side since that one is bigger
                removeNode(node->pRight, student);
            }
            else if (node->datum.age > student.age) {
                // if the value lies on the left side
                removeNode(node->pLeft, student);
            }
        }

        void removeNodeFromTree(Student student) {
            removeNode(pRoot, student);
        }

};


int main()
{
    binarySearchTree tree1;
    Student student1;
    Student student2;
    
    cout << "Is the tree empty? " << tree1.isEmpty() << endl;

    int numOfNodes; // using createList() function from doublyLinkedList
    cout << "Please enter the number of nodes that you want to insert in the tree: " << endl;
    cin >> numOfNodes;

    int count = 0;
    while (count < numOfNodes) { // asking the user for total number of nodes
        cout << "Enter the Name, Age and Fee for the rest of the list. " << endl;
        cin >> student1.name;
        cin >> student1.age;
        cin >> student1.fee;

        tree1.insertNode(student1);
        count++;
    }

    cout << endl;
    tree1.printTreeInOrderTraversal();
    cout << endl;

    cout << "Enter the Name, Age and fee which you want to remove. " << endl;
    cin >> student2.name;
    cin >> student2.age;
    cin >> student2.fee;
    tree1.removeNodeFromTree(student2);

    Node* node1 = tree1.findMaxValue();
    cout << "The maximum value from the tree is: " << endl;
    cout << node1->datum.name << " " << node1->datum.age << " " << node1->datum.fee << endl;
    
    Node* node2 = tree1.finMinValue();
    cout << "The minimum value from the tree is: " << endl;
    cout << node2->datum.name << " " << node2->datum.age << " " << node2->datum.fee << endl;

    Node* node3 = tree1.searchNode(student1);

    cout << "Is (s1, 25, 20.25) a node of the tree? " << (node3!=nullptr) << endl;
    cout << endl; 
    cout << "The tree in pre-order-fashion is as: " << endl;
    cout << endl;
    tree1.printTreeInPreOrderTraversal();
    cout << endl;

    cout << "The tree in post-order-fashion is as: " << endl;
    cout << endl;
    tree1.printTreeInPostOrderTraversal(); 
    cout << endl;

    return 0;
}