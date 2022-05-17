#include "../header.h"

float normalize_ray(float angle)
{
	angle = remainder(angle, DOUBLE_PI);
	if (angle < 0)
	{
		angle = DOUBLE_PI + angle;
	}
	return angle;
}

float distance_between_points(float x1, float y1, float x2, float y2) 
{
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

void init_ray_direction(t_direction *direction, float ray_angle)
{
    direction->found_wall = FALSE;
	direction->wall_content = 0;
	direction->wall_hit_x = 0;
	direction->wall_hit_y = 0;
    direction->facing_down = (ray_angle > 0 && ray_angle < PI);
	direction->facing_up = !direction->facing_down;
	direction->facing_right = ray_angle < 0.5 * PI || ray_angle > 1.5 * PI;
	direction->facing_left = !direction->facing_right;
}

void calcul_horizontal_rays(t_mlx *root, t_direction *horz, float ray_angle)
{
	  // Find the y-coordinate of the closest horizontal grid intersection
    horz->yintercept = floor(root->player->y / TILE_SIZE) * TILE_SIZE;
    horz->yintercept += horz->facing_down ? TILE_SIZE : 0;

    // Find the x-coordinate of the closest horizontal grid intersection
    horz->xintercept = root->player->x + (horz->yintercept - root->player->y) / tan(ray_angle);

    // Calculate the increment xstep and ystep
    horz->ystep = TILE_SIZE;
    if (horz->facing_up)
        horz->ystep *= -1;
    horz->xstep = TILE_SIZE / tan(ray_angle);
    if (horz->facing_left && horz->xstep > 0)
        horz->xstep *= -1;
    if ((horz->facing_right && horz->xstep < 0))
        horz->xstep *= -1;

    horz->next_touch_x = horz->xintercept;
    horz->next_touch_y = horz->yintercept;

    // Increment xstep and ystep until we find a wall
    while ((horz->next_touch_x >= 0 && horz->next_touch_x <= WINDOW_WIDTH) && ( horz->next_touch_y >= 0 &&  horz->next_touch_y <= WINDOW_HEIGHT)) 
	{
        horz->x_to_check = horz->next_touch_x;
        horz->y_to_check = horz->next_touch_y + (horz->facing_up ? -1 : 0);
        
        if (there_is_wall(root, horz->x_to_check, horz->y_to_check)) 
		{
            // found a wall hit
            horz->wall_hit_x = horz->next_touch_x;
            horz->wall_hit_y =  horz->next_touch_y;
            horz->wall_content = root->map[(int)floor(horz->y_to_check / TILE_SIZE)][(int)floor(horz->x_to_check / TILE_SIZE)];
            printf("%d\n", horz->wall_content);
            horz->found_wall = TRUE;
            break;
        }
		else 
		{
             horz->next_touch_x += horz->xstep;
             horz->next_touch_y += horz->ystep;
        }
	}
}

void calcul_vertical_rays(t_mlx *root, t_direction *vert, float ray_angle)
{

	  // Find the x-coordinate of the closest vertical grid intersection
    vert->xintercept = floor(root->player->x / TILE_SIZE) * TILE_SIZE;
    vert->xintercept += vert->facing_right ? TILE_SIZE : 0;

    // Find the y-coordinate of the closest vertical grid intersection
    vert->yintercept = root->player->y + (vert->xintercept - root->player->x) * tan(ray_angle);

    // Calculate the increment xstep and ystep
    vert->xstep = TILE_SIZE;
    vert->xstep *= vert->facing_left ? -1 : 1;

    vert->ystep = TILE_SIZE * tan(ray_angle);
    vert->ystep *= (vert->facing_up && vert->ystep > 0) ? -1 : 1;
    vert->ystep *= (vert->facing_down && vert->ystep < 0) ? -1 : 1;

    float nextVertTouchX = vert->xintercept;
    float nextVertTouchY = vert->yintercept;

    // Increment xstep and ystep until we find a wall
    while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT) 
	{
        float xToCheck = nextVertTouchX + (vert->facing_left ? -1 : 0);
        float yToCheck = nextVertTouchY;
        if (there_is_wall(root, xToCheck, yToCheck)) 
		{
            // found a wall hit
            vert->wall_hit_x = nextVertTouchX;
            vert->wall_hit_y = nextVertTouchY;
            vert->wall_content = root->map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
            vert->found_wall = TRUE;
            break;
        } 
		else 
		{
            nextVertTouchX += vert->xstep;
            nextVertTouchY += vert->ystep;
        }
	}

}

// Calculate both horizontal and vertical hit distances and choose the smallest one
void calcul_hit_distance(t_mlx *root, t_direction *horz, t_direction *vert)
{
    if (horz->found_wall)
        horz->hit_distance = distance_between_points(root->player->x, root->player->y, horz->wall_hit_x, horz->wall_hit_y);
    else
        horz->hit_distance = FLT_MAX;
    if (vert->found_wall)
        vert->hit_distance = distance_between_points(root->player->x, root->player->y, vert->wall_hit_x, vert->wall_hit_y);
    else
        vert->hit_distance = FLT_MAX;
}

void find_smallest_hit_distance(t_rays *rays, t_direction *horz, t_direction *vert)
{
    rays->distance = horz->hit_distance;
    rays->wall_hit_x = horz->wall_hit_x;
    rays->wall_hit_y = horz->wall_hit_y;
    rays->wall_hit_content = horz->wall_content;
    rays->was_hit_vertical = FALSE;
    if (vert->hit_distance < horz->hit_distance) 
    {
        rays->distance = vert->hit_distance;
        rays->wall_hit_x = vert->wall_hit_x;
        rays->wall_hit_y = vert->wall_hit_y;
        rays->wall_hit_content = vert->wall_content;
        rays->was_hit_vertical = TRUE;
    } 
}



void cast_one_ray(t_mlx *root, float ray_angle, t_rays *rays)
{
    t_direction vert;
    t_direction horz;

	ray_angle = normalize_ray(ray_angle);
    init_ray_direction(&horz, ray_angle);
    calcul_horizontal_rays(root, &horz, ray_angle);
    init_ray_direction(&vert, ray_angle);
    calcul_vertical_rays(root, &vert, ray_angle);
    calcul_hit_distance(root, &horz, &vert);
    find_smallest_hit_distance(rays, &horz, &vert);
    rays->ray_angle = ray_angle;
    rays->is_ray_facing_down = vert.facing_down;
    rays->is_ray_facing_up = vert.facing_up;
    rays->is_ray_facing_left = vert.facing_left;
    rays->is_ray_facing_right = vert.facing_right;
}

// ray_angle = root->player->rotation_angle - (FOV_ANGLE / 2);
// ray_angle += FOV_ANGLE / NUMBER_OF_RAYS;
void raycast(t_mlx *root) 
{
    float ray_angle;
	int id;

	id = 0;
	ray_angle = root->player->rotation_angle + atan((id - NUMBER_OF_RAYS / 2) / ((WINDOW_WIDTH / 2) / tan((120 * (PI / 180)) / 2)));
	root->rays = malloc(sizeof(t_rays) * NUMBER_OF_RAYS + 1);
	while (id < NUMBER_OF_RAYS)
	{
        cast_one_ray(root, ray_angle, &root->rays[id]);
    	ray_angle = root->player->rotation_angle + atan((id - NUMBER_OF_RAYS / 2) / ((WINDOW_WIDTH / 2) / tan((120 * (PI / 180)) / 2)));
        id++;
    }
}