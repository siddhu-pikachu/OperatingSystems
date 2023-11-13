#include "exceptions.h"

// every exception is described appropriately in its return string respectively
const char* exceptions::no_arguments::what() const noexcept {
    return "No arguments received, idle...";
}

const char* exceptions::file_notfound::what() const noexcept {
    return "File not found,im not a magician!";
}

const char* exceptions::invalid_arguments::what() const noexcept {
    return "Invalid arguments!";
}

const char* exceptions::invalid_input::what() const noexcept {
    return "Invalid input!";
}

const char* exceptions::unsupported_operation::what() const noexcept {
    return "Unsupported operation, i just cant :')";
}

const char* exceptions::outof_bounds::what() const noexcept {
    return "Going out of bounds, even computers can set boundaries +_=";
}

const char* exceptions::invalid_dimensions::what() const noexcept {
    return "Invalid dimensions for matrix!";
}

const char* exceptions::divideby_zero::what() const noexcept {
    return "Cannot divide by zero, really?!";
}

const char* exceptions::negative_value::what() const noexcept {
    return "Value cannot be negative, be positive!";
}

const char* exceptions::nonsquare_matrix::what() const noexcept {
    return "Operation works only on square matrices, love symmetry!";
}