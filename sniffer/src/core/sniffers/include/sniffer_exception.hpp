#include <exception>
#include <string>

namespace Sniffer {
    namespace Core {
        namespace Sniffers {
            class sniffer_exception : public std::exception {
                private:
                    std::string message_;

                public:
                    sniffer_exception(const std::string& message)
                        : message_{message}
                    {}

                    virtual const char* what() const throw() {
                        return message_.c_str();
                    }
            };
        }
    }
}
