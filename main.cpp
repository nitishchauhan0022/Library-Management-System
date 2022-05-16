#include <iostream>
#include <curses.h>
#include <string.h>
#include <stdlib.h>
#include <iomanip>
#include <pqxx/pqxx>
#include <bits/stdc++.h>
#include <ctime>

using namespace std;
using namespace pqxx;

class book
{

public:
    void show_all_books();
    bool search_books(int);
    void add_book();
    void delete_book();
    void modify_book();
    void issued_books();
};

void book::show_all_books()
{
    system("clear");

    try
    {
        //Database login details
        connection C("dbname = librarydb user = nitishchauhan password = ********** port = 5432");
        if (C.is_open())
        {
            cout << setw(60) << "**********************************************" << endl;
            cout << setw(60) << "*           Viewing book details             *" << endl;
            cout << setw(60) << "**********************************************" << endl;
            cout << endl;

            string sql = "select * from books";
            work W(C);
            result R(W.exec(sql));

            for (result::const_iterator c = R.begin(); c != R.end(); ++c)
            {
                cout << "Book ID = " << c[0].as<int>() << endl;
                cout << "Book Name = " << c[1].as<string>() << endl;
                cout << "Author Name = " << c[2].as<string>() << endl;
                cout << "Copies Available = " << c[3].as<int>() << endl;
                cout << "===========================================================" << endl;
            }
            W.commit();
        }
        else
        {
            cout << "Connection to database unsuccessful";
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
    cout << "Press any key to continue...";
    cin.get();
}

bool book::search_books(int id)
{
    system("clear");
    try
    {
        connection C("dbname = librarydb user = nitishchauhan password = ********** port = 5432");
        if (C.is_open())
        {
            cout << setw(60) << "**********************************************" << endl;
            cout << setw(60) << "*             Book Search Menu               *" << endl;
            cout << setw(60) << "**********************************************" << endl;
            cout << endl;
            string sql = "select * from books where book_id =(" + std::to_string(id) + ");";

            work W(C);

            result R(W.exec(sql));
            if (R.empty())
            {
                cout << "NO book with this id exist" << endl;
                cout << "Press any character for continue" << endl;
                cin.get();
                cin.get();
                return false;
            }

            for (result::const_iterator c = R.begin(); c != R.end(); ++c)
            {
                std::cout << "Book ID = " << c[0].as<int>() << endl;
                std::cout << "Book Name = " << c[1].as<string>() << endl;
                std::cout << "Author Name = " << c[2].as<string>() << endl;
                std::cout << "Copies Available = " << c[3].as<int>() << endl;
            }
            W.commit();
        }
        else
        {
            std::cout << "Connection to database unsuccessful";
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
    cout << "Press any Key for continue....";
    cin.get();
    cin.get();
    return true;
}

void book::add_book()
{
    system("clear");

    try
    {
        connection C("dbname = librarydb user = nitishchauhan password = ********** port = 5432");
        if (C.is_open())
        {
            int id;
            string name;
            string author;
            string domain;
            int copies;

            char c1;

            do
            {
                system("clear");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*             Adding book detail             *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;

                cout << "Enter the Book id :";
                cin >> id;
                cout << "Enter the Book name :";
                cin.ignore();
                getline(cin, name);
                cout << "Enter the Author name :";
                getline(cin, author);
                cout << "Enter no. of Copies :";
                cin >> copies;

                string sql = "INSERT INTO books (book_id,book_name,author_name,copies) VALUES (" + std::to_string(id) + "," + "'" + name + "'" + "," + "'" + author + "'" + "," + std::to_string(copies) + ");";

                work W(C);
                W.exec(sql);
                W.commit();
                cout << "Do you want to you continue to add another book ... press (y/n)";
                cin >> c1;
            } while (c1 == 'y');

            cout << "Book record added successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
    std::getchar();
}

void book::delete_book()
{
    system("clear");

    try
    {
        connection C("dbname = librarydb user = nitishchauhan password = ********** port = 5432");
        if (C.is_open())
        {
            int id;
            char c;

            do
            {
                system("clear");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*          REMOVING BOOK RECORD              *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;

                cout << "Enter the book id to be Delete :";
                cin >> id;

                std::string sql = "delete from books where book_id = (" + std::to_string(id) + ");";
                work W(C);

                W.exec(sql);
                W.commit();
                cout << endl;
                cout << "Do you want to delete more books?... press (y/n)";
                cin >> c;

            } while (c == 'y');
            cout << endl;
            cout << "Book Records Deleted Successfully" << endl;
            getch();
        }
        else
        {
            cout << "Can't open database" << endl;
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }

    std::getchar();
}

void book::modify_book()
{
    system("clear");
    try
    {
        connection C("dbname = librarydb user = nitishchauhan password = ********** port = 5432");
        if (C.is_open())
        {
            char c;

            do
            {
                system("clear");
                cout << setw(60) << "**********************************************" << endl;
                cout << setw(60) << "*            Modifying BOOK DETAIL           *" << endl;
                cout << setw(60) << "**********************************************" << endl;
                cout << endl;
                int choice;
                string column;
                string value;
                int id;
                cout << "Enter the Book id of the book that need to be updated:";
                cin >> id;
                bool result = search_books(id);
                if (result == false)
                {
                    return;
                }

                // code to check if book with this id exits or not

                cout << endl;

                cout << "Enter the correct option according to fied that need to be updated" << endl;

                cout << "\t=> Enter 1 for updating Book name " << endl;
                cout << "\t=> Enter 2 for updating Book author " << endl;
                cout << "\t=> Enter 3 for updating Book copies " << endl;
                cout << "\t=> Enter 4 for exit " << endl;

                cout << "Enter your choice of field : ";
                cin >> choice;

                cout << "\n\n================================================================";
                cout << endl;
                bool c2 = false;
                while (c2 == false)
                {
                    if (choice == 1)
                    {
                        column = "book_name";
                        cout << "Enter the new book name : ";
                        cin.ignore();
                        getline(cin, value);
                        c2 = true;
                    }
                    else if (choice == 2)
                    {
                        column = "author_name";
                        cout << "Enter the new author name : ";
                        cin.ignore();
                        getline(cin, value);
                        c2 = true;
                    }
                    else if (choice == 3)
                    {
                        column = "copies";
                        cout << "Enter the new copies : ";
                        cin.ignore();
                        getline(cin, value);
                        c2 = true;
                    }
                    else if (choice == 4)
                    {
                        return;
                    }
                    else
                    {
                        cout << "Enter correct choice between 1-4 : ";
                        cin >> choice;
                    }
                }

                std::string sql = "update books set " + (column) + "=" + "'" + (value) + "'" + "  where book_id = " + std::to_string(id);
                work W(C);
                W.exec(sql);
                W.commit();
                cout << "Do you want to you continue to update ?... Enter [y/n]";
                cin >> c;

            } while (c == 'y');
            cout << "Book Record Updated successfully" << endl;
        }
        else
        {
            cout << "Can't open database" << endl;
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
    std::getchar();
}

void book::issued_books()
{
    system("clear");

    try
    {
        connection C("dbname = librarydb user = nitishchauhan password = ********** port = 5432");
        if (C.is_open())
        {
            cout << setw(60) << "**********************************************" << endl;
            cout << setw(60) << "*           Issued books details             *" << endl;
            cout << setw(60) << "**********************************************" << endl;
            cout << endl;

            string sql = "select * from issued_books";
            work W(C);
            result R(W.exec(sql));

            for (result::const_iterator c = R.begin(); c != R.end(); ++c)
            {
                cout << "Student ID = " << c[1].as<int>() << endl;
                cout << "Student Name = " << c[2].as<string>() << endl;
                cout << "Book ID = " << c[3].as<int>() << endl;
                cout << "Book Name = " << c[4].as<string>() << endl;
                cout << "Issued Date = " << c[5].as<string>() << endl;
                cout << "===========================================================" << endl;
            }
            W.commit();
        }
        else
        {
            cout << "Connection to database unsuccessful";
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
    cout << "Press any key to continue...";
    cin.get();
}

class student
{

public:
    void book_issue();
    void book_deposit();
};

void student::book_issue()
{
    system("clear");

    try
    {
        //
        connection C("dbname = librarydb user = nitishchauhan password = ********** port = 5432");
        if (C.is_open())
        {
            cout << setw(60) << "**********************************************" << endl;
            cout << setw(60) << "*              Book Issue Menu               *" << endl;
            cout << setw(60) << "**********************************************" << endl;
            cout << endl;

            int id;
            int copies;
            string bookname;
            cout << "Enter the book id to be issued : ";
            cin >> id;
            string sql = "select * from books where book_id =(" + std::to_string(id) + ");";
            work W(C);
            result R(W.exec(sql));
            if (R.empty())
            {
                cout << "NO book with this id exist" << endl;
                cout << "Press any character for continue" << endl;
                cin.get();
                cin.get();
                return;
            }
            else
            {

                for (result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    bookname = c[1].as<string>();
                    copies = c[3].as<int>();
                }
                if (copies > 1)
                {
                    int studentid;
                    string studentname;
                    cout << "Enter the ID no. of the student : ";
                    cin >> studentid;
                    cout << "Enter the name of the student : ";
                    cin.ignore();
                    getline(cin, studentname);

                    //++++++++++++++++++++++++++++++++++++++++++
                    time_t currTime;
                    tm *currTm;
                    time(&currTime);
                    currTm = localtime(&currTime);
                    char todaysdate[12];
                    strftime(todaysdate, 12, "%Y-%m-%d", currTm);
                    //++++++++++++++++++++++++++++++++++++++++++++

                    // Decreasing book copies
                    sql = "update books set copies =" + std::to_string(copies - 1) + "where book_id =" + std::to_string(id);
                    W.exec(sql);

                    // adding the issued book record
                    sql = "insert into issued_books(student_id,student_name,book_id,book_name,issue_date) values(" + std::to_string(studentid) + "," + "'" + studentname + "'" + "," + std::to_string(id) + "," + "'" + bookname + "'" + "," + "'" + todaysdate + "');";
                    W.exec(sql);
                    W.commit();
                    cout << "Book issued Successfully" << endl;
                }
                else
                {
                    cout << "There is no available copies of this book right now" << endl;
                    W.commit();
                }
            }
        }
        else
        {
            cout << "Connection to database unsuccessful";
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
    cout << "Press any key to continue...";
    cin.get();
}

void student::book_deposit()
{
    system("clear");
    try
    {
        connection C("dbname = librarydb user = nitishchauhan password = ********** port = 5432");
        if (C.is_open())
        {
            cout << setw(60) << "**********************************************" << endl;
            cout << setw(60) << "*              Book Deposit Menu               *" << endl;
            cout << setw(60) << "**********************************************" << endl;
            cout << endl;
            int copies;
            int id;
            cout << "Enter the book id to be deposited : ";
            cin >> id;
            string sql = "select * from books where book_id =(" + std::to_string(id) + ");";
            work W(C);
            result R(W.exec(sql));
            if (R.empty())
            {
                cout << "NO book with this id exist" << endl;
                cout << "Press any character for continue" << endl;
                cin.get();
                cin.get();
                return;
            }
            else
            {
                for (result::const_iterator c = R.begin(); c != R.end(); ++c)
                {
                    copies = c[3].as<int>();
                }

                int studentid;
                string studentname;
                cout << "Enter the admno. of the student : ";
                cin >> studentid;

                sql = "select * from issued_books where student_id =" + std::to_string(studentid) + " AND book_id = " + std::to_string(id);

                result N(W.exec(sql));
                cout << endl
                     << endl;
                cout << "===========================================================" << endl;
                cout << "Book to be deposited : " << endl;

                for (result::const_iterator c = N.begin(); c != N.end(); ++c)
                {
                    cout << "Student ID = " << c[1].as<int>() << endl;
                    cout << "Student Name = " << c[2].as<string>() << endl;
                    cout << "Book ID = " << c[3].as<int>() << endl;
                    cout << "Book Name = " << c[4].as<string>() << endl;
                }
                cout << "===========================================================" << endl;
                cout << "Press any key to deposit the book...";
                cin.get();
                cin.get();

                sql = "update books set copies =" + std::to_string(copies + 1) + "where book_id =" + std::to_string(id);
                W.exec(sql);

                sql = "delete from issued_books where student_id =" + std::to_string(studentid) + " AND book_id = " + std::to_string(id);
                W.exec(sql);
                W.commit();

                cout << "\n\nBook Deposited Successfully" << endl;
            }
        }
        else
        {
            cout << "Connection to database unsuccessful";
        }
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << std::endl;
    }
    cout << "Press any key to continue to Main Menu...";
    cin.get();
}

int menu()
{
    system("clear");
    book b;
    student s;
    int opt;
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t*         1. Book view                            *" << endl;
    cout << "\t\t\t\t\t\t*         2. Book Search                          *" << endl;
    cout << "\t\t\t\t\t\t*         3. Add Book                             *" << endl;
    cout << "\t\t\t\t\t\t*         4. Delete Book                          *" << endl;
    cout << "\t\t\t\t\t\t*         5. Modify Book                          *" << endl;
    cout << "\t\t\t\t\t\t*         6. Issued Books                         *" << endl;
    cout << "\t\t\t\t\t\t*         7. Book Issue                           *" << endl;
    cout << "\t\t\t\t\t\t*         8. Book Deposit                         *" << endl;
    cout << "\t\t\t\t\t\t*         9. Exit                                 *" << endl;
    cout << "\t\t\t\t\t\t*                                                 *" << endl;
    cout << "\t\t\t\t\t\t***************************************************" << endl;
    cout << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t\tPlease enter your choice: ";
    cin >> opt;
    cin.ignore();

    switch (opt)
    {
    case 1:
    {
        system("clear");
        b.show_all_books();
        break;
    }

    case 2:
    {
        system("clear");
        int id;
        cout << "Enter the id of the book to be searched : ";
        cin >> id;
        b.search_books(id);
        break;
    }

    case 3:
    {
        system("clear");
        b.add_book();
        break;
    }
    case 4:
    {
        system("clear");
        b.delete_book();
        break;
    }
    case 5:
    {
        system("clear");
        b.modify_book();
        break;
    }
    case 6:
    {
        system("clear");
        b.issued_books();
        break;
    }
    case 7:
    {
        system("clear");
        s.book_issue();
        break;
    }
    case 8:
    {
        system("clear");
        s.book_deposit();
        break;
    }
    case 9:
    {
        system("clear");
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;
        cout << "\t\t\t\t\t\t*********************************************" << endl;
        cout << "\t\t\t\t\t\t*                                           *" << endl;
        cout << "\t\t\t\t\t\t*        You have exited the system!        *" << endl;
        cout << "\t\t\t\t\t\t*                 Thank You!                *" << endl;
        cout << "\t\t\t\t\t\t*                                           *" << endl;
        cout << "\t\t\t\t\t\t*********************************************" << endl;
        cout << endl
             << endl
             << endl;
        exit(0);
    }

    default:
    {
        system("clear");
        cout << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl
             << endl;
        cout << "\t\t\t\t\t\t   Sorry! The system do not have this function!" << endl;
        cout << "\t\t\t\t\t\t   Press any key to continue!" << endl;
        cin.get();
        cin.get();
        menu();
    }
    }
    if (opt != 9)
    {
        menu();
    }

    return 0;
}

int main_screen()
{

    system("clear");
    cout << endl
         << endl
         << endl
         << endl
         << endl
         << endl;
    cout << "\t\t\t\t\t\t**************************************************" << endl;
    cout << "\t\t\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t\t\t*                    WELCOME TO                  *" << endl;
    cout << "\t\t\t\t\t\t*            LIBRARY MANAGEMENT SYSTEM           *" << endl;
    cout << "\t\t\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t\t\t*                                                *" << endl;
    cout << "\t\t\t\t\t\t**************************************************" << endl;
    cout << endl
         << "\t\t\t\t\t\t\t    Press any Key to continue!" << endl
         << endl;
    cin.get();
    menu();
    return 0;
}

int main()
{
    main_screen();
    return 0;
}
