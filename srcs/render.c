#include "../includes/fdf.h"

// Interpolate between two RGB colors
int interpolate_color(int color1, int color2, float t)
{
    // Extract the red, green, and blue components of color1
    int r1 = (color1 >> 16) & 0xFF;
    int g1 = (color1 >> 8) & 0xFF;
    int b1 = color1 & 0xFF;

    // Extract the red, green, and blue components of color2
    int r2 = (color2 >> 16) & 0xFF;
    int g2 = (color2 >> 8) & 0xFF;
    int b2 = color2 & 0xFF;

    // Interpolate each color component separately
    int r = r1 + (int)((r2 - r1) * t); // Interpolate red
    int g = g1 + (int)((g2 - g1) * t); // Interpolate green
    int b = b1 + (int)((b2 - b1) * t); // Interpolate blue

    // Combine the interpolated components to form the final color
    int interpolated_color = ((r << 16) | (g << 8) | b);

    return interpolated_color;
}

// Function to update Bresenham's algorithm state for drawing a line
static void fbresenham(t_bresenham *bresenham, t_draw *line)
{
    // Calculate the error term multiplied by 2
    bresenham->e2 = 2 * bresenham->err;
    // Check if the error term is greater than the negative dy (vertical distance)
    if (bresenham->e2 > -bresenham->dy)
    {
        // Adjust the error term and move the drawing position in the x-direction
        bresenham->err -= bresenham->dy;
        line->p0.x += bresenham->sx;
    }
    // Check if the error term is less than the dx (horizontal distance)
    if (bresenham->e2 < bresenham->dx)
    {
        // Adjust the error term and move the drawing position in the y-direction
        bresenham->err += bresenham->dx;
        line->p0.y += bresenham->sy;
    }
}

// Function to initialize Bresenham's algorithm with line parameters
static void initialize_bresenham(t_bresenham *bresenham, t_draw line)
{
    // Calculate the absolute horizontal and vertical distances
    bresenham->dx = abs(line.p1.x - line.p0.x);
    bresenham->dy = abs(line.p1.y - line.p0.y);

    // Determine the sign of the step in the x and y directions
    if (line.p0.x < line.p1.x)
        bresenham->sx = 1; // Move right
    else
        bresenham->sx = -1; // Move left
    
    if (line.p0.y < line.p1.y)
        bresenham->sy = 1; // Move down
    else
        bresenham->sy = -1; // Move up
    // Initialize the error term
    bresenham->err = bresenham->dx - bresenham->dy;
}


// Function to draw a line using Bresenham's algorithm with color interpolation
void draw_line(t_fdf *fdf, t_draw line, int c1, int c2)
{
    t_bresenham bresenham;
    int color;
    float t;

    // Initialize Bresenham's algorithm state
    initialize_bresenham(&bresenham, line);
    t = 0.0;

    // Loop until the entire line is drawn
    while (line.p0.x != line.p1.x || line.p0.y != line.p1.y)
    {
        // Interpolate color between c1 and c2
        color = interpolate_color(c1, c2, t);

        // Draw a pixel with the interpolated color
        mlx_pixel_put(fdf->mlx, fdf->win, line.p0.x, line.p0.y, color);

        // Update Bresenham's algorithm state for the next step
        fbresenham(&bresenham, &line);

        // Increment the interpolation factor
        t += 1.0 / (sqrt(bresenham.dx * bresenham.dx + bresenham.dy * bresenham.dy) + 1);
    }

    // Draw the last pixel with the interpolated color
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
