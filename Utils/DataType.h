#ifndef NETWORKING_DATATYPE_H
#define NETWORKING_DATATYPE_H

#endif //NETWORKING_DATATYPE_H

#include <iostream>
#include "PlayerClass.h"
#include "../libs/json.hpp"

using nlohmann::json;

enum Type{
    MESSAGE,
    PLAYERCLASS
};

class DataType{
public:
    DataType(){};
    static void PlayerClassToJSON(const std::vector<PlayerClass > *in, json &j){
        //json j;
        for(auto i = in->begin(); i != in->end(); i++){
            j["Players"][std::distance(in->begin(), i)]["name"] = i->name;
            j["Players"][std::distance(in->begin(), i)]["x"] = i->position.x;
            j["Players"][std::distance(in->begin(), i)]["y"] = i->position.y;
/*
            j["Players"][std::distance(in->begin(), i)]["z"] = i->position.z;
*/

        }
        //std::cout << to_string(j).c_str() << std::endl;
        //return j;
    }

    static nlohmann::json PlayerClassToJSON(const std::vector<PlayerClass >* in){
        json j;
        for(auto i = in->begin(); i != in->end(); i++){
            j["Players"][std::distance(in->begin(), i)]["name"] = i->name;
            j["Players"][std::distance(in->begin(), i)]["x"] = i->position.x;
            j["Players"][std::distance(in->begin(), i)]["y"] = i->position.y;
/*
            j["Players"][std::distance(in->begin(), i)]["z"] = i->position.z;
*/

        }
        return j;
    }

    static nlohmann::json PlayerClassToJSON(const std::vector<PlayerClass > in){
        json j;
        for(auto i = in.begin(); i != in.end(); i++){
            j["Players"][std::distance(in.begin(), i)]["name"] = i->name;
            j["Players"][std::distance(in.begin(), i)]["x"] = i->position.x;
            j["Players"][std::distance(in.begin(), i)]["y"] = i->position.y;
            //j["Players"][std::distance(in.begin(), i)]["z"] = i->position.z;

        }
        return j;
    }

    static void JSONToPlayerClass(std::vector<PlayerClass >* in, const json &j){

        for(auto it = j["Players"].begin(); it != j["Players"].end(); it++){
            if (it->contains("name")) {
                //std::cout << (*it)["name"] << std::endl;
            }

            //vec3f test{(*it)["x"], (*it)["y"], (*it)["z"]};
            vec2f test{(*it)["x"], (*it)["y"]};
            in->emplace_back(PlayerClass{(*it)["name"], test});

/*            if (it->contains("Player")) {
                auto const player = (*it).get<std::string>();
*//*                auto const x = player["x"];
                auto const y = player["y"];
                auto const z = player["z"];*//*

                //in->push_back(PlayerClass{player["name"], vec3f{x, y, z}});
                std::cout << player *//*<< " | " << x << y << z*//* << std::endl;
*//*                for(auto jt = name.begin(); jt != name.end(); jt++){

                    if(jt->contains("name"))
                        std::cout << (*jt) << std::endl;
                }*//*
            }*/
        }
/*        for(auto it = j.begin(); it != j.end(); it++){
            if(it->contains("Player")){
                std::string const name = (*it)["name"].get<std::string>();
                std::cout << name << std::endl;
            }
        }*/
/*        in->push_back(PlayerClass{to_string(j["Players"]).c_str(), vec3f{}});
        std::cout << in->size() << std::endl;*/
    }
};