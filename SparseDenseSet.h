#include <memory>
#include <vector>
#include <string>
#include <limits>
#include <assert.h>


typedef uint64_t ID;
template<typename T>
struct SparseDenseSet {
    
	static constexpr uint64_t INVALID_ID = static_cast<uint64_t>(-1);
	static constexpr uint64_t ID_MASK = 0x000000000000FFFF; //16 bits para o index
	
	bool contains(uint64_t id) const {
		const uint16_t rawID = _rawID(id);
		return rawID < mVersion.size() && mVersion[rawID] == id >> 16;
	}
	
	uint16_t size() const {
		return static_cast<uint16_t>(mData.size());
	}
	
	uint64_t insert(std::unique_ptr<T> data) {
		if (mIndexesSize == std::numeric_limits<uint16_t>::max()) {
			return INVALID_ID; //Chegou no limite - Maximo de 65536 objetos existindo ao mesmo tempo.
		}
		const uint16_t newIndex = mIndexesSize < mIndexes.size() ? mIndexes[mIndexesSize] : mIndexesSize;
		if (newIndex == mIndexesSize) {
			mVersion.emplace_back(0);
		}
		mData.emplace_back(std::move(data));
		mIndexes.emplace_back(newIndex);
		++mIndexesSize;

		const uint64_t newID = (mVersion[newIndex] << 16) | newIndex; //48 bits para a versão e 16 bits para o index
		return newID;
	}
	
	bool remove(uint64_t id) {
		if (contains(id)) {
			const uint16_t rawID = _rawID(id);
			++mVersion[rawID]; //Cada index pode ser reciclado mais de 281 trilhoes de vezes até IDs começarem a repetir
			std::swap(mData.back(), mData[mIndexes[rawID]]);
			std::swap(mIndexes[mIndexesSize - 1], mIndexes[rawID]);
			--mIndexesSize;
			mData.pop_back();
			return true;
		}
		return false;
	}
	
	T* get(uint64_t id) const {
		return contains(id) ? mData[mIndexes[_rawID(id)]].get() : nullptr;
	}
	
private:
	uint16_t _rawID(uint64_t id) const {
		return static_cast<uint16_t>(id & ID_MASK);
	}
	uint16_t mIndexesSize = 0;
	std::vector<uint64_t> mVersion;
	std::vector<uint16_t> mIndexes;
	std::vector<std::unique_ptr<T>> mData;
};
