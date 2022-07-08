#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <cstdio>
using namespace std;

string username, password;                  // global var username and password     
int class_count = 0;                        // global var class_count

bool loginSys(){
    string un, pw;
    cout<<"Please Login: ";                     //login system
    cin>>username;
    cout<<"Please enter your password: ";      //checks if username and password are correct
    cin>>password;

    fstream read(username+".txt");          
    getline(read, un);
    getline(read, pw);

    if(un==username && pw==password){           //if username and password are correct return true and if false return false
        return true;
    }
    else{
        return false;
    }
}

bool create_account(){
    int id;
        cout<<"Please create a login to continue." << endl;         //if user does not have an account, creates one
        cout<<"Please enter your username: ";cin>>username;
        cout<<"Please enter your password: ";cin>>password;

        fstream file;   
        file.open(username+".txt", ios::out);                   //creates a file with the username and password user enters

        file<<username<<endl;
        file<<password<<endl;

        file.close();
        id = loginSys();
        return id;                                                  //returns true if username and password are correct
}

int login(int id){
    if (id==1){
        cout<<"Welcome to the semester grade calculator!" << endl;          //if username and password are correct, welcome user
    }
    else if(id==0){
        cout<<"Invalid username or password. Please try again." << endl;        //if username and password are incorrect, tell user and retry login
        loginSys();
    }
    return 0;
}

void create_grade_entry(string class_name, int class_grade, int class_credit){                  //creates a file with the class name, grade, and credit
    fstream file;
    file.open(username+"classes.txt", ios::app);
    file<<class_name<<endl;
    file.close();
    file.open(username+"grades.txt", ios::app);
    file<<class_grade<<endl;
    file.close();
    file.open(username+"credit.txt", ios::app);
    file<<class_credit<<endl;
    file.close();
}
void current_GPA(){
    string grade;                                       //grade is the grade of the class
    fstream file;                                       
    double sum_grades=0;                                //sum is the sum of all the grades
    int count=0;                                        //count is the number of classes
    string credit;
    int sum_credit=0;
    double weight;                                      //weight is the weight of the class
    file.open(username+"grades.txt", ios::in);
    if(file.is_open()){
        while(getline(file, grade)){                    //while the file is open, get the grade
            int num = stoi(grade);
            sum_grades = num+sum_grades;
            count++;
        }
    }
    file.close();
    file.open(username+"credit.txt", ios::in);          //while the file is open, get the credit
    if(file.is_open()){
        while(getline(file, credit)){                   
            int weight = stoi(credit);
            sum_credit = weight+sum_credit;
        }
    }
    file.close();
    float GPA = (((((sum_grades/count)/100)*sum_credit)/sum_credit)*4);         //calculates the GPA and prints it
    cout<<"Your current GPA is: "<<GPA<<endl;
}

string modify_class_num(){                                              //identifying the class number to modify
    fstream file;
    string class_change;
    string getcontent;
    string class_compare;
    class_count = 0;                                                    //resetting class count after every modification
    cout<<"What class would you like to modify? \n";                    //asks user to enter class name
    file.open(username+"classes.txt", ios::in);
    if(file.is_open()){ 
        cout<<file.rdbuf()<< "\n";                                      //prints the classes that the user is in
    }
    cout<<"Enter: ";cin>>class_change;                                  //asks user to enter class name they want to change
    file.close();
    file.open(username+"classes.txt", ios::in);
    if(file.is_open()){
        while(getline(file, class_compare)){                            //compares value and returns location for modification of grade
            int x = class_compare.compare(class_change);
            if(x==0){
                return class_change;                                    //returns the class name
            }
            else{                                                       //if class name is not found, increase count to identify corresponding class grade if user wants to modify
                class_count++;
            }
        }
    }
    return 0;
}

void modify_class_name(string class_name){                              //modify_class_name is the function that modifies the class name
    fstream file;
    fstream outFile;                                                    
    string getcontent;
    string new_class;
    file.open(username+"classes.txt", ios::in|ios::out);
    outFile.open("temp.txt", ios::out);                                 //creating temp file
    if(file.is_open()){
        while(getline(file, getcontent)){                       
            if(getcontent==class_name){
                cout<<"What would you like to change the class name to? \n";            //changing the class name
                cin>>new_class;
                outFile<<new_class<<endl;                                               //writing to temp file
            }
            else{
                outFile<<getcontent<<endl;                                                //writing to temp file
            }
        }
    }
    file.close();
    outFile.close();
    string fileName = username+"classes.txt";                                   //deleting the old file and renaming the temp file
    string tempName = "temp.txt";
    string newFileName = username+"classes.txt";
    remove(fileName.c_str());
    rename(tempName.c_str(), newFileName.c_str());
}

void modify_grade(int count){
    fstream file;                                               
    fstream outFile;
    string getcontent;
    string new_grade;
    int i = 0;                                                //i is the count for the number of classes
    file.open(username+"grades.txt", ios::in|ios::out);         //opening file pathes for modification
    outFile.open("temp.txt", ios::out);
    if(file.is_open()){
        while(getline(file, getcontent)){                       //while the file is open, get the grade
                if(i==count){                                   //if the count is equal to the class number, ask user to enter new grade
                    cout<<"The current Grade is: "<<getcontent<<endl;
                    cout<<"What would you like to change the grade to? \n";
                    cin>>new_grade;                                                         //replaces the grade with the new grade
                    outFile<<new_grade<<endl;
                }
                else{
                    outFile<<getcontent<<endl;                                  //writes other grades to temp file
                }
                i++;
            }
        }
    file.close();
    outFile.close();
    string fileName = username+"grades.txt";                                   //deleting the old file and renaming the temp file
    string tempName = "temp.txt";
    string newFileName = username+"grades.txt";         
    remove(fileName.c_str());
    rename(tempName.c_str(), newFileName.c_str());
}

