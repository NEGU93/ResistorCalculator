#include "allegro.h"
#include "def.h"


#define FPS 30
#define FONTSIZE 60

#define OK 0
#define READY 1
#define EXIT -1

//////////////////////////////////////////////////////////////////////////////////////////////
//				INICIALIZO ALLEGRO Y TODOS LOS COMPLEMENTOS QUE SE USAN						//
//////////////////////////////////////////////////////////////////////////////////////////////
int init_allegro(ALL *allegro) {
	int state = FALSE;
	//Initialize Allegro
	if (al_init()) {
		if (al_init_primitives_addon()) {
			if (al_init_image_addon()) {
				if (al_install_mouse()) {
					if (al_install_keyboard()) {
						if (allegro->display = al_create_display(SCREEN_X, SCREEN_Y)) {
							//CODE TO FULLSCREEN, CHANGE IN CASE OF MULFUNCTION
							/*TODO: lo comento porque es dificil para debuguear... luego agregarlo. tira mas facha*/
							/*ALLEGRO_DISPLAY_MODE   disp_data;
							al_get_display_mode(al_get_num_display_modes() - 1, &disp_data);
							al_set_new_display_flags(ALLEGRO_FULLSCREEN);
							allegro->display = al_create_display(disp_data.width, disp_data.height);
							allegro->screenWidth = disp_data.width;
							allegro->screenHeight = disp_data.height;*/
							//allegro->display = al_create_display(SCREEN_X, SCREEN_Y);
							allegro->screenWidth = SCREEN_X;
							allegro->screenHeight = SCREEN_Y;

							//if (allegro->fondo = al_load_bitmap_resized("Resources/BackImage.jpg", allegro)) {
								state = TRUE;
							//}
							//else { printf("Couldn't load BackImage.jpg"); }
						}
						else { printf("Failed to create display"); }
					}
					else { printf( "Failed to initialize keyboard" ); al_uninstall_mouse(); }
				}
				else { printf( "Failed to initialize mouse" ); al_shutdown_image_addon(); }
			}
			else { printf( "Failed to initialize image addon" ); al_shutdown_primitives_addon(); }
		}
		else { printf( "Failed to initialize primitives addon" ); }
	}
	else { printf( "Failed to initialize allegro" ); }
	
	//Initialize events
	if (state) {
		state = FALSE;
		if (allegro->timer = al_create_timer(1.0 / FPS)) {
			al_start_timer(allegro->timer);
			if (allegro->events_queue = al_create_event_queue()) {
				al_register_event_source(allegro->events_queue, al_get_timer_event_source(allegro->timer));
				al_register_event_source(allegro->events_queue, al_get_keyboard_event_source());
				al_register_event_source(allegro->events_queue, al_get_mouse_event_source());
				al_register_event_source(allegro->events_queue, al_get_display_event_source(allegro->display));
				state = TRUE;
			}
		}
		else { printf( "Failed to initialize timer" ); }
	}
	//Initialize fonts
	if (state) {
		state = FALSE;
		al_init_font_addon();
		if (al_init_ttf_addon()) {
			if (allegro->font = al_load_ttf_font("Resources/consola.ttf", 12, 0)) {
				state = TRUE;
			}
			else { printf( "Failed to initialize arial.ttf" ); }
		}
		else { printf( "Failed to initialize ttf addon" ); }
	}

	al_flip_display();
	al_start_timer(allegro->timer);

	return state;
}

void destroyAll(ALL *allegro) {
	al_destroy_event_queue(allegro->events_queue);
	//Timers
	al_destroy_timer(allegro->timer);
	//Fonts
	al_destroy_font(allegro->font);
	//Bitmaps
	//al_destroy_bitmap(allegro->fondo);
	//Addons
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_shutdown_image_addon();
	al_shutdown_ttf_addon();
	al_shutdown_primitives_addon();
	al_uninstall_audio();
}

ALLEGRO_BITMAP *al_load_bitmap_resized(const char *filename, ALL* allegro) {
	ALLEGRO_BITMAP *resized_bmp, *loaded_bmp, *prev_target;
	//Same as al_load_bitmap but resized according to the display size

	// 1. load the bitmap at the original size				 
	loaded_bmp = al_load_bitmap(filename);
	if (!loaded_bmp) return NULL;

	// 2. create a temporary bitmap of size we want
	resized_bmp = al_create_bitmap(al_get_bitmap_width(loaded_bmp) * allegro->screenWidth / MAXRESOLUTION_X, al_get_bitmap_height(loaded_bmp) * allegro->screenHeight / MAXRESOLUTION_Y);
	if (!resized_bmp) {
		al_destroy_bitmap(loaded_bmp);
		return NULL;
	}

	// 3. set the target bitmap to the resized bmp
	prev_target = al_get_target_bitmap();
	al_set_target_bitmap(resized_bmp);

	// 4. copy the loaded bitmap to the resized bmp
	al_draw_scaled_bitmap(loaded_bmp,
		0, 0,                                // source origin
		al_get_bitmap_width(loaded_bmp),     // source width
		al_get_bitmap_height(loaded_bmp),    // source height
		0, 0,                                // target origin
		al_get_bitmap_width(loaded_bmp) * allegro->screenWidth / MAXRESOLUTION_X,		// target dimensions
		al_get_bitmap_height(loaded_bmp) * allegro->screenHeight / MAXRESOLUTION_Y,
		0                                    // flags
		);

	// 5. restore the previous target and clean up
	al_set_target_bitmap(prev_target);
	al_destroy_bitmap(loaded_bmp);

	return resized_bmp;
}

void draw_line(int x1, int y1, int x2, int y2, ALLEGRO_COLOR color, float thickness) {
	al_draw_line(x1, y1, x2, y1, color, thickness);
	al_draw_line(x2, y1, x2, y2, color, thickness);
}