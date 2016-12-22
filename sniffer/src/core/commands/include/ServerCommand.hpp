#ifndef SERVER_COMMAND_HPP_
#define SERVER_COMMAND_HPP_

#include <string>
#include <vector>
#include <map>

#include "../../include/Server.hpp"
#include "../../serialization/include/SerializedObject.hpp"

namespace Sniffer {
    namespace Communications {
        namespace Commands {
            class ServerCommand {
                protected:
                    using Server = Sniffer::Communications::Server;

                    std::string name_;

                    Server* server_;

                    SerializationMgr serializer_;

                public:
                    ServerCommand(const std::string& name, Server* server,
                            const SerializationMgr& serializer)
                        : name_{name}, server_{server}, serializer_{serializer}
                    {}

                    std::string get_name() const {
                        return name_;
                    }

                    bool matches(const std::string& data) const {
                        Serialization::SerializedObject data_obj { data };
                        return serializer_.object_exists(data_obj, get_name());
                    }

                    virtual std::map<std::string, std::vector<std::string>>
                        parse(const std::string& data) const = 0;

                    virtual void execute(const ConnectionData& con_data,
                            std::map<std::string, std::vector<std::string>> args) = 0;

                    virtual ~ServerCommand() {};
            };
        }
    }
}

#endif
