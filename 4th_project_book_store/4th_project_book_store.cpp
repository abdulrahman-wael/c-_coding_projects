#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <assert.h>
#include <ctime>
using namespace std;

//////////// HELPER FNs /////////////
// reading and writing from a file (+ check if failed to open + close it)
vector<string> read_from_file(const string &path)
{
    fstream file(path.c_str());
    vector<string> output;

    if (file.fail())
    {
        cout << "\nERROR: failed to open the file\n\n";
        return output;
    }

    string line;
    while (getline(file, line))
    {
        if (line.size() == 0)
            continue;
        output.push_back(line);
    }
    file.close();
    return output;
}
void write_to_file(const string &path, const vector<string> &input, bool append = true)
{
    auto status = ios::in | ios::out | ios::app;
    if (!append)
        status = ios::in | ios::out | ios::trunc;

    fstream file(path.c_str(), status);
    if (file.fail())
    {
        cout << "\nERROR: can't write to the file\n\n";
        return;
    }
    for (auto &line : input)
        file << line << '\n';

    file.close();
}

// string manipulators
vector<string> split_string(const string &str, const string &delimiter = ",")
{
    string input = str;
    vector<string> output;

    int pos = 0;
    string substr;
    while ((pos = (int)input.find(delimiter)) != -1)
    {
        substr = input.substr(0, pos);
        output.push_back(substr);
        input.erase(0, pos + delimiter.length());
    }
    output.push_back(input);
    return output;
}
string aggregate_string(const vector<string> &input, const string &delimiter = ",")
{
    ostringstream oss;
    oss << input[0];
    for (int indx = 1; indx < (int)input.size(); indx++)
    {
        oss << delimiter << input[indx];
    }
    return oss.str();
}

// inter a valid integer to the system from the range provided
int read_int(int low, int high)
{
    int choice;
    while (true)
    {
        cout << "Enter a choice from " << low << " to " << high << ": ";
        cin >> choice;
        if (low <= choice && choice <= high)
            break;
        else
            cout << "invalid input .. try again!\n";
    }

    return choice;
}

// display a menu to the screen from a vector list
int display_menu(const vector<string> &menu)
{
    cout << "################################################\n";
    cout << "\nMenu:\n ";
    for (int i = 0; i < (int)menu.size(); i++)
    {
        cout << "\t" << i + 1 << ": " << menu[i] << '\n';
    }
    return read_int(1, (int)menu.size());
}

////////////// level 1 ////////////////
class User
{
private:
    int id = 0;
    string username;
    string password;
    string name;
    string email;

    // customer = 0 , admin = 1
    bool type = 0;

    // setters
    void set_id(const int &id)
    {
        this->id = id;
    }
    void set_username(const string &username)
    {
        this->username = username;
    }
    void set_password(const string &password)
    {
        this->password = password;
    }
    void set_name(const string &name)
    {
        this->name = name;
    }
    void set_email(const string &email)
    {
        this->email = email;
    }
    void set_type(const bool &type)
    {
        this->type = type;
    }

public:
    // set data from string line
    User(const string &line)
    {
        vector<string> substrs = split_string(line);

        assert(substrs.size() == 6);
        set_id(stoi(substrs[0]));
        set_username(substrs[1]);
        set_password(substrs[2]);
        set_name(substrs[3]);
        set_email(substrs[4]);
        set_type(stoi(substrs[5]));
    }
    User() = default;

    void set(const int &id, const string &username, const string &password, const string &name, const string &email)
    {
        set_id(id);
        set_username(username);
        set_password(password);
        set_name(name);
        set_email(email);
    }

    const string user_to_string(char delim = ',') const
    {
        ostringstream oss;
        oss << id << delim << username << delim << password << delim << name << delim << email << delim << type;
        return oss.str();
    }

