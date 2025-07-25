#include <Systems/Entropator.h>
#include <Core/Coordinator.h>
#include <SFML/System.hpp>
#include <cstdlib>

extern Coordinator coordinator;

void Entropator::entropate() {
	for (const auto& entity : entities) {
		auto& position = coordinator.getComponent<sf::Vector2f>(entity);
		
		float deltaX = rand() % 128 / 32.f - (128 / 32 / 2);
		float deltaY = rand() % 128 / 32.f - (128 / 32 / 2);
		position += sf::Vector2f({ deltaX, deltaY });
	}
}