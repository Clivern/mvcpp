/*
 *  (c) Lewis Maitland 2015
*/
#pragma once

#include <vector>
#include <streambuf>
#include <iostream>
#include <Log/Log.hpp>
#include <Http/Http.hpp>
#include <Exception/Exception.hpp>

using namespace std;

namespace Http {

    /**
     * Response.
     * Class for encapsulating HTTP Responses.
     * This class is used to create HTTP responses from the
     * application. Version and headers can be
     * added to the response object. Piping data into the
     * response object buffers the output to the client.
    */
    class Response {

        HttpVersion version_;
        HttpHeaders headers_;
        ostream& out_;

    public:

        /**
         * Constructor.
         * This constructor builds a response object
         * @param[in] version HttpVersion of the response
         * @param[in] headers Default headers for response objects
         * @param[in] out ostream for writing responses to
        */
        Response( HttpVersion version, HttpHeaders headers, ostream& out ) noexcept;

        /**
         * send.
         * Send will send the headers to the client.
         * @param[in] code Status code to send in the reply
        */
        void send( HttpStatus code );

        /**
         * Operator<<.
         * This operator to the response class is used to pipe the input
         * object directly into the output stream. This operator is used
         * as other objects etc can overload this operator for easy class
         * writing to json.
         * NOTE: If the headers have not been sent they will be sent after the
         * first write.
        */
        template<typename T>
        ostream& operator<<(T in) {
            send( Http::OK );
            return out_ << in;
        }
    };
}