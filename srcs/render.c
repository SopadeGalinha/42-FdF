#include "../includes/fdf.h"


int interpolate_color(int color1, int color2, float t)
{
	int r1 = (color1 >> 16) & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = color1 & 0xFF;
	
	int r2 = (color2 >> 16) & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = color2 & 0xFF;
	
	int r = r1 + (int)((r2 - r1) * t);
	int g = g1 + (int)((g2 - g1) * t);
	int b = b1 + (int)((b2 - b1) * t);
	
	return ((r << 16) | (g << 8) | b);
}

static void fbresenham(t_bresenham *bresenham, t_draw *line)
{
	bresenham->e2 = 2 * bresenham->err;
	if (bresenham->e2 > -bresenham->dy)
	{
		bresenham->err -= bresenham->dy;
		line->p0.x += bresenham->sx;
	}
	if (bresenham->e2 < bresenham->dx)
	{
		bresenham->err += bresenham->dx;
		line->p0.y += bresenham->sy;
	}
}

static void initialize_bresenham(t_bresenham *bresenham, t_draw line)
{
	bresenham->dx = abs(line.p1.x - line.p0.x);
	bresenham->dy = abs(line.p1.y - line.p0.y);
	if (line.p0.x < line.p1.x)
		bresenham->sx = 1;
	else
		bresenham->sx = -1;
	if (line.p0.y < line.p1.y)
		bresenham->sy = 1;
	else
		bresenham->sy = -1;
	bresenham->err = bresenham->dx - bresenham->dy;
}

void draw_line(t_fdf *fdf, t_draw line, int c1, int c2)
{
	t_bresenham bresenham;
	int color;
	float t;

	initialize_bresenham(&bresenham, line);
	t = 0.0;
	while (line.p0.x != line.p1.x || line.p0.y != line.p1.y)
	{
		color = interpolate_color(c1, c2, t);
		mlx_pixel_put(fdf->mlx, fdf->win, line.p0.x, line.p0.y, color);
		fbresenham(&bresenham, &line);
		t += 1.0 / (sqrt(bresenham.dx * bresenham.dx + bresenham.dy * bresenham.dy) + 1);
	}
	color = interpolate_color(c1, c2, t);
	mlx_pixel_put(fdf->mlx, fdf->win, line.p0.x, line.p0.y, color);
}


static void draw_map(t_fdf *fdf, t_points *pts)
{
	t_draw line;
	int i;

	i = 0;
	while (pts[i].x != INT_MIN)
	{
		if (i % fdf->map_size.x != fdf->map_size.x - 1)
		{
			line.p0 = (t_points){pts[i].x, pts[i].y};
			line.p1 = (t_points){pts[i + 1].x, pts[i + 1].y};
			draw_line(fdf, line, fdf->colors[i], fdf->colors[i + 1]);
		}
		if (i + fdf->map_size.x < fdf->map_size.x * fdf->map_size.y)
		{
			line.p0 = (t_points){pts[i].x, pts[i].y};
			line.p1 = (t_points){pts[i + fdf->map_size.x].x,
								pts[i + fdf->map_size.x].y};
			draw_line(fdf, line, fdf->colors[i],
					fdf->colors[i + fdf->map_size.x]);
		}
		i++;
	}
}

static void isometric_projection(t_fdf fdf, t_points *points_to_draw)
{
	while (fdf.coords->x != INT_MIN)
	{
		points_to_draw->x = fdf.coords->x * fdf.zoom + fdf.offset.x;
		points_to_draw->y = -fdf.coords->z * fdf.zoom + fdf.offset.y;
		fdf.coords++;
		points_to_draw++;
	}
	points_to_draw->x = INT_MIN;
}

void render(t_fdf *fdf)
{
	t_points *points_to_draw;

	points_to_draw = malloc(sizeof(t_points) * (fdf->map_size.x * fdf->map_size.y + 1));
	isometric_projection(*fdf, points_to_draw);
	draw_map(fdf, points_to_draw);
	free(points_to_draw);
}
