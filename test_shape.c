#include <stdio.h>
#include <assert.h>
#include "shape.h"

int 
main() {
	#ifdef debug
		printf("Start test shapes\n");
	#endif	
	
	#if 0
		// Test shape allocation
	#endif
	
	shape_t * shape1 = alloc_shape(3);
	assert(shape1->cntVertex == 3);
	assert(shape1->cntVertex != 4);
	free_shape(shape1);
	free(shape1);
	#if 0
		// Test point allocation
	#endif
	vec3_t pData = { 1.f, 2.f, 3.f };
	shape_t * point = create_shape_point3(&pData);
	
	assert(point->cntVertex == 1);
	assert(vec3_equals(&point->vertices[0]->vec, &pData));
	assert(point->vertices[0]->color.r == 1.0f);
	assert(point->vertices[0]->color.g == 0.0f);
	assert(point->vertices[0]->color.b == 0.0f);
	
	free_shape(point);
	free(point);
	#if 0
		// Test line allocation
	#endif
	vec3_t lData = { 1.f, 2.f, 3.f };
	vec3_t lData2 = { 4.f, 5.f, 6.f };
	shape_t * line = create_shape_line3(&lData, &lData2);
	
	assert(line->cntVertex == 2);
	assert(vec3_equals(&line->vertices[0]->vec, &lData));
	assert(vec3_equals(&line->vertices[1]->vec, &lData2));
	assert(line->vertices[0]->color.r == 1.0f);
	assert(line->vertices[0]->color.g == 0.0f);
	assert(line->vertices[0]->color.b == 0.0f);
	assert(line->vertices[1]->color.r == 0.0f);
	assert(line->vertices[1]->color.g == 1.0f);
	assert(line->vertices[1]->color.b == 0.0f);
	
	free_shape(line);
	free(line);
	#if 0
		// Test triangle allocation
	#endif
	vec3_t tData = { 1.f, 2.f, 3.f };
	vec3_t tData2 = { 4.f, 5.f, 6.f };
	vec3_t tData3 = { 7.f, 8.f, 9.f };
	shape_t * triangle = create_shape_triangle3(&tData, &tData2, &tData3);
	
	assert(triangle->cntVertex == 3);
	assert(vec3_equals(&triangle->vertices[0]->vec, &tData));
	assert(vec3_equals(&triangle->vertices[1]->vec, &tData2));
	assert(vec3_equals(&triangle->vertices[2]->vec, &tData3));
	assert(triangle->vertices[0]->color.r == 1.0f);
	assert(triangle->vertices[0]->color.g == 0.0f);
	assert(triangle->vertices[0]->color.b == 0.0f);
	assert(triangle->vertices[1]->color.r == 0.0f);
	assert(triangle->vertices[1]->color.g == 1.0f);
	assert(triangle->vertices[1]->color.b == 0.0f);
	assert(triangle->vertices[2]->color.r == 0.0f);
	assert(triangle->vertices[2]->color.g == 0.0f);
	assert(triangle->vertices[2]->color.b == 1.0f);
	
	#if 0
		// Test copy of triangle
	#endif
	
	shape_t * copy_triangle = copy_triangle3(triangle);
	
	#ifdef debug
		printf("t1 %p und t2 %p\n",triangle, copy_triangle);
	#endif
	assert(copy_triangle != triangle);
	assert(copy_triangle->cntVertex == 3);
	assert(vec3_equals(&copy_triangle->vertices[0]->vec, &tData));
	assert(vec3_equals(&copy_triangle->vertices[1]->vec, &tData2));
	assert(vec3_equals(&copy_triangle->vertices[2]->vec, &tData3));
	assert(copy_triangle->vertices[0]->color.r == 1.0f);
	assert(copy_triangle->vertices[0]->color.g == 0.0f);
	assert(copy_triangle->vertices[0]->color.b == 0.0f);
	assert(copy_triangle->vertices[1]->color.r == 0.0f);
	assert(copy_triangle->vertices[1]->color.g == 1.0f);
	assert(copy_triangle->vertices[1]->color.b == 0.0f);
	assert(copy_triangle->vertices[2]->color.r == 0.0f);
	assert(copy_triangle->vertices[2]->color.g == 0.0f);
	assert(copy_triangle->vertices[2]->color.b == 1.0f);
	
	free_shape(triangle);
	free_shape(copy_triangle);
	free(triangle);
	free(copy_triangle);
	#ifdef debug
		printf("End test shape\n");
	#endif
	return 0;
}