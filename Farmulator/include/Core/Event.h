#pragma once

#include "Types.h"
#include <any>
#include <unordered_map>


class Event {
private:
	EventId mType{};
	std::unordered_map<EventId, std::any> mData{};

public:
	Event() = delete;

	explicit Event(EventId type) : mType(type) {}

	template<typename T>
	void setParam(EventId id, T value) {
		mData[id] = value;
	}

	template<typename T>
	T getParam(EventId id) {
		return std::any_cast<T>(mData[id]);
	}

	EventId getType() const {
		return mType;
	}
};
