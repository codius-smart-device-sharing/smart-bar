//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_EXAMPLE_COMMON_ROOT_CERTIFICATES_HPP
#define BOOST_BEAST_EXAMPLE_COMMON_ROOT_CERTIFICATES_HPP

#include <boost/asio/ssl.hpp>
#include <string>

namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>

namespace detail {

// The template argument is gratuituous, to
// allow the implementation to be header-only.
//
template<class = void>
void
load_root_certificates(ssl::context& ctx, boost::system::error_code& ec)
{
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

    ctx.add_certificate_authority(
        boost::asio::buffer(cert.data(), cert.size()), ec);
    if(ec)
        return;
}

} // detail

// Load the root certificates into an ssl::context
//
// This function is inline so that its easy to take
// the address and there's nothing weird like a
// gratuituous template argument; thus it appears
// like a "normal" function.
//

inline
void
load_root_certificates(ssl::context& ctx, boost::system::error_code& ec)
{
    detail::load_root_certificates(ctx, ec);
}

inline
void
load_root_certificates(ssl::context& ctx)
{
    boost::system::error_code ec;
    detail::load_root_certificates(ctx, ec);
    if(ec)
        throw boost::system::system_error{ec};
}

#endif