#pragma once

#include "Types.h"
#include <array>
#include <cassert>
#include <unordered_map>


class IComponentArray
{
public:
	virtual ~IComponentArray() = default;
	virtual void entityDestroyed(Entity entity) = 0;
};


template<typename T>
class ComponentArray : public IComponentArray {
private:
	std::array<T, MAX_ENTITIES> mComponentArray{};
	std::unordered_map<Entity, size_t> mEntityToIndexMap{};
	std::unordered_map<size_t, Entity> mIndexToEntityMap{};
	size_t mSize{};

public:
	void insertData(Entity entity, T component) {
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");

		// Put new entry at end
		size_t newIndex = mSize;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentArray[newIndex] = component;
		++mSize;
	}

	void removeData(Entity entity) {
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");

		// Copy element at end into deleted element's place to maintain density
		size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mSize - 1;
		mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

		// Update map to point to moved spot
		Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
		mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);

		--mSize;
	}

	T& getData(Entity entity) {
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");

		return mComponentArray[mEntityToIndexMap[entity]];
	}

	void entityDestroyed(Entity entity) override {
		if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
			removeData(entity);
		}
	}
};
