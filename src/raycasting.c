#include "../header.h"

#include <float.h>


float normalize_ray(float angle)
{
	angle = remainder(angle, DOUBLE_PI);
	if (angle < 0)
	{
		angle = DOUBLE_PI + angle;
	}
	return angle;
}

float distanceBetweenPoints(float x1, float y1, float x2, float y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void cast_one_ray(t_mlx *root, float ray_angle, size_t id)
{
	ray_angle = normalize_ray(ray_angle);
	int facing_down = ray_angle > 0 && ray_angle < PI;
	int facing_up = !facing_down;
	int facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	int facing_left = !facing_right;

	float xintercept, yintercept;
	float xstep, ystep;

    // HORIZONTAL PART
	int found_horrizontal_wall = FALSE;
	float horizontal_wall_hit_x = 0;
	float horizontal_wall_hit_y = 0;
	float horizontal_wall_content = 0;


	  // Find the y-coordinate of the closest horizontal grid intersection
    yintercept = floor(root->player->y / TILE_SIZE) * TILE_SIZE;
    yintercept += facing_down ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    xintercept = root->player->x + (yintercept - root->player->y) / tan(ray_angle);

    // Calculate the increment xstep and ystep
    ystep = TILE_SIZE;
    ystep *= facing_up ? -1 : 1;

    xstep = TILE_SIZE / tan(ray_angle);
    xstep *= (facing_left && xstep > 0) ? -1 : 1;
    xstep *= (facing_right && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) 
	{
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (facing_up ? -1 : 0);
        
        if (there_is_wall(root, xToCheck, yToCheck)) 
		{
            // found a wall hit
            horizontal_wall_hit_x = nextHorzTouchX;
            horizontal_wall_hit_y = nextHorzTouchY;
            horizontal_wall_content = 1;
            found_horrizontal_wall = TRUE;
            break;
        } 
		else 
		{
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
	}

    // VERTICAL PART
    int found_vertical_wall = FALSE;
	float vertical_wall_hit_x = 0;
	float vertical_wall_hit_y = 0;
	float vertical_wall_content = 0;


	  // Find the x-coordinate of the closest vertical grid intersection
    xintercept = floor(root->player->y / TILE_SIZE) * TILE_SIZE;
    xintercept += facing_right ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    yintercept = root->player->y + (xintercept - root->player->x) / tan(ray_angle);

    // Calculate the increment xstep and ystep
    xstep = TILE_SIZE;
    xstep *= facing_left ? -1 : 1;

    ystep = TILE_SIZE / tan(ray_angle);
    ystep *= (facing_up && ystep > 0) ? -1 : 1;
    ystep *= (facing_down && ystep < 0) ? -1 : 1;

    float nextVertTouchX = xintercept;
    float nextVertTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) 
	{
        float xToCheck = nextVertTouchX;
        float yToCheck = nextVertTouchY + (facing_left ? -1 : 0);
        
        if (there_is_wall(root, xToCheck, yToCheck)) 
		{
            // found a wall hit
            vertical_wall_hit_x = nextVertTouchX;
            vertical_wall_hit_y = nextVertTouchY;
            vertical_wall_content = 1;
            found_vertical_wall = TRUE;
            break;
        } 
		else 
		{
            nextVertTouchX += xstep;
            nextVertTouchY += ystep;
        }
	}

        // Calculate both horizontal and vertical hit distances and choose the smallest one
    float horzHitDistance = found_horrizontal_wall
        ? distanceBetweenPoints(root->player->x, root->player->y, horizontal_wall_hit_x, horizontal_wall_hit_y)
        : FLT_MAX;
    float vertHitDistance = found_vertical_wall
        ? distanceBetweenPoints(root->player->x, root->player->y, vertical_wall_hit_x, vertical_wall_hit_y)
        : FLT_MAX;

    if (vertHitDistance < horzHitDistance) 
    {
        root->rays[id]->distance = vertHitDistance;
        root->rays[id]->wall_hit_x = vertical_wall_hit_x;
        root->rays[id]->wall_hit_y = vertical_wall_hit_y;
        root->rays[id]->wallHitContent = vertical_wall_content;
        root->rays[id]->was_hit_vertical = TRUE;
    } 
    else 
    {
        root->rays[id]->distance = horzHitDistance;
        root->rays[id]->wall_hit_x = horizontal_wall_hit_x;
        root->rays[id]->wall_hit_y = horizontal_wall_hit_y;
        root->rays[id]->wallHitContent = horizontal_wall_content;
        root->rays[id]->was_hit_vertical = FALSE;
    }
    root->rays[id]->ray_angle = ray_angle;
    root->rays[id]->is_ray_facing_down = facing_down;
    root->rays[id]->is_ray_facing_up = facing_up;
    root->rays[id]->is_ray_facing_left = facing_left;
    root->rays[id]->is_ray_facing_right = facing_right;
}

void raycast(t_mlx *root) 
{
    float ray_angle;
	size_t id;

	ray_angle = root->player->rotation_angle - (FOV_ANGLE / 2);
	id = -1;
	while (++id < NUMBER_OF_RAYS)
	{
        cast_one_ray(root, ray_angle, id);
        ray_angle += FOV_ANGLE / NUMBER_OF_RAYS;
    }
}


// dessinge toutes les rays : du player jusqu'au premier mur touche
void render_rays(t_mlx *root) 
{
    float x = root->player->x;
    float y = root->player->y;
    for (int i = 0; i < NUMBER_OF_RAYS; i++) 
    {
        while (x < root->rays[i]->wall_hit_x && y < root->rays[i]->wall_hit_y)
		    mlx_pixel_put(root->mlx, root->mlx_win, root->player->x + x, root->player->y + y, 0x00FF0000);
    }
}