#include "shape.h"

const size_t vertex_size = sizeof(vertex_t);
const size_t shape_size = sizeof(shape_t);
const size_t vertex_ptr_size = sizeof(vertex_t*);
const size_t shape_ptr_size = sizeof(shape_t*);

shape_t * 
alloc_shape(const unsigned int vertexcount){
	shape_t * newshape = malloc(shape_size);
	newshape->texId = -1;
	newshape->cntVertex = vertexcount;
	newshape->vertices = malloc(vertexcount * vertex_ptr_size);
	for (unsigned int vtx = 0; vtx < newshape->cntVertex; ++vtx){
		newshape->vertices[vtx] = NULL;//malloc(sizeof(vertex_t));
	}

	return newshape;
}

void 
free_shape(shape_t *shape){
	for (unsigned int vtx = 0; vtx < shape->cntVertex; ++vtx){
		vertex_t * curVertex = shape->vertices[vtx];
		if(curVertex != NULL){
			free(curVertex);
		}
	}
	free(shape->vertices);
	shape->vertices = NULL;
}

bool 
ispoint(const shape_t * shape){
	return shape->cntVertex == 1;
}

bool 
isline(const shape_t * shape){
	return shape->cntVertex == 2;
}

bool 
istriangle(const shape_t * shape){
	return shape->cntVertex == 3;
}

shape_t * 
create_shape_point3(const vec3_t *p1){
	shape_t * point = alloc_shape(1);
	vertex_t ** vertices = point->vertices;
	vertices[0] = malloc(vertex_size);
	vec3_copy_dest(&vertices[0]->vec, p1);
	cRGB_t * color = &vertices[0]->color;
	color->r = 1.0f;
	color->g = 0.0f;
	color->b = 0.0f;
	return point;
}

shape_t * 
create_shape_line3(const vec3_t *p1, const vec3_t *p2){
	shape_t * line = alloc_shape(2);
	vertex_t ** vertices = line->vertices;
	vertices[0] = malloc(vertex_size);
	vertices[1] = malloc(vertex_size);
	vec3_copy_dest(&vertices[0]->vec, p1);
	vec3_copy_dest(&vertices[1]->vec, p2);
	cRGB_t * color = &vertices[0]->color;
	color->r = 1.0f;
	color->g = 0.0f;
	color->b = 0.0f;
	color = &vertices[1]->color;
	color->r = 0.0f;
	color->g = 1.0f;
	color->b = 0.0f;
	return line;
}

shape_t *
create_shape_triangle3(const vec3_t *p1, const vec3_t *p2, const vec3_t *p3){
	shape_t * triangle = alloc_shape(3);
	vertex_t ** vertices = triangle->vertices;
	vertices[0] = malloc(vertex_size);
	vertices[1] = malloc(vertex_size);
	vertices[2] = malloc(vertex_size);
	vec3_copy_dest(&vertices[0]->vec, p1);
	vec3_copy_dest(&vertices[1]->vec, p2);
	vec3_copy_dest(&vertices[2]->vec, p3);
	cRGB_t * color = &vertices[0]->color; 
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

shape_t * 
copy_triangle3(const shape_t *t1){
	shape_t * copy = NULL;
	if ( t1->cntVertex == 3 ) {
		copy = create_shape_triangle3(&t1->vertices[0]->vec, &t1->vertices[1]->vec, &t1->vertices[2]->vec);
		crgb_crgb_copy(&copy->vertices[0]->color, &t1->vertices[0]->color);
		crgb_crgb_copy(&copy->vertices[1]->color, &t1->vertices[1]->color);
		crgb_crgb_copy(&copy->vertices[2]->color, &t1->vertices[2]->color);
	}
	return copy;
}

void 
set_shape_color(shape_t *shape, const cRGB_t * color){
	vertex_t ** vertices = shape->vertices;
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
mat_mul_shape(shape_t *shape, const mat3_t * matrix){
	vertex_t ** vertices = shape->vertices;
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
scale_shape(shape_t *shape, const float scalex, const float scaley, const float scalez ){
	vec3_t *vec;
	vertex_t ** vertices = shape->vertices;
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
translate_shape(shape_t *shape, const float tx, const float ty, const float tz ){
	vec3_t *vec;
	vertex_t ** vertices = shape->vertices;
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

void 
debug_shape(const shape_t * shape){
	printf("cnt vertex: %i\n shape vertex:\n", shape->cntVertex);
	for(unsigned int vertex = 0; vertex < shape->cntVertex; ++vertex){
		vec3_print(&shape->vertices[vertex]->vec);
	}
}
