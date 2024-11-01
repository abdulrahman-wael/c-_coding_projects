#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <assert.h>
using namespace std;

/////////////// HELPER FNs //////////////////
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
string dash_to_space(string str)
{
	for (int char_indx = 0; char_indx < str.size(); char_indx++)
	{
		if (str[char_indx] == '_')
			str[char_indx] = ' ';
	}
	return str;
}
string space_to_dash(string str)
{
	for (int char_indx = 0; char_indx < str.size(); char_indx++)
	{
		if (str[char_indx] == ' ')
			str[char_indx] = '_';
	}
	return str;
}
int read_int(const int &num_of_options)
{
	int result;
	bool correct_choice = false;

	while (!correct_choice)
	{
		const int MIN_CHOICE = 1;
		const int MAX_CHOICE = num_of_options;
		cout << "Enter number in range " << MIN_CHOICE << " - " << MAX_CHOICE << ": ";
		cin >> result;

		if (MIN_CHOICE > result || result > MAX_CHOICE)
		{
			cout << "Invalid choice ... Try again\n";
			continue;
		}
		correct_choice = true;
	}
	return result;
}
int display_menu(const vector<string> &points)
{
	cout << "Menu: \n";

	int i = 1;
	for (const string &point : points)
	{
		cout << "\t" << i++ << ": " << point << "\n";
	}
	cout << "\n";
	const int OPTIONS = points.size();
	return read_int(OPTIONS);
}

///////////// back_end level 1 /////////////
class User
{
private:
	int user_id = 0;
	string username;
	bool anonymous_questioning = 0;
	string name;
	string email;
	string password;

public:
	User(int &user_id, string &username, bool &anonymous_questioning, string &name, string &email, string &password)
	{
		set(user_id, username, anonymous_questioning, name, email, password);
	}
	void set(int &user_id, string &username, bool &anonymous_questioning, string &name, string &email, string &password)
	{
		this->user_id = user_id;
		this->username = username;
		this->anonymous_questioning = anonymous_questioning;
		this->name = name;
		this->email = email;
		this->password = password;
	}
	void set_from_vector(const vector<string> &input)
	{
		assert(input.size() == 6);

		user_id = stoi(input[0]);
		anonymous_questioning = stoi(input[2]);
		username = input[1];
		name = dash_to_space(input[3]);
		email = input[4];
		password = input[5];
	}

	User() = default;

	string to_string(char delim = ',') const
	{
		ostringstream oss;
		oss << user_id << delim << username << delim << anonymous_questioning << delim;

		string new_name = space_to_dash(name);

		oss << new_name << delim << email << delim << password;
		return oss.str();
	}

	bool check_login(const string &current_username, const string &current_password) const
	{
		if (username == current_username && password == current_password)
			return true;
		return false;
	}

	bool check_sign_up(const string &current_username, const string &current_email) const
	{
		if (current_username == username)
		{
			cout << "This username is token!\n";
			return false;
		}
		if (current_email == email)
		{
			cout << "This email is token!\n";
			return false;
		}
		return true;
	}

	int get_id() const
	{
		return user_id;
	}

	const bool AQ() const
	{
		return anonymous_questioning;
	}

	void print_user() const
	{
		cout << "ID: " << user_id << "		Name: " << name << "\n";
	}
};
class Question
{
private:
	int question_id = 0;
	int from_user = 0;
	int to_user = 0;
	bool anonymous_question = 0;
	string question_text;
	string answer;

public:
	Question(const int question_id, const int from_user, const int to_user, const bool anonymous_question, string &question_text, string answer = "") : question_id(question_id), from_user(from_user), to_user(to_user), anonymous_question(anonymous_question), question_text(question_text), answer(answer) {}

	Question() = default;

	void set_from_vector(const vector<string> &input)
	{

		if (input.size() >= 6)
		{
			question_id = stoi(input[0]);
			from_user = stoi(input[2]);
			to_user = stoi(input[3]);
			anonymous_question = stoi(input[4]);
			question_text = dash_to_space(input[5]);
			if (input.size() == 7)
				answer = dash_to_space(input[6]);
			else
				answer = "";
		}
		else
			cout << "Invalid vector size.\n\n";
	}

	void set_answer(const string &line)
	{
		answer = line;
	}

