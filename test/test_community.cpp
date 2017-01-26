#include "gtest/gtest.h"
#include "person.h"
#include "community.h"

// this class is used for testing public methods in class Community
class test_community: public ::testing::Test {
protected:
	Community community;
};


void gen_random(char *s, const int len) {
	static const char alphanum[] =
	"0123456789"
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz";
}

// you should complete the following test cases
// you should add more if you see fit

// test get_name
TEST_F(test_community, get_name) {

}

// test set_name
TEST_F(test_community, set_name) {
	//Test character length
	EXPECT_FALSE(community.set_name("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	EXPECT_TRUE(community.set_name("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
	//Test alphanumeric
	EXPECT_FALSE(community.set_name("@"));
	EXPECT_FALSE(community.set_name("jakl23;"));
	EXPECT_TRUE(community.set_name("B"));
	EXPECT_TRUE(community.set_name("jfdsakl"));
	//Test empty string
	EXPECT_FALSE(community.set_name(""));
	EXPECT_FALSE(community.set_name("   "));
	EXPECT_TRUE(community.set_name("notemptyorspace"));
	//Test start with digit
	EXPECT_FALSE(community.set_name("1"));
	EXPECT_FALSE(community.set_name("12a"));
	EXPECT_TRUE(community.set_name("a12"));

	


}

// test add_person
TEST_F(test_community, add_person) {
	//Test that a username is not used yet
	community = community();
	person1 = person("leeholim", "leeho", "lim", "m", 22, "I like Rohin");
	person2 = person("rohinbhargava", "rohin", "bhargava", "m", 20, "I like Leeho (;");
	person3 = person("Leeholim", "leeho", "lim", "m", 22, "I still like Rohin");
	EXPECT_TRUE(community.add_person(person1));
	EXPECT_FALSE(community.add_person(person1));
	EXPECT_TRUE(community.add_person(person2));
	EXPECT_TRUE(community.add_person(person3));




}

// test get_all_usernames
//   there's no EXPERT functions for comparing non-built-in types, you need to
//   do some parsing by yourself
TEST_F(test_community, get_all_usernames) {
}

// test find_member by first name and age range
TEST_F(test_community, find_member) {
}

// test get_member
TEST_F(test_community, get_member) {
}

// test send_msg
TEST_F(test_community, send_msg) {
}

