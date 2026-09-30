#include <raylib.h>

const int WIDTH = 1000;
const int HEIGHT = 1000;
const int CELL_SIZE = 10;

const int COLS = WIDTH / CELL_SIZE;
const int ROWS = HEIGHT / CELL_SIZE;

bool grid[COLS * ROWS] = {};
bool newGen[COLS * ROWS] = {};

int idx(int i, int j) { return j * COLS + i; }

int main() {
	SetConfigFlags(FLAG_WINDOW_HIGHDPI);
	InitWindow(WIDTH, HEIGHT, "Game of Life");
	SetTargetFPS(10);

	for (int i = 0; i < COLS * ROWS; i++)
		grid[i] = GetRandomValue(0, 100) > 50;

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(BLACK);

		for (int i = 0; i < COLS; i++) {
			for (int j = 0; j < ROWS; j++) {
				int neighbours = 0;

				for (int x = -1; x <= 1; x++) {
					for (int y = -1; y <= 1; y++) {
						if (x == 0 && y == 0)
							continue;

						int dx = (i + x + COLS) % COLS;
						int dy = (j + y + ROWS) % ROWS;

						if (grid[idx(dx, dy)])
							neighbours++;
					}
				}

				if (grid[idx(i, j)]) {
					newGen[idx(i, j)] = (neighbours == 2 || neighbours == 3);
					DrawRectangle(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE,
					              CELL_SIZE, WHITE);
				} else {
					newGen[idx(i, j)] = neighbours == 3;
					DrawRectangleLines(i * CELL_SIZE, j * CELL_SIZE, CELL_SIZE,
					                   CELL_SIZE, DARKGRAY);
				}
			}
		}

		for (int i = 0; i < COLS * ROWS; i++)
			grid[i] = newGen[i];

		EndDrawing();
	}
	CloseWindow();
}
