#include <string>
#include "member.h"

Member::Member(std::string member_first_name, std::string member_last_name, int member_id) : name{member_first_name, member_last_name}, id{member_id} {
    // TODO(student)


    //First name and last name check

    if (member_first_name.empty() && member_last_name.empty()) {
            throw std::invalid_argument("Invalid name");
        }

        for (char c : member_first_name) {
                if (!(std::isalpha(c))) {
                    throw std::invalid_argument("Invalid name");
                }
            }
    
            for (char c : member_last_name) {
                if (!(std::isalpha(c))) {
                    throw std::invalid_argument("Invalid name");
                }
            }

    // ID check
        if (member_id < 1000) {
            throw std::invalid_argument("Invalid id");
        }
}

Member::Member(MemberName member_name, int member_id) : name{member_name}, id{member_id} {
    // TODO(student)

    //First name and last name check

    if (name.first_name.empty() && name.last_name.empty()) {
            throw std::invalid_argument("Invalid name");
        }

        for (char c : name.first_name) {
                if (!(std::isalpha(c))) {
                    throw std::invalid_argument("Invalid name");
                }
            }
    
            for (char c : name.last_name) {
                if (!(std::isalpha(c))) {
                    throw std::invalid_argument("Invalid name");
                }
            }

    // ID check
        if (member_id < 1000) {
            throw std::invalid_argument("Invalid id");
        }

}

const MemberName& Member::get_name() const {
    // TODO(student)
    return name;
}

int Member::get_id() const {
    // TODO(student)
    return id;
}

std::ostream& operator<<(std::ostream& os, const Member& member) {
    // TODO(student)
    os << "Member: " << member.get_name().first_name << " " << member.get_name().last_name
       << ", id: " << member.get_id();
    return os;
}
