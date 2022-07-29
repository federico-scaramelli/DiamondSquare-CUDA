#include "DiamondSquareSequential.h"

std::random_device rd;
//std::mt19937 gen(0);
std::mt19937 generator(rd());
std::uniform_real_distribution<double> unif {-1.0, 1.0};

void DiamondSquareSequential::InitializeDiamondSquare(uint32_t initValuesDistance) {
	/*for (int i = 0; i < 100; i++) {
		std::cout << unif(generator) << std::endl;
	}*/
	for (int x = 0; x < size; x += initValuesDistance) {
		//if (x > size) continue;
		for (int y = 0; y < size; y += initValuesDistance) {
			//if (y > size) continue;
			map[GetIndex(x, y)] = unif(generator);  
		}
	}

	step = initValuesDistance;
}

void DiamondSquareSequential::DiamondSquare() {

	//step = size - 1;

	while (step > 1) {
		half = step / 2;

		for (uint32_t y = half; y < size + half; y += step) {
			for (uint32_t x = half; x < size + half; x += step) {
				DiamondStep(x, y);
			}
		}

		//PrintMap();

		for (uint32_t x = 0; x < size; x += half) {
			for (uint32_t y = (x + half) % step; y < size; y += step) {
				SquareStep(x, y);
			}
		}
		
		//PrintMap();

		randomScale /= 2.0;
		step /= 2;
	}
}

void DiamondSquareSequential::DiamondStep(uint32_t x, uint32_t y) {

	double value = 0;

	value = map[GetIndex(x - half, y - half)] +
		map[GetIndex(x + half, y - half)] +
		map[GetIndex(x - half, y + half)] +
		map[GetIndex(x + half, y + half)];

	value /= 4.0;
	value += unif(generator) * randomScale;
	value = value > 1 ? 1 : value;
	value = value < -1 ? -1 : value;

	map[GetIndex(x, y)] = value;
}

void DiamondSquareSequential::SquareStep(uint32_t x, uint32_t y) {

	double value = map[GetIndex(x - half, y)] +
				map[GetIndex(x + half, y)] +
				map[GetIndex(x, y - half)] +
				map[GetIndex(x, y + half)];

	value /= 4.0;
	value += unif(generator) * randomScale;
	value = value > 1 ? 1 : value;
	value = value < -1 ? -1 : value;

	map[x * size + y] = value;
}
