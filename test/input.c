#include "../src/input.h"
#include "../thirdparty/ctest.h"

CTEST(figure_check, input_circle)
{
    // Given
    char* str = "circle";
    int size = 20;
    Geometry* geo = NULL;
    int row_count = 5;
    // When
    int real = input_processing(str, size, NULL, row_count);
    // Then
    const int exp = -1;

    ASSERT_EQUAL(exp, real);
}
