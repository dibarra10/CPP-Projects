#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include "Cities.h"
#include "LinkedList.h"

// TODO(student): implement the dispatch scheduler

void ltrim(std::string &s) {
    // Find first character that is NOT a space, tab, or newline
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start != std::string::npos) {
        s.erase(0, start);
    } else {
        s.clear(); // String is all whitespace
    }
}

bool city_check(std::string cityName){
    if (cityName == "HQ" || cityName == "Boston" || cityName == "Hartford" || cityName == "New York" || cityName == "Philadelphia" || cityName == "Baltimore" || cityName == "Washington, DC" || cityName == "Pittsburgh" || cityName == "Cleveland" || cityName == "Detroit" || cityName == "Chicago" || cityName == "Indianapolis" || cityName == "Nashville" || cityName == "Atlanta" || cityName == "Houston" || cityName == "Austin" || cityName == "Dallas" || cityName == "Denver" || cityName == "Albuquerque" || cityName == "Phoenix" || cityName == "Sacramento"){
        return true;
    }
    return false;
}

void push(LinkedList& schedule, City city) {
    
    // Add city to front of schedule 

    if (!schedule.empty() && schedule.front() == city){
        return;
    }

    schedule.add(city, 0);

}

void pop(LinkedList& schedule) {

    if (schedule.empty()){
        std::cout << "Cannot pop from an empty schedule." << std::endl;
        return;
    }
    schedule.remove(0);
}

void add(LinkedList& schedule, City city) {

    //check if city exists

    if (!city_check(CityToString(city))){ 
        std::cout << "Unknown city" << std::endl;
        return;
    }

    
    unsigned index = 0;
    while (index < schedule.size() && schedule.at(index) <= city){
        index++;
    }

    if (index > 0 && schedule.at(index-1) == city){
        return;
    }
    schedule.add(city, index);


}

void remove(LinkedList& schedule, std::string cityName) {

    //check if city exists
    if (!city_check(cityName)){

        std::cout << "Unknown city." << std::endl;
        return;
    }

    City x = StringToCity(cityName);

    //iterate through schedule and remove first occurrences of x
    for (unsigned i = 0; i < schedule.size(); i++){
        if (schedule.at(i) == x){
            schedule.remove(i);
            return;
        }
    }

    std::cout << cityName << " is not on the schedule." << std::endl;

}

void print(LinkedList& schedule) {

    //Calculate route length based on enum values and print the route using CityToString.

    enum City prev = HQ;
    int route_length = 0;


    if (schedule.empty()){
        std::cout << "The schedule is empty." << std::endl;
        return;
    }

    //Iterate through the schedule and print the name of each city using CityToString, separated by ->
    for (unsigned i = 0; i < schedule.size(); i++){
        std::cout << CityToString(static_cast<City>(schedule.at(i))) << " -> ";

        route_length += abs(prev - schedule.at(i));
        prev = static_cast<City>(schedule.at(i));
        
    }

    route_length += abs(prev - HQ);
    std::cout << '.' << " (" << route_length << ")" << std::endl;

}




int main() {

    LinkedList schedule;

    std::string line = "";
    std::stringstream ss;

    while (line != "quit") {
        
        std::getline(std::cin, line);
        ss.clear();
        ss.str(line);

        std::string command;
        ss >> command;

        if (command == "push") {
            std::string cityName;
            std::getline(ss, cityName);
            ltrim(cityName);
            if (!city_check(cityName)){
                std::cout << "Unknown city." << std::endl;
                continue;
            }
            //Use StringToCity from cities.h to convert cityName to a City enum value, then push it onto the schedule
            push(schedule, StringToCity(cityName));

            // TODO(student): convert cityName to City and push
        } else if (command == "pop") {
            pop(schedule);
        } else if (command == "add") {
            std::string cityName;
            std::getline(ss, cityName);
            ltrim(cityName);
            if (!city_check(cityName)){
                std::cout << "Unknown city." << std::endl;
                continue;
            }
            City city(StringToCity(cityName));
            add(schedule, city);
        } else if (command == "remove") {
            std::string cityName;
            std::getline(ss, cityName);
            ltrim(cityName);
            
            remove(schedule, cityName);
        } else if (command == "print") {
            print(schedule);
        } else if (command == "clear") {
            schedule.clear();

        } else if (command != "quit") {
            std::cout << "Unknown command." << std::endl;
        }
    }
    
}

