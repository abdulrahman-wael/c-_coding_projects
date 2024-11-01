#include <iostream>
#include <algorithm>
using namespace std;

int const MAX_BOOKS{100};
int const MAX_USERS{100};


struct book
{
    int id{};
    string name;
    int quantity{};
    int borrowed{};

};
struct user
{
    string name;
    string books[MAX_BOOKS];
    int national_id{};
    int borrowing{};

};

bool is_prefix(string name, string prefix)
{
    for(int i =0; i< prefix.size(); i++){
        if (prefix[i] != name[i])
            return false;
    }
    return true;
}
bool compare_name(book &a, book &b)
{
    return a.name < b.name;
}
bool compare_id (book &a, book &b)
{
    return a.id < b.id;
}


struct library_system
{
    book b[MAX_BOOKS];
    user u[MAX_USERS];
    int num_of_books{};
    int num_of_users{};


    void run()
    {
        cout << "Library menu: \n";
        cout << "1) add_book\n";
        cout << "2) search_books_by_prefix\n";
            cout << "3) print_who_borrowed_book_by_name\n";
        cout << "4) print_library_by_id\n";
        cout << "5) print_library_by_name\n";
        cout << "6) add_user\n";
        cout << "7) user_borrow_book\n";
        cout << "8) user_return_book\n";
        cout<< "9) print_users\n";
        cout << "10) Exit\n";

        while(true)
        {
            int choice = menu();
            if(choice == 1)
                add_book();
            else if(choice == 2)
                search_books_by_prefix();
            else if(choice == 3)
                print_who_borrowed_book_by_name();
            else if(choice == 4)
                print_library_by_id();
            else if(choice == 5)
                print_library_by_name();
            else if(choice == 6)
                add_user();
            else if(choice == 7)
                user_borrow_book();
            else if(choice == 8)
                user_return_book();
            else if(choice == 9)
                print_users();
            else
                break;
        }

    }

    int menu()
    {
        int choice = -1;
        while(choice == -1)
        {
            cout << "Enter your choice [1 - 10]: ";
            cin >> choice;
            if(choice < 1 || choice > 10)
            {
                cout << "Invalid choice. please, try again!";
                choice = -1;
            }

        }
        return choice;
    }

    void add_book()
    {
        cout << "Enter book info: id & name & total quantity: ";
        int id;
        string name;
        int total_quantity;
        cin >> id >> name >> total_quantity;
        b[num_of_books].id = id;
        b[num_of_books].name = name;
        b[num_of_books].quantity = total_quantity;
        num_of_books++;
    }

    void search_books_by_prefix()
    {
        cout << "Enter book name prefix: ";
        string prefix; cin >> prefix;

        for(int i=0; i< num_of_books; i++){
            if(is_prefix(b[i].name, prefix))
                cout << b[i].name << endl;

            if(i == num_of_books -1) cout << "No book with such prefix\n";
        }

    }

    void print_who_borrowed_book_by_name()
    {
        cout << "Enter book name: ";
        string name; cin >> name;

                bool valid = false;
        for(int i=0; i< num_of_books; i++)
        {
            if(name == b[i].name) valid = true;
        }
        if(!valid)
        {
            cout << "Invalid book name.\n";
            return;
        }

        for(int i=0; i< num_of_users; i++){
            for(int j=0; j< u[i].borrowing; j++){
                if(u[i].books[j] == name)
                    cout << u[i].name << endl;
            }
        }


    }

    void print_library_by_id()
    {

        sort(b,b+num_of_books, compare_id );
        for(int item=0; item < num_of_books; item++){
            cout << "\n" << "id= "<< b[item].id << " name= " << b[item].name << " total_quantity: "<< b[item].quantity << " total_borrowed: " << b[item].borrowed ;
        }
    }
    void print_library_by_name()
    {
                sort(b,b+num_of_books, compare_name);
        for(int item =0; item<num_of_books; item++){
            cout << "\n" << "id= "<< b[item].id << " name= " << b[item].name << " total_quantity: "<< b[item].quantity << " total_borrowed: " << b[item].borrowed ;
        }
    }

    void add_user()
    {
               cout << "Enter user name & national id: ";
       string name; int id; cin >> name >> id;
       u[num_of_users].name= {name};
        u[num_of_users].national_id= {id};
       num_of_users++;
    }

    void user_borrow_book()
    {

        cout << "Enter user name and book name: ";
        string user, book; cin >> user >> book;


        for(int i=0; i< num_of_books; i++){
            if(b[i].name == book){
                    if(b[i].borrowed == b[i].quantity){
                        cout << "sorry, all copies of this book are borrowed\n";
                        return;
                    }


                b[i].borrowed++;
                break;
            }

            if(i == num_of_books-1) cout<< "This book doesn't exist\n";
        }

        for(int j=0; j< num_of_users; j++){
            if(u[j].name == user){
                u[j].books[ u[j].borrowing++ ]= {book};
                break;
            }
            if(j == num_of_users-1) cout << "This user doesn't exist\n";
        }

    }

    void user_return_book()
    {
        cout << "Enter user name and book name: ";
        string user, book; cin >> user >> book;

        for(int i=0; i< num_of_users; i++){
            if(u[i].name == user){
                for(int j=0; j< u[i].borrowing; j++){
                if(u[i].books[j] == book){

                    for(int k=0; k<u[i].borrowing;k++){
                        u[i].books[k-1] = u[i].books[k];
                    }
                    u[i].borrowing--;



                    for(int k=0; k<num_of_books; k++){
                        if(b[k].name == book){
                            b[k].borrowed--;
                            break;
                        }
                    }



                    break;
                }
                if(j == u[i].borrowing-1) cout << "This user didn't borrow this book\n";
            }

                break;
            }
            if(i == num_of_users -1) cout << "This user doesn't exist\n";

        }

    }

    void print_users()
    {
        for(int i=0; i< num_of_users;i++){
            cout << "\n" << "user = " << u[i].name << ", id = " << u[i].national_id << " borrowed books ids = ";
            for(int j=0; j<u[i].borrowing;j++){
                for(int k=0; k<num_of_books;k++){
                    if(u[i].books[j] == b[k].name)
                        cout << b[k].id << " ";
                }
            }
        }
    }



};

int main()
{
    library_system Mansoura_library = library_system();
    Mansoura_library.run();

    return 0 ;
}
