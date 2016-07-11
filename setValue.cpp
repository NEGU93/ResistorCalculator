#include "setValue.h"

/*solo toma datos si apretas un numero,a las letras o otras cosas las ignora.
Para salir de la funcion y que me devuelva el valor de la resistencia apretar ENTER.
Para borrar usar la letra BACKSPACE*/

double setValue(ALLEGRO_FONT* font)
{
	ALLEGRO_DISPLAY *display2 = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue2 = NULL;
	ALLEGRO_TIMER *timer2 = NULL;

	bool key[11] = { false, false, false, false , false , false , false , false , false , false };
	bool redraw = true;
	bool doexit = false;
	double fnumber;
	int i = 0;
	char number[30];
	char *p2number;
	p2number = number;


	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if (!al_install_keyboard()) {
		fprintf(stderr, "failed to initialize the keyboard!\n");
		return -1;
	}

	timer2 = al_create_timer(1.0 / FPS);
	if (!timer2) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display2 = al_create_display(SCREEN_W, SCREEN_H);
	if (!display2) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer2);
		return -1;
	}
	al_set_window_title(display2, "Set Value");


	al_init_font_addon();



	al_clear_to_color(al_map_rgb(255, 0, 255));

	al_set_target_bitmap(al_get_backbuffer(display2));

	event_queue2 = al_create_event_queue();
	if (!event_queue2) {
		fprintf(stderr, "failed to create event_queue!\n");

		al_destroy_display(display2);
		al_destroy_timer(timer2);
		return -1;
	}

	al_register_event_source(event_queue2, al_get_display_event_source(display2));

	al_register_event_source(event_queue2, al_get_timer_event_source(timer2));

	al_register_event_source(event_queue2, al_get_keyboard_event_source());

	al_clear_to_color(al_map_rgb(0, 0, 0));

	al_draw_text(font, al_map_rgb(255, 255, 255), 150 / 2, 30, ALLEGRO_ALIGN_CENTRE, "value:");

	al_flip_display();

	al_start_timer(timer2);

	while (!doexit)
	{
		ALLEGRO_EVENT ev2;
		al_wait_for_event(event_queue2, &ev2);

		if (ev2.type == ALLEGRO_EVENT_TIMER) {

			if (key[KEY_0] && i < 20) {
				*(p2number + i) = '0';
				*(p2number + i + 1) = '\0';
				i++;
			}

			if (key[KEY_1] && i < 20) {
				*(p2number + i) = '1';
				*(p2number + i + 1) = '\0';
				i++;
			}

			if (key[KEY_2] && i < 20) {
				*(p2number + i) = '2';
				*(p2number + i + 1) = '\0';
				i++;
			}

			if (key[KEY_3] && i < 20) {
				*(p2number + i) = '3';
				*(p2number + i + 1) = '\0';
				i++;
			}
			if (key[KEY_4] && i < 20) {
				*(p2number + i) = '4';
				*(p2number + i + 1) = '\0';
				i++;
			}
			if (key[KEY_5] && i < 20) {
				*(p2number + i) = '5';
				*(p2number + i + 1) = '\0';
				i++;
			}
			if (key[KEY_6] && i < 20) {
				*(p2number + i) = '6';
				*(p2number + i + 1) = '\0';
				i++;
			}
			if (key[KEY_7] && i < 20) {
				*(p2number + i) = '7';
				*(p2number + i + 1) = '\0';
				i++;
			}
			if (key[KEY_8] && i < 20) {
				*(p2number + i) = '8';
				*(p2number + i + 1) = '\0';
				i++;
			}
			if (key[KEY_9] && i < 20) {
				*(p2number + i) = '9';
				*(p2number + i + 1) = '\0';
				i++;
			}
			if (key[KEY_BACKSPACE] && i >0) {

				*(p2number + i - 1) = '\0';
				i--;
			}





			redraw = true;
		}
		else if (ev2.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}
		else if (ev2.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev2.keyboard.keycode) {

			case ALLEGRO_KEY_0:
				key[KEY_0] = true;
				break;
			case ALLEGRO_KEY_1:
				key[KEY_1] = true;
				break;

			case ALLEGRO_KEY_2:
				key[KEY_2] = true;
				break;

			case ALLEGRO_KEY_3:
				key[KEY_3] = true;
				break;

			case ALLEGRO_KEY_4:
				key[KEY_4] = true;
				break;

			case ALLEGRO_KEY_5:
				key[KEY_5] = true;
				break;

			case ALLEGRO_KEY_6:
				key[KEY_6] = true;
				break;

			case ALLEGRO_KEY_7:
				key[KEY_7] = true;
				break;

			case ALLEGRO_KEY_8:
				key[KEY_8] = true;
				break;

			case ALLEGRO_KEY_9:
				key[KEY_9] = true;
				break;
			case ALLEGRO_KEY_BACKSPACE:
				key[KEY_BACKSPACE] = true;
				break;
			}
		}
		else if (ev2.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev2.keyboard.keycode) {
			case ALLEGRO_KEY_0:
				key[KEY_0] = false;
				break;

			case ALLEGRO_KEY_1:
				key[KEY_1] = false;
				break;

			case ALLEGRO_KEY_2:
				key[KEY_2] = false;
				break;

			case ALLEGRO_KEY_3:
				key[KEY_3] = false;
				break;

			case ALLEGRO_KEY_4:
				key[KEY_4] = false;
				break;

			case ALLEGRO_KEY_5:
				key[KEY_5] = false;
				break;

			case ALLEGRO_KEY_6:
				key[KEY_6] = false;
				break;

			case ALLEGRO_KEY_7:
				key[KEY_7] = false;
				break;

			case ALLEGRO_KEY_8:
				key[KEY_8] = false;
				break;

			case ALLEGRO_KEY_9:
				key[KEY_9] = false;
				break;

			case ALLEGRO_KEY_BACKSPACE:
				key[KEY_BACKSPACE] = false;
				break;

			case ALLEGRO_KEY_ENTER:
				doexit = true;
				break;
			}
		}

		if (redraw && al_is_event_queue_empty(event_queue2)) {
			redraw = false;

			al_clear_to_color(al_map_rgb(WHITE));

			al_draw_filled_rectangle(55, 10, 290, 40, al_map_rgb(GRAY));

			al_draw_text(font, al_map_rgb(BLACK), 10, SCREEN_MIDDLE_H, ALLEGRO_ALIGN_LEFT, "Value:");

			al_draw_text(font, al_map_rgb(WHITE), 60, SCREEN_MIDDLE_H, ALLEGRO_ALIGN_LEFT, number);

			al_flip_display();
		}
	}

	fnumber = atof(number);

	printf("%f \n", fnumber);


	al_destroy_timer(timer2);
	al_destroy_display(display2);
	al_destroy_event_queue(event_queue2);

	return fnumber;
}