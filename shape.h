#if 0
/**
	This is a simple shape class. 
*/
#endif

#ifndef SHAPE_H
#define SHAPE_H

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "vec.h"
#include "mat.h"
#include "color.h"
#include "utilsmath.h"

typedef struct {
	vec3_t ndc;
	vec3_t raster;
} vertex_render_info_t;

typedef struct {
	vec3_t vec;
	cRGB_t color;
	vec2_t texCoord;
	vertex_render_info_t info;
} vertex_t;

typedef struct {
	int texId;
	unsigned int cntVertex;
	vertex_t ** vertices;
} shape_t;

extern const size_t vertex_size;
extern const size_t vertex_ptr_size;
extern const size_t shape_size;
extern const size_t shape_ptr_size;

#if 0
	/**
		This function allocates and init shape instance with given vertexcount.
	*/
#endif
shape_t * alloc_shape(const unsigned int vertexcount);

#if 0
	/**
		This function frees all memory from using shape.
	*/
#endif
void free_shape(shape_t *shape);

#if 0
	//checks if shape is a point
#endif
bool ispoint(const shape_t * shape);

#if 0
	//checks if shape is a line
#endif
bool isline(const shape_t * shape);

#if 0
	//checks if shape is a point
#endif
bool istriangle(const shape_t * shape);

#if 0
	//checks if shape is a point
#endif
bool ispolygon(const shape_t * shape);

#if 0
	/**
		This function creates a point "shape". You must free the memory by yourself.
	*/
#endif
shape_t * create_shape_point3(const vec3_t *p1);

#if 0
	/**
		This function creates a line shape. You must free the memory by yourself.
	*/
#endif
shape_t * create_shape_line3(const vec3_t *p1, const vec3_t *p2);

#if 0
	/**
		This function creates a triangle shape. You must free the memory by yourself.
	*/
#endif
shape_t * create_shape_triangle3(const vec3_t *p1, const vec3_t *p2, const vec3_t *p3);

#if 0
	/**
		This function creates a polygon shape. You must free the memory by yourself.
	*/
#endif
shape_t * create_shape_polygon3(const vec3_t *vecs, size_t cnt_vecs);

#if 0
	/**
		This function creates a new triangle with walues from triangle t1.
		Returns NULL if shape not a type of triangle
	*/
#endif
shape_t * copy_triangle3(const shape_t *t1);

#if 0
	/**
		set all vertices from shape to color
	*/
#endif
void set_shape_color(shape_t *t1, const cRGB_t * color);

#if 0
	/**
		multiplies every vertex coords with given matrix like transform or roation one
	*/
#endif
void mat_mul_shape(shape_t *shape, const mat3_t * matrix);

#if 0
	/**
		scales shape
	*/
#endif
void scale_shape(shape_t *shape, const float scalex, const float scaley, const float scalez );

#if 0
	/**
		translate shape
	*/
#endif
void translate_shape(shape_t *shape, const float tx, const float ty, const float tz );

void shape_set_texture(shape_t *shape, unsigned int texID, const vec2_t *vertex_1_texCoords,
					   const vec2_t *vertex_2_texCoords, const vec2_t *vertex_3_texCoords);

#if 0
	/**
		shows detailed shape info
	 */
#endif
void debug_shape(const shape_t * shape);

#if 0
	/**
		shows detailed shape info
	 */
#endif
vec3_t * shape_to_vec3ptr(const shape_t * shape);

#endif