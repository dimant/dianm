#ifndef VALUE_H
#define VALUE_H

#include <functional>
#include <memory>

#include "operators.h"

namespace grad
{
    class Value
    {
        private:
            std::unique_ptr<Value> other;
            double data;
            double grad;
            OperatorType opType;
            std::function<void()> backward = [](){};

            double set_grad(double grad)
            {
                this->grad = grad;
            }

        public:
            Value(double data) : data(data), grad(1.0), opType(NOP)
            {}

            ~Value()
            {}

            double get_data()
            {
                return data;
            }

            double get_grad()
            {
                return grad;
            }

            std::unique_ptr<Value> operator+(std::unique_ptr<Value>& other)
            {
                opType = PLUS;
                this->other = std::move(other);
                auto out = std::make_unique<Value>(data + other->get_data());
                this->backward = [this]()
                {
                    this->set_grad(1);
                    this->other->set_grad(1);
                };
                return out;
            }

            std::unique_ptr<Value> operator-(std::unique_ptr<Value>& other)
            {
                opType = MINUS;
                this->other = std::move(other);
                this->backward = [this]()
                {
                    this->set_grad(1);
                    this->other->set_grad(-1);
                };
                return std::make_unique<Value>(data - other->get_data());
            }

            std::unique_ptr<Value> operator*(std::unique_ptr<Value>& other)
            {
                opType = MUL;
                this->other = std::move(other);
                this->backward = [this]()
                {
                    this->set_grad(this->other->get_data());
                    this->other->set_grad(this->data);
                };
                return std::make_unique<Value>(data * other->get_data());
            }

            std::unique_ptr<Value> operator/(std::unique_ptr<Value>& other)
            {
                opType = DIV;
                this->other = std::move(other);
                this->backward = [this]()
                {
                    this->set_grad(1 / this->other->get_data());
                    this->other->set_grad(-this->data / (this->other->get_data() * this->other->get_data()));
                };
                return std::make_unique<Value>(data / other->get_data());
            }
    };
}

#endif