#include <stdio.h>
#include <iostream>
#include <Http/Http.hpp>
#include <Http/Response.hpp>
#include <Http/Request.hpp>
#include <Routing/Route.hpp>
#include <Routing/Router.hpp>

#define ITERATIONS 100000

int main() {

    Routing::Router router({
        Routing::Route( Http::GET,  "/api/test/index",       []( Http::Request& request, Http::Response& response ){} ),
        Routing::Route( Http::POST, "/api/test/{id}",        []( Http::Request& request, Http::Response& response ){} ),
        Routing::Route( Http::POST, "/api/test/{id}/{name}", []( Http::Request& request, Http::Response& response ){} )
    });

    for(int i=0; i< ITERATIONS; i++) {
        ostringstream output;
        istringstream input(
            "POST /api/test/hello?some=parameters&to=test&parsing=ability&empty&ones=aswell HTTP/1.1\r\n"
            "Header: test\r\n"
            "Another: Header\r\n"
            "Header1: This is a very very very very long header that should test the ability to parse the longer strings\r\n"
            "\r\n"
        );
        Http::Request  request( input );
        Http::Response response( Http::HTTP1_1, {
            { "CARPSESSION", "12345678" },
            { "Content-type", "application/json" }
        }, output );
        router.handleRequest( request, response );
    }
    return 0;
}