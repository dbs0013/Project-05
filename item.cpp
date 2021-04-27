#include "item.hpp"

Item::Item(JsonItemBuilder &jsonBuiltItem, uint32_t uid)
{
    _builder = jsonBuiltItem.BuildItem(uid);

    _uid = uid;
    _name = _builder.name;
    _type = _builder.type;
    _damage = _builder.damage;
    _armor = _builder.armor;
    // Aspects
    // HP drains fast for a short period
    _serration = _builder.serration;
    // Deals much damage over time for susceptible targets
    _tindering = _builder.tindering;
    // Does damage over time 
    _poisoning = _builder.poisoning;
    // Steals health from target and heals for damage given
    _lifedrain = _builder.lifedrain;
    // Determining active status
    if (_serration != 0) {
        _activestatus = "Serration";
    }
    else if (_tindering != 0) {
        _activestatus = "Tindering";
    }
    else if (_poisoning != 0) {
        _activestatus = "Poisoning";
    }
    else if (_lifedrain != 0) {
        _activestatus = "Life Drain";
    }
    else {
        _activestatus = "None";
    }
}


uint32_t Item::UID() const
{
    return _uid;
}

uint32_t Item::Damage() const
{
    return _damage;
}

uint32_t Item::Armor() const
{
    return _armor;
}

std::string Item::Name() const
{
    return _name;
}

std::string Item::Type() const 
{
    return _type;
}
// Status effects
uint32_t Item::Serration() const 
{
    return _serration;
}

uint32_t Item::Tindering() const
{
    return _tindering;
}

uint32_t Item::Poisoning() const
{
    return _poisoning;
}

uint32_t Item::LifeDrain() const
{
    return _lifedrain;
}

std::string Item::ActiveStatus() const {
    return _activestatus;
}

std::ostream& operator<<(std::ostream& os, const Item& item)
{
    os << "[" << item._name << "]: \n"
              << "\tType : " << item._type
              << "\n\tArmor: " << item._armor
              << "\n\tDamage: " << item._damage
              // Print status effect
              << "\n\tStatus Effect: " << item._activestatus
              << std::endl;
              
    return os;
}