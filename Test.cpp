/*
AUTHORS: Levana Sciari,Mayanne zeevi, Lior Samuel-Levy 

*/

#include "doctest.h"
#include <string.h>
#include "FamilyTree.hpp"

using namespace family;
using namespace std;

TEST_CASE("Test") { 
	Tree T ("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");    
    CHECK(T.relation("Yaakov") == "father");
    CHECK(T.relation("Rachel") == "mother");
    CHECK(T.relation("Rivka") == "grandmother");
    CHECK(T.relation("Avraham") == "great-grandfather");
    CHECK(T.relation("Terah") == "great-great-grandfather");
    CHECK(T.relation("xyz") == "unrelated");
    CHECK(T.relation("Yosef") == "me");

    CHECK(T.find("great-great-grandfather") == "Terah");
    CHECK(T.find("mother") == "Rachel");
    CHECK(T.find("father") == "Yaakov");

    CHECK(T.relation("terah") == "unrelated");
    CHECK(T.relation(" Terah") == "unrelated");
    CHECK(T.relation("  Terah  ") == "unrelated");
    CHECK(T.relation("Terah ") == "unrelated");


	T.remove("Avraham"); // removes Avraham and Terah
    T.remove("Yaakov");
    CHECK(T.relation("Terah") == "unrelated");
    CHECK(T.find("father") == "unrelated");
}//16

TEST_CASE("Test"){
    Tree T ("lior");
    T.addFather("lior", "ronnie")
     .addFather("ronnie", "benny")
     .addMother("ronnie", "edit")
     .addMother("lior", "sara")
     .addMother("sara", "zhava")
     .addFather("sara", "ytzhak");

    CHECK(T.relation("lior") == "me");
    CHECK(T.relation("ronnie") == "father");
    CHECK(T.relation("sara") == "mother");
    CHECK(T.relation("edit") == "grandmother");
    CHECK(T.relation("ytzhak") == "grandfather");

    CHECK(T.find("me") == "lior");
    CHECK(T.find("mother") == "sara");
    CHECK(T.find("father") == "ronnie");
    CHECK(T.find("grandmother") == "zhava");
    CHECK(T.find("grandfather") == "benny");

    CHECK(T.relation("gila") == "unrelated");
	CHECK(T.relation("shosana") == "unrelated");

    T.remove("ronnie");
    T.remove("sara");
    CHECK(T.find("father") == "unrelated");
    CHECK(T.find("mother") == "unrelated");
}//14

TEST_CASE("Test"){
    Tree T ("roy");
    T.addFather("roy", "moshe")
     .addFather("moshe", "efraim")
     .addMother("roy", "efrat")
     .addMother("efrat", "sara")
     .addMother("sara", "zhava")
     .addFather("zhava", "zvi");

    CHECK(T.relation("roy") == "me");
    CHECK(T.relation("moshe") == "father");
    CHECK(T.relation("efrat") == "mother");
    CHECK(T.relation("sara") == "grandmother");
    CHECK(T.relation("efraim") == "grandfather");
    CHECK(T.relation("zhava") == "great-grandmother");
    CHECK(T.relation("zvi") == "great-great-grandmother");

    CHECK(T.find("great-great-grandmother") == "zvi");
    CHECK(T.find("mother") == "efrat");
    CHECK(T.find("great-grandmother") == "zhava");

    CHECK(T.relation("lior") == "unrelated");
	CHECK(T.relation("morr") == "unrelated");

    T.remove("roy");
    CHECK(T.find("me") == "unrelated");
    CHECK(T.find("mother") == "unrelated");
}//14


TEST_CASE("Test"){
    Tree T ("morr");
    T.addFather("morr", "moshe")
     .addFather("moshe", "nissim")
     .addMother("moshe", "miriam")
     .addMother("morr", "orit")
     .addMother("orit", "naomi")
     .addFather("orit", "shlomo");

    CHECK(T.relation("morr") == "me");
    CHECK(T.relation("moshe") == "father");
    CHECK(T.relation("orit") == "mother");
    CHECK(T.relation("miriam") == "grandmother");
    CHECK(T.relation("shlomo") == "grandfather");

    CHECK(T.find("me") == "morr");
    CHECK(T.find("mother") == "orit");
    CHECK(T.find("father") == "moshe");
    CHECK(T.find("grandmother") == "naomi");
    CHECK(T.find("grandfather") == "nissim");

    CHECK(T.relation("orly") == "unrelated");
	CHECK(T.relation("ilanit") == "unrelated");

    T.remove("moshe");
    T.remove("orit");
    CHECK(T.find("father") == "unrelated");
    CHECK(T.find("mother") == "unrelated");
}//14


