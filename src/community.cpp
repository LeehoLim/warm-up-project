#include "community.h"

Community::Community()
  : name(""), people(map<string,Person>()) {
}

Community::Community(string _name, map<string,Person> _people)
  : people(_people) {
    if (!set_name(_name)) {
        std::cout << "Something went wrong constructing this community. Default values will be used.\n";
        _name = "";
    }
    people = _people;
}

//Will get the name from the current name in the community class. 
//Default is set to empty string
string Community::get_name() {
	return name;
}

//Community name will set name given it meets conditions
//Conditions: Name cannot be empty string, but no more than 128 characters
//name cannot be digit for first digits (only alphabetical), but otherwise  alphanumeric
//If this is false, return false
bool Community::set_name(string _name) {
	if(str_isalnum(_name) && 0 < _name.size() && _name.size() <= 128 && !std::isdigit(_name[0])) {
    name = _name;
    return true;
  }
  return false;
}

//Will add a person assuming that the number of usernames is greater than 0 and
//The username of the person is not empty string (cannot be empty string)
bool Community::add_person(Person _person) {
    if (people.count(_person.get_username()) > 0 || !_person.get_username().compare(""))
      return false;
    else {
      people.insert(std::pair<string,Person>(_person.get_username(), _person));
      return true;
    }
}

// Given a username, get_member will look for a person with that username
// and return the person object for a given username 
Person Community::get_member(string username) {
    if (people.find(username) != people.end()) {
        return people[username];
    }
    else {
        return Person();
    }
}

//Will return a list of all usernames when invoked
//Simply traverses through the mapping of people and pushes usernames onto string list
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

//Prints all the usernames to console. Iterates through the map
void Community::print_all_usernames() {
    std::map<string,Person>::iterator it = people.begin();
    while (it != people.end()) {
      cout << it->first;
      ++it;
    }
	// print all usernames of members to the console
}

//Given a firstname, will return a list of people that have the same first name
//Will iterate through the map and push onto a list of people 
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


//Given a lower and upper integer bound (inclusive), will return a list of people that
//fall within this range. Same method of iterating through the mapping and 
//pushing people that are within the age range
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

//Given a list of usernames and a string message, this function will send the message to all 
//users listed. If the message sends to the users, will output true, else false.
//Traverses through the given list and invokes the get_msg function in the
// "Person" class to relay the message to the user
bool Community::send_msg(list<string> usernames, string msg) {
  bool good = true;
  std::list<string>::iterator it = usernames.begin();
  while(it != usernames.end()) {
    if(get_member(*it).get_username() == "") {
      good = false;
      continue;
    }
    else {
      get_member(*it).get_msg(msg);
    }
    ++it;
  }
	// send msg to a Person addressed by username
	// make sure the username is validated
	return good;
}