    // used for encapsulating the data especially the password from being seen in the other system parts
    bool check_login(const string &username, const string &password) const
    {
        if ((this->username == username) && (this->password == password))
            return true;
        return false;
    }
    bool check_sign_up(const string &username, const string &email) const
    {
        if ((this->username == username) && (this->email == email))
        {
            cout << "Both username and email are token!\n";
            return false;
        }
        else if (this->username == username)
        {
            cout << "This username is token!\n";
            return false;
        }
        else if (this->email == email)
        {
            cout << "This email is token!\n";
            return false;
        }
        return true;
    }

    // available getters
    const string &get_name() const
    {
        return name;
    }
    const string &get_username() const
    {
        return username;
    }
    const string &get_email() const
    {
        return email;
    }
    const bool &is_admin() const
    {
        return type;
    }
    const int &get_id() const
    {
        return id;
    }
};

class Book
{
private:
    string ISBN;
    string title;
    string author_name;
    vector<string> pages;

public:
    void new_book(const string &ISBN)
    {
        pages.clear();
        string filler; // this is for tackling the '\n' reading problem for the first input
        this->ISBN = ISBN;
        cout << "Enter Title: ";
        getline(cin, filler);
        getline(cin, title);
        cout << "Author Name: ";
        getline(cin, author_name);
        cout << "Enter how many pages: ";
        int total_num;
        cin >> total_num;
        for (int current_num = 1; current_num <= total_num; current_num++)
        {
            cout << "Enter page # " << current_num << ": ";
            string content;
            if (current_num == 1)
                getline(cin, filler);

            getline(cin, content);
            pages.push_back(content);
        }
    }

    void set(const string &line)
    {
        pages.clear();

        string str = line;
        const auto &substrs = split_string(str);
        ISBN = substrs[0];
        title = substrs[1];
        author_name = substrs[2];
        for (int indx = 3; indx < (int)substrs.size(); indx++)
        {
            pages.push_back(substrs[indx]);
        }
    }

    const string book_to_string(char delim = ',') const
    {
        ostringstream oss;
        oss << ISBN << delim << title << delim << author_name;
        for (const string &page : pages)
            oss << delim << page;
        return oss.str();
    }

    // getters
    const int &total_pages() const
    {
        return pages.size();
    }
    void display_page(const int &indx) const
    {
        cout << "Current page: " << indx << '/' << total_pages() << "\n";
        cout << pages.at(indx - 1) << "\n";
    }
    const string &get_title() const
    {
        return title;
    }
    const string &get_ISBN() const
    {
        return ISBN;
    }
};

////////////// level 2 ///////////////
class Users_manager
{
private:
    int lastID;
    User active_user;
    vector<User> users;

    void load_data()
    {
        users.clear();
        lastID = 0;
        // read users data + their reading history
        vector<string> lines = read_from_file("users.txt");

        // create users and push them to the vector
        for (const string &line : lines)
        {
            // construct the user from this string line
            User user(line);
            lastID = max(lastID, user.get_id());
            users.push_back(user);
        }
    }

    void update_data(const User &user)
    {
        users.push_back(user);
        string line = user.user_to_string();
        const vector<string> &lines{line};
        write_to_file("users.txt", lines);
    }

    void hello()
    {
        cout << "\n\nHello " << active_user.get_name() << " | ";
        if (active_user.is_admin())
            cout << "Admin View\n\n";
        else
            cout << "User View\n\n";
    }

    void login()
    {
        load_data();

        string username, password;
        cout << "Enter username & password: ";
        cin >> username >> password;

        for (const auto &user : users)
        {
            // check_login checks if the user exists in the database
            if (user.check_login(username, password))
                active_user = user;
        }
        if (!active_user.get_id())
        {
            cout << "invalid login.. Try again or sign-up instead?\n";
            return access_menu();
        }
        hello();
    }

