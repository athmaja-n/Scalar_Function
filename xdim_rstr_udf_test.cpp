#include "xdim_rstr_udf.h"
#include <iostream>
using namespace nielsen;

void compareAsLong(long actual, long expected, int error) {
    if (!error && actual == expected) {
        std::cout << "TEST PASSED - actual: " << actual << " matches expected: " << expected << "\n";
    } else {
        std::cerr << "TEST FAILED - actual: " << actual << " doesn't match expected: " << expected << " or error occurred\n";
    }
}

void printException(const std::exception& e) {
    std::cerr << "TEST FAILED - Unexpected exception: " << e.what() << "\n";
}

int main() {
    try {
        int error = 0;
        long result;

        // Tests for UDF XDIM_RSTR_UDF
        result = xdim_rstr_udf_eval(5, 4, 0, &error);
        compareAsLong(result, 1, error);

        result = xdim_rstr_udf_eval(0, 0, 0, &error);
        compareAsLong(result, 1, error);

        result = xdim_rstr_udf_eval(1, 1, 1, &error);
        compareAsLong(result, 0, error);  // 0 indicates no value was returned (equivalent to nullopt).

        // Simulating invalid (null) inputs by using a designated "invalid" value, e.g., -1
        result = xdim_rstr_udf_eval(-1, 1, 1, &error);  // Input includes -1, expect 1
        compareAsLong(result, 1, error);  // Expect 1, not 0

        result = xdim_rstr_udf_eval(1, -1, 1, &error);  // Input includes -1, expect 1
        compareAsLong(result, 1, error);  // Expect 1, not 0

        result = xdim_rstr_udf_eval(1, 1, -1, &error);  // Input includes -1, expect 1
        compareAsLong(result, 1, error);  // Expect 1, not 0

        // Tests for another UDF can go here if implemented similarly.

    } catch (const std::exception& e) {
        printException(e);
    }

    return 0;
}
