#ifndef CONFIGURATION_MANAGER_HPP_
#define CONFIGURATION_MANAGER_HPP_

#include <string>
#include <memory>

#include "Configuration.hpp"

namespace Sniffer {
    namespace Utils {
        template<
            template <class> class StoragePolicy,
            template <class> class FormattingPolicy
        >
        class ConfigurationManager :
            public StoragePolicy<Configuration>,
            public FormattingPolicy<Configuration> {
                private:
                    std::string resource_;

                public:
                    ConfigurationManager(const std::string& resource)
                        : resource_{resource}
                    {}

                    template<typename U>
                    U get_value(const std::string& object, const std::string& key) {
                        auto configuration =
                            StoragePolicy<Configuration>::read(resource_);

                        return FormattingPolicy<Configuration>::template
                            get_value<U>(configuration, object, key);
                    }

                    template<typename U>
                    void set_value(
                            const std::string& object,
                            const std::string& key, U value) {
                        auto old_config =
                            StoragePolicy<Configuration>::read(resource_);

                        auto new_config =
                            FormattingPolicy<Configuration>::template
                            set_value<U>(old_config, object, key, value);

                        StoragePolicy<Configuration>::write(new_config, resource_);
                    }
        };
    }
}

#endif
