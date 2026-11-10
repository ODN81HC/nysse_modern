#pragma once
#include <exception>
#include <string>


/**
  * @file
  * @brief Defines an exception class for initialization errors.
  */


namespace Interface {

/**
 * @brief Exception class that expresses errors during the initialization of the game.
 */
class InitError : public std::exception
{
public:

    /**
     * @brief Default constructor.
     * @post Creates InitError without a message.
     */
    InitError() = default;

    /**
     * @brief Constructor.
     * @param message a message that clarifies the error.
     * @pre -
     * @post Creates InitError that constains the message.
     */
    explicit InitError(std::string message);

    /**
     * @brief Destructor.
     */
    virtual ~InitError() override = default;

    /**
     * @brief Implements std::exception interface.
     * @pre -
     * @post Exception guarantee: nothrow.
     * @return Name of the exception class.
     */
    virtual const char* what() const noexcept;

    /**
     * @brief giveMessage gives a message that clarifies the cause of the exception.
     * @pre -
     * @post Exception guarantee: nothrow.
     * @return Message given in the constructor or empty string.
     *
     */
    std::string giveMessage() const;


private:
    std::string message_;
};

} // Namespace Interface
