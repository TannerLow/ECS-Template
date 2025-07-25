#include <Core/Coordinator.h>
#include <chrono>
#include <random>
#include <SFML/System.hpp>
#include <Systems/Entropator.h>
#include <Systems/Reporter.h>


Coordinator coordinator;

int main() {
	coordinator.init();

	coordinator.registerComponent<sf::Vector2f>();

	auto entropator = coordinator.registerSystem<Entropator>();
	{
		Signature signature;
		signature.set(coordinator.getComponentType<sf::Vector2f>());
		coordinator.setSystemSignature<Entropator>(signature);
	}

	auto reporter = coordinator.registerSystem<Reporter>();
	{
		Signature signature;
		signature.set(coordinator.getComponentType<sf::Vector2f>());
		coordinator.setSystemSignature<Reporter>(signature);
	}

	Entity entity = coordinator.createEntity();
	coordinator.addComponent(entity, sf::Vector2f({ 500, 500 }));

	for (int i = 0; i < 1000; i++) {
		entropator->entropate();
		reporter->report();
	}

	return EXIT_SUCCESS;
}
