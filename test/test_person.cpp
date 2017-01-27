#include "gtest/gtest.h"
#include "person.h"

// this class is used for testing public methods in class Person
class test_person: public ::testing::Test {
protected:
	Person person;
	Person recipient;
};

// test get_username and set_username
TEST_F(test_person, test_username) {
	//Constructor testing
	Person person1 = Person("leeholim", "leeho", "lim", "m", 22, "I like Rohin");
	Person person2 = Person("rohinbhargava", "rohin", "bhargava", "m", 20, "I like Leeho");
	Person person3 = Person("LeehoLim", "leeho", "lim", "m", 22, "I still like Rohin");
	Person person4 = Person();

	//Get username of a person that already has username
	EXPECT_EQ(person1.get_username(), "leeholim");
	EXPECT_NE(person1.get_username(), person3.get_username());

	//Get username of a person that does not have username
	EXPECT_NE(person4.get_username(), "leeholim");
	EXPECT_EQ(person4.get_username(), "");

	//Username max 64 characters
	EXPECT_FALSE(person.set_username("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_TRUE(person.set_username("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_TRUE(person.set_username("LeehoAndRohin"));

	//Must be alphanumeric
	EXPECT_FALSE(person.set_username("@"));
	EXPECT_FALSE(person.set_username("Leeho+Rohin"));
	EXPECT_FALSE(person.set_username("Leeho and Rohin"));
	EXPECT_TRUE(person.set_username("Leeho12Rohin"));

	//Cannot start with a digit
	EXPECT_FALSE(person.set_username("12a"));
	EXPECT_FALSE(person.set_username("1"));
	EXPECT_TRUE(person.set_username("A12"));

	//Cannot be the empty string
	EXPECT_FALSE(person.set_username(""));
	EXPECT_FALSE(person.set_username(" "));
	EXPECT_TRUE(person.set_username("notempty"));
}

// test get_firstname and set_firstname
TEST_F(test_person, test_firstname) {
	//SET FIRSTNAME

  //Must constain only alphabetic
	EXPECT_FALSE(person.set_firstname("abcdefg0")); //Contains number
	EXPECT_FALSE(person.set_firstname("abcdefg;")); //Contains semicolon

	//CAN BE EMPTY
	EXPECT_TRUE(person.set_firstname("")); //Empty string
	EXPECT_FALSE(person.set_firstname(" ")); //Space string

	//Must have maximum of 64 characters
	EXPECT_FALSE(person.set_firstname("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklm")); //65
  EXPECT_TRUE(person.set_firstname("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl")); //64

	//GET FIRSTNAME

	//Check to see for a firstname that exists/is filled
	EXPECT_STREQ(person.get_firstname().c_str(), "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl"); //exists
	EXPECT_STRNE(person.get_firstname().c_str(), ""); //exists, so it is not empty

	//Check to see for a person that does not have a firstname
	Person EmptyPerson = Person();
	EXPECT_STREQ(EmptyPerson.get_firstname().c_str(), "");
	EXPECT_STRNE(EmptyPerson.get_firstname().c_str(), "something");

}

// test get_lastname and set_lastname
TEST_F(test_person, test_lastname) {

  //Must contain only alphanumeric
	EXPECT_FALSE(person.set_lastname("abcdefg0")); //Contains number
	EXPECT_FALSE(person.set_lastname("abcdefg;")); //Contains semicolon

	//CAN BE EMPTY
	EXPECT_TRUE(person.set_lastname("")); //Empty string
	EXPECT_FALSE(person.set_lastname(" ")); //Space string

	//Must have maximum of 64 characters
  EXPECT_FALSE(person.set_lastname("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklm")); //65
  EXPECT_TRUE(person.set_lastname("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl")); //64

	//Check to see for a person that has a last name
	EXPECT_STREQ(person.get_lastname().c_str(), "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijkl"); //exists, so empty
	EXPECT_STRNE(person.get_lastname().c_str(), ""); //exists, so it is not empty

	//Check to see for a person that does not have a lastname
	Person EmptyPerson = Person();
	EXPECT_STREQ(EmptyPerson.get_lastname().c_str(), ""); //Does not have a last name, so should be empty
	EXPECT_STRNE(EmptyPerson.get_lastname().c_str(), "something"); //Does not have a last name, so should not be something

}

/**you may need to write more test functions.
 *  What we provide here is just for your reference
 */

// test get_age and set_age
//   test_person is the name of class your inherit from the base Test class
//   test_age is the name of this test case, which will show up in the test
//     results
//   make sure you cover every subroutine and branches
//   here we test edge cases of invalid ages
//   also, we test the get_age() method
//   avoid using ASSERT_FALSE here; if there is something wrong in ASSERT,
//   it will abort the whole testing which will hinder the grading process
TEST_F(test_person, test_age) {
	//Person cannot be negative age
	EXPECT_FALSE(person.set_age(-1));

	//Person can be a positive age
	EXPECT_TRUE(person.set_age(0)); //Set to 0
	EXPECT_EQ(person.get_age(), 0); //The person is 0
	EXPECT_NE(person.get_age(), 1); //The person is not 1

	//Person can be up to 127 years old (128 exclusive)
	EXPECT_TRUE(person.set_age(127)); //Set to 127, legal
	EXPECT_EQ(person.get_age(), 127); //The person is 127
	EXPECT_NE(person.get_age(), 128); //The person is not 128
	EXPECT_NE(person.get_age(), 10); //The person is not 10

	//Person cannot be 128 years old
	EXPECT_FALSE(person.set_age(128)); //The person cannot be 128
	EXPECT_NE(person.get_age(), 128); //The person is not 128 years old, because this was not set
}

// test get_tagline and set_tagline
TEST_F(test_person, test_tagline) {
	//Tagline is limited to 512 characters
	EXPECT_TRUE(person.set_tagline("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa2aaaa;aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa")); //512 characters //allowed with non alphanumerical characters
	EXPECT_EQ(person.get_tagline(), "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa2aaaa;aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"); //should equal each other
	EXPECT_NE(person.get_tagline(), "aa"); //should not equal that

	EXPECT_FALSE(person.set_tagline("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab")); //513 characters not allowed
	EXPECT_NE(person.get_tagline(), "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"); //Should therefore not equal the attempted set_tagline string

	//Empty is legal, because only limitation is 512 characters
	EXPECT_TRUE(person.set_tagline("")); //Set to empty is legal
	EXPECT_EQ(person.get_tagline(), ""); //Should equal empty string
	EXPECT_NE(person.get_tagline(), " "); //Should not equal space or anything, because it was declared empty
}

//test get_gender and set_gender
TEST_F(test_person, test_gender) {
	//False if gender is not m or f
	EXPECT_FALSE(person.set_gender("male")); //male should be m
	EXPECT_FALSE(person.set_gender("female")); //female should be f
	EXPECT_FALSE(person.set_gender("M")); //M should be m
	EXPECT_FALSE(person.set_gender("F")); //F should be f
	EXPECT_FALSE(person.set_gender("lizard")); //Not accounting for non-binary
	EXPECT_TRUE(person.set_gender("m")); //m for male
	EXPECT_TRUE(person.set_gender("f")); //f for female
}


// test get_info and set_info
TEST_F(test_person, test_info) {
	Person Rightperson1 = Person("a", "", "", "m", 0, "wubba wub");
	Person Rightperson2 = Person("a1steaksauc3", "", "", "f", 127, "h00ba hub3-a");

	//Wrong username
	EXPECT_FALSE(person.set_info("1hubba", "leeho", "lim", "m", 22, "hubba hubba"));

	//Wrong firstname
	EXPECT_FALSE(person.set_info("Valid", "leeh0", "lim", "m", 22, "hubba hubba"));

	//Wrong lastname
	EXPECT_FALSE(person.set_info("KylieJenner", "NotKylie", "J3nner", "f", 20, "hubba not so hubba"));

	//Wrong gender
	EXPECT_FALSE(person.set_info("WhatWhatInThe", "What", "What", "lizard", 20, "hubba not so hubba"));

	//Wrong age
	EXPECT_FALSE(person.set_info("Hello", "It", "IsI", "m", 128, "I am old"));

	//Correct with blank names, max age
	EXPECT_TRUE(person.set_info("a", "", "", "m", 0, "wubba wub"));

	//Correct with blank names, max age, non-alphanumeric characters in tagline
	EXPECT_TRUE(person.set_info("a1steaksauc3", "", "", "f", 127, "h00ba hub3-a"));

}

// test send_msg and read_msg
//   to make your code shorter, we suggest combining these tests together; you
//   can also separate them into several test cases
TEST_F(test_person, test_msg) {
	person.get_msg("Hey there :)\n");
	person.read_msg();
	person.read_msg();
	person.read_msg();
}
