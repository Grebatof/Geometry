#include "../src/processing.h"
#include "../thirdparty/ctest.h"

CTEST(figure_check, input_circle)
{
    // Given
    char* str = "circle";
    // When
    int real = figure_check(str);
    // Then
    const int exp = 1;

    ASSERT_EQUAL(exp, real);
}

CTEST(figure_check, input_triangle_error)
{
    // Given
    char* str = "trianglle";
    // When
    int real = figure_check(str);
    // Then
    const int exp = 0;

    ASSERT_EQUAL(exp, real);
}

CTEST(figure_check, input_NULL)
{
    // Given
    char* str = "trianglle";
    // When
    int real = figure_check(NULL);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
