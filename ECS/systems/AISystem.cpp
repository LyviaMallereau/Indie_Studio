/*
** EPITECH PROJECT, 2020
** tmp
** File description:
** AISytem.cpp
*/


#include "ECS/systems/AISystem.hpp"

namespace engine {
    static void createBomb(ECS::World &world, ECS::Guid entity, engine::Transform &tr)
    {
        BombSettings &settings = world.getComponent<BombSettings>(entity);
        if (settings.nbBombs > 0) {
            auto bomb = world.createEntity();
            world.addComponent(bomb, Bomb({settings.lifetimeBuff + 100, settings.power, settings.piercing, entity}));
            world.addComponent(bomb, engine::Transform({
                Vector3{float(int(tr.position.x + 0.5)), tr.position.y, float(int(tr.position.z + 0.5))},
                {0}, 1
            }));
            settings.nbBombs--;
        }
    }

    static bool isWalkable(engine::AISystem::CollideMap &map, int z, int x)
    {
        if (map[z][x] != Cubemap::INDESTRUCTIBLE &&
            map[z][x] != Cubemap::DESTRUCTIBLE &&
            map[z][x] != Cubemap::BOMB)
        {
            return true;
        }
        return false;
    }

    static void move(ControllerInput &inp, engine::AI::Direction dir)
    {
        switch (dir) {
            case engine::AI::Direction::UP:
                inp.up = true;
                break;
            case engine::AI::Direction::DOWN:
                inp.down = true;
                break;
            case engine::AI::Direction::LEFT:
                inp.left = true;
                break;
            case engine::AI::Direction::RIGHT:
                inp.right = true;
                break;
            default:
                break;
        }
    }

    static void centerToBlock(engine::Transform &tr, ControllerInput &inp)
    {
        float posX = tr.position.x + 0.5f;
        float posZ = tr.position.z + 0.5f;

        float distX = fmod(posX, 1.0f);
        float distZ = fmod(posZ, 1.0f);

        if (inp.up || inp.down) {
            if (distX < 0.5f)
                move(inp, engine::AI::Direction::RIGHT);
            else
                move(inp, engine::AI::Direction::LEFT);
        }
        else if (inp.left || inp.right) {
            if (distZ < 0.5f)
                move(inp, engine::AI::Direction::DOWN);
            else
                move(inp, engine::AI::Direction::UP);
        }
    }
}

engine::AISystem::AISystem(void)
{
}

ECS::Signature engine::AISystem::getSignature(ECS::World &world)
{
    ECS::Signature signature;
    signature.set(world.getComponentType<AI>());
    signature.set(world.getComponentType<engine::Transform>());
    signature.set(world.getComponentType<ControllerInput>());
    return signature;
}

void engine::AISystem::update(ECS::World &world, engine::AISystem::CollideMap &map)
{
    for (auto &&entity : _entities) {
        auto &tr = world.getComponent<engine::Transform>(entity);
        auto &inp = world.getComponent<ControllerInput>(entity);
        auto &ai = world.getComponent<AI>(entity);

        AI::Direction tmp = this->checkBomb(tr, map);

        inp.left = false;
        inp.right = false;
        inp.up = false;
        inp.down = false;

        std::cout << tmp << std::endl;
        if (tmp == AI::NONE)
            this->playAggressive(world, entity, tr, map, inp);
        else
            this->playSafe(tmp, tr, map, inp);
        centerToBlock(tr, inp);
    }
}

engine::AI::Direction engine::AISystem::checkBomb(engine::Transform &tr, engine::AISystem::CollideMap &map)
{
    const int viewDistance = 5;
    int posX = tr.position.x + 0.5f;
    int posZ = tr.position.z + 0.5f;

    AI::Direction dir = AI::NONE;
    int bombDistance = 100;

    if (map[posZ][posX] == Cubemap::BOMB)
        return AI::SELF;

    for (int i = 1; i < viewDistance; i++) {
        if (posZ + i < 14 && map[posZ + i][posX] == Cubemap::BOMB) {
            if (i < bombDistance) {
                bombDistance = i;
                dir = AI::DOWN;
            }
        }
    }
    for (int i = 1; i < viewDistance; i++) {
        if (posZ - i > 0 && map[posZ - i][posX] == Cubemap::BOMB) {
            if (i < bombDistance) {
                bombDistance = i;
                dir = AI::UP;
            }
        }
    }
    for (int i = 1; i < viewDistance; i++) {
        if (posX + i < 14 && map[posZ][posX + i] == Cubemap::BOMB) {
            if (i < bombDistance) {
                bombDistance = i;
                dir = AI::RIGHT;
            }
        }
    }
    for (int i = 1; i < viewDistance; i++) {
        if (posX - i > 0 && map[posZ][posX - i] == Cubemap::BOMB) {
            if (i < bombDistance) {
                bombDistance = i;
                dir = AI::LEFT;
            }
        }
    }
    // if (int(dir) != 0)
    // std::cout << int(dir) << std::endl;
    return dir;
}

