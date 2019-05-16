#include <utility>

#include <iostream>
#include <vector>

#include <boost/asio.hpp>

class Node {

};

class Authentificator : public Node {

};

class Balancer : public Node {

};

class Daemon : public Node {

};

class Communicator : public Node {

};

/*!
 * @brief Machine
 */
class Domain {
public:
    explicit Domain( boost::asio::ip::address __address ) : address( std::move( __address ) ) {
    }

protected:
    boost::asio::ip::address address;
};

/*!
 * @brief Group of machine
 */
class Segment {
public:
    template<class ... Args>
    Segment( Args ...__domains ) {
        ( domains.push_back( __domains ), ... );
    }
private:
    std::vector<std::shared_ptr<Domain>> domains;
};

/*!
 * @brief Group of segments
 */
class StaticCluster {
public:
    template<class ... Args>
    StaticCluster( Args ...__segments ) {
        ( segments.push_back( __segments ), ... );
    }

    std::size_t size() {
        return segments.size();
    }
protected:
    std::vector<std::shared_ptr<Segment>> segments;
};

int main() {
    StaticCluster cluster( std::make_shared<Segment>(
                                    std::make_shared<Daemon>(),
                                    std::make_shared<Authentificator>(),
                                    std::make_shared<Communicator>(),
                                    std::make_shared<Balancer>()
                                ),
                           std::make_shared<Segment>(
                                   std::make_shared<Daemon>(),
                                   std::make_shared<Authentificator>(),
                                   std::make_shared<Communicator>(),
                                   std::make_shared<Balancer>()
                                ),
                           std::make_shared<Segment>(
                                   std::make_shared<Daemon>(),
                                   std::make_shared<Authentificator>(),
                                   std::make_shared<Communicator>(),
                                   std::make_shared<Balancer>()
                               ) );

    return 0;
}