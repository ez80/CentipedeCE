typedef struct Tile {
	int x;
	int y;
	int width;
	int height;
} Tile;
void spriteSheet(uint8_t *data, uint8_t *output, uint8_t originalWidth, uint8_t originalHeight, uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void addTile(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
void gameLoop();
int generateRandomNumber(int max, int previous);