	string to_string(const int &parent_question_id, const char &delim = ',') const
	{
		ostringstream oss;
		oss << question_id << delim << parent_question_id << delim << from_user << delim << to_user << delim
			<< anonymous_question << delim;

		string new_question_text = space_to_dash(question_text);
		string new_answer = space_to_dash(answer);

		oss << new_question_text << delim << new_answer;
		return oss.str();
	}

	bool print_to_user() const
	{
		cout << "Question Id (" << question_id << ")";
		if (!anonymous_question)
			cout << " from user id(" << from_user << ")";
		cout << "		Question: " << question_text << "\n";

		if (answer != "")
		{
			cout << "		Answer: " << answer << "\n";
			return true;
		}
		cout << "NOT ANSWERED YET!\n";
		return false;
	}

	void print_thread() const
	{
		cout << "		Thread: ";
		cout << "Question Id (" << question_id << ")";
		if (!anonymous_question)
			cout << " from user id(" << from_user << ")";
		cout << "		Question: " << question_text << "\n";

		cout << "		Thread:";
		if (answer != "")
			cout << "		Answer: " << answer << "\n";
		else
			cout << "NOT ANSWERED YET!\n";
	}

	void print_from_user() const
	{
		cout << "Question Id (" << question_id << ")";
		if (!anonymous_question)
			cout << " !AQ";
		cout << " to user id(" << to_user << ")";
		cout << "		Question: " << question_text << "\n";

		if (answer != "")
			cout << "		Answer: " << answer << "\n";
		else
			cout << "NOT ANSWERED YET!\n";
	}

	void feed() const
	{
		cout << "Question Id (" << question_id << ")";
		if (!anonymous_question)
			cout << " from user id(" << from_user << ")";
		cout << " to user id(" << to_user << ")";
		cout << "		Question: " << question_text << "\n";

		if (answer != "")
			cout << "		Answer: " << answer << "\n";
		else
			cout << "NOT ANSWERED YET!\n";
	}

	int get_id() const
	{
		return question_id;
	}

	const bool check_to_user(const int &ID) const
	{
		if (ID == to_user)
			return true;
		return false;
	}

	const bool check_from_user(const int &ID) const
	{
		if (ID == from_user)
			return true;
		return false;
	}
};

//////// back_end level 2 (systems) ////////
class Users_system
{
private:
	map<int, User> userID_to_user;
	User active_user;
	int lastID = 0;

	void update_users(const User &new_user)
	{
		userID_to_user.emplace(new_user.get_id(), new_user);
		string line = new_user.to_string();
		vector<string> lines;
		lines.push_back(line);
		write_to_file("users_file.txt", lines);
	}

public:
	void load_users()
	{
		userID_to_user.clear();
		lastID = 0;

		string line;
		vector<string> lines = read_from_file("users_file.txt");
		for (auto &line : lines)
		{
			if (line == "")
				break;
			istringstream iss(line);

			vector<string> tokens;
			string token;
			while (getline(iss, token, ','))
			{
				tokens.push_back(token);
			}
			User current_user;
			current_user.set_from_vector(tokens);
			userID_to_user.emplace(current_user.get_id(), current_user);
			lastID = max(lastID, current_user.get_id());
		}
	}

	const User &first_menu()
	{

		int choice = display_menu({"Login", "Sign up"});
		if (choice == 1)
			return login();
		else
			return sign_up();
	}

	const User &login()
	{
		load_users();

		string username, password;
		cout << "Enter username & password: ";
		cin >> username >> password;

		for (const pair<int, User> &current_item : userID_to_user)
		{
			if (current_item.second.check_login(username, password))
				active_user = current_item.second;
		}
		if (!active_user.get_id())
		{
			cout << "invalid login.. Try again or sign-up instead?\n";
			return first_menu();
		}
		return active_user;
	}

	const User &sign_up()
	{
		load_users();

		bool correct_sign_up = 0;
		while (!correct_sign_up)
		{
			bool invalid = false;

			string username, password, name, email;
			bool anonymous_questioning;
			cout << "Enter user name. (NO SPACES): ";
			cin >> username;

			cout << "Enter email: ";
			cin >> email;

			for (const pair<int, User> &current_item : userID_to_user)
			{
				if (!current_item.second.check_sign_up(username, email))
					invalid = true;
			}
			if (invalid)
				continue;

			cout << "Enter password: ";
			cin >> password;
			cout << "Enter name: ";
			getline(cin, name);
			getline(cin, name);
			cout << "Allow anonymous questions?: (0 or 1) ";
			cin >> anonymous_questioning;

			correct_sign_up = true;

			active_user.set(++lastID, username, anonymous_questioning, name, email, password);
		}

		update_users(active_user);
		return active_user;
	}

