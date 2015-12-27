#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

const int WIDTH = 1460;
const int HEIGHT = 669;

struct Background
{
	float x;
	float y;
	float velX;
	float velY;
	int dirX;
	int dirY;

	int width;
	int height;

	ALLEGRO_BITMAP *image;
};

void InitBackground(Background &back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image);
void UpdateBackground(Background &back);
void DrawBackground(Background &back);

int main(void)
{
	//variables
	bool done = false;
	bool render = false;

	Background BG;
	//Background MG;
	//Background FG;

	//allegro variable
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer;
	ALLEGRO_BITMAP *bgImage = NULL;
	ALLEGRO_BITMAP *mgImage = NULL;
	ALLEGRO_BITMAP *fgImage = NULL;

	//program init
	if (!al_init())										//initialize Allegro
		return -1;

	display = al_create_display(WIDTH, HEIGHT);			//create our display object

	if (!display)										//test display object
		return -1;

	//addon init
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();

	bgImage = al_load_bitmap("sample_terrain.bmp.jpg");
	assert(bgImage && "no bgimage");
	//mgImage = al_load_bitmap("sample_terrain.bmp");
	//fgImage = al_load_bitmap("starFG.png");

	InitBackground(BG, 0, 0, 1, 0, 9270, 423, -1, 1, bgImage);
	//InitBackground(MG, 0, 0, 3, 0, 1600, 600, -1, 1, mgImage);
	//InitBackground(FG, 0, 0, 5, 0, 800, 600, -1, 1, fgImage);

	event_queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60);

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	while (!done)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_LEFT:

				break;
			case ALLEGRO_KEY_RIGHT:

				break;
			case ALLEGRO_KEY_UP:

				break;
			case ALLEGRO_KEY_DOWN:

				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			UpdateBackground(BG);
			//UpdateBackground(MG);
			//UpdateBackground(FG);
			render = true;
		}

		if (render && al_is_event_queue_empty(event_queue))
		{
			render = false;

			DrawBackground(BG);
			//DrawBackground(MG);
			//DrawBackground(FG);

			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}

	al_destroy_bitmap(bgImage);
	//al_destroy_bitmap(mgImage);
	//al_destroy_bitmap(fgImage);
	al_destroy_event_queue(event_queue);
	al_destroy_display(display);						//destroy our display object

	return 0;
}

void InitBackground(Background &back, float x, float y, float velx, float vely, int width, int height, int dirX, int dirY, ALLEGRO_BITMAP *image)
{
	back.x = x;
	back.y = y;
	back.velX = velx;
	back.velY = vely;
	back.width = width;
	back.height = height;
	back.dirX = dirX;
	back.dirY = dirY;
	back.image = image;
}
void UpdateBackground(Background &back)
{
	back.x += back.velX * back.dirX;
	if (back.x + back.width <= 0)
		back.x = 0;
}
void DrawBackground(Background &back)
{
	al_draw_scaled_bitmap(back.image,0,0, back.width, back.height, back.x, back.y, back.width*3, back.height * 3, 0);

	//if (back.x + back.width < WIDTH)
		al_draw_bitmap(back.image, back.x + back.width, back.y, 0);
}