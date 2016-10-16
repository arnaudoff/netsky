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
                    static constexpr auto config_path = "../config/config.";

                public:
                    template<typename U>
                    U get_value(const std::string& object, const std::string& key) {
                        auto resource_path = config_path +
                            FormattingPolicy<Configuration>::get_format_extension();

                        auto configuration =
                            StoragePolicy<Configuration>::read(resource_path);

                        return FormattingPolicy<Configuration>::template
                            get_value<U>(configuration, object, key);
                    }

                    template<typename U>
                    void set_value(
                            const std::string& object,
                            const std::string& key, U value) {
                        auto resource_path = config_path +
                            FormattingPolicy<Configuration>::get_format_extension();

                        auto old_config =
                            StoragePolicy<Configuration>::read(resource_path);

                        auto new_config =
                            FormattingPolicy<Configuration>::template
                            set_value<U>(old_config, object, key, value);

                        StoragePolicy<Configuration>::write(new_config, resource_path);
                    }
        };
    }
}

#endif
