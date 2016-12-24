#ifndef SNIFFER_EXCEPTION_HPP_
#define SNIFFER_EXCEPTION_HPP_

#include <exception>
#include <string>

namespace Sniffer {
    namespace Core {
        class SnifferException : public std::exception {
            private:
                std::string message_;

            public:
                SnifferException(const std::string& message)
                    : message_{message}
                {}

                virtual const char* what() const throw() {
                    return message_.c_str();
                }
        };
    }
}

#endif
