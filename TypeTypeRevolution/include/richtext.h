/** Rich text extension for sfml
 * https://bitbucket.org/jacobalbano/sfml-richtext/
 */

#ifndef RICHTEXT_H
#define RICHTEXT_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/String.hpp>
#include <vector>
#include <map>

namespace sfe
{
	class RichText : public sf::Drawable, public sf::Transformable
	{
		public:
			RichText();
			RichText(const sf::String& source, const sf::Font& font, unsigned int characterSize = 30);

			enum Style
			{
				Regular = sf::Text::Regular,
				Bold = sf::Text::Bold,
				Italic = sf::Text::Italic,
				Underlined = sf::Text::Underlined,
			};

			sf::String getString() const;
			sf::String getSource() const;
			void setString(const sf::String& source);
			void clear();

			unsigned int getCharacterSize() const;
			void setCharacterSize(unsigned int size);

			const sf::Font* getFont() const;
			void setFont(const sf::Font& font);

			sf::FloatRect getLocalBounds() const;
			sf::FloatRect getGlobalBounds() const;

			//	Set names for color substitutions (for example, ff0000 would be substituted for "red")
			void addColor(const sf::String& name, const sf::Color& color);
			void addColor(const sf::String& name, unsigned int argbHex);

		private:
			void draw(sf::RenderTarget& target, sf::RenderStates states) const;

			void initializeColors();
			sf::Color getColor(const sf::String& source) const;
			sf::Color getColor(unsigned int argbHex) const;

			std::map<sf::String, sf::Color> colors;
			std::vector<sf::Text> texts;

			unsigned int characterSize;
			const sf::Font* font;

			sf::String source;
			sf::String string;
			sf::FloatRect bounds;
	};

#endif // RICHTEXT_H

// Example main
//	int main()
//	{
//		sf::Font arial;
//		arial.loadFromFile("arial.ttf");
//
//		std::string source;
//		std::ifstream in("source.txt");
//
//		while (in)
//		{
//			std::string line;
//			std::getline(in, line);
//			source += line + '\n';
//		}
//
//		sfe::RichText rich(source, arial);
//
//		sf::RenderWindow window;
//		window.create(sf::VideoMode(700, 250), "SFML Rich text");
//
//		while(window.isOpen())
//		{
//			sf::Event event;
//			while(window.pollEvent(event))
//			{
//				if(event.type == sf::Event::Closed)
//					window.close();
//			}
//
//			window.clear();
//			window.draw(rich);
//			window.display();
//		}
//	}

}
