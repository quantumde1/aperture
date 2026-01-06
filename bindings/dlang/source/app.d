import aperture;

// example.

void main() {
	int argc;
	char** argv;
	InitWindow(argc, argv, 800, 600, "test");
	Texture tex = LoadTexture("test.png");
	while (!WindowShouldClose()) {
		SetTargetFPS(60);
		PollWindowEvents();
		ClearBackground(Colors.BLACK);
		BeginDrawing();
		DrawTexture(tex, GetScreenWidth()/2, GetScreenHeight()/2, 1.0, Color(128, 128, 128, 255));
		DrawText("test", GetScreenWidth()/2, GetScreenHeight()/2, 5, Colors.WHITE);
		EndDrawing();
	}
	UnloadTexture(tex);
	CloseWindow();
}