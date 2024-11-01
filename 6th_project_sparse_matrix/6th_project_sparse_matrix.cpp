#include <iostream>
#include <cassert>
#include <climits>

#include <vector> // for debug
#include <algorithm>
#include <sstream>
using namespace std;

bool debug_mode = false;

struct Node
{
    int data{};
    int indx{};
    Node *next{};
    Node *prev{}; // Previous node!

    Node(int data, int indx) : data(data), indx(indx) {}

    void set(Node *next, Node *prev)
    {
        this->next = next;
        this->prev = prev;
    }

    ~Node()
    {
        cout << "Destroy value: " << data << " at address " << this << "\n";
    }
};

class Sparse_array
{
    Node *head{};
    Node *tail{};
    int length = 0;
    int limit = 0;

    void debug_verify_data_integrity()
    {
        if (length == 0)
        {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else
        {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!head->prev);
            assert(!tail->next);
        }
        int len = 0;
        for (Node *cur = head; cur; cur = cur->next, len++)
        {
            if (len == length - 1) // make sure we end at tail
                assert(cur == tail);
        }

        assert(length == len);
        // assert(length == (int )debug_data.size());

        len = 0;
        for (Node *cur = tail; cur; cur = cur->prev, len++)
        {
            if (len == length - 1) // make sure we end at head
                assert(cur == head);
        }
        // cout << "\n";
    }
    void link(Node *first, Node *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }
    Node * embed_after(Node *node_before, int value, int indx)
    {
        // Add a node with value between node and its next
        Node *middle = new Node(value, indx);
        ++length;

        Node *node_after = node_before->next;
        link(node_before, middle);

        if(!node_after)
            tail = middle;
        else
        link(middle, node_after);
        return middle;
    }
    void insert_front(int value, int indx)
    {
        Node *item = new Node(value, indx);
        length++;

        if (!head)
            head = tail = item;
        else
        {
            link(item, head);
            head = item;
        }
        debug_verify_data_integrity();
    }

    bool indx_checker(int indx)
    {
        if (indx > limit - 1 || indx < 0)
        {
            cout << "invalid indx\n";
            return false;
        }
        return true;
    }

    Node * get_indx(int indx, bool create_if_missing) // not used -> from the Dr. solution
    {
        Node*prev = head;
        while(prev->next && prev->next->indx < indx)
        prev = prev->next;

        bool found = prev->next && prev->next->indx == indx;
        if(found)
        return prev->next;

        if(!create_if_missing)
        return nullptr;

        return embed_after(prev, 0, indx);
    }

public:
    Sparse_array *next{};
    Sparse_array *prev{};
    int indx = 0;

    bool check_indx_then_add(const int &value, const int &indx)
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->indx > indx)
                return false;
            if (cur->indx == indx)
            {
                cur->data += value;
                return true;
            }
        }
        return false;
    }
    Node *find_node(int indx)
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->indx == indx)
                return cur;
        }
        return nullptr;
    }
    bool indx_exists(int indx) // not used
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->indx > indx)
                return false;
            if (cur->indx == indx)
                return true;
        }
        return false;
    }
    bool change_value(int indx) // not used
    {
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur->indx == indx)
            {
                cur->indx = indx;
                return true;
            }
            else if (cur->indx > indx)
            {
                return false;
            }
        }
        return false;
    }
    void expand_limit(int limit)
    {
        if(this->limit < limit)
        this->limit = limit;
    }

    Sparse_array(int limit, int indx = 0) : limit(limit), indx(indx) {}
    void set_value(int value, int indx)
    {
        if (!indx_checker(indx))
            return;

        if (!length || indx < head->indx)
            insert_front(value, indx);
        else
        {
            // Find the node I am less than. Then I am before it
            for (Node *cur = head; cur; cur = cur->next)
            {
                if (indx == cur->indx)
                {
                    cur->data = value;
                    break;
                }
                else if (indx < cur->indx)
                {
                    embed_after(cur->prev, value, indx);
                    break;
                }
            }
        }
        debug_verify_data_integrity();
        if (debug_mode)
            cout << "successful_set_value\n";
    }
    void print_array()
    {
        if (!head)
            return;
        Node *cur = head;
        for (int i = 0; i < limit; i++)
        {
            if (i)
                cout << " ";
            if (cur && cur->indx == i)
            {
                cout << cur->data;
                cur = cur->next;
            }
            else
                cout << 0;
        }
        cout << "\n";
        if (debug_mode)
            cout << "print_array_successful\n";
    }
    void print_array_nonzero()
    {
        if (!head)
            return;
        for (Node *cur = head; cur; cur = cur->next)
        {
            if (cur != head)
                cout << " ";
            cout << cur->data;
        }
        cout << "\n";
        if (debug_mode)
            cout << "print_array_non_zero_successful\n";
    }
    int get_value(int indx)
    {
        if (!indx_checker(indx))
            return 0;
        return find_node(indx)->data;
    }
    void add(const Sparse_array &another)
    {
        expand_limit(another.limit);

        for (Node *cur = another.head; cur; cur = cur->next)
        {
            if (!check_indx_then_add(cur->data, cur->indx))
            {
                set_value(cur->data, cur->indx);
            }
        }
        debug_verify_data_integrity();
        if (debug_mode)
            cout << "add_successful\n";
    }
};

