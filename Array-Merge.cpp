//Name: Kabeer Sheikh
//Student ID: 200438835
//Question 1
//Part of this code has been borrowed from professor's code


#include <iostream>
#include <string>

using namespace std;

struct Student { //struct Student
    string name;
    int age;
    double fee;

    Student() {
        name = " ";
        age = 0;
        fee = 0.0;
    }

    Student (string Name, int Age, double Fee) {
        name = Name;
        age = Age;
        fee = Fee;
    }
};

void merge(Student array[], int l, int m, int r) { //merge function that will arrange our list in ascending order according to age
    int n1 = m - l + 1; //m index of the middle, l is the left most value
    int n2 = r - m;
    
    Student *leftSubArray = new Student[n1]; //dynamically allocating leftSubArray and rightSubArray
    Student *rightSubArray = new Student[n2];
    
    //for loop to put element in the left Sub Array
    for (int i = 0; i < n1; i++) {
        leftSubArray[i] = array[l + i]; //index of hte first element + i
    }
    
    for (int j = 0; j < n2; j++) {
        rightSubArray[j] = array[m + 1 + j]; //index of the first element + j
    }
    
    int i = 0;
    int j = 0;
    int k = l; //let k be the index of the left most element
    
    while (i < n1 && j < n2) {
        if (leftSubArray[i].age <= rightSubArray[j].age) {
            array[k] = leftSubArray[i];
            i++;
        }
        else {
            array[k] = rightSubArray[j];
            j++;
        }
        k++; //increment the index of the combined sub array left and right
    }
    
    while (i < n1) { //when all the elements of i are not exhausted
        array[k] = leftSubArray[i];
        i++;
        k++;
    }
    
    while (j < n2) { //when all the elements of j are not exhausted
        array[k] = rightSubArray[j];
        j++;
        k++;
    }
}

void mergeSort(Student array[], int l, int r) { //recursive function to call in main
    if (l >= r) {
        return;
    }
    
    int m = l + (r - l)/2; //calculate the midpoint index
    
    mergeSort(array, l, m); //this fucntions calls the mergeSort and merge in itself and creates the divisions
    mergeSort(array, m + 1, r);
    merge(array, l, m, r);
}

int binarySearch (const Student list[], int target, int listSize) { //provides us the index/location at which the element is at
    int low = 0;
    int high = listSize - 1;
    
    while (high >= low) {
        int mid = (low + high)/2;
        if (target < list[mid].age) {
            high = mid - 1;
        }
        else if (target == list[mid].age) {
            return mid;
        }
        else {
            low = mid + 1;
        }
    }
    return -low - 1;
}

void printAppropriateStatement (Student array[], Student student, int arraySize) {
    //this is just a print statement which calls the binary search index and prints the element and the location of its index.
    if (binarySearch(array, student.age, arraySize) >= 0) {
        cout << "The element (" << student.name << ", " << student.age << ", " << student.fee << ") is found." << endl;
        cout << "This element was found at index: " << binarySearch(array, student.age, arraySize) << endl;
    }
    else { //
        cout << "The element (" << student.name << ", " << student.age << ", " << student.fee << ") should be at index " << -1*(binarySearch(array, student.age, arraySize) + 1) << endl;
    }
}

void printArray(Student array[], int arraySize) { //to print the array before and after merging
    for (int i = 0; i < arraySize; i++) {
        cout << array[i].name << " " << array[i].age << " " << array[i].fee << endl;
    }
    cout << endl;
}


int main() {

    Student student0 = {"Kabeer", 19, 35.17}; //7 instances of the student
    Student student1 = {"John", 21, 31.65};
    Student student2 = {"Paul", 25, 33.43};
    Student student3 = {"Kaur", 18, 34.93};
    Student student4 = {"Patel", 23, 36.37};
    Student student5 = {"Alexandera", 22, 33.78};
    Student student6 = {"Ramesh", 27, 34.46};
    
    Student A[] = {student0, student1, student2, student3, student4, student5, student6};
    //let A be the set of the 7 instances of the student
    
    int n = sizeof(A)/sizeof(A[0]); //finds the actual size of the list
    
    cout << "The unsorted array is: " << endl;
    printArray(A, n); //printing
    cout << endl;
    
    mergeSort(A, 0, n-1); //merging
    
    cout << "The sorted array is: " << endl;
    printArray(A, n); //printing after merging
    
    printAppropriateStatement(A, student2, n);
    
    printAppropriateStatement(A, student5, n);
    
    return 0;
}
