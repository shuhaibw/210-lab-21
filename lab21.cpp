// COMSC-210 | Lab 21 | Shuhaib Walahi
// IDE used: VS Code

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MIN_LS = 5, MAX = 20, SIZE = 15;

class Goat
{
    private:
        int age;
        string name;
        string color;
        string names[SIZE] = {"Billy", "Nibbles", "Daisy", "Ginger", "Luna", 
                              "Misty", "Oliver", "Pepper", "Clover", "Sunny", 
                              "Mabel", "Willow", "Hazel", "Ruby", "Ziggy"};
        string colors[SIZE] = {"White", "Brown", "Black", "Gray", "Spotted", 
                               "Golden", "Cream", "Chocolate", "Rust", "Tan", 
                               "Piebald", "Sable", "Fawn", "Slate", "Dappled"};

    public:
        // default constructor
        Goat() 
        {
            // assign random age from 1-20
            age = rand() % MAX + 1;
            // assign random name
            name = names[rand() % SIZE];
            // assign random color
            color = colors[rand() % SIZE];
        }

        // parameter constructor
        Goat(int a, string n, string c) 
        {
            age = a;
            name = n;
            color = c;
        }

        // getters
        int getAge() const {return age;}
        string getName() const {return name;}
        string getColor() const {return color;}

        // print goat objects
        void print_goat() const
        {
            cout << "    " << name << " (" << color 
            << ", " << age << ")" << endl;
        }
};

class DoublyLinkedList 
{
private:
    struct Node 
    {
        Goat obj;
        Node* prev;
        Node* next;

        Node(const Goat& g, Node* p = nullptr, Node* n = nullptr) 
        {
            // assign given value to goat obj 
            obj = g;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() 
    {
        head = nullptr; 
        tail = nullptr; 
    }

    void push_back(const Goat& obj) 
    {
        Node* newNode = new Node(obj);
        if (!tail) // if there's no tail, the list is empty
        {
            head = tail = newNode;
        } 
        else 
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(const Goat& obj) 
    {
        Node* newNode = new Node(obj);
        if (!head) // if there's no head, the list is empty
        {
            head = tail = newNode;
        } 
        else 
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(const Goat& obj, int position) 
    {
        if (position < 0) 
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(obj);
        if (!head) 
        {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i) 
        {
            temp = temp->next;
        }

        if (!temp) 
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next) 
        {
            temp->next->prev = newNode;
        } 
        else 
        {
            tail = newNode; // Inserting at the end
        }

        temp->next = newNode;
    }

    void delete_node(const Goat& g) 
    {
        if (!head) 
        {
            return; // Empty list
        }

        Node* temp = head;
        while (temp) 
        {
            // check if we find the node
            if(temp->obj.getAge() == g.getAge()
            && temp->obj.getName() == temp->obj.getName() 
            && g.getColor() == g.getColor())
                {
                    break;
                }
            // otherwise continue 
            temp = temp->next;
        }

        if (!temp) 
        {
            return; // Value not found
        }

        if (temp->prev) 
        {
            temp->prev->next = temp->next;
        } 
        else 
        {
            head = temp->next; // Deleting the head
        }

        if (temp->next) 
        {
            temp->next->prev = temp->prev;
        } 
        else 
        {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() 
    {
        Node* current = head;
        if (!current) 
        {
            return;
        }

        while (current) 
        {
            // call the print goat member function 
            current->obj.print_goat();
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() 
    {
        Node* current = tail;
        if (!current) 
        {
            return;
        }

        while (current) 
        {
            // call the print goat member function 
            current->obj.print_goat();
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() 
    {
        while (head) 
        {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() 
{
    // seed random num generator
    srand(static_cast<unsigned>(time(0)));

    DoublyLinkedList list;
    // get random int between 5-20
    int random = rand() % (MAX-MIN_LS+1) + MIN_LS;

    // add 5-20 goat objects to the list
    for (int i = 0; i < random; ++i) 
    {
        list.push_back(Goat());
    }

    cout << "Forward: " << endl;
    list.print();

    cout << "Backward: " << endl;
    list.print_reverse();
   
    return 0;
}

