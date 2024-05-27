#include "shape.h"

const size_t vertex_size = sizeof(Vertex);
const size_t shape_size = sizeof(Shape);
const size_t vertex_ptr_size = sizeof(Vertex*);
const size_t shape_ptr_size = sizeof(Shape*);

Shape * 
alloc_shape(const unsigned int vertexcount){
	Shape * newshape = malloc(shape_size);
	newshape->texId = -1;
	newshape->cntVertex = vertexcount;
	newshape->vertices = malloc(vertexcount * vertex_ptr_size);
	for (unsigned int vtx = 0; vtx < newshape->cntVertex; ++vtx){
		newshape->vertices[vtx] = NULL;//malloc(sizeof(Vertex));
	}

	return newshape;
}

void 
free_shape(Shape *shape){
	for (unsigned int vtx = 0; vtx < shape->cntVertex; ++vtx){
		Vertex * curVertex = shape->vertices[vtx];
		if(curVertex != NULL){
			free(curVertex);
		}
	}
	free(shape->vertices);
	shape->vertices = NULL;
}

bool 
ispoint(const Shape * shape){
	return shape->cntVertex == 1;
}

bool 
isline(const Shape * shape){
	return shape->cntVertex == 2;
}

bool 
istriangle(const Shape * shape){
	return shape->cntVertex == 3;
}

bool 
ispolygon(const Shape * shape){
	return shape->cntVertex > 3;
}

Shape * 
create_shape_point3(const Vec3 *p1){
	Shape * point = alloc_shape(1);
	Vertex ** vertices = point->vertices;
	vertices[0] = malloc(vertex_size);
	vec3_copy_dest(&vertices[0]->vec, p1);
	ColorRGB * color = &vertices[0]->color;
	color->r = 1.0f;
	color->g = 0.0f;
	color->b = 0.0f;
	return point;
}

Shape * 
create_shape_line3(const Vec3 *p1, const Vec3 *p2){
	Shape * line = alloc_shape(2);
	Vertex ** vertices = line->vertices;
	vertices[0] = malloc(vertex_size);
	vertices[1] = malloc(vertex_size);
	vec3_copy_dest(&vertices[0]->vec, p1);
	vec3_copy_dest(&vertices[1]->vec, p2);
	ColorRGB * color = &vertices[0]->color;
	color->r = 1.0f;
	color->g = 0.0f;
	color->b = 0.0f;
	color = &vertices[1]->color;
	color->r = 0.0f;
	color->g = 1.0f;
	color->b = 0.0f;
	return line;
}

Shape *
create_shape_triangle3(const Vec3 *p1, const Vec3 *p2, const Vec3 *p3){
	Shape * triangle = alloc_shape(3);
	Vertex ** vertices = triangle->vertices;
	vertices[0] = malloc(vertex_size);
	vertices[1] = malloc(vertex_size);
	vertices[2] = malloc(vertex_size);
	vec3_copy_dest(&vertices[0]->vec, p1);
	vec3_copy_dest(&vertices[1]->vec, p2);
	vec3_copy_dest(&vertices[2]->vec, p3);
	ColorRGB * color = &vertices[0]->color; 
	color->r = 1.0f;
	color->g = 0.0f;
	color->b = 0.0f;
	color = &vertices[1]->color;
	color->r = 0.0f;
	color->g = 1.0f;
	color->b = 0.0f;
	color = &vertices[2]->color;
	color->r = 0.0f;
	color->g = 0.0f;
	color->b = 1.0f;
	return triangle;
}

Shape * 
create_shape_polygon3(const Vec3 *vecs, size_t cnt_vecs) {
	Shape * polygon = alloc_shape(cnt_vecs);
	Vertex ** vertices = polygon->vertices;

	for( size_t curVec = 0; curVec < cnt_vecs; ++curVec ) {
		vertices[curVec] = malloc(vertex_size);
		vec3_copy_dest(&vertices[curVec]->vec, &vecs[curVec]);
		ColorRGB * color = &vertices[curVec]->color;
		color->r = 1.0f;
		color->g = 0.0f;
		color->b = 0.0f;
	}

	return polygon;
}

