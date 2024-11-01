// a modified version that uses structs





#include<iostream>
using namespace std;

const int SPECIALIZATIONS = 20;
const int QUEUE = 5;

struct hospital_queue{

int spec;
int len;
int stat[QUEUE];
string name[QUEUE];

hospital_queue(){
len =0;
spec = -1;
}
hospital_queue(int _spec){
len =0, spec = _spec;
}

bool add_front(string nm, int st)
{
    if(len == QUEUE){
        cout << "sorry we can't add more patients for this specialization";
        return false;
    }
    // shift right
    for(int i=len-1; i >= 0; i--){
        name[i+1] = name[i];
        stat[i+1] = stat[i];
    }
    len++;
    name[0] = nm, stat[0] = st;
    return true;
}
bool add_end(string nm, int st)
{
    if(len == QUEUE){
        cout << "sorry we can't add more patients for this specialization";
        return false;
    }
    name[len] = nm, stat[len] = st;
    len++;
    return true;
}
void print()
{
    if(!len) return;
    cout << "There are " << len << " patients in specialization "<< spec << endl;
    for(int i=0; i< len; i++){
        cout << name[i] << " ";
        if(stat[i]) cout << "urgent\n";
        else cout << "normal\n";

    }
    cout << endl;

}
void remove_item()
{
    if(!len){
        cout << "no patients at the moment. Have a rest, Dr\n";
        return;
    }
    cout << name[0] << " please go with the Dr\n";

    // shift left
        for(int i=1; i < len; i++){
        name[i-1] = name[i];
        stat[i-1] = stat[i];
    }
    len--;
}


};
struct hospital_system{
hospital_queue q[SPECIALIZATIONS+1];
hospital_system(){

for(int i=1; i<SPECIALIZATIONS+1; i++)
    q[i] = hospital_queue(i);
}

void run()
{
    while(true){
        int choice = menu();
    if(choice == 1)
        add_patient();
    else if(choice == 2)
        print_patients();
    else if(choice == 3)
        get_next_patient();
    else break;
    }

}
int menu()
{
    int choice  = -1;
    while(choice == -1){
        cout << "\nEnter your choice\n";
        cout << "1) Add new patient\n";
        cout << "2) Print all patients\n";
        cout << "3) Get next patient\n";
        cout << "4) Exit\n";

        cin >> choice;
        if(!(1 <= choice && choice <= 4)){
            cout << "Invalid choice. Try again\n";
            choice =-1;
        }

    }
    return choice;
}
void add_patient()
{
    int spec =-1, status= -1;
    string name;
    while(spec == -1 || status == -1){


   cout << "Enter specialization, name, status: ";

   cin >> spec >> name >> status;

   if(spec < 1 || spec > 20){
    cout << "invalid specialization number. Please try again\n";
    spec =-1;
   }
   if(status != 0 && status != 1){
    cout << "invalid status number. Please try again\n";
    status=-1;
   }

   }
    if(status) q[spec].add_end(name,status);
    else q[spec].add_front(name,status);


}
void print_patients()
{
    cout << "***********************************\n";
    for(int i=0; i< SPECIALIZATIONS+1; i++){
            q[i].print();
    }


}
void get_next_patient()
{
    cout << "Enter specialization: ";
    int spec; cin >> spec;
    q[spec].remove_item();
}

};

int main() {

hospital_system hospital = hospital_system();
hospital.run();

	return 0;
}
