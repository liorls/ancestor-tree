/*
AUTHORS: Levana Sciari,Mayanne zeevi, Lior Samuel-Levy 

*/ 

#include <iostream>
#include <string>
#include <stdexcept>
#include "FamilyTree.hpp"

using namespace std;
using namespace family;

        Tree::Tree(string text){ //constructor - the young!

        }
        Tree& Tree::addFather(string son, string f){

            return *this;
        }
        Tree& Tree::addMother(string son, string m){

            return *this;
        }
        string Tree::relation(string name){

            return "relation";
        }
        string Tree::find(string y){

            return "find";
        }
        void Tree::display(){

        }
        void Tree::remove(string r){

        }