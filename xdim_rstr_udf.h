#ifndef XDIM_RSTR_UDF_H
#define XDIM_RSTR_UDF_H

#include <vector>
#include <string>
#include <any>
#include <stdexcept>
#include <optional>
#include <cmath> // Include cmath for std::isnan
#include <typeinfo>

namespace nielsen {

class InputHandler {
private:
    std::vector<std::any> inputArgs;  // Holds any type of input arguments.

public:
    InputHandler() {}

    template<typename T>
    void addInputArg(std::optional<T> element) {
        if (element.has_value()) {
            inputArgs.push_back(*element);  // Store the value if present.
        } else {
            inputArgs.push_back(std::any());  // Store an empty any object to represent nullopt.
        }
    }

    template<typename T>
    T getArg(int idx) {
        if (idx < 0 || idx >= inputArgs.size()) {
            throw std::out_of_range("Index out of range for inputArgs.");
        }
        const std::any& storedAny = inputArgs[idx];
        if (storedAny.has_value()) {
            try {
                return std::any_cast<T>(storedAny);
            } catch (const std::bad_any_cast&) {
                throw std::invalid_argument("Failed to convert argument at index " + std::to_string(idx) + " to the requested type.");
            }
        } else {
            throw std::invalid_argument("Null value encountered at index " + std::to_string(idx));
        }
    }

    bool isArgNull(int idx) {
        if (idx < 0 || idx >= inputArgs.size()) {
            throw std::out_of_range("Index out of range for inputArgs.");
        }
        return !inputArgs[idx].has_value();
    }

    size_t inputArgsMaxSize() const {
        return inputArgs.size();
    }
};

class EvaluateHandler {
public:
    virtual std::optional<long> evaluateAsLong(InputHandler& input) = 0;  // Pure virtual function for evaluating as long.
};

} // namespace nielsen

// Declare the C linkage for function available to C and C++ code
extern "C" {
    long xdim_rstr_udf_eval(int value1, int value2, int value3, int* error);
}

#endif // XDIM_RSTR_UDF_H