	void list_system_users()
	{
		for (const pair<int, User> &current_item : userID_to_user)
		{
			current_item.second.print_user();
		}
		cout << "\n";
	}

	void validate_user_id(int &result_id, User &result_user) const
	{
		bool valid = false;
		while (!valid)
		{
			cout << "Enter user id or -1 to cancel: ";
			cin >> result_id;

			if (result_id == -1)
				return;

			for (pair<int, User> search_item : userID_to_user)
			{
				if (search_item.first == result_id)
				{
					result_user = userID_to_user.at(result_id);
					valid = true;
				}
			}
			if (!valid)
				cout << "Invalid input.. try again\n";
		}
	}

	const User &logout()
	{
		cout << "logging you out ... good bye :)\n";
		active_user.print_user();
		return first_menu();
	}

	const User &get_current_user()
	{
		return active_user;
	}
};
class Questions_system
{
private:
	User active_user;
	int lastID = 0;

	// map from parent question ids to all ids (including the parent questions them selves)
	multimap<int, int> question_to_thread;

	// all question ids to their question object
	map<int, Question> questionID_to_question;

	// helper member functions
	int validate_input_id(const User &User)
	{
		int result;
		cout << "Enter question id or -1 to cancel: ";
		cin >> result;
		if (result == -1)
			return -1;
		if (!question_to_thread.count(result))
		{
			cout << "this ID doesn't exist! \n";
			return validate_input_id(User);
		}

		const Question &Question = questionID_to_question.find(result)->second;
		if (!Question.check_to_user(User.get_id()))
		{
			cout << "Invalid question ID. try again\n";
			return validate_input_id(User);
		}

		return result;
	}

	void update_questions(const int &parent_id, const Question &new_question)
	{
		questionID_to_question.emplace(new_question.get_id(), new_question);
		question_to_thread.emplace(parent_id, new_question.get_id());
		string line = new_question.to_string(parent_id);
		vector<string> lines;
		lines.push_back(line);
		write_to_file("questions_file.txt", lines);
	}
	void update_whole_data()
	{
		// current_relation: parent = first, child = second (IDs)
		vector<string> lines;

		for (const pair<int, int> &current_relation : question_to_thread)
		{
			const Question &current_question = questionID_to_question[current_relation.second];
			string line = current_question.to_string(current_relation.first);
			lines.push_back(line);
		}
		write_to_file("questions_file.txt", lines, false);
	}

public:
	Questions_system() = default;
	void load_questions()
	{
		lastID = 0;
		questionID_to_question.clear();
		question_to_thread.clear();

		string line;
		vector<string> lines = read_from_file("questions_file.txt");
		for (auto &line : lines)
		{
			if (line == "")
				break;

			istringstream iss(line);

			vector<string> tokens;
			string token;
			while (getline(iss, token, ','))
			{
				tokens.push_back(token);
			}

			Question current_question;
			if (tokens.size() < 7)
			{
				for (int i = tokens.size(); i <= 7; i++)
				{
					tokens.push_back("");
				}
			}
			current_question.set_from_vector(tokens);
			lastID = max(lastID, current_question.get_id());

			// to get each question
			questionID_to_question.emplace(current_question.get_id(), current_question);

			// to set labels to each question as parent and children (aka: threaded and non-threaded questions)
			int parent = stoi(tokens[1]);
			int child = stoi(tokens[0]);
			question_to_thread.emplace(parent, child);
		}
	}
	void set_active_user(const User &input)
	{
		active_user = input;
	}
	void print_questions_to_user()
	{
		for (const pair<int, int> &current_relation : question_to_thread)
		{
			const Question &current_question = questionID_to_question[current_relation.second];

			if (current_question.check_to_user(active_user.get_id()))
			{
				if (current_relation.first != current_relation.second)
					current_question.print_thread();
				else
					current_question.print_to_user();
			}
		}
	}
	void print_questions_from_user()
	{
		for (const pair<int, int> &current_relation : question_to_thread)
		{
			const Question &current_question = questionID_to_question[current_relation.second];

			if (current_question.check_from_user(active_user.get_id()))
			{
				current_question.print_from_user();
			}
		}
	}
	void answer_question(const User &User)
	{
		int input_id = validate_input_id(User);
		if (input_id == -1)
			return;

		Question &current_question = questionID_to_question[input_id];

		// the function print_question() returns a boolean function that is = true when there is an answer
		bool found_answer = current_question.print_to_user();
		if (found_answer)
			cout << "Warning: Already answered. Answer will be updated\n";

		cout << "Enter answer: ";
		string line;
		getline(cin, line);
		getline(cin, line);
		current_question.set_answer(line);

		update_whole_data();
	}

