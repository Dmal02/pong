
#include <stdio.h>

#include "ww.h"

//step 1 declare sprites
#include "player_one.h"
#include "player_two.h"
#include "backboard.h"
#include "bluescore.h"
#include "redscore.h"
#include "ball.h"

//adding this to allow location of player 2 and ball location
int screen_width = 1024;
int screen_height = 576;
int y_dir = -5;
int x_dir = -5;

int main( int argc, char * argv[] ) {
	
	if(ww_window_create(argc, argv, "Pixarray", 1024, 576)) {
		printf("Closing..\n");
		return 1;
	}
	
	//step 2 declare sprites
	init_player_one();
	init_player_two();
	init_backboard();
	init_bluescore();
	init_redscore();
	init_ball();
	
	
	//object locations
	bluescore->scale = .5;
	redscore->scale = .5;
	backboard->scale = .5;
	
	bluescore->pad_x = (screen_width / 2) - (backboard->width / 2) + 125;
	bluescore->pad_y = 29;
	
	redscore->pad_x = bluescore->pad_x + 108;
	redscore->pad_y = 29;
	
	backboard->pad_x = (screen_width / 2) - (backboard->width / 2) + 100;
		
	//mathing the paddle location
	player_two->pad_x = (screen_width - player_two->width);
		
	//offset to get location of ball
	ball->pad_y = (screen_height / 2)	-	(ball->height / 2);
	ball->pad_x = (screen_width / 2)	-	(ball->width / 2);
	
	while(!ww_window_received_quit_event()) {
		
		//adding movement to paddles
		if (keystate.w == 1 && player_one->pad_y > 0)  {
		player_one->pad_y = player_one->pad_y - 4;
		}
		if (keystate.s == 1 && player_one->pad_y < screen_height - player_one->height) {
		player_one->pad_y = player_one->pad_y + 4;
		}
		if (keystate.up == 1 && player_two->pad_y > 0){
		player_two->pad_y = player_two->pad_y - 4;
		}
		if (keystate.dn == 1 && player_two->pad_y < screen_height - player_two->height) {
		player_two->pad_y = player_two->pad_y + 4;
		}
		
		//ball movement 
		ball->pad_y = ball->pad_y + y_dir;
		ball->pad_x = ball->pad_x + x_dir;
		
		//keep ball on screen
		if (ball->pad_y > (screen_height - ball->height) || ball->pad_y <= 0) {
			y_dir = y_dir * -1;	
		}
		
		
		//**paddle bounce**
		if (ball->pad_x <= player_one->pad_x + player_one->width && 
			ball->pad_y <= player_one->pad_y + player_one->height && 
			ball->pad_y > player_one->pad_y) {
		
				x_dir = x_dir * -1;
				ball->pad_x = player_one->width + 1;	
				
		}
		
		if (ball->pad_x >= player_two->pad_x - player_two->width && 
			ball->pad_y <= player_two->pad_y + player_two->height && 
			ball->pad_y > player_two->pad_y) {
				
				x_dir = x_dir * -1;
				
			
		}
		
		//scoreboard
		if (ball->pad_x > screen_width) {
			bluescore->active_animation = bluescore->active_animation + 1; 
				if (bluescore->active_animation == 10) {
					printf ("Blue Wins!!!") ;
					ww_window_send_quit_event();
			}
		}	
		
		if (ball->pad_x < 0) {
			redscore->active_animation = redscore->active_animation + 1; 
				if (redscore->active_animation == 10) {
					printf ("Red Wins!!!") ;
					ww_window_send_quit_event();
			}
		
		}
		
		//respawn ball
		if (ball->pad_x < 0 || ball->pad_x > screen_width) {
			ball->pad_x = (screen_width/2) - (ball->width/2);
			ball->pad_y = (screen_height/2) - (ball->height/2);
			x_dir = x_dir * -1;
			
		}	
	
		
		//portal pong
		//if (player_one->pad_y > screen_height) {
			//player_one = 0;
		
		
		//step 3 add sprites to game
		ww_draw_sprite (player_one);
		ww_draw_sprite (player_two);
		ww_draw_sprite (backboard);
		ww_draw_sprite (bluescore);
		ww_draw_sprite (redscore);
		ww_draw_sprite (ball);
		
		ww_window_update_events();
		ww_window_update_buffer();
	}
	
	ww_window_destroy();
	return 0;
}
