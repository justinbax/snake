#ifndef SFML_CLIPBOARD_HPP
#define SFML_CLIPBOARD_HPP

#include <SFML/Window/Export.hpp>
#include <SFML/System/String.hpp>


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Give access to the system clipboard
///
////////////////////////////////////////////////////////////
class SFML_WINDOW_API Clipboard
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Get the content of the clipboard as string data
    ///
    /// This function returns the content of the clipboard
    /// as a string. If the clipboard does not contain string
    /// it returns an empty sf::String object.
    ///
    /// \return Clipboard contents as sf::String object
    ///
    ////////////////////////////////////////////////////////////
    static String getString();

    ////////////////////////////////////////////////////////////
    /// \brief Set the content of the clipboard as string data
    ///
    /// This function sets the content of the clipboard as a
    /// string.
    ///
    /// \warning Due to limitations on some operating systems,
    ///          setting the clipboard contents is only
    ///          guaranteed to work if there is currently an
    ///          open window for which events are being handled.
    ///
    /// \param text sf::String containing the data to be sent
    /// to the clipboard
    ///
    ////////////////////////////////////////////////////////////
    static void setString(const String& text);
};

} // namespace sf


#endif // SFML_CLIPBOARD_HPP


////////////////////////////////////////////////////////////
/// \class sf::Clipboard
/// \ingroup window
///
/// sf::Clipboard provides an interface for getting and
/// setting the contents of the system clipboard.
///
/// It is important to note that due to limitations on some
/// operating systems, setting the clipboard contents is
/// only guaranteed to work if there is currently an open
/// window for which events are being handled.
///
/// Usage example:
/// \code
/// // get the clipboard content as a string
/// sf::String string = sf::Clipboard::getString();
///
/// // or use it in the event loop
/// sf::Event event;
/// while(window.pollEvent(event))
/// {
///     if(event.type == sf::Event::Closed)
///         window.close();
///     if(event.type == sf::Event::KeyPressed)
///     {
///         // Using Ctrl + V to paste a string into SFML
///         if(event.key.control && event.key.code == sf::Keyboard::V)
///             string = sf::Clipboard::getString();
///
///         // Using Ctrl + C to copy a string out of SFML
///         if(event.key.control && event.key.code == sf::Keyboard::C)
///             sf::Clipboard::setString("Hello World!");
///     }
/// }
/// \endcode
///
/// \see sf::String, sf::Event
///
////////////////////////////////////////////////////////////
