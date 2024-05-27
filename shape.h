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
	Vec3 ndc;
	Vec3 raster;
} VertexRenderInfo;

typedef struct {
	Vec3 vec;
	ColorRGB color;
	Vec2 texCoord;
	VertexRenderInfo info;
} Vertex;

typedef struct {
	int texId;
	unsigned int cntVertex;
	Vertex ** vertices;
} Shape;

extern const size_t vertex_size;
extern const size_t vertex_ptr_size;
extern const size_t shape_size;
extern const size_t shape_ptr_size;

#if 0
	/**
		This function allocates and init shape instance with given vertexcount.
	*/
#endif
Shape * alloc_shape(const unsigned int vertexcount);

#if 0
	/**
		This function frees all memory from using shape.
	*/
#endif
void free_shape(Shape *shape);

#if 0
	//checks if shape is a point
#endif
bool ispoint(const Shape * shape);

#if 0
	//checks if shape is a line
#endif
bool isline(const Shape * shape);

#if 0
	//checks if shape is a point
#endif
bool istriangle(const Shape * shape);

#if 0
	//checks if shape is a point
#endif
bool ispolygon(const Shape * shape);

#if 0
	/**
		This function creates a point "shape". You must free the memory by yourself.
	*/
#endif
Shape * create_shape_point3(const Vec3 *p1);

#if 0
	/**
		This function creates a line shape. You must free the memory by yourself.
	*/
#endif
Shape * create_shape_line3(const Vec3 *p1, const Vec3 *p2);

#if 0
	/**
		This function creates a triangle shape. You must free the memory by yourself.
	*/
#endif
Shape * create_shape_triangle3(const Vec3 *p1, const Vec3 *p2, const Vec3 *p3);

#if 0
	/**
		This function creates a polygon shape. You must free the memory by yourself.
	*/
#endif
Shape * create_shape_polygon3(const Vec3 *vecs, size_t cnt_vecs);

#if 0
	/**
		This function creates a new triangle with walues from triangle t1.
		Returns NULL if shape not a type of triangle
	*/
#endif
Shape * copy_triangle3(const Shape *t1);

#if 0
	/**
		set all vertices from shape to color
	*/
#endif
void set_shape_color(Shape *t1, const ColorRGB * color);

#if 0
	/**
		multiplies every vertex coords with given matrix like transform or roation one
	*/
#endif
void mat_mul_shape(Shape *shape, const Mat3 * matrix);

#if 0
	/**
		scales shape
	*/
#endif
void scale_shape(Shape *shape, const float scalex, const float scaley, const float scalez );

#if 0
	/**
		translate shape
	*/
#endif
void translate_shape(Shape *shape, const float tx, const float ty, const float tz );

void shape_set_texture(Shape *shape, unsigned int texID, const Vec2 *vertex_1_texCoords,
					   const Vec2 *vertex_2_texCoords, const Vec2 *vertex_3_texCoords);

#if 0
	/**
		shows detailed shape info
	 */
#endif
void debug_shape(const Shape * shape);

#if 0
	/**
		shows detailed shape info
	 */
#endif
Vec3 * shape_to_vec3ptr(const Shape * shape);

#endif