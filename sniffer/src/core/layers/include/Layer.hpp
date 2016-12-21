#ifndef LAYER_HPP_
#define LAYER_HPP_

#include <vector>
#include <memory>
#include <boost/iterator/indirect_iterator.hpp>

#include "../../../communications/serialization/include/SerializedObject.hpp"
#include "../../include/ReceptionHandler.hpp"
#include "../../../protocols/headers/metadata/include/HeaderMetadata.hpp"

namespace Sniffer {
    namespace Protocols {
        namespace Headers {
            class HeaderFactory;
        }
    }

    namespace Core {
        class SniffedPacket;

        namespace Layers {
            class Layer {
                private:
                    using HeaderMetadata =
                        Sniffer::Protocols::Headers::Metadata::HeaderMetadata;

                    using HeaderMetadataCollection =
                        std::vector<std::unique_ptr<HeaderMetadata>>;

                    Layer* lower_layer_;
                    Layer* upper_layer_;
                    HeaderMetadataCollection supported_headers_;

                protected:
                    ReceptionHandler reception_handler_;

                public:
                    Layer(const SerializationMgr& serializer,
                          const Sniffer::Protocols::Headers::HeaderFactory& hf);

                    virtual void handle_reception(
                            SniffedPacket& packet,
                            Communications::Serialization::SerializedObject acc,
                            int next_header_id) = 0;

                    Layer* get_lower_layer() const;

                    void set_lower_layer(Layer* layer);

                    Layer* get_upper_layer() const;

                    void set_upper_layer(Layer* layer);

                    using SupportedHeadersIterator =
                        boost::indirect_iterator<
                            HeaderMetadataCollection::iterator,
                            const HeaderMetadata>;

                    SupportedHeadersIterator begin();

                    SupportedHeadersIterator end();

                    void set_supported_headers(
                            HeaderMetadataCollection&& headers);

                    virtual ~Layer() {};
            };

        }
    }
}

#endif