    // admins cannot sign_up but can login only..
    void sign_up()
    {
        load_data();

        while (true)
        {
            bool invalid = false;

            string username, email, password, name;
            cout << "Enter user name. (NO SPACES): ";
            cin >> username;

            cout << "Enter email: ";
            cin >> email;

            for (const auto &user : users)
            {
                // check_sign_up makes sure that this username and email DO NOT exist in the system (contrary to check_login)
                if (!user.check_sign_up(username, email))
                    invalid = true;
            }
            if (invalid){
                continue;
            }

            cout << "Enter password: ";
            cin >> password;
            cout << "Enter name: ";
            getline(cin, name);
            getline(cin, name);

            active_user.set(++lastID, username, password, name, email);

            break;
        }
        hello();
        update_data(active_user);
    }

public:
    const User &get_active_user() const
    {
        return active_user;
    }

    void access_menu()
    {
        int choice = display_menu({"Login", "Sign Up"});
        if (choice == 1)
            return login();
        return sign_up();
    }

    void view_profile()
    {
        cout << "\nName: " << active_user.get_name();
        cout << "\nEmail: " << active_user.get_email();
        cout << "\nUsername: " << active_user.get_username() << "\n";
    }

    void logout() const
    {
        cout << "logging you out ... good bye " << active_user.get_name() << ":)\n";
    }
};

class Books_manager
{
private:
    vector<Book> books;
    map<int, vector<string>> userID_to_readingHistory;
    Book current_book;

    void display_books()
    {
        cout << "\nOur current book collection: \n";
        const int NUM_OF_BOOKS = books.size();

        for (int current_book_num = 1; current_book_num <= NUM_OF_BOOKS; current_book_num++)
        {
            cout << current_book_num << ": " << books.at(current_book_num - 1).get_title() << "\n";
        }
        int chosen_book_num = read_int(1, NUM_OF_BOOKS);
        current_book = books.at(chosen_book_num -1);
    }

    int display_history(const int &userID)
    {
        cout << "\nYour reading history: \n";
        // if there is no reading history for this user
        if (!userID_to_readingHistory.count(userID))
        {
            cout << "no reading history recorded for this user\n";
            return -1;
        }

        const vector<string> &reading_history = userID_to_readingHistory.at(userID);
        const int &NUM_OF_ENTRIES = reading_history.size();

        for (int current_entry_num = 1; current_entry_num <= NUM_OF_ENTRIES; current_entry_num++)
        {
            cout << current_entry_num << ": ";
            string str = reading_history.at(current_entry_num - 1);
            const vector<string> &data = split_string(str);
            cout << data[0] << " Page: " << data[1] << "/" << data[2]<< " - " << data[3] << " " << data[4];
            cout << "\n";
        }

        // changing the values to user input
        int chosen_entry_num = read_int(1, NUM_OF_ENTRIES);
        // this aims to find the book that has a title identical to that found in the chosen entry text
        string chosen_entry = reading_history.at(chosen_entry_num - 1);
        const auto &data = split_string(chosen_entry);
        for (const auto &search : books)
        {
            if (search.get_title() == data[1])
                current_book = search; // now the book variable we used as parameter = search item which has the same title
        }
        return stoi(data[2]);
    }

    void navigation(int &page_num)
    {
        while (true)
        {
            current_book.display_page(page_num);
            int choice = display_menu({"Next page", "Previous page", "Stop reading"});
            if (choice == 1)
                if (current_book.total_pages() == page_num)
                    cout << "This is the last page .. can't go further\n";
                else
                    page_num++;
            else if (choice == 2)
                if (page_num == 1)
                    cout << "This is the first page .. can't go further\n";
                else
                    page_num--;
            else
                break;
        }
    }

