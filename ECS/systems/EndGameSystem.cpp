/*
** EPITECH PROJECT, 2020
** B-YEP-400-MPL-4-1-indiestudio-alec.ferrari
** File description:
** EndGameSystem.cpp
*/

#include "ECS/systems/EndGameSystem.hpp"

namespace engine
{
    ECS::Signature EndGameSystem::getSignature(ECS::World &world)
    {
        ECS::Signature signature;
        signature.set(world.getComponentType<PlayerStat>());
        return signature;
    }

    void EndGameSystem::update(ECS::World &world, ECS::GameManager &gm)
    {
        if (_entities.size() <= 1) {
            PlayerStat &player = world.getComponent<PlayerStat>(*(_entities.begin()));
            gm.stop();
            gm.getSharedState<std::string>() = player.name;
            gm.setReturnCode(ECS::GameManager::NEXT);
        }
    };
} // namespace engine
