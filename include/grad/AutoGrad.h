#ifndef AUTOGRAD_H
#define AUTOGRAD_H

#include <string>
#include <memory>
#include <functional>
#include <cmath>

class Value
{
    private:
        double value;
        double gradient;
        std::function<void(double)> _backprop = [](double g) {};

        Value* left = NULL;
        Value* right = NULL;

        void set_gradient(double gradient)
        {
            this->gradient = gradient;
        }

    public:
        Value(double value) : value(value), gradient(1.0) {}

        Value(double value, Value* left, Value* right) :
            value(value),
            gradient(1.0),
            left(left),
            right(right)
        {}

        double getValue() const { return value; }

        double getGradient() const { return gradient; }

        Value* operator+(Value* other)
        {
            this->_backprop = [this, other](double gradient) mutable {
                this->set_gradient(gradient);
                other->set_gradient(gradient);
            };
            return new Value(value + other->value, this, other);
        }

        Value* operator*(Value* other)
        {
            this->_backprop = [this, other](double gradient) mutable {
                this->set_gradient(gradient * other->value);
                other->set_gradient(gradient * this->value);
            };
            return new Value(value * other->value, this, other);
        }

        void backprop(double gradient = 1.0)
        {
            this->_backprop(gradient);

            if (left != NULL)
            {
                left->backprop(this->gradient);
            }

            if (right != NULL)
            {
                right->backprop(this->gradient);
            }
        }
};

#endif