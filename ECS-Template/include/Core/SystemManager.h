#pragma once

#include "System.h"
#include "Types.h"
#include <cassert>
#include <memory>
#include <unordered_map>


class SystemManager {
private:
	std::unordered_map<const char*, Signature> mSignatures{};
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};

public:
	template<typename T>
	std::shared_ptr<T> registerSystem() {
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

		auto system = std::make_shared<T>();
		mSystems.insert({ typeName, system });
		return system;
	}

	template<typename T>
	void setSignature(Signature signature) {
		const char* typeName = typeid(T).name();

		assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

		mSignatures.insert({ typeName, signature });
	}

	void entityDestroyed(Entity entity) {
		for (auto const& pair : mSystems) {
			auto const& system = pair.second;

			system->entities.erase(entity);
		}
	}

	void entitySignatureChanged(Entity entity, Signature entitySignature) {
		for (auto const& pair : mSystems) {
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mSignatures[type];

			if ((entitySignature & systemSignature) == systemSignature) {
				system->entities.insert(entity);
			}
			else {
				system->entities.erase(entity);
			}
		}
	}
};
