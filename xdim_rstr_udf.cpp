#include "xdim_rstr_udf.h"
#include <any>
using namespace nielsen;

class XdimRstrUdfDemo : public EvaluateHandler {
public:
    XdimRstrUdfDemo() {}

    // Ensure this matches the declaration in EvaluateHandler
    std::optional<long> evaluateAsLong(InputHandler& input) override {
        try {
            if (input.isArgNull(0) || input.isArgNull(1) || input.isArgNull(2)) {
                throw std::invalid_argument("Null argument provided to XDIM_RSTR_UDF");
            }

            int mktrstr = std::any_cast<int>(input.getArg<int>(0));
            int prdcexclchr = std::any_cast<int>(input.getArg<int>(1));
            int prdcrstr = std::any_cast<int>(input.getArg<int>(2));

            if (mktrstr <= 0 || prdcexclchr <= 0 || prdcrstr <= 0) {
                return 1;
            }

            int result1 = mktrstr & prdcexclchr;
            if (result1 == 0) {
                return 1;
            }

            int result2 = result1 & prdcrstr;
            if (result2 == 0) {
                return 1;
            }
            if (result2 >= 1) {
                return std::nullopt;
            }
        } catch (const std::bad_any_cast& e) {
            throw std::runtime_error("Invalid type conversion in XDIM_RSTR_UDF");
        }
        return std::nullopt;
    }
};

extern "C" long xdim_rstr_udf_eval(int value1, int value2, int value3, int* error) {
    // Initialize error to 0 to indicate no error by default
    *error = 0;

    // Check if any input is non-positive
    if (value1 <= 0 || value2 <= 0 || value3 <= 0) {
        return 1;  // Return 1 as specified, if any input is zero or negative
    }

    // First bitwise AND operation
    int result1 = value1 & value2;
    if (result1 == 0) {
        return 1;  // Return 1 if the result of the first AND operation is 0
    }

    // Second bitwise AND operation
    int result2 = result1 & value3;
    if (result2 == 0) {
        return 1;  // Return 1 if the result of the second AND operation is 0
    }

    // If the second result is non-zero, return 0 as a placeholder for null
    return 0;
}
