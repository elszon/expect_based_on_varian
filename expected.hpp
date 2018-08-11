#pragma once

#include <exception>

#include <boost/variant/variant.hpp>
#include <boost/variant/static_visitor.hpp>
#include <boost/variant/apply_visitor.hpp>
#include <boost/variant/get.hpp>

template < typename Val>
class Expected {
public:
    using Err = std::unique_ptr<std::exception>;
private:
    using Memory = boost::variant<Val, Err>;
public:
    Expected(const Val& v)                          : memory{v}{}
    Expected(Val&& v)                               : memory{std::move(v)}{}
    Expected(std::unique_ptr<std::exception> e)     : memory{std::move(e)}{}
    template < typename Error > Expected(Error&& e) : memory{std::make_unique<Error>(std::forward<Error>(e))}{}

    void swap(Expected& e) noexcept(noexcept (std::declval<Memory>().swap(std::declval<Memory>()))){
        memory.swap(e.memory);
    }

    bool hasValue() const {
        struct HasValue : public boost::static_visitor<bool> {
          bool operator()(const Val&) const { return true; }
          bool operator()(const Err&) const { return false; }
        };
        return boost::apply_visitor(HasValue{}, memory);
    }

    const Val& value() const& {
        struct GetValue : public boost::static_visitor<const Val&> {
          const Val& operator()(const Val& v) const {
              std::cout << "ref" << std::endl;
              return v;
          }
          const Val& operator()(const Err&) const { throw std::runtime_error{"has no value"}; }
        };
        return boost::apply_visitor(GetValue{}, memory);
    }

    Val value() && {
        struct GetValue : public boost::static_visitor<Val> {
          Val operator()(Val& v) const {
              std::cout << "move" << std::endl;
              return std::move(v);
          }
          Val operator()(const Err&) const { throw std::runtime_error{"has no value"}; }
        };
        return boost::apply_visitor(GetValue{}, memory);
    }

    Err error() const { return boost::get<Err>(memory); }

private:
    Memory memory;
};


template < typename Err, typename ... Args>
std::unique_ptr<std::exception> makeError(Args&& ... args){
    return std::make_unique<Err>(std::forward<Args>(args)...);
}
