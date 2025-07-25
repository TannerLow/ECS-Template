#include <Systems/Reporter.h>
#include <Core/Coordinator.h>
#include <SFML/System.hpp>
#include <cstdio>


extern Coordinator coordinator;


void Reporter::report() {
	for (const auto& entity : entities) {
		const auto& position = coordinator.getComponent<sf::Vector2f>(entity);
		
		printf("Entity at (%.3f, %.3f)\n", position.x, position.y);
	}
}