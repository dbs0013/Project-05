#ifndef JSONITEMBUILDER_HPP
#define JSONITEMBUILDER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "json.hpp"


struct ItemBuilder
{
    bool valid = false;

    uint32_t uid = 0;
    
    std::string name = "";
    std::string type = "";

    uint32_t damage = 0;
    uint32_t armor = 0;
    // Aspects
    uint32_t serration = 0;
    uint32_t tindering = 0;
    uint32_t poisoning = 0;
    uint32_t lifedrain = 0;
};



class JsonItemBuilder
{
public:
    JsonItemBuilder(const std::string & fileName);

    ItemBuilder BuildItem(uint32_t uid);


private:

    nlohmann::json::value_type* GetItemFromID(const std::string & item, uint32_t id);

    const std::string STR_ITEM_ID = "items";

    const std::string STR_UID = "UID";
    const std::string STR_NAME = "name";
    const std::string STR_TYPE = "type";
    const std::string STR_DAMAGE = "damage";
    const std::string STR_ARMOR = "armor value";
    // Aspects
    const std::string STR_SERRATION = "serration";
    const std::string STR_TINDERING = "tindering";
    const std::string STR_POISONING = "poisoning";
    const std::string STR_LIFEDRAIN = "life drain";

    using json = nlohmann::json;
    std::string _file;
    json j;
    json _items;

};


#endif