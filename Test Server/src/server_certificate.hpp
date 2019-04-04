//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_EXAMPLE_COMMON_SERVER_CERTIFICATE_HPP
#define BOOST_BEAST_EXAMPLE_COMMON_SERVER_CERTIFICATE_HPP

#include <boost/asio/buffer.hpp>
#include <boost/asio/ssl/context.hpp>
#include <cstddef>
#include <memory>

/*  Load a signed certificate into the ssl context, and configure
    the context for use with a server.
    For this to work with the browser or operating system, it is
    necessary to import the "Beast Test CA" certificate into
    the local certificate store, browser, or operating system
    depending on your environment Please see the documentation
    accompanying the Beast certificate for more details.
*/
inline
void
load_server_certificate(boost::asio::ssl::context& ctx)
{
    /*
        The certificate was generated from CMD.EXE on Windows 10 using:
        winpty openssl dhparam -out dh.pem 2048
        winpty openssl req -newkey rsa:2048 -nodes -keyout key.pem -x509 -days 10000 -out cert.pem -subj "//C=US\ST=CA\L=Los Angeles\O=Beast\CN=www.example.com"
    */

    std::string const cert =
        "-----BEGIN CERTIFICATE-----\n"
        "MIIDijCCAnKgAwIBAgIJAICzEzgaoB7iMA0GCSqGSIb3DQEBCwUAMFoxCzAJBgNV\n"
        "BAYTAlVTMQswCQYDVQQIDAJDQTEUMBIGA1UEBwwLTG9zIEFuZ2VsZXMxDjAMBgNV\n"
        "BAoMBUJlYXN0MRgwFgYDVQQDDA93d3cuZXhhbXBsZS5jb20wHhcNMTkwNDA0MTQz\n"
        "NDA5WhcNNDYwODIwMTQzNDA5WjBaMQswCQYDVQQGEwJVUzELMAkGA1UECAwCQ0Ex\n"
        "FDASBgNVBAcMC0xvcyBBbmdlbGVzMQ4wDAYDVQQKDAVCZWFzdDEYMBYGA1UEAwwP\n"
        "d3d3LmV4YW1wbGUuY29tMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA\n"
        "trCOU8GV9xGXxpDWEVOV9YZzyeKbqv+m9lFZ1cPGSwip+aWBwgNzcRkGIcoLkf2g\n"
        "NI/tmfEIqPGHey6svmHo//cDyosHWc5GGxVSee1QmZR5rbQ3Mco90e0WPOIfM0YE\n"
        "qxAjadU5A/khowJoopB0TBeT6IFwnSgwvTbmXkTbtCvA4wqLPgrmfBRJE6O83ftS\n"
        "RfyC5oLB0ZbxPddrPkz7fU291ayk2n227VwPwCw0k4F/gWGo9MT6se0+z9sBKZDg\n"
        "fSeQBJKfzsew4YHxql+4s0hpaW3mSgbYmE4Bij039dNJ0I5NNnDImqL+WWsW42FZ\n"
        "HSCIUD3njbPbbxP0aJDF+QIDAQABo1MwUTAdBgNVHQ4EFgQUNVkUj0BA0Fvk2axJ\n"
        "xO1foH+uHucwHwYDVR0jBBgwFoAUNVkUj0BA0Fvk2axJxO1foH+uHucwDwYDVR0T\n"
        "AQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAdh9jFEWOHOumEYr4PF3ZZty3\n"
        "rRrk735JkJGrVE5mLdJvNF48JXhZrv3nIVLyjScaeZvG8NqiuKrfqMUntzDdu8mK\n"
        "r4TXsQ4cX4p7+tmLHxJfPmWTW42Tf6mmAY4oAtB9MzvoO1GIc0+kT1qZUNWfF38o\n"
        "UeeVJB8sfgLMNN2Md1rw9OTerSl50QBUZcJmbpFGvtkzx+f1xLLANoa/VPo4T73U\n"
        "YCdgWPCYIrF/Bc+by6Li7Hk2phuCfwEnYDMPFin/0idcsZAe/iq4hmSPJZ0IeUQS\n"
        "SdSRMYMw4Hk/eI0JAV08ErIg/e7lu3cVPVrE0uUAxjwdfjsSTmnZxVv9u2I19g==\n"
        "-----END CERTIFICATE-----\n";

    std::string const key =
        "-----BEGIN PRIVATE KEY-----\n"
        "MIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQC2sI5TwZX3EZfG\n"
        "kNYRU5X1hnPJ4puq/6b2UVnVw8ZLCKn5pYHCA3NxGQYhyguR/aA0j+2Z8Qio8Yd7\n"
        "Lqy+Yej/9wPKiwdZzkYbFVJ57VCZlHmttDcxyj3R7RY84h8zRgSrECNp1TkD+SGj\n"
        "AmiikHRMF5PogXCdKDC9NuZeRNu0K8DjCos+CuZ8FEkTo7zd+1JF/ILmgsHRlvE9\n"
        "12s+TPt9Tb3VrKTafbbtXA/ALDSTgX+BYaj0xPqx7T7P2wEpkOB9J5AEkp/Ox7Dh\n"
        "gfGqX7izSGlpbeZKBtiYTgGKPTf100nQjk02cMiaov5ZaxbjYVkdIIhQPeeNs9tv\n"
        "E/RokMX5AgMBAAECggEBAINb8grRUFZlpP9W10WAF3yCX7FTKmFLD69fETw+V89N\n"
        "/IIP+nwZZSF2P8197NHdTxtcPhkJkhOAD82H4xfFaPbbkzNIwlFVm10P+MzI0cKM\n"
        "Wu2GfoVjiQ3v7qR6ZrrEZsjlgsEvWp67vO7r5Xa2bZjk/yoYIHQwGNOErSItWthx\n"
        "wIYyWhI7UNjVCj1NXjC9eoUJHLQ5Qas6lgAZJGoFiw4g6XJM/g2JQWYP3MzuBQg8\n"
        "S8f+xBN1s6qfZhoWfhuaHGZPvl2926c1+hYT1d/aLnctbUzs8BqTFHYjraIODFer\n"
        "WfZbPvR9IiieMo3VbwMDgUVB9G9GtVE3uTvLe4/JDZ0CgYEA8aODr2O/bagZHamQ\n"
        "1TtRPEuIeGgttGIh1VxNvPSWD04vT24EnNVGcYOh/CBi6QgQngW+Oz3mEEF1nkrU\n"
        "wIOx+KmSosK5bnLw47gcjKcEjQSSTiSCunRQFCwehSTYhJ8dhQWrviDxtydOlkcM\n"
        "anUSxbu/lXe2U8rWKImiAesv5K8CgYEAwYwkr1tLhqBDcyfBQXfYtPoD5yGEQcEI\n"
        "KDQu3IS2dHknhxmuFNESfMe96xItCaVecUbR3EyHbFd4udU2MEuaAmqu3R1GZYhx\n"
        "UamNI8IuWDeGvLaKPMKOwCglnx9lal0/QjzyUTKES9X+l6Z09t2miILU1Th8FB90\n"
        "FNOnqEYPedcCgYBWv8U+6iiHTZn2tDFy2+DGLLfJwlzmLXTIDGM8OvLEe+UwNuch\n"
        "BtBLYF5/DYF095g/owAwdIBrxZRcR7EpjB4Qj5A9Lnsz07/3gNl/BVb06Xc85o6o\n"
        "MamuFEjAtAGnWxhV8Ts+/sTIZCwqd0dV0MH0ivq0xk2Gt4M6+m5XEgAXsQKBgHBb\n"
        "R8yYhg6gKKfH81NrHF1rKirZ9Soqwe585JtVW4nf70dpa/pfqIjRd3noMkcAPgQq\n"
        "ZZeqwY7udIIEuRFuQfiXL+3imcRFYetTL0EL79V8XnZczYEaPL5mT/jAxCHsAdYV\n"
        "BWKHne9cShCFLC9HWu6ybJVe1gDkhYG1oQV5rnA/AoGAZVgXXuPf5Klo3lCZAkZ+\n"
        "9IWfblWzxavQkJPy/8JZkE2Ozqfml8z5cvjwGqQdY0v8bynUVzKTnVjBaCSIiSrQ\n"
        "EiqOIrqGvhLlGR36Ymp1y/oA36fEJb/4jXJJG7Mp+qmNvTTJJvGLE75ooYLF7y2U\n"
        "n+p/8qs7ZcH6UmBRfuJY0MU=\n"
        "-----END PRIVATE KEY-----\n";

    std::string const dh =
        "-----BEGIN DH PARAMETERS-----\n"
        "MIIBCAKCAQEAmesA8hoTAJgUsQJKIosCjTDYPWQlJpUeStHwn783MC9DZ42K5lq9\n"
        "OUvEILThtdNjTP6M++t1ouRzbSoecD7DuWTcPelyyiamWosUsOaEyNDZvGJWFJNe\n"
        "Zm1m+2yabn1LmN0KVYzScd/ifIJI62ikfUGzv8lFmz9ThgIPM+NirYzi+ACegc9j\n"
        "hS9luNg3exUXXAcXYPxIjoGQaj3g1QQ+l9qgoQRKB98sqvLOXc6b+Gs2iA7BzQ5/\n"
        "E+xeLGhaErFVd4HexJrGBlN6jX0LggK0KRlcpiKluHxB0Bu8Fn+TnnGvxQFap4aq\n"
        "AG/9yfjzKXPzMwsPGc5fkVX1z/ulu0It0wIBAg==\n"
        "-----END DH PARAMETERS-----\n";
    
    ctx.set_password_callback(
        [](std::size_t,
            boost::asio::ssl::context_base::password_purpose)
        {
            return "test";
        });

    ctx.set_options(
        boost::asio::ssl::context::default_workarounds |
        boost::asio::ssl::context::no_sslv2 |
        boost::asio::ssl::context::single_dh_use);

    ctx.use_certificate_chain(
        boost::asio::buffer(cert.data(), cert.size()));

    ctx.use_private_key(
        boost::asio::buffer(key.data(), key.size()),
        boost::asio::ssl::context::file_format::pem);

    ctx.use_tmp_dh(
        boost::asio::buffer(dh.data(), dh.size()));
}

#endif