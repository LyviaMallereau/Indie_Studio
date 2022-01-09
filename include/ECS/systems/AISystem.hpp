/*
** EPITECH PROJECT, 2020
** tmp
** File description:
** AISystem.hpp
*/

#pragma once

#include "ECS/World.hpp"
#include "ECS/System.hpp"
#include "ECS/components/AI.hpp"
#include "ECS/systems/BombSystem.hpp"
#include "ECS/components/ControllerInput.hpp"
#include "stdInclude.hpp"

namespace engine
{
    class AISystem : public ECS::System
    {
        private:
            AI _ai;
            std::vector<std::string> _map;
        public:
            using CollideMap = std::array<std::array<int, 16>, 16>;
            AISystem(void);
            ~AISystem(void) = default;
            void update(ECS::World &world, CollideMap &map);
            AI::Direction checkBomb(engine::Transform &tr, CollideMap &map);
            void playSafe(AI::Direction dir, engine::Transform &tr, CollideMap &map, ControllerInput &inp);
            void playAggressive(ECS::World &world, ECS::Guid entity, engine::Transform &tr, CollideMap &map, ControllerInput &inp);
            ECS::Signature getSignature(ECS::World &world);
    };

} // namespace engine
