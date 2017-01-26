#include "community.h"

Community::Community()
  : name(""), people(map<string,Person>()) {
}

Community::Community(string _name, map<string,Person> _people) 
  : name(_name), people(_people) {
}

string Community::get_name() {
	return name;
}

bool Community::set_name(string _name) {
	if((str_isalnum(_name) == 1) && (0 < _name.size()) && (_name.size() <= 128) && (std::isdigit(_name[0]) == 0)) {
    return true;
  }
  return false;
}

bool Community::add_person(Person _person) {
    contact to_add(_person.get_username(), _person);
    
    return false;
}

// return the person object for a given username
Person Community::get_member(string username) {
    if (people.find(username) != people.end()) {
        return people[username];
    }
    else {
        return Person();
    }
}
    
list<string> Community::get_all_usernames() {
    list<string> usernames;
    std::map<string,Person>::iterator it = people.begin();
    while (it != people.end()) {
      usernames.push_back(it->first);
      ++it;
    }

    // return all usernames of members as a list
    return usernames;
}

void Community::print_all_usernames() {
    std::map<string,Person>::iterator it = people.begin();
    while (it != people.end()) {
      cout << it->first;
      ++it;
    }
	// print all usernames of members to the console
}

list<Person> Community::find_member(string firstname) {
    list<Person> ret;
    std::map<string,Person>::iterator it = people.begin();
    while (it != people.end()) {
      if(firstname.compare(it->second.get_firstname()) == 0) {
        ret.push_back(it->second);
        ++it;
    }
    // find users with a certain first name
  }
  return ret;
}

list<Person> Community::find_member(int age_lb, int age_ub) {
  list<Person> ret;
  std::map<string,Person>::iterator it = people.begin();
  while (it != people.end()) {
    int age = it->second.get_age();
      if(age_lb <= age <= age_ub){
        ret.push_back(it->second);
      }
    }
  // find users within certain ages [age_lb, age_ub], both lower bound and upper bound shall be inclusive
  return ret;
}

bool Community::send_msg(list<string> usernames, string msg) {
  std::list<string>::iterator it = usernames.begin();
  while(it != usernames.end()) {
    if(get_member(*it).get_info() == "") {
      continue;
    }
    else {
      get_member(*it).get_msg(msg);
    }
    ++it;
  }
	// send msg to a Person addressed by username
	// make sure the username is validated
	return false;
}