Shape * 
copy_triangle3(const Shape *t1){
	Shape * copy = NULL;
	if ( t1->cntVertex == 3 ) {
		copy = create_shape_triangle3(&t1->vertices[0]->vec, &t1->vertices[1]->vec, &t1->vertices[2]->vec);
		crgb_crgb_copy(&copy->vertices[0]->color, &t1->vertices[0]->color);
		crgb_crgb_copy(&copy->vertices[1]->color, &t1->vertices[1]->color);
		crgb_crgb_copy(&copy->vertices[2]->color, &t1->vertices[2]->color);
	}
	return copy;
}

void 
set_shape_color(Shape *shape, const ColorRGB * color){
	Vertex ** vertices = shape->vertices;
	switch(shape->cntVertex) {
		case 3:
			crgb_crgb_copy(&vertices[2]->color, color);
		case 2:
			crgb_crgb_copy(&vertices[1]->color, color);
		case 1:
			crgb_crgb_copy(&vertices[0]->color, color);
			break;
	}
}

void 
mat_mul_shape(Shape *shape, const Mat3 * matrix){
	Vertex ** vertices = shape->vertices;
	switch(shape->cntVertex) {
		case 3:
			mat_vec_mul_3(matrix, &vertices[2]->vec);
		case 2:
			mat_vec_mul_3(matrix, &vertices[1]->vec);
		case 1:
			mat_vec_mul_3(matrix, &vertices[0]->vec);
			break;
	}
}

void 
scale_shape(Shape *shape, const float scalex, const float scaley, const float scalez ){
	Vec3 *vec;
	Vertex ** vertices = shape->vertices;
	switch(shape->cntVertex) {
		case 3:
			vec = &vertices[2]->vec;
			vec->x *= scalex;
			vec->y *= scaley;
			vec->z *= scalez;
		case 2:
			vec = &vertices[1]->vec;
			vec->x *= scalex;
			vec->y *= scaley;
			vec->z *= scalez;
		case 1:
			vec = &vertices[0]->vec;
			vec->x *= scalex;
			vec->y *= scaley;
			vec->z *= scalez;
			break;
	}
}

void 
translate_shape(Shape *shape, const float tx, const float ty, const float tz ){
	Vec3 *vec;
	Vertex ** vertices = shape->vertices;
	switch(shape->cntVertex) {
		case 3:
			vec = &vertices[2]->vec;
			vec->x += tx;
			vec->y += ty;
			vec->z += tz;
		case 2:
			vec = &vertices[1]->vec;
			vec->x += tx;
			vec->y += ty;
			vec->z += tz;
		case 1:
			vec = &vertices[0]->vec;
			vec->x += tx;
			vec->y += ty;
			vec->z += tz;
			break;
	}
}

void shape_set_texture(Shape *shape, unsigned int texID, const Vec2 *vertex_1_texCoords,
					   const Vec2 *vertex_2_texCoords, const Vec2 *vertex_3_texCoords)
{
	Vec2 *vec;
	Vertex ** vertices = shape->vertices;
	shape->texId = (float)texID;

	switch(shape->cntVertex) {
		case 3:
			vec = &vertices[2]->texCoord;
			vec->x = vertex_3_texCoords->x;
			vec->y = vertex_3_texCoords->y;
		case 2:
			vec = &vertices[1]->texCoord;
			vec->x = vertex_2_texCoords->x;
			vec->y = vertex_2_texCoords->y;
		case 1:
			vec = &vertices[0]->texCoord;
			vec->x = vertex_1_texCoords->x;
			vec->y = vertex_1_texCoords->y;
			break;
	}
}

void 
debug_shape(const Shape * shape){
	printf("cnt vertex: %i\n shape vertex:\n", shape->cntVertex);
	for(unsigned int vertex = 0; vertex < shape->cntVertex; ++vertex){
		vec3_print(&shape->vertices[vertex]->vec);
	}
}

Vec3 * 
shape_to_vec3ptr(const Shape * shape) {
	Vec3 *vecptr = malloc(shape->cntVertex * sizeof(Vec3) );
	for(unsigned int vertex = 0; vertex < shape->cntVertex; ++vertex){
		vec3_copy_dest(&vecptr[vertex], &shape->vertices[vertex]->vec); 
	}
	return vecptr;
}
