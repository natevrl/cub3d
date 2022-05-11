#include "../header.h"

void cast_one_ray(t_mlx *root, float ray_angle, size_it id)
{
	ray_angle = normalize_ray(ray_angle);
	int facing_down = ray_angle > 0 && ray_angle < PI;
	int facing_up = !facing_down;
	int faceing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	int facing_left = !faceing_right;

	float xintercept, yintercept;
	float xstep, ystep;

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
    xstep *= (faceing_right && xstep < 0) ? -1 : 1;

    float nextHorzTouchX = xintercept;
    float nextHorzTouchY = yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) 
	{
        float xToCheck = nextHorzTouchX;
        float yToCheck = nextHorzTouchY + (facing_up ? -1 : 0);
        
        if (mapHasWallAt(xToCheck, yToCheck)) 
		{
            // found a wall hit
            horizontal_wall_hit_x = nextHorzTouchX;
            horizontal_wall_hit_y = nextHorzTouchY;
            horizontal_wall_content = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            horizontal_wall_content = TRUE;
            break;
        } 
		else 
		{
            nextHorzTouchX += xstep;
            nextHorzTouchY += ystep;
        }
	}
}

float normalize_ray(float angle)
{
	angle = remainder(angle, DOUBLE_PI);
	if (angle < 0)
	{
		angle = DOUBLE_PI + angle;
	}
	return angle;
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