    void update_reading_history(const int &page_num, const int &userID)
    {
        if(! userID_to_readingHistory.count(userID))
            userID_to_readingHistory.emplace(userID,vector<string>{});

        // composing the history entry line
        time_t row_time_data = time(nullptr);
        struct tm *arranged_time_data = localtime(&row_time_data);
        string current_date = to_string(arranged_time_data->tm_year + 1900) + "-" + to_string(arranged_time_data->tm_mon + 1) + "-" + to_string(arranged_time_data->tm_mday);
        string current_time = to_string(arranged_time_data->tm_hour) + ":" + to_string(arranged_time_data->tm_min) + ":" + to_string(arranged_time_data->tm_sec);

        // note that this line entry will change a bit when it's time to display it ... using the display_history member function
        string line = current_book.get_title() + "," + to_string(page_num) + "," + to_string(current_book.total_pages()) + "," + current_date + "," + current_time;
        userID_to_readingHistory.at(userID).push_back(line);

        // making the userID and the history entry into one line
        line = to_string(userID) + "," + line;
        const vector<string> &lines{line};
        write_to_file("reading_history.txt", lines);
    }

    void load_data()
    {
        userID_to_readingHistory.clear();
        books.clear();

        // adding userIDs and reading history vectors to userID_to_readingHistory map
        const vector<string> &lines_1 = read_from_file("reading_history.txt");
        int prev_id = -1;
        int id = -1;
        for (const auto &line : lines_1)
        {
            istringstream iss(line);
            char delim;
            string history_entry;
            iss >> id >> delim;
            getline(iss, history_entry);
            if (id != prev_id)
            {
                userID_to_readingHistory.emplace(id, vector<string>{history_entry});
                prev_id = id;
            }
            else
                userID_to_readingHistory.at(id).push_back(history_entry);
        }
        // adding books to the book vector
        const auto &lines_2 = read_from_file("books.txt");
        for (const auto &line : lines_2)
        {
            current_book.set(line);
            books.push_back(current_book);
        }
    }

public:
    void read_book(const int &userID)
    {
        load_data();
        // this changes the value of the current_book to the chosen book
        display_books();

        // using these values
        int page_num = 1;
        navigation(page_num);

        // record new history entry
        update_reading_history(page_num, userID);
    }

    void read_history(const int &userID)
    {
        load_data();
        int page_num = display_history(userID);
        if (page_num == -1)
        {
            return; // if there is no history recorded for this user .. we will not continue executing
        }
        navigation(page_num);
        update_reading_history(page_num, userID);
    }

    void add_book()
    {
        while (true)
        {
            // check if ISBN already exists in the database as it works as a special ID for the book
            bool invalid = false;
            cout << "Enter ISBN: ";
            string ISBN;
            cin >> ISBN;
            for (const auto &book : books)
            {
                if (book.get_ISBN() == ISBN)
                {
                    cout << "This ISBN already exists in our database\n";
                    invalid = true;
                    break;
                }
            }
            if (invalid)
                continue;

            current_book.new_book(ISBN);
            books.push_back(current_book);
            string line = current_book.book_to_string();
            const vector<string> &lines{line};
            write_to_file("books.txt", lines);
        }
    }
};

////////////// level 3 ///////////////
class Book_store
{
private:
    Users_manager users_manager;
    Books_manager books_manager;
    User user;
    void admin_view()
    {
        while (true)
        {
            int choice = display_menu({"View Profile", "Add Book", "Logout"});
            if (choice == 1)
                users_manager.view_profile();
            else if (choice == 2)
                books_manager.add_book();
            else
            {
                users_manager.logout();
                break;
            }
        }
    }
    void user_view()
    {
        while (true)
        {
            int choice = display_menu({"View Profile", "List & Select from My Reading History", "List & Select from Available Books", "Logout"});
            if (choice == 1)
                users_manager.view_profile();
            else if (choice == 2)
                books_manager.read_history(user.get_id());
            else if (choice == 3)
                books_manager.read_book(user.get_id());
            else
            {
                users_manager.logout();
                break;
            }
        }
    }

public:
    void run()
    {
        while (true)
        {
            users_manager.access_menu();
            user = users_manager.get_active_user();
            if (user.is_admin())
                admin_view();
            else
                user_view();
        }
    }
};

int main()
{
    Book_store book_store;
    book_store.run();
    return 0;
}