void modify_credit(int count){
    fstream file;                                               
    fstream outFile;
    string getcontent;
    string new_credit;
    int i = 0;                                                //i is the count for the number of classes
    file.open(username+"credit.txt", ios::in|ios::out);         //opening file pathes for modification
    outFile.open("temp.txt", ios::out);
    if(file.is_open()){
        while(getline(file, getcontent)){                       //while the file is open, get the grade
                if(i==count){                                   //if the count is equal to the class number, ask user to enter new grade
                    cout<<"The current credit is: "<<getcontent<<endl;
                    cout<<"What would you like to change the credit to? \n";
                    cin>>new_credit;                                                         //replaces the grade with the new grade
                    outFile<<new_credit<<endl;
                }
                else{
                    outFile<<getcontent<<endl;                                  //writes other grades to temp file
                }
                i++;
            }
        }
    file.close();
    outFile.close();
    string fileName = username+"credit.txt";                                   //deleting the old file and renaming the temp file
    string tempName = "temp.txt";
    string newFileName = username+"credit.txt";         
    remove(fileName.c_str());
    rename(tempName.c_str(), newFileName.c_str());
}

int main(){
    string Login_ans;                                                                       //Variable to store the answer to the login question
    int id;                                                                                 //Variable to store the id of the user
    cout<<"=================================================================" << endl;
    cout<<"====================Semester Grade Calculator====================" << endl;
    cout<<"=================================================================" << endl;
    cout<<"This program will use your class grades to calculate your semester GPA." << endl;
    cout<<"Have you logged in with our system before (Y or N)?"<<endl;                          //Welcome message and asking for login system use
    cin>>Login_ans;
    if(Login_ans =="Y"){                                                                        //If the user has logged in before 
        id = loginSys();                                                                        //checks the login system for user
        login(id);
    }
    else if(Login_ans =="N"){                                                                   //If the user has not logged in before                                                              //asks user to create an account
        cout<<"Please create a login to continue." << endl;
        cout<<"Please enter your username: ";cin>>username;
        cout<<"Please enter your password: ";cin>>password;

        fstream file;
        file.open(username+".txt", ios::out);                                                  //creates a file with the username and password

        file<<username<<endl<<password;

        file.close();
        id = loginSys();                                                                        //checks the login system for user after account is created
        login(id);
    }
    else{
        cout<<"Invalid input. Please try again." << endl;                                       //If the user enters an invalid input
    }
    int post_login_ans;
    if(Login_ans=="Y"||Login_ans=="N"){
        do{
        string term;
        cout<<"=================================================================" << endl;
        cout<<"Would you like to (1) add a class to this semester, (2) check your current GPA, or (3) modify classes (enter 4 to terminate)? ";                 //Asking user if they want to add a class
        cin>>post_login_ans;
        if(post_login_ans == 1){                                                                    //If the user wants to add a class
            string class_name;                                                                      //Variable to store the class name
            int class_grade;
            int class_weight;
            cout<<"What is the name of the course: ";cin>>class_name;                               //Asking user for class name
            cout<<"What was the grade you earned: ";cin>>class_grade;                               //Asking user for class grade
            cout<<"What was the weight of the course: ";cin>>class_weight;                          //Asking user for class weight
            create_grade_entry(class_name,class_grade,class_weight);
        }
        else if(post_login_ans == 2){                                                               //If the user wants to check their current GPA
            current_GPA();
        }
        else if(post_login_ans==3){                                                             //If the user wants to modify their class list
            string class_change;
            int modify_ans;
            int class_num;
            class_change = modify_class_num();                                                  //returning the class name to be modified and a count to modify the grade
            cout<<"Would you like to change the class name or the grade? (1) Class name (2) Grade or (3) credit of Course: "<<endl;           //asking if they want to change the name or grade
            cin>>modify_ans;
            if(modify_ans==1){                                                                  //If the user wants to change the class name then returns updated list
                modify_class_name(class_change);
                cout<<"Here is your updated class list: "<<endl;
                fstream file;
                file.open(username+"classes.txt", ios::in);
                    if(file.is_open()){
                        cout<<file.rdbuf()<< "\n";                                              //printing the updated class list
                    }
            }
            else if(modify_ans==2){                                                             //If the user wants to change the grade then returns updated list
                modify_grade(class_count);
            }
            else if(modify_ans==3){
                modify_credit(class_count);
            }
            else{
                cout<<"Invalid input. Please try again."<<endl;                                 //If the user enters an invalid input
            }
            }
        else if(post_login_ans==4){
            cout<<"Thank you for using the semester grade calculator."<<endl;                   //If the user wants to terminate the program
            cout<<"Please come back again."<<endl;
        }
        else{
            cout<<"Invalid input. Please try again."<<endl;                                     //If the user enters an invalid input
        }
        }while(post_login_ans == 1 || post_login_ans == 2 || post_login_ans == 3);     
    }
}
