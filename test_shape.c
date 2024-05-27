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
	
	Shape * shape1 = alloc_shape(3);
	assert(shape1->cntVertex == 3);
	assert(shape1->cntVertex != 4);
	free_shape(shape1);
	free(shape1);
	#if 0
		// Test point allocation
	#endif
	Vec3 pData = { 1.f, 2.f, 3.f };
	Shape * point = create_shape_point3(&pData);
	
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
	Vec3 lData = { 1.f, 2.f, 3.f };
	Vec3 lData2 = { 4.f, 5.f, 6.f };
	Shape * line = create_shape_line3(&lData, &lData2);
	
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
	Vec3 tData = { 1.f, 2.f, 3.f };
	Vec3 tData2 = { 4.f, 5.f, 6.f };
	Vec3 tData3 = { 7.f, 8.f, 9.f };
	Shape * triangle = create_shape_triangle3(&tData, &tData2, &tData3);
	
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
	
	Shape * copy_triangle = copy_triangle3(triangle);
	
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

	#if 0
		// Test polygon
	#endif

	Vec3 points[12] = { {1.f, 1.f, .0f} , { 2.5f, 2.f, .0f}, { 4.f, 1.f, .0f}  , { 4.f, 3.f, .0f}, 
						 {4.5f,1.5f, .0f}, { 3.f, 3.5f, .0f}, { 3.5f, 2.f, .0f}, { 2.f, 3.f, .0f},
						 {1.5f,4.f, .0f}, { 1.5f, 2.f, .0f}, { 3.f, 0.5f, .0f}, { 2.0f, .5f, .0f}};
	Shape *polygon = create_shape_polygon3(points, 12);

	#ifdef debug
		debug_shape(polygon);
	#endif

	Vec3 *poly_vec3arr = shape_to_vec3ptr(polygon);

	#ifdef debug
		printf("printing converted shape\n");
		for ( unsigned int cntVec = 0; cntVec < polygon->cntVertex; ++cntVec ) {
			vec3_print(&poly_vec3arr[cntVec]);
		}
	#endif

	free_shape(polygon);
	free(polygon);
	free(poly_vec3arr);

	#ifdef debug
		printf("End test shape\n");
	#endif
	return 0;
}