class Sparse_matrix
{
private:
    Sparse_array *head{};
    Sparse_array *tail{};
    int length = 0;
    int limit_i = 0; // related to sparse_arrays
    int limit_j = 0; // related to the nodes of a sparse_array

    void debug_verify_data_integrity()
    {
        if (length == 0)
        {
            assert(head == nullptr);
            assert(tail == nullptr);
        }
        else
        {
            assert(head != nullptr);
            assert(tail != nullptr);
            if (length == 1)
                assert(head == tail);
            else
                assert(head != tail);
            assert(!head->prev);
            assert(!tail->next);
        }
        int len = 0;
        for (Sparse_array *cur = head; cur; cur = cur->next, len++)
        {
            if (len == length - 1) // make sure we end at tail
                assert(cur == tail);
        }

        assert(length == len);
        // assert(length == (int )debug_data.size());

        len = 0;
        for (Sparse_array *cur = tail; cur; cur = cur->prev, len++)
        {
            if (len == length - 1) // make sure we end at head
                assert(cur == head);
        }
        // cout << "\n";
    }
    void sparse_array_link(Sparse_array *first, Sparse_array *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }
    Sparse_array *sparse_array_embed_after(Sparse_array *Sparse_array_before, int i, Sparse_array *specific_arr_to_add = nullptr)
    {
        Sparse_array * ret;
        // Add a Sparse_array with value between Sparse_array and its next
        if(!specific_arr_to_add){
        specific_arr_to_add = new Sparse_array(limit_j, i);
        ret = specific_arr_to_add;
        }
        else
        ret = specific_arr_to_add->next;

        ++length;

        Sparse_array *Sparse_array_after = Sparse_array_before->next;
        sparse_array_link(Sparse_array_before, specific_arr_to_add);
        sparse_array_link(specific_arr_to_add, Sparse_array_after);
        return ret;
    }
    Sparse_array *sparse_array_insert_end(int i, Sparse_array *specific_arr_to_add = nullptr)
    {
        Sparse_array * ret;
        if(!specific_arr_to_add){
        specific_arr_to_add = new Sparse_array(limit_j, i);
        ret = specific_arr_to_add;
        }
        else
        ret = specific_arr_to_add->next;
        length++;

        if (!head)
            head = tail = specific_arr_to_add;
        else
        {
            sparse_array_link(tail, specific_arr_to_add);
            tail = specific_arr_to_add;
            tail->next = nullptr;
        }
        debug_verify_data_integrity();
        return ret;
    }
    Sparse_array *sparse_array_insert_front(int i, Sparse_array *specific_arr_to_add = nullptr)
    {
        // the returned value = the next value to the specific_array_to_add before it's added to our array_matrix
        // this is done to avoid losing the sequence of sparse_arrays connected to our "specific_array" before it's added to our matrix
        Sparse_array *ret;
        if(!specific_arr_to_add){
        specific_arr_to_add = new Sparse_array(limit_j, i);
        ret = specific_arr_to_add;
        }
        else
        ret = specific_arr_to_add->next;
        length++;

        if (!head)
            head = tail = specific_arr_to_add;
        else
        {
            sparse_array_link(specific_arr_to_add, head);
            head = specific_arr_to_add;
            head->prev = nullptr;
        }
        debug_verify_data_integrity();
        return ret;
    }

    bool check_i_and_j(int i, int j)
    {
        if (i > limit_i - 1 || i < 0 || j > limit_j - 1 || j < 0)
        {
            cout << "invalid indexes: " << i << " and " << j<<  "\n";
            return false;
        }
        return true;
    }
    Sparse_array *find_sparse_array(int i)
    {
        for (Sparse_array *cur = head; cur; cur = cur->next)
        {
            if (cur->indx == i)
                return cur;
        }
        return nullptr;
    }
    bool indexes_found(int i, int j)
    {
        for (Sparse_array *cur = head; cur; cur = cur->next)
        {
            if (cur->indx > i)
                return false;
            if (cur->indx == i)
                return cur->indx_exists(j);
        }
        return false;
    }
    bool sparse_array_found(int i)
{
            for (Sparse_array *cur = head; cur; cur = cur->next)
        {
            if (cur->indx > i)
                return false;
            if (cur->indx == i)
                return true;
        }
        return false;
}
    // this will change the value of sp_arr is the condition is met
    bool check_indx_then_add(Sparse_array * &sp_arr)
    {
        int i = sp_arr->indx;
        for (Sparse_array *cur = head; cur; cur = cur->next)
        {
            if (cur->indx > i)
                return false;
            if (cur->indx == i)
            {
                cur->add(*sp_arr);
                sp_arr = sp_arr->next;
                return true;
            }
        }
        return false;
    }

