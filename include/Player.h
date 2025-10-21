// Author: Francesco Fantin
#ifndef BATTLESHIPPROJECT_PLAYER_H_
#define BATTLESHIPPROJECT_PLAYER_H_

#include "DefenseMap.h"
#include "AttackGrid.h"
#include "Move.h"
#include "Ship.h"
#include "Ironclad.h"
#include "SupportShip.h"
#include "Submarine.h"
#include "Utility.h"
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

class Player
{
public:
    virtual Move get_move(const std::string &cmd) = 0;

    // Function that allows adding a ship to the list of ships according
    // to the specifications given by the command and the size.
    // Returns true if the insertion was successful, false otherwise.
    virtual bool add_ships(std::string &cmd, int size) = 0;

    // Function that searches the vector of ships for the ship whose center
    // is at the specified position. Returns nullptr if no such ship exists.
    std::shared_ptr<Ship> get_ship(const Position origin);

    // Function that returns a vector of AttackUnit for the submarine operation.
    // Each element of the vector represents a cell of the area scanned by the
    // submarine, indicating the result of the operation (whether a ship was detected or not).
    std::vector<AttackUnit> retrieve_unit(const Position &target);

    // Function that updates the player's defense map after being attacked by
    // an enemy ironclad. If a ship is sunk, it is removed from the list of ships.
    AttackUnit receive_attack(const Position &target);

    // Function that, depending on the type of move passed as a parameter,
    // calls the corresponding methods, requesting the update of the map for the
    // player receiving the move. Returns a vector of AttackUnit indicating the
    // state of the cells affected by the move.
    std::vector<AttackUnit> execute_move(const Position &target, const MoveType &type);

    // Function that handles receiving attack units from the opposing player.
    // Returns true if the ship's action was performed correctly, false otherwise.
    bool handle_response(std::vector<AttackUnit> units, const Move &m);


    // Getter methods
    std::string nickname() { return nickname_; }

    AttackGrid &attack_grid() { return attack_grid_; }

    DefenseMap &defense_map() { return defense_map_; }

    int get_ships_left() { return ship_list.size(); }

    // Destructor
    virtual ~Player();

protected:
    // Constructor given the player's name
    Player(const std::string &);

    // Player's name
    std::string nickname_;

    // Player's attack map
    AttackGrid attack_grid_;

    // Player's defense map
    DefenseMap defense_map_;

    // Vector of shared pointers to ships
    std::vector<std::shared_ptr<Ship>> ship_list;

private:
    // Constant useful for command-to-position and vice versa conversions
    static constexpr int kDefaultCapitalAscii = 65;

    // Constant useful for command-to-position and vice versa conversions
    static constexpr int kEqualityVectorPosition = 1;
};

// Returns the direction of the ship to be inserted
Direction get_direction(const Position &bow, const Position &stern);

// Returns the size of the ship to be inserted
int get_size(const Position &bow, const Position &stern);

#endif
