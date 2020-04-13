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
    CHECK_THROWS(T.addFather("Dana","David").addFather("Dana","Shlomo"));
    CHECK_THROWS(T.addMother("Dana","Rachel").addMother("Dana","leh"));
}//2


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








TEST_CASE("Test"){
	Tree T("Erez");
	T.addFather("Erez", "Aharon"); 
	T.addMother("Erez", "Sigalit");
	CHECK(T.relation("Aharon") == "father");
	CHECK(T.relation("Sigalit") == "mother");
	CHECK(T.find("father") == "Aharon");
	CHECK(T.find("mother") == "Sigalit");
}

TEST_CASE("Test"){
	Tree T("Boaz");
	T.addFather("Boaz", "Aharon");
	T.addMother("Boaz", "Sigalit");
	T.addFather("Aharon","Shlomo");
	T.addMother("Aharon","Yona");
	CHECK(T.relation("Aharon") == "father");
	CHECK(T.relation("Sigalit") == "mother");
	CHECK(T.relation("Yona") == "grandmother");
	CHECK(T.relation("Shlomo") == "grandfather");
	CHECK(T.find("father") == "Aharon");
	CHECK(T.find("mother") == "Aharon");
}


TEST_CASE("Test"){
	Tree T("Shlomi");
	T.addFather("Shlomi", "Aharon");
	T.addMother("Shlomi", "Sigalit");
	T.addFather("Aharon","Shlomo");
	T.addMother("Aharon","Yona");
	T.addFather("Sigalit","Boaz");
	T.addMother("Sigalit","Mazal");
	CHECK(T.relation("Aharon") == "father");
	CHECK(T.relation("Sigalit") == "mother");
	CHECK(T.relation("Yona") == "grandmother");
	CHECK(T.relation("Boaz") == "grandfather");
        CHECK(T.relation("Mazal") == "grandmother");
	CHECK(T.relation("Shlomo") == "grandfather");
	CHECK(T.find("father") == "Aharon");
	CHECK(T.find("mother") == "Sigalit");
}


TEST_CASE("Test"){
	Tree T("Ruth");
	T.addFather("Ruth", "Aharon");
	T.addMother("Ruth", "Sigalit");
	T.addFather("Aharon","Shlomo");
	T.addMother("Aharon","Yona");
	T.addFather("Sigalit","Boaz");
	T.addMother("Sigalit","Mazal");
	CHECK(T.find("father") == "Aharon");
	CHECK(T.find("mother") == "Sigalit");
	CHECK(T.relation("Aharon") == "father");
	CHECK(T.relation("Sigalit") == "mother");
	CHECK(T.relation("Yona") == "grandmother");
	CHECK(T.relation("Boaz") == "grandfather");
        CHECK(T.relation("Mazal") == "grandmother");
	CHECK(T.relation("Shlomo") == "grandfather");
	T.remove("Aharon");
	CHECK(T.find("father") == "unrelated");
	T.addFather("Ruth", "Aharon");
	CHECK(T.relation("Aharon") == "father");
}



TEST_CASE("Test"){
	Tree T("Yonit");
	T.addFather("Yonit", "Aharon");
	T.addMother("Yonit", "Sigalit");
	T.addFather("Aharon","Shlomo");
	T.addMother("Aharon","Yona");
	T.addFather("Sigalit","Boaz");
	T.addMother("Sigalit","Mazal");
	T.addFather("Shlomo","Yosef");
	T.addMother("Shlomo","Bracha");
	CHECK(T.find("father") == "Aharon");
	CHECK(T.find("mother") == "Sigalit");
	CHECK(T.relation("Aharon") == "father");
	CHECK(T.relation("Sigalit") == "mother");
	CHECK(T.relation("Yona") == "grandmother");
	CHECK(T.relation("Boaz") == "grandfather");
        CHECK(T.relation("Mazal") == "grandmother");
	CHECK(T.relation("Shlomo") == "grandfather");
	CHECK(T.relation("Yosef") == "great-grandfather");
	CHECK(T.relation("Bracha") == "great-grandmother");
	CHECK(T.find("father") == "Aharon");
	T.remove("Aharon");
	CHECK(T.find("father") == "unrelated");
	T.addFather("Ruth", "Aharon");
	CHECK(T.relation("Aharon") == "father");
}


TEST_CASE("Test"){
    Tree T ("Ella");

	T.addMother("Ella", "Harper") 
	 .addMother("Harper", "Avery") 
	 .addMother("Avery", "Madison")
	 .addMother("Madison", "Lily")
	 .addMother("Lily", "Lillian")
	 .addMother("Lillian", "Aubrey")
	 .addFather("Ella", "Carter")
	 .addFather("Carter", "Wyatt")
	 .addFather("Wyatt", "Jack")
	 .addFather("Jack", "Julian")
	 .addFather("Julian", "Jaxon")
	 .addFather("Jaxon", "Austin");
	CHECK(T.relation("Ella") == "me");
	CHECK(T.relation("Harper") == "mother");
	CHECK(T.relation("Avery") == "grandmother");
	CHECK(T.relation("Madison") == "great-grandmother");
	CHECK(T.relation("Lily") == "great-great-grandmother");
	CHECK(T.relation("Lillian") == "great-great-great-grandmother");
	CHECK(T.relation("Carter") == "father");
	CHECK(T.relation("Wyatt") == "grandfather");
	CHECK(T.relation("Jack") == "great-grandfather");
	CHECK(T.relation("Julian") == "great-great-grandfather");
	CHECK(T.relation("Jaxon") == "great-great-great-grandfather");
	CHECK(T.relation("Austin") == "great-great-great-great-grandfather");
	CHECK(T.relation("Terahby") == "unrelated");
	CHECK(T.relation("Yosef") == "unrelated");
	CHECK(T.find("me") == "Ella");
	CHECK(T.find("mother") == "Harper");
	CHECK(T.find("grandmother") == "Avery");
	CHECK(T.find("great-grandmother") == "Madison");
	CHECK(T.find("great-great-grandmother") == "Lily");
	CHECK(T.find("great-great-great-grandmother") == "Lillian");
	CHECK(T.find("father") == "Carter");
	CHECK(T.find("grandfather") == "Wyatt");
	CHECK(T.find("great-grandfather") == "Jack");
	CHECK(T.find("great-great-grandfather") == "Julian");
	CHECK(T.find("great-great-great-great-grandfather") == "Julian");
	CHECK(T.find("mother") == "Austin");
	CHECK(T.find("great-great-great-grandfather") == "Jaxon");
	CHECK(T.find("mother") == "Rachel");

}


