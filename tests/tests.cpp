#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "grad/AutoGrad.h"

TEST_CASE( "x", "[autograd]" )
{
    Value* x = new Value(3.0);
    REQUIRE( x->getValue() == Catch::Approx(3.0) );
}

TEST_CASE( "dx x", "[autograd]" )
{
    Value* x = new Value(3.0);
    x->backprop();
    REQUIRE( x->getGradient() == Catch::Approx(1.0) );
}

TEST_CASE( "x + y", "[autograd]" )
{
    Value* x = new Value(3.0);
    Value* y = new Value(2.0);

    Value* z = (*x) + y;

    REQUIRE( z->getValue() == Catch::Approx(5.0) );
}

TEST_CASE( "dx, dy x + y", "[autograd]" )
{
    Value* x = new Value(3.0);
    Value* y = new Value(2.0);

    Value* z = (*x) + y;
    z->backprop();

    REQUIRE( x->getGradient() == Catch::Approx(1.0) );
    REQUIRE( y->getGradient() == Catch::Approx(1.0) );
}

TEST_CASE( "u * v + w", "[autograd]" )
{
    Value* u = new Value(5.0);
    Value* v = new Value(4.0);
    Value* w = new Value(3.0);

    Value* x = (*u) * v;
    Value* y = (*x) + w;

    REQUIRE( y->getValue() == Catch::Approx(23.0) );
}

TEST_CASE( "du, dv, dw u * v + w", "[autograd]" )
{
    Value* u = new Value(5.0);
    Value* v = new Value(4.0);
    Value* w = new Value(3.0);

    Value* x = (*u) * v;
    Value* y = (*x) + w;

    y->backprop();

    REQUIRE( u->getGradient() == Catch::Approx(4.0) );
    REQUIRE( v->getGradient() == Catch::Approx(5.0) );
    REQUIRE( w->getGradient() == Catch::Approx(1.0) );
}
