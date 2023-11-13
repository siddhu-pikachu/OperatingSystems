#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>
// all the exceptions come under the following namespace so that
namespace exceptions
{
    class no_arguments : public std::exception {
        virtual const char* what() const noexcept override;
    };

    class file_notfound : public std::exception {
        virtual const char* what() const noexcept override;
    };

    class invalid_arguments : public std::exception {
        virtual const char* what() const noexcept override;
    };

    class invalid_input : public std::exception {
        virtual const char* what() const noexcept override;
    };

    class unsupported_operation : public std::exception {
        virtual const char* what() const noexcept override;
    };
    class outof_bounds : public std::exception {
        virtual const char* what() const noexcept override;
    };

    class invalid_dimensions : public std::exception {
        virtual const char* what() const noexcept override;
    };

    class divideby_zero : public std::exception {
        virtual const char* what() const noexcept override;
    };

    class negative_value : public std::exception {
        virtual const char* what() const noexcept override;
    };

    class nonsquare_matrix : public std::exception {
        virtual const char* what() const noexcept override;
    };

}
#endif //_EXCEPTIONS_H_
