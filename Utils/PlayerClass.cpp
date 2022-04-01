//
// Created by tanguy on 31/03/22.
//

#include "PlayerClass.h"

void to_json(json &j, const std::vector<PlayerClass> &value) {
    for(auto& c : value){
        j[c.name]["position"]["x"] = c.position.x;
        j[c.name]["position"]["y"] = c.position.y;
        //j[c.name]["position"]["z"] = c.position.z;
    }
}

void from_json(const json &j, std::vector<PlayerClass> &value) {
    for(auto &entry : j.items()){
        PlayerClass c{};
        c.name = entry.key();
        c.test = entry.value().get<std::map<std::string, std::string>>();
        value.push_back(c);
    }
}
