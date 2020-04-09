#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<fstream>
using namespace std;
class Book
{
private:
    int bookid;
    char title[20];
    float price;
public:
    Book()
    {
        bookid=0;
        strcpy(title,"no title");
        price=0;
    }
    void getBookData()
    {
        cout<<"Enter the details of Book id, title and Price: ";
        cin>>bookid;
        cin.ignore();
        cin.getline(title,19);
        cin>>price;
    }
    void showBookData()
    {
        cout<<"\n"<<"Book id: "<<bookid<<" "<<"Book title: "<<title<<" "<<"Book Price: "<<price;
    }
    int storeBook();
    void viewAllBooks();
    void searchBook(char *);
    void deleteBook(char *);
    void updateBook(char *);
};

int Book::storeBook()
{
    if(bookid==0 && price==0)
    {
        cout<<"Book Data not initialized";
        return 0;
    }
    else{
        ofstream fout;
        fout.open("record.dat",ios::app|ios::binary);
        fout.write((char *)this,sizeof(*this));
        fout.close();
        return 1;
    }
}
void Book::viewAllBooks()
{
    ifstream fin;
    fin.open("record.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\n File not found";
    else{
        fin.read((char *)this,sizeof(*this));
        while(!fin.eof())
        {
            showBookData();
            fin.read((char *)this,sizeof(*this));
        }
        fin.close();
    }
}
void Book::searchBook(char *t)
{
    int counter=0;
    ifstream fin;
    fin.open("record.dat", ios::in|ios::binary);
    if(!fin)
        cout<<"\nFile not found";
    else
    {
        fin.read((char *)this,sizeof(*this));
        while(!fin.eof())
        {
            if(!strcmp(t,title))
            {
                showBookData();
                counter++;
            }
            fin.read((char *)this,sizeof(*this));
        }
        if(counter==0)
            cout<<"\n Record not Found";
        fin.close();
    }
}
void Book::deleteBook(char *t)
{
    ifstream fin;
    ofstream fout;
    fin.open("record.dat",ios::in|ios::binary);
    if(!fin)
        cout<<"\nFile not found";
    else
    {
       fout.open("tempfile.dat",ios::out|ios::binary);
       fin.read((char *)this,sizeof(*this));
       while(!fin.eof())
       {
           if(strcmp(t,title))
            fout.write((char *)this, sizeof(*this));
           fin.read((char *)this,sizeof(*this));
       }
       fin.close();
       fout.close();
       remove("record.dat");
       rename("tempfile.dat","record.dat");
       cout<<"\n Record deleted successfuly";
    }
}
void Book::updateBook(char *t)
{
    fstream file;
    file.open("record.dat",ios::in|ios::out|ios::ate|ios::binary);
    file.seekg(0);
    file.read((char *)this,sizeof(*this));
    while(!file.eof())
    {
        if(!strcmp(t,title)){
            getBookData();
            file.seekp(file.tellp()- sizeof(*this));
            file.write((char *)this,sizeof(*this));
        }
       file.read((char *)this,sizeof(*this));
    }
    file.close();
}
int menu()
{
    int choice;
    cout<<"\n\t\t\t\tBOOK RECORD MANAGEMENT";
    cout<<"\n-----------------------------------------------------------------------------------------------";
    cout<<"\n1. Insert Book Record";
    cout<<"\n2. View All Book Record";
    cout<<"\n3. Search a particular Book";
    cout<<"\n4. Delete Book Record";
    cout<<"\n5. Update Book Record";
    cout<<"\n6. Exit";
    cout<<"\n\n Enter your choice: ";
    cin>>choice;
    return(choice);
}
int main()
{
    Book b1;
    char title[20];
    while(1){
        system("cls");
        switch(menu())
        {
        case 1:
            b1.getBookData();
            b1.storeBook();
            cout<<"\n Record Inserted";
            break;
        case 2:
            b1.viewAllBooks();
            break;
        case 3:
            cout<<"\n Enter the title of the book to search: ";
            cin.ignore();
            cin.getline(title,19);
            b1.searchBook(title);
            break;
        case 4:
            cout<<"\n Enter book title to delete record: ";
            cin.ignore();
            cin.getline(title,19);
            b1.deleteBook(title);
            break;
        case 5:
            cout<<"\n Enter Book title to update the Record: ";
            cin.ignore();
            cin.getline(title,19);
            b1.updateBook(title);
            cout<<"\n Record Updated";
            break;
        case 6:
            cout<<"\n Thank You for using the Book Record Management Application";
            cout<<"\n Press any key to exit";
            getch();
            exit(0);
        default:
            cout<<"\n Invalid Choice";
        }
        getch();
    }

}
