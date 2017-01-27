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

std::string gen_random_username11(const int len) {
		char s[len];
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

		s[0] = alphanum[(rand() % (sizeof(alphanum) - 11)) + 10];
    for (int i = 1; i < len - 2; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;

		return std::string(s);
}

std::string gen_random_name1(const int len) {
		char s[len];
    static const char alpha[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < len - 1; ++i) {
        s[i] = alpha[rand() % (sizeof(alpha) - 1)];
    }

    s[len] = 0;

		return std::string(s);
}

std::string gen_random_tagline1(const int len) {
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
//   there"s no EXPERT functions for comparing non-built-in types, you need to
//   do some parsing by yourself
TEST_F(test_community, get_all_usernames) {
	//No members in community
	EXPECT_EQ(community.get_all_usernames().size(), 0);

	//Creating different people for new community
	Person person1 = Person("leeholim", "leeho", "lim", "m", 22, "I like Rohin");
	Person person2 = Person("rohinbhargava", "rohin", "bhargava", "m", 20, "I like Leeho");
	Person person3 = Person("donnydailey", "donny", "dailey", "m", 127, "I still like Rohin");

	list<string> tester;

	//Creating new community with people
	community.set_name("NewCommunity");
	community.add_person(person1);
	tester.push_back(person1.get_username());
	community.add_person(person2);
	tester.push_back(person2.get_username());
	community.add_person(person3);
	tester.push_back(person3.get_username());

	list<string> temp = community.get_all_usernames();
	for (std::list<string>::iterator ig = temp.begin(); ig != temp.end(); ++ig)
		EXPECT_TRUE(*std::find(tester.begin(), tester.end(), *ig) == *ig);

	community = Community();

	//fuzz testing
	list<string> container;
	for (int i = 0; i < 50; ++i) {
		int r_age = rand() % 128;
		string m_f = "f";
		if (rand() % 101 > 50)
			m_f = "m";
		Person p_i = Person(gen_random_username11(64), gen_random_name1(64), gen_random_name1(64), m_f, r_age, gen_random_tagline1(512));
		bool x = community.add_person(p_i);

		//fuzz testing for add_person, as well... not unit testing for this method per se, but more tests don't hurt
		EXPECT_TRUE(x);
		if (x)
			container.push_back(p_i.get_username());
	}

	list<string> toTest = community.get_all_usernames();
	for (std::list<string>::iterator it = toTest.begin(); it != toTest.end(); ++it)
		EXPECT_TRUE(*std::find(container.begin(), container.end(), *it) == *it);
}

// test find_member by first name and age range
TEST_F(test_community, find_member) {
	//Creating different people for new community
	Person person1 = Person("leeholim", "leeho", "lim", "m", 22, "I like Rohin");
	Person person2 = Person("rohinbhargava", "rohin", "bhargava", "m", 20, "I like Leeho (;");
	Person person3 = Person("donnydailey", "donny", "dailey", "m", 127, "I still like Rohin");
	Person person4 = Person("LeehoLim", "leeho", "lim", "m", 22, "I also like Rohin");

	//Creating new community with people
	community.set_name("NewCommunity");
	community.add_person(person1);
	community.add_person(person2);
	community.add_person(person3);
	community.add_person(person4);

	//If the search result has a first name that is found in the list, then:
	list<Person> searchmembers = community.find_member("leeho"); //Finding members
	list<string> ideal;
	ideal.push_back(person1.get_info());
	ideal.push_back(person4.get_info());

	for (std::list<Person>::iterator it = searchmembers.begin(); it != searchmembers.end(); ++it)
		EXPECT_TRUE(*std::find(ideal.begin(), ideal.end(), it->get_info()) == it->get_info());


	//If the search result has a first name that is now found within the list:
	list<Person> nomembersearch = community.find_member("yobutt");
	EXPECT_EQ(nomembersearch.size(), 0); //There should be no members

	//If the search reuslts finds people within
	list<Person> agesearch = community.find_member(20, 22);
	list<string> ideal2;
	ideal2.push_back(person1.get_info());
	ideal2.push_back(person2.get_info());
	ideal2.push_back(person4.get_info());

	for (std::list<Person>::iterator it = agesearch.begin(); it != agesearch.end(); ++it)
		EXPECT_TRUE(*std::find(ideal2.begin(), ideal2.end(), it->get_info()) == it->get_info());

	//If the search result for age finds no users in the list:
	list<Person> agesearch2 = community.find_member(24, 126);

	EXPECT_EQ(agesearch2.size(), 0); //There should be no one that fits in this range
}

// test get_member
TEST_F(test_community, get_member) {
	//Creating different people for new community
	Person person1 = Person("leeholim", "leeho", "lim", "m", 22, "I like Rohin");
	Person person2 = Person("rohinbhargava", "rohin", "bhargava", "m", 20, "I like Leeho");
	Person person3 = Person("donnydailey", "donny", "dailey", "m", 127, "I still like Rohin");
	Person person4 = Person("LeehoLim", "leeho", "lim", "m", 22, "I also like Rohin");

	//Creating new community with people
	community.set_name("NewCommunity");
	community.add_person(person1);
	community.add_person(person2);
	community.add_person(person3);

	Person extractedmember1 = community.get_member("leeholim");
	//Case where it finds
	//Should pull all the same information for the user "leeholim"
	EXPECT_EQ(extractedmember1.get_info(), "Username: leeholim First Name: leeho Last Name: lim Gender: m Age: 22 Tagline: I like Rohin\n");

	//Case where it does not find
	Person extractedmember2 = community.get_member("nouserwho");
	EXPECT_EQ(extractedmember2.get_username(), "");

	//fuzz testing
	list<string> container;
	list<string> toTest;
	for (int i = 0; i < 50; ++i) {
		int r_age = rand() % 128;
		string m_f = "f";
		if (rand() % 101 > 50)
			m_f = "m";
		Person p_i = Person(gen_random_username11(64), gen_random_name1(64), gen_random_name1(64), m_f, r_age, gen_random_tagline1(512));
		bool x = community.add_person(p_i);

		//fuzz testing for add_person, as well... not unit testing for this method per se, but more tests don't hurt
		EXPECT_TRUE(x);
		if (x) {
			container.push_back(p_i.get_info());
			toTest.push_back(p_i.get_username());
		}
	}

	std::list<string>::iterator iv = container.begin();
	for (std::list<string>::iterator it = toTest.begin(); it != toTest.end(); ++it)
	{
		EXPECT_EQ(community.get_member(*it).get_info(), *iv);
		++iv;
	}
}

// test send_msg
TEST_F(test_community, send_msg) {
	for (int i = 0; i < 50; ++i) {
		int r_age = rand() % 128;
		string m_f = "f";
		if (rand() % 101 > 50)
			m_f = "m";
		community.add_person(Person(gen_random_username11(64), gen_random_name1(64), gen_random_name1(64), m_f, r_age, gen_random_tagline1(512)));
	}

	EXPECT_TRUE(community.send_msg(community.get_all_usernames(), "hello!"));

	list<string> faulty = community.get_all_usernames();
	faulty.push_back("leeholim");
	faulty.push_back("rohinbhargava");
	faulty.push_back("donnydailey");
	faulty.push_back("LeehoLim");

	EXPECT_FALSE(community.send_msg(faulty, "hello!"));

	// std::list<string> toTest = community.get_all_usernames();
	// for (std::list<string>::iterator it = toTest.begin(); it != toTest.end(); ++it)
	// 	EXPECT_TRUE(community.get_member(*it).read_msg());
}
