
#include <string>
#include <raylib.h>

#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

int main(void)
{
	// Initialization
	//--------------------------------------------------------------------------------------
	const int screenWidth = 800;
	const int screenHeight = 400;

	InitWindow(screenWidth, screenHeight, "Empty");
	// NOTE: Textures/Fonts MUST be loaded after Window initialization (OpenGL context is required)

	/**
	 * Load textures and set elements position
	 */
	Texture2D player = LoadTexture("assets/sprites.png");
	Texture2D BG1 = LoadTexture("assets/desert_BG.png");
	Texture2D BG2 = LoadTexture("assets/desert_BG.png");
	Vector2 playerPosition = { 50.0f, 240.0f };
	Vector2 BG1Position = { 0,0 };
	Vector2 BG2Position = { BG1.width,0 };

	/**
	 * The sprite sheet contains 8 column, 7 dedicated to the player running state and 4 lines
	 */
	int nb_sprite_by_line = 7;
	int nb_lines = 4;

	/**
	 * It will be the vignette that select which part of the sheet to draw
	 */
	Rectangle frameRec = { 0.0f, 0.0f, (float)player.width / nb_sprite_by_line - 1, (float)player.height * 2 / (3 * nb_lines) };
	int currentFrame = 0;

	int framesCounter = 0;
	int framesSpeed = 8;
	bool isJumping = false;

	SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
									//--------------------------------------------------------------------------------------
									// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		framesCounter++;
		/**
		 * Check th jum state
		 */
		if (isJumping)
		{
			frameRec.y = (float)player.height / nb_lines;
			if (framesCounter < 16)
			{
				frameRec.x = 0;
				playerPosition.y -= 8;
			}
			else if (framesCounter < 31)
			{
				frameRec.x = (float)player.width / nb_sprite_by_line;
				playerPosition.y += 8;
			}
			else
			{
				isJumping = false;
				framesCounter = 0;
				frameRec.y = 0;
			}
		}
		else if (framesCounter >= (60 / framesSpeed))
		{
			/**
			 * Change the frame to display (use the "vignette" over the sprite sheet)
			 */
			framesCounter = 0;
			currentFrame++;

			if (currentFrame > (nb_sprite_by_line - 2)) currentFrame = 0;

			frameRec.x = (float)currentFrame * (float)player.width / nb_sprite_by_line;
		}

		/**
		 * Move the brackground
		 */
		BG1Position.x--;
		if (BG1Position.x + BG1.width <= 0)
			BG1Position.x = BG1.width;
		BG2Position.x--;
		if (BG2Position.x + BG2.width <= 0)
			BG2Position.x = BG2.width;

		// Control frames speed
		if (IsKeyPressed(KEY_RIGHT)) framesSpeed++;
		else if (IsKeyPressed(KEY_LEFT)) framesSpeed--;
		if (IsKeyPressed(KEY_SPACE) && !isJumping)
		{
			isJumping = true;
			framesCounter = 0;
		}

		if (framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
		else if (framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;

		//----------------------------------------------------------------------------------
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		/**
		 * Draw the background
		 */
		DrawTexture(BG1, BG1Position.x, BG1Position.y, WHITE);
		DrawTexture(BG2, BG2Position.x, BG2Position.y, WHITE);

		/**
		 * Draw the hero
		 */
		DrawTextureRec(player, frameRec, playerPosition, WHITE);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------


	CloseWindow();              // Close window and OpenGL context

	return 0;
}