void engine::AISystem::playSafe(AI::Direction dir, engine::Transform &tr, engine::AISystem::CollideMap &map, ControllerInput &inp)
{
    const int posX = tr.position.x + 0.5f;
    const int posZ = tr.position.z + 0.5f;

    if (dir == AI::SELF) {
        if (isWalkable(map, posZ, posX + 1))
            inp.right = true;
        else if (isWalkable(map, posZ, posX - 1))
            inp.left = true;
        else if (isWalkable(map, posZ + 1, posX))
            inp.down = true;
        else if (isWalkable(map, posZ - 1, posX))
            inp.up = true;
    }

    if (dir == AI::UP) {
        if (isWalkable(map, posZ, posX + 1))
            inp.right = true;
        else if (isWalkable(map, posZ, posX - 1))
            inp.left = true;
        else if (isWalkable(map, posZ + 1, posX))
            inp.down = true;
    }
    else if (dir == AI::DOWN) {
        if (isWalkable(map, posZ, posX + 1))
            inp.right = true;
        else if (isWalkable(map, posZ, posX - 1))
            inp.left = true;
        else if (isWalkable(map, posZ - 1, posX))
            inp.up = true;
    }
    else if (dir == AI::LEFT) {
        if (isWalkable(map, posZ, posX + 1))
            inp.right = true;
        else if (isWalkable(map, posZ - 1, posX))
            inp.up = true;
        else if (isWalkable(map, posZ + 1, posX))
            inp.down = true;
    }
    else if (dir == AI::RIGHT) {
        if (isWalkable(map, posZ, posX - 1))
            inp.left = true;
        else if (isWalkable(map, posZ - 1, posX))
            inp.up = true;
        else if (isWalkable(map, posZ + 1, posX))
            inp.down = true;
    }

    std::cout << "play safe" << std::endl;
    std::cout << "right: " << inp.right << std::endl;
    std::cout << "left: " << inp.left << std::endl;
    std::cout << "down: " << inp.down << std::endl;
    std::cout << "up: " << inp.up << std::endl << std::endl;

}

void engine::AISystem::playAggressive(ECS::World &world, ECS::Guid entity, engine::Transform &tr, engine::AISystem::CollideMap &map, ControllerInput &inp)
{
    const int posX = tr.position.x + 0.5f;
    const int posZ = tr.position.z + 0.5f;

    if (map[posZ][posX + 1] == Cubemap::DESTRUCTIBLE ||
        map[posZ][posX - 1] == Cubemap::DESTRUCTIBLE ||
        map[posZ + 1][posX] == Cubemap::DESTRUCTIBLE ||
        map[posZ - 1][posX] == Cubemap::DESTRUCTIBLE)
    {
        createBomb(world, entity, tr);
    } else { // if no wall to destroy, move in random direction
        std::vector<engine::AI::Direction> possibleDir;

        if (isWalkable(map, posZ + 1, posX))
            possibleDir.push_back(engine::AI::Direction::DOWN);
        if (isWalkable(map, posZ - 1, posX))
            possibleDir.push_back(engine::AI::Direction::UP);
        if (isWalkable(map, posZ, posX + 1))
            possibleDir.push_back(engine::AI::Direction::RIGHT);
        if (isWalkable(map, posZ, posX - 1))
            possibleDir.push_back(engine::AI::Direction::LEFT);

        if (possibleDir.size() > 0) {
            int rd = rand() % possibleDir.size();
            move(inp, possibleDir[rd]);
        }

        std::cout << posX << " : " << posZ << std::endl;
        std::cout << possibleDir << std::endl;

        std::cout << "play agressive" << std::endl;
        std::cout << "right: " << inp.right << std::endl;
        std::cout << "left: " << inp.left << std::endl;
        std::cout << "down: " << inp.down << std::endl;
        std::cout << "up: " << inp.up << std::endl << std::endl;
    }
}