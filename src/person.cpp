#include "person.h"

bool str_isalpha(const string str){
    for(unsigned long i = 0; i < str.size(); i++)
    	if((isalpha(str[i]) == 0) || (str[i] == ' '))
    		return false;
    return true;
}

bool str_isalnum(const string s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isalnum(*it)) ++it;
    return !s.empty() && it == s.end();
}

Person::Person()
  : username(""), firstname(""), lastname(""), gender(""), age(0), tagline("") {
}

Person::Person(string _username, string _firstname, string _lastname,
               string _gender, int _age, string _tagline) {
      if (!set_info(_username, _firstname, _lastname, _gender, _age, _tagline))
          std::cout << "Something went wrong in creating this person. Using default values.\n";
}


//Simply returns the current username of the person as a string
string Person::get_username() {
    return username;
}

//Simply returns the current firstname of the person as a string
string Person::get_firstname() {
    return firstname;
}

//Returns the current last name of the person as a string
string Person::get_lastname() {
    return lastname;
}

//Returns the current gender of the person as a string "m" or "f"
string Person::get_gender(){
    return gender;
}

//Returns the current age listed of the person
int Person::get_age() {
    return age;
}

//Returns the current tagline of the person as a string
string Person::get_tagline() {
    return tagline;
}

//If the parameters are not empty, then append the information to the string
//Does so in sequential order (username, fn, ln, gender, age, tagline)
string Person::get_info() {
	  string ret = "";
    if (get_username() != "") {
      ret += "Username: ";
      ret += get_username();
      ret += " ";
    }
    if (get_firstname() != "") {
      ret += "First Name: ";
      ret += get_firstname();
      ret += " ";
    }
    if (get_lastname() != "") {
      ret += "Last Name: ";
      ret += get_lastname();
      ret += " ";
    }
    if (get_gender() != "") {
      ret += "Gender: ";
      ret += get_gender();
      ret += " ";
    }
    if (!!get_age() || (!get_age() && !ret.compare(""))) {
      ret += "Age: ";
      ret += std::to_string(get_age());
      ret += " ";
    }
    if (get_tagline() != "") {
      ret += "Tagline: ";
      ret += get_tagline();
      ret += "\n";
    }
    
    return ret;
}

//Sets the username given that the input matches the conditions of the username:
//That the first character is not a digit, the # of chars is no more than 64,
//and the username is alphanumeric, but not the empty string
//Returns true if this is sucessful and false if otherwise
bool Person::set_username(string _username) {
  if (str_isalnum(_username) && !std::isdigit(_username[0]) && _username.size() <= 64 && _username.compare("")) {
    username = _username;
  	return true;
  }
  else {
    return false;
  }
}

//Sets the first name, given the input for first name is
// alphabetical and no more than 64 characters
//Returns true if successful and false if otherwise
bool Person::set_firstname(string _firstname) {
  if (str_isalpha(_firstname) && _firstname.size() <= 64) {
      firstname = _firstname;
      return true;
    }
  else {
      return false;
    }
}

//Sets the last name given the input for the last name is
//alphabetical and no more than 64 characters
//Returns true if successful and false if otherwise
bool Person::set_lastname(string _lastname) {
    // TODO
	if (str_isalpha(_lastname) && _lastname.size() <= 64) {
        lastname = _lastname;
        return true;
    }
    else {
        return false;
    }
}

//Sets the gender to the input if it is either 'm' or 'f'
//Cannot be "male", "female", and does not accept
//non-binary genders
//Returns true if successful, and false otherwise
bool Person::set_gender(string _gender){
    if ((_gender[0] == 'm' || _gender[0] == 'f') && _gender.size() == 1) {
      gender = _gender;
      return true;
    }
    else {
      return false;
    }
}

//Sets the age to the input age (integer)
//The age must be in between 0 and 127 (cannot be 128)
//Returns true if this value is successfully changed,
//returns false if otherwise
bool Person::set_age(int _age) {
    if (_age >= 0 && _age < 128) {
        age = _age;
        return true;
    }
    else {
        return false;
    }
}

//Sets the tagline given it is at most 512 characters
//This can be any character (alphanumerical, symbols, etc)
//Returns true if successful, and returns false if otherwise
bool Person::set_tagline(string _tagline) {
    if (_tagline.size() <= 512) {
        tagline = _tagline;
        return true;
    }
    else {
        return false;
    }
}

//Sets the information of a person depending on the different inputs given for
//username, firstname, lastname, gender, age, and tagline
//Must adhere to ALL limitations placed on EVERY criteria of person
//If this is not the case, then a blank person will be set, and "false" will be returned
//Otherwise, if everything is properly met, then the person will be set to the input values and
//the value will return "true"
bool Person::set_info(string _username, string _firstname, string _lastname, string _gender,
                      int _age, string _tagline) {
  if (set_username(_username) && set_firstname(_firstname) && set_lastname(_lastname) && set_gender(_gender) && set_age(_age) && set_tagline(_tagline))
    return true;

  else
  {
    username = "";
    firstname = "";
    lastname = "";
    gender = "";
    age = 0;
    tagline = "";
    return false;
  }
}

//Given a person and a string message, the recipient will simply receive a message
void Person::send_msg(Person &recipient, string msg) {
    recipient.get_msg(msg);
    }

//Given a messag string, the current person will receive a message into his inbox
void Person::get_msg(string msg) {
	  inbox.push(msg);
    }

//In order for a person to read a message, he must have a message
//Therefore the inbox size cannot be 0.
//If there are messages to be read, read each message by showing the message onto the console
//And pop message off because it has been read
bool Person::read_msg() {
    if (inbox.size() == 0) {
      std::cout << "No messages to read.\n";
      return false;
    }
    else {
      std::cout << inbox.front();
      inbox.pop();
      return true;
    }
}
