
// all of those are included in the uncommented library included below
// #include "helperFNs_and_properties.h"
// #include "Users_system.h"
// #include "Payment_system.h"
#include "Itinerary_system.h"

// for each class that must be initialized with dummy data .. we will use a function : void dummy_reader(.. some variables)

////////////// front-end system //////////
class Expedia
{
private:
	Users_manager *users_manager;
	Itinerary_manager *itinerary_manager;
	User *user;
	Payment_manager *payment_manager;

	void load_data()
	{
		users_manager->load_users();
		itinerary_manager->load_itineraries();
		itinerary_manager->load_data_sources();
		payment_manager->load_cards();
	}

	void customer_view()
	{
		auto *customer = dynamic_cast<Customer *>(user);
		while (true)
		{
			int choice = display_menu({"View Profile", "Make itinerary", "List my itineraries", "Logout"});
			if (choice == 1)
				users_manager->view_profile();
			else if (choice == 2)
				itinerary_manager->make_itinerary(payment_manager, customer);
			else if (choice == 3)
				itinerary_manager->list_itineraries(customer);
			else
				break;
		}
	}
	// and each type of user we add later will have a separate view connected to the application
	void admin_view()
	{
		std::cout << "\n\nWorking on it :)\n\n";
	}

public:
	Expedia(const Expedia &expedia) = delete;
	Expedia &operator=(const Expedia &expedia) = delete;
	Expedia()
	{
		itinerary_manager = new Itinerary_manager();
		users_manager = new Users_manager();
		payment_manager = new Payment_manager();
	}
	void run()
	{
		// load all the data once at the begging of the program to save some type
		load_data();
		while (true)
		{
			users_manager->access_menu();
			user = users_manager->get_current_user();
			if (user->get_type() == "Customer")
				customer_view();
			else
				admin_view();
		}
	}

	~Expedia()
	{
		if (users_manager != nullptr)
		{
			delete users_manager;
			users_manager = nullptr;
		}
		if (itinerary_manager != nullptr)
		{
			delete itinerary_manager;
			itinerary_manager = nullptr;
		}
		if (user != nullptr)
		{
			delete user;
			user = nullptr;
		}
		if (payment_manager != nullptr)
		{
			delete payment_manager;
			nullptr;
		}
	}
};

int main()
{
	Expedia *site = new Expedia();
	site->run();
	delete site;
	return 0;
}