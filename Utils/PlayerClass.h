//
// Created by tanguy on 31/03/22.
//

#ifndef NETWORKING_PLAYERCLASS_H
#define NETWORKING_PLAYERCLASS_H

#include "glm/glm.hpp"
#include "../libs/json.hpp"
#include "Utils.h"

using nlohmann::json;

class PlayerClass {
public:
    PlayerClass(){};
    //PlayerClass(std::string n, vec3f v){name = n; position = v; };
    PlayerClass(std::string n, vec2f v){name = n; position = v; };
    friend void to_json(json& j, const std::vector<PlayerClass>& value);
    friend void from_json(const json& j, std::vector<PlayerClass>& value);


    struct sPlayerDescription{
        uint32_t nUniqueID = 0;
        uint32_t nHealth = 100;

        glm::vec3 vPos;
        glm::vec3 vVel;
    };
/*
private:
*/
    std::string name;
    std::map<std::string , std::string> test{};
    //vec3f position{};
    vec2f position{};
    vec3f lookVector{};
    vec3f velocity{};
};


#endif //NETWORKING_PLAYERCLASS_H