    void start_printing()
    {
        cout << "Print Matrix: " << limit_i << " X " << limit_j << "\n";
    }
    void expand_limit(int limit_i, int limit_j)
    {
        if (this->limit_i < limit_i)
            this->limit_i = limit_i;
        if (this->limit_j < limit_j){
            this->limit_j = limit_j;
            for(Sparse_array *cur = head; cur ; cur = cur->next)
            {
                cur->expand_limit(limit_j);
            }
        }
    }

    Sparse_array *add_new_sparse_array(int i, Sparse_array * specific_arr_to_add = nullptr)
    {
        if (!length || i <= head->indx)
            return sparse_array_insert_front(i, specific_arr_to_add);
        else if (tail->indx <= i)
            return sparse_array_insert_end(i, specific_arr_to_add);
        else
        {
            // Find the node I am less than. Then I am before it
            for (Sparse_array *cur = head; cur; cur = cur->next)
            {
                if (i <= cur->indx)
                {
                    return sparse_array_embed_after(cur->prev, i, specific_arr_to_add);
                }
            }
        }
    }

public:
    Sparse_matrix(int limit_i, int limit_j) : limit_i(limit_i), limit_j(limit_j) {}
    void set_value(int value, int i, int j)
    {
        Sparse_array *target_array;
        if (!check_i_and_j(i, j)){
            return;
        }
        if (!sparse_array_found(i))
        {
            target_array = add_new_sparse_array(i);
        }
        else
        {
            target_array = find_sparse_array(i);
        }
        target_array->set_value(value, j);

        debug_verify_data_integrity();
        if (debug_mode)
            cout << "successful_set_value\n";
    }
    void print_matrix()
    {
        start_printing();
        if (!head)
            return;
        Sparse_array *cur = head;
        for (int i = 0; i < limit_i; i++)
        {
            if (cur && cur->indx == i)
            {
                cur->print_array();
                cur = cur->next;
            }
            else
                for (int j = 0; j < limit_j; j++){
                    cout << 0 << " ";
                    if(j == limit_j-1 && i != limit_i-1) cout << "\n";
                }
        }
        cout << "\n";
        if (debug_mode)
            cout << "print_matrix_successful\n";
    }
    void print_matrix_nonzero()
    {
        start_printing();
        for (Sparse_array *cur = head; cur; cur = cur->next)
        {
            cur->print_array_nonzero();
        }
        if (debug_mode)
            cout << "print_matrix_non_zero_successful\n";
    }
    void add(const Sparse_matrix &another)
    {
        expand_limit(another.limit_i, another.limit_j);

        for (Sparse_array *cur = another.head; cur;)
        {
            if(!check_indx_then_add(cur))
            {
                cur = add_new_sparse_array(cur->indx, cur);
            }
        }
        debug_verify_data_integrity();
        if (debug_mode)
            cout << "add_matrix_successful\n";
    }
};

static int counter = 0;
static void new_test()
{
    cout << "\n\n******************* test: (" << ++counter <<  ") *********************\n\n";
}

int main()
{
new_test(); // separator

Sparse_array arr(10);
arr.set_value(50,5);
arr.set_value(20,2);
arr.set_value(70,7);
arr.set_value(40,4);
arr.set_value(400,4); // overriding an old value
arr.print_array();
// 0 0 20 0 40 50 0 70 0 0 
arr.print_array_nonzero();
// 20 40 50 70 
cout << arr.get_value(7);

new_test(); // separator

Sparse_array arr2(11);
arr2.set_value(1,4);
arr2.set_value(3,7);
arr2.set_value(4,6);
arr2.set_value(10,10);
arr2.print_array();

arr.add(arr2); // arr must expand it's limit in order for this function to be done
arr.print_array();

new_test(); // separator

Sparse_matrix mat(10,10);
mat.set_value(5,3,5);
mat.set_value(7,3,7);
mat.set_value(2,3,2);
mat.set_value(0,3,2);
mat.set_value(6,5,6);
mat.set_value(4,5,4);
mat.set_value(3,7,3);
mat.set_value(1,7,1);
mat.set_value(1,70,1);
mat.print_matrix();
mat.print_matrix_nonzero();

new_test(); // separator

Sparse_matrix mat2(11,11);
mat2.set_value(5,3,5);
mat2.set_value(5,1,9);
mat2.set_value(6,3,8);
mat2.set_value(9,9,9);
mat2.set_value(10,10,10);

mat.print_matrix_nonzero();
mat2.print_matrix_nonzero();
mat.add(mat2);
mat.print_matrix_nonzero();
    return 0;
}