TEST_CASE("Test some fathers or some mothers exceptions"){
    Tree T("Dana");
    T.addFather("Dana", "avi")
    .addFather("Dana", "haim");
    CHECK_THROWS(T.addFather("Dana","haim"));
    CHECK_THROWS(T.addFather("Dana","David").addFather("Dana","Shlomo"));
    CHECK_THROWS(T.addMother("Dana","Rachel").addMother("Dana","leh"));
}//3


TEST_CASE("Find Test Exception Message"){
    Tree T("lior");
    try{
        T.find("uncle");
    }
    catch(const exception& ex){
        CHECK(ex.what() ==  "The tree cannot handle the 'uncle' relation");
    }
     try{
        T.find("Hatan");
    }
    catch(const exception& ex){
        CHECK(ex.what() ==  "The tree cannot handle the 'Hatan' relation");
    }
}//2




void BuildTree(Tree T){
    T.addFather("Yosef", "Yaakov")   // Tells the tree that the father of Yosef is Yaakov.
     .addMother("Yosef", "Rachel")   // Tells the tree that the mother of Yosef is Rachel.
     .addFather("Rachel", "Lavan")
     .addMother("Rachel", "Mom")
     .addFather("Lavan", "Sahor")
     .addMother("Lavan", "Levana")
     .addMother("Mom", "Motek")
            .addFather("Mom", "Potek")
            .addFather("Yaakov", "Isaac")
            .addMother("Yaakov", "Rivka")
            .addFather("Rivka", "Betoel")
            .addMother("Rivka", "Tova")
            .addFather("Isaac", "Avraham")
            .addMother("Isaac", "Sarah")
            .addFather("Avraham", "Terah")
            .addMother("Avraham", "Ela")
            .addFather("Sarah", "Shalom")
            .addMother("Sarah", "Milka")
            .addMother("Milka", "Hava")
            .addFather("Milka", "Adam")
            .addFather("Terah", "Nahor")
            .addMother("Terah", "Rot");
}
TEST_CASE("check addFather function"){
    Tree T("Yosef");
    BuildTree(T);
    CHECK(T.relation("Yaakov")== string("father"));
    CHECK(T.relation("Isaac")== string("grandfather"));
    CHECK(T.relation("Lavan")== string("grandfather"));
    CHECK(T.relation("Sahor")== string("great-grandfather"));
    CHECK(T.relation("Betoel")== string("great-grandfather"));
    CHECK(T.relation("Potek")== string("great-grandfather"));
    CHECK(T.relation("Avraham")== string("great-grandfather"));
    CHECK(T.relation("Terah")== string("great-great-grandfather"));
    CHECK(T.relation("Shalom")== string("great-great-grandfather"));
    CHECK(T.relation("Nahor")== string("great-great-great-grandfather"));
    CHECK(T.relation("Adam")== string("great-great-great-grandfather"));
    CHECK(T.relation("Aba")== string("unrelated"));
    CHECK(T.relation("yza")== string("unrelated"));
}
//13
TEST_CASE("check addMother function"){
    Tree T("Yosef");
    BuildTree(T);
    CHECK(T.relation("Rachel")== string("mother"));
    CHECK(T.relation("Mom")== string("grandmother"));
    CHECK(T.relation("Rivka")== string("grandmother"));
    CHECK(T.relation("Tova")== string("great-grandMother"));
    CHECK(T.relation("Sarah")== string("great-grandMother"));
    CHECK(T.relation("Motek")== string("great-grandMother"));
    CHECK(T.relation("Levana")== string("great-grandMother"));
    CHECK(T.relation("Milka")== string("great-great-grandmother"));
    CHECK(T.relation("Ela")== string("great-great-grandmother"));
    CHECK(T.relation("Hava")== string("great-great-great-grandmother"));
    CHECK(T.relation("Rot")== string("great-great-great-grandmother"));
    CHECK(T.relation("Aba")== string("unrelated"));
    CHECK(T.relation("yza")== string("unrelated"));
    CHECK(T.relation("Maayan")== string("unrelated"));
    CHECK(T.relation("ava")== string("unrelated"));
}
//15
TEST_CASE("check relation function"){
    Tree T("Yosef");
    BuildTree(T);
    CHECK(T.relation("Rachel")== string("mother"));
    CHECK(T.relation("Rivka")== string("grandmother"));
    CHECK(T.relation("Mom")== string("grandmother"));
    CHECK(T.relation("Levana")== string("great-grandMother"));
    CHECK(T.relation("Motek")== string("great-grandMother"));
    CHECK(T.relation("Sarah")== string("great-grandMother"));
    CHECK(T.relation("Tova")== string("great-grandMother"));
    CHECK(T.relation("Milka")== string("great-great-grandmother"));
    CHECK(T.relation("Ela")== string("great-great-grandmother"));
    CHECK(T.relation("Hava")== string("great-great-great-grandmother"));
    CHECK(T.relation("Yaakov")== string("father"));
    CHECK(T.relation("Isaac")== string("grandfather"));
    CHECK(T.relation("Lavan")== string("grandfather"));
    CHECK(T.relation("Avraham")== string("great-grandfather"));
    CHECK(T.relation("Betoel")== string("great-grandfather"));
    CHECK(T.relation("Terah")== string("great-great-grandfather"));
    CHECK(T.relation("Shalom")== string("great-great-grandfather"));
    CHECK(T.relation("Nahor")== string("great-great-great-grandfather"));
    CHECK(T.relation("Adam")== string("great-great-great-grandfather"));
    CHECK(T.relation("Yosef")== string("me"));
    CHECK(T.relation("Dani")== string("unrelated"));
    CHECK(T.relation("Moshe")== string("unrelated"));
    CHECK(T.relation("Esav")== string("unrelated"));
}
//23
TEST_CASE("check find function"){
    Tree T("Yosef");
    BuildTree(T);
    CHECK(T.find("mother")== string("Rachel"));
    CHECK(T.find("father")== string("Yaakov"));
    CHECK(T.find("grandmother")== string("Rivka") || 
            T.find("grandmother")== string("Mom"));
    CHECK(T.find("great-grandmother")== string("Sara") ||
             T.find("great-grandmother")== string("Tova") || 
             T.find("great-grandmother")== string("Levana") || 
             T.find("great-grandmother")== string("Motek"));
    CHECK(T.find("great-great-grandmother")== string("Milka") ||
            T.find("great-great-grandmother")== string("Ela"));
    CHECK(T.find("great-great-great-grandmother")== string("Hava") || 
            T.find("great-great-great-grandmother")== string("Rot"));
    CHECK(T.find("grandfather")== string("Isaac") || 
            T.find("grandfather")== string("Lavan"));
    CHECK(T.find("great-grandfather")== string("Avraham") || 
            T.find("great-grandfather")== string("Betoel")|| 
            T.find("great-grandfather")== string("Sahor") || 
            T.find("great-grandfather")== string("Potek"));
    CHECK(T.find("great-great-grandfather")== string("Terah") || 
            T.find("great-great-grandfather")== string("Shalom"));
    CHECK(T.find("great-great-great-grandfather")== string("Nahor") || 
            T.find("great-great-great-grandfather")== string("Adam"));
    CHECK_THROWS(T.find("great-great-great-great-grandfather"));
    CHECK_THROWS(T.find("uncle"));
    CHECK_THROWS(T.find("saba"));
    CHECK_THROWS(T.find("aba"));
    CHECK_THROWS(T.find("xyz"));
    CHECK_THROWS(T.find("aakov"));
    CHECK_THROWS(T.find("Maayan"));
    CHECK_THROWS(T.find("Eyal"));
}
//18
TEST_CASE("remove function"){
    Tree T("Yosef");
    BuildTree(T);
    T.remove("Yaacov");
    CHECK(T.relation("Yaacov") == string("unrelated"));
    CHECK(T.relation("Isaac") == string("unrelated"));
    CHECK(T.relation("Rivka") == string("unrelated"));
    CHECK(T.relation("Avraham") == string("unrelated"));
    CHECK(T.relation("Sarah") == string("unrelated"));
    CHECK(T.relation("Betoel") == string("unrelated"));
    CHECK(T.relation("Tova") == string("unrelated"));
    CHECK(T.relation("Terah") == string("unrelated"));
    CHECK(T.relation("Ela") == string("unrelated"));
    CHECK(T.relation("Shalom") == string("unrelated"));
    CHECK(T.relation("Milka") == string("unrelated"));
    CHECK(T.relation("Hava") == string("unrelated"));
    CHECK(T.relation("Adam") == string("unrelated"));
    CHECK(T.relation("Rot") == string("unrelated"));
    CHECK(T.relation("Nahor") == string("unrelated"));
    
    T.remove("Rachel");
    CHECK(T.relation("Rachel") == string("unrelated"));
    CHECK(T.relation("Lavan") == string("unrelated"));
    CHECK(T.relation("Mom") == string("unrelated"));
    CHECK(T.relation("Sahor") == string("unrelated"));
    CHECK(T.relation("Levana") == string("unrelated"));
    CHECK(T.relation("Motek") == string("unrelated"));
    CHECK(T.relation("Potek") == string("unrelated"));
}
//22
