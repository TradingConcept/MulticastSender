#define BOOST_TEST_MODULE MulticastSenderTest

#include "MulticastSenderLib.hpp"

#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(MulticastSenderSuite)

BOOST_AUTO_TEST_CASE(Test1)
{    
    BOOST_CHECK_EQUAL(MulticastSenderLib::Test1(), 1);
}

BOOST_AUTO_TEST_CASE(Test2)
{    
    BOOST_CHECK_EQUAL(MulticastSenderLib::Test2(), 2);
}


BOOST_AUTO_TEST_SUITE_END()