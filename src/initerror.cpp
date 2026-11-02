#include "initerror.hpp"


namespace Interface
{

InitError::InitError(std::string message) :
    std::exception(), message_(std::move(message))
{}

const char* InitError::what() const noexcept
{
    return "Interface::InitError";
}


std::string InitError::giveMessage() const
{
    return message_;
}

}
