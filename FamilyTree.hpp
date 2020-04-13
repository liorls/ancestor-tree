#include <iostream>
#include <string>


using namespace std;

namespace family{

    class Tree{
        public:
        Tree(string text);
        Tree& addFather(string son, string f);
        Tree& addMother(string son, string m);
        string relation(string name);
        string find(string y);
        void display();
        void remove(string r);

    };
}