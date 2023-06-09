#include "LevelLoader.h"
#include <fstream>
#include "Block.h"

using namespace pengo;

LevelLoader::LevelLoader(engine::GameObject* pOwner, float gridSize)
	: Component(pOwner)
	, m_LevelPaths{}
	, m_GridSize{ gridSize }
{
}

void LevelLoader::AddLevelPath(const std::string& path) {
	m_LevelPaths.emplace_back(path);
}

engine::GameObject* LevelLoader::LoadLevel(int index) const{
	engine::GameObject* pLevelObject = new engine::GameObject();

	// Read from .dat file
    if (std::ifstream input{ m_LevelPaths[index], std::ios::binary}; input.is_open()) {
        
		// Get grid size 
		int32_t rows{}, cols{};
		input.read((char*)&cols, sizeof(cols));
		input.read((char*)&rows, sizeof(rows));	

		// Debug
		//std::cout << "\n" << rows << " " << cols << "\n";

		// Load ice blocks
		// This is gonna be a bit unconventional since I store the information per bit, but can only read in at 8 bits at a time
		int cell{ 0 };
		while (cell < rows * cols) {
			
			char data{};
			input.read(&data, sizeof(data));
			
			// Check each bit
			for (int shiftIndex{ 7 }; shiftIndex >= 0; --shiftIndex) {

				// Check that the cell is still in the grid
				if (!(cell < rows * cols)) { break; }

				// Get the correct bit
				char bit = data >> shiftIndex & 0x1;

				// Add ice block at correct position if bit == 1
				if (bit) {
					glm::vec3 pos{ 0,0,0 };
					pos.x = m_GridSize * (cell % cols);
					pos.y = m_GridSize * (cell / cols);

					engine::GameObject* block = CreateIceBlock(pos);
					block->AttachTo(pLevelObject, false);
				}

				// Also increase cellnumber
				++cell;

				// Debug
				//std::cout << ((bit) ? '1' : '0');
				/*if (cell % cols == 0) { 
					std::cout << "\n"; 
				}*/
			}
		}
    }

	pLevelObject->SetLocalPosition(16, 16);

	return pLevelObject;
}