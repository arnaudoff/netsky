#ifndef INTERFACE_RETRIEVER_EXCEPTION_HPP_
#define INTERFACE_RETRIEVER_EXCEPTION_HPP_

#include <exception>
#include <string>

namespace Sniffer {
    namespace Core {
        class InterfaceRetrieverException : public std::exception {
            private:
                std::string message_;

            public:
                InterfaceRetrieverException(const std::string& message)
                    : message_{message}
                {}

                virtual const char* what() const throw() {
                    return message_.c_str();
                }
        };
    }
}

#endif
