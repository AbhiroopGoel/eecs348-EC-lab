#include <iostream>
#include <string>
#include <iomanip>

const double INVALID_RESULT = -999999.99;

double extractNumeric(const std::string &input) {
    bool hasDigits = false;       // To check if the input contains valid digits
    bool hasDecimal = false;      // To ensure at most one decimal point
    bool hasSign = false;         // To allow optional leading '+' or '-'
    size_t length = input.length();

    if (length == 0 || length > 20) {
        return INVALID_RESULT; // Invalid if empty or exceeds length
    }

    for (size_t i = 0; i < length; ++i) {
        char currentChar = input[i];

        // Handle leading '+' or '-' sign
        if ((currentChar == '+' || currentChar == '-') && i == 0) {
            hasSign = true;
        }
        // Check for digits
        else if (isdigit(currentChar)) {
            hasDigits = true;
        }
        // Handle decimal point
        else if (currentChar == '.' && !hasDecimal) {
            hasDecimal = true;
        }
        // Invalid character detected
        else {
            return INVALID_RESULT;
        }
    }

    // Ensure at least one digit exists and no trailing decimal point
    if (!hasDigits || (input.back() == '.')) {
        return INVALID_RESULT;
    }

    // Conversion logic without std::stod
    double result = 0.0;
    double fractionalPart = 0.0;
    double divisor = 1.0;
    bool isNegative = (input[0] == '-');
    bool parsingFraction = false;

    for (size_t i = (hasSign ? 1 : 0); i < length; ++i) {
        if (input[i] == '.') {
            parsingFraction = true;
        } else if (!parsingFraction) {
            result = result * 10 + (input[i] - '0'); // Accumulate integer part
        } else {
            fractionalPart = fractionalPart * 10 + (input[i] - '0'); // Accumulate fractional part
            divisor *= 10;
        }
    }

    result += fractionalPart / divisor; // Combine integer and fractional parts
    return isNegative ? -result : result;
}

int main() {
    std::string userInput;

    std::cout << "Enter a string (type END to quit): ";

    while (std::getline(std::cin, userInput)) {
        if (userInput == "END") {
            break;
        }

        double extractedValue = extractNumeric(userInput);

        if (extractedValue == INVALID_RESULT) {
            std::cout << "The input is invalid.\n";
        } else {
            std::cout << "The input is: " << std::fixed << std::setprecision(4) << extractedValue << "\n";
        }

        std::cout << "Enter a string (type END to quit): ";
    }

    return 0;
}