	void delete_question(const User &User)
	{
		int input_id = validate_input_id(User);
		if (input_id == -1)
			return;

		vector<int> ids_to_remove;

		if (question_to_thread.count(input_id))
		{
			auto range = question_to_thread.equal_range(input_id);
			for (auto itr = range.first; itr != range.second; itr++)
			{
				ids_to_remove.push_back(itr->second);
			}

			question_to_thread.erase(input_id);
		}
		else
		{
			ids_to_remove.push_back(input_id);

			for (auto itr = question_to_thread.begin(); itr != question_to_thread.end();)
			{
				if (itr->second == input_id)
				{
					itr = question_to_thread.erase(itr);
					break;
				}
				else
				{
					++itr;
				}
			}
		}

		for (const int &id : ids_to_remove)
		{
			questionID_to_question.erase(id);
		}

		update_whole_data();
	}

	void ask_question(const Users_system &active_users_system)
	{
		int current_user_id;
		User current_user;
		// this function returns boolean expression + changes the content of current_id, current_user
		active_users_system.validate_user_id(current_user_id, current_user);
		if (current_user_id == -1)
			return;

		// can this user be asked anonymously
		if (!current_user.AQ())
		{
			cout << "Note: Anonymous questions are not allowed for this user\n";
		}

		int current_question_id;
		bool correct_choice = false;
		string current_question_text;
		while (!correct_choice)
		{
			cout << "For thread question: Enter question id or -1 for new question: ";
			cin >> current_question_id;
			if (current_question_id == -1)
				correct_choice = true;
			else
			{
				auto itr = questionID_to_question.find(current_question_id);
				if (itr != questionID_to_question.end())
					correct_choice = true;
			}
			if (!correct_choice)
				cout << "invalid .. try again\n";
		}

		cout << "Enter question text: ";
		string line;
		getline(cin, line);
		getline(cin, line);
		current_question_text = line;

		const int SENDING_USER_ID = active_user.get_id();
		const int RECEIVING_USER_ID = current_user_id;
		Question current_question(++lastID, SENDING_USER_ID, RECEIVING_USER_ID, current_user.AQ(), current_question_text);

		if (current_question_id == -1)
		{
			// current_question_id = -1 indicating new question .. so the id is generated automatically for the new question and it's the parent of itself
			update_questions(current_question.get_id(), current_question);
		}
		else
		{
			// current_question_id is for an existing question .. so the parent is current_question
			update_questions(current_question_id, current_question);
		}
	}

	void list_feed()
	{
		for (const auto &pair : question_to_thread)
		{
			const Question &question = questionID_to_question.at(pair.second);

			// this means that it's a thread not a parent question
			if (pair.first != pair.second)
				cout << "Thread Parent Question ID (" << pair.first << ") ";

			question.feed();
		}
	}
};

//////////////// front_end ////////////////
class AskFM
{
private:
	Users_system users_system;
	Questions_system questions_system;

public:
	void run()
	{
		User active_user = users_system.first_menu();
		questions_system.set_active_user(active_user);

		while (true)
		{
			vector<string> menu;
			menu.push_back("Print Questions to me");
			menu.push_back("Print Questions from me");
			menu.push_back("Answer Question");
			menu.push_back("Delete Question");
			menu.push_back("Ask Question");
			menu.push_back("List System Users");
			menu.push_back("Feed");
			menu.push_back("Logout");
			int choice = display_menu(menu);
			questions_system.load_questions();
			switch (choice)
			{
			case (1):
				questions_system.print_questions_to_user();
				break;
			case (2):
				questions_system.print_questions_from_user();
				break;
			case (3):
				questions_system.answer_question(active_user);
				break;
			case (4):
				questions_system.delete_question(active_user);
				break;
			case (5):
				questions_system.ask_question(users_system);
				break;
			case (6):
				users_system.list_system_users();
				break;
			case (7):
				questions_system.list_feed();
				break;
			default:
				// this will two things: make the current user logout then make a new user login
				// value of active_user is reassigned
				active_user = users_system.logout();
			}
		}
	}
};

int main()
{
	AskFM system;
	system.run();

	return 0;
}