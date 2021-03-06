#include "entity.hpp"


Entity::Entity(JsonEntityBuilder & builder, JsonItemBuilder & inventory, uint32_t uid) 
{
    _builder = builder.BuildEntity(uid);

    _uid = uid;
    _name = _builder.name;
    _hp = _builder.hp;
    _race = _builder.race;
    _maxHP = _hp;
    _strength = _builder.strength;
    _intelligence = _builder.intelligence;
    _agility = _builder.agility;
    _wisdom = _builder.wisdom;
    _class = _builder.Class;

    _inventory.Init(inventory, _builder.inventoryIDs);
    // Equipped item imparts the status damage of the weapon
    _currentEquipped = this->_inventory.GetFirstItem();
    // Assess status effect
    _serration = _currentEquipped.Serration();
    _tindering = _currentEquipped.Tindering();
    _poisoning = _currentEquipped.Poisoning();
    _lifedrain = _currentEquipped.LifeDrain();
}

Entity::~Entity()
{

}

// implement
// prints the inventory of this entity
void Entity::PrintInventory() const
{
    _inventory.PrintInventory();
}

// implement
// removes an item from the inventory of this entity
// based on the UID passed to this funciton.
Item Entity::LoseAnItem(uint32_t uid)
{
    return _inventory.LootAnItem(uid);
}

// implement
// 
bool Entity::HasItemsInInventory() const
{
    return !_inventory.IsEmpty();
}

// implement
// this will loop through the targets inventory
// and add one item at a time to this Entity's inventory
//
// entity is assumed to never be null, 
// you do not have to check for this.
void Entity::LootAnEntity(Entity *target)
{
    _inventory.LootAnotherInventory(target->_inventory);
}

// implement
// if item passed is null, do nothing.
void Entity::add_item_to_inventory(const Item & item)
{
    announce_item_loot(item);
    _inventory.AddItemToInventory(item);
}

uint32_t Entity::CurrentHP() const
{
    return _hp;
}
// Prints current status level
void Entity::CurrentStatuses() const 
{
    std::cout << "Serration: " << _serration
              << "Tindering: " << _tindering
              << "Poisoning: " << _poisoning; 
}

bool Entity::IsAlive() const
{
    return _hp != 0;
}

std::string Entity::Name() const
{
    return _name;
}

std::string Entity::Class() const
{
    return _class;
}

void Entity::Attack(Entity *target, uint32_t amount, const std::string &attackName)
{
    // Recalculate statuses before every attack
    target->StatusCalc();
    std::cout << this->Name() << " uses " << attackName << " on target "
              << target->Name() << " dealing " << amount << " damage."
              << std::endl;
    // Life steal kicks in 
    if (this->_lifedrain > 0) {
        std::cout << this->Name() << ": "
                  << _lifedrain << " HP stolen from " 
                  << target->Name() << std::endl;
        // Lifesteal plus damage given to target
        target->take_damage(amount + _lifedrain);
        // Healing
        this->take_healing(_lifedrain);
    }
    // If no life steal, target takes flat weapon damage
    else {
        target->take_damage(amount);
    }
}

void Entity::Heal(Entity *target, uint32_t amount, const std::string & healName)
{
    std::cout << this->Name() << " uses " << healName << " on target "
              << target->Name() << " healing for " << amount
              << std::endl;
    // Reset status effects on heal
    target->_serration = 0;
    target->_tindering = 0;
    target->_poisoning = 0;
    // Heal
    target->take_healing(amount);
}

void Entity::StatusCalc() {
    // Serration level decreases per turn
    if (_serration != 0) {
        _serration--;
    }
    // Tindering level decreases per turn
    if (_tindering != 0) {
        _tindering--;
    }
    // Poisoning level increases per turn
    if (_poisoning < 1) {
        _poisoning += 0.1;
    }
}

void Entity::take_damage(uint32_t amount)
{
    uint32_t tempDamage = 0;
    if(_hp < amount)
    {
        _hp = 0;
        std::cout << Name() << " dies" << std::endl;
        return;
    }
    // Status calculations
    if (_serration != 0) {
        tempDamage = amount + _serration;
        std::cout << Name() << " took " << tempDamage
                  << " from serration! " << std::endl;
        _hp -= tempDamage;
    }
    else if (_tindering != 0) {
        tempDamage = amount + _tindering;
        std::cout << Name() << " took " << tempDamage
                  << " from tindering! " << std::endl;
        _hp -= tempDamage;
    }
    else if (_poisoning != 0) {
        tempDamage = amount + (amount * _poisoning);
        std::cout << Name() << " took " << tempDamage
                  << " from poison! " << std::endl;
        _hp -= tempDamage;
    }
    else {
        _hp -= amount;
    }
}

void Entity::take_healing(uint32_t amount)
{
    if(_maxHP < _hp + amount)
    {
        _hp = _maxHP;
        return;
    }
    _hp += amount;
}

void Entity::announce_item_loot(const Item & item)
{
    std::cout << Name() << " has looted an item: " << item.Name() << std::endl;
}

void Entity::errorFindingAbility(const std::string& spellName)
{
    std::cout << _class << " encountered an error trying to use spell: " 
              << spellName << std::endl;
}
// Equipped item from inventory
Item Entity::CurrentEquipped() const 
{
    return _currentEquipped;
}

std::string Entity::Race() const
{
    return _race;
}

uint32_t Entity::GetStrength() const 
{
    return _strength;
}

uint32_t Entity::GetIntelligence() const
{
    return _intelligence;
}

uint32_t Entity::GetAgility() const
{
    return _agility;
}

uint32_t Entity::GetWisdom() const
{
    return _wisdom;
}

uint32_t Entity::UID() const
{
    return _uid;
}
