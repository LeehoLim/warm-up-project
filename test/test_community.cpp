#include "gtest/gtest.h"
#include "person.h"
#include "community.h"

// this class is used for testing public methods in class Community
class test_community: public ::testing::Test {
protected:
	Community community;
};

// you should complete the following test cases
// you should add more if you see fit

std::string gen_random_username(const int len) {
		char s[len];
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

		s[0] = alphanum[rand() % (sizeof(alphanum) - 11) + 10];
    for (int i = 0; i < len - 1; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;

		return std::string(s);
}

std::string gen_random_name(const int len) {
		char s[len];
    static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len - 1; ++i) {
        s[i] = alpha[rand() % (sizeof(alpha) - 1)];
    }

    s[len] = 0;

		return std::string(s);
}

std::string gen_random_tagline(const int len) {
	char s[len];
	static const char arr[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz;'./<>~!@#$%^&*() _+=\\|{}[]`\"";

	for (int i = 0; i < len - 1; ++i) {
			s[i] = arr[rand() % (sizeof(arr) - 1)];
	}

	s[len] = 0;

	return std::string(s);
}

// test get_name
TEST_F(test_community, get_name) {
	community = Community("HelloWorld", map<string,Person>());
	EXPECT_EQ(community.get_name(), "HelloWorld");
	community = Community();
	EXPECT_EQ(community.get_name(), "");
	community = Community("12323jdfalsf", map<string,Person>());
	EXPECT_EQ(community.get_name(), "");
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
	community = Community();
	Person person1 = Person("leeholim", "leeho", "lim", "m", 22, "I like Rohin");
	Person person2 = Person("rohinbhargava", "rohin", "bhargava", "m", 20, "I like Leeho (;");
	Person person3 = Person("Leeholim", "leeho", "lim", "m", 22, "I still like Rohin");
	EXPECT_TRUE(community.add_person(person1));
	EXPECT_FALSE(community.add_person(person1));
	EXPECT_TRUE(community.add_person(person2));
	EXPECT_TRUE(community.add_person(person3));
	EXPECT_FALSE(community.add_person(Person()));
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
