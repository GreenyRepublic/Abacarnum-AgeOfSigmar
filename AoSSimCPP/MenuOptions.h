#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

// Class storing menu options with corresponding text and function callbacks
template<class T, typename ARG>
class NumberedMenu
{
public:
	typedef std::pair < std::string, void(T::*)(ARG)> MenuOption;

	NumberedMenu() {};
	NumberedMenu(std::initializer_list<MenuOption>& items) :
		MenuData()
	{
		for (auto item = items.begin(); item != items.end(); ++item)
		{
			MenuData.push_back(*item);
		}
	}

	~NumberedMenu() {};
		
	inline void operator()(size_t option, ARG arg = ARG())
	{
		if (option <= MenuData.size())
		{
			auto test = MenuData[option].second;
			(*test)(arg);
		}
		else
		{
			std::cout << "Invalid option!" << std::endl;
		}
	};

	void AddOption(MenuOption& option)
	{
		MenuData.push_back(option);
	}

	void PrintMenu()
	{
		for (size_t i = 0; i < MenuData.size(); ++i)
		{
			std::cout << (i + 1) << ": " << MenuData[i].first << std::endl;
		}
	}

private:
	std::vector<MenuOption> MenuData;
};

#define CREATE_NUMBERED_MENU(NAME, PARENTTYPE, ARGTYPE) using NumberedMenu = NumberedMenu<PARENTTYPE, ARGTYPE>; using MenuOption = NumberedMenu::MenuOption; NumberedMenu NAME = NumberedMenu(); 
#define CREATE_NUMBERED_MENU(NAME, PARENTTYPE, ARGTYPE, INITLIST) using NumberedMenu = NumberedMenu<PARENTTYPE, ARGTYPE>; using MenuOption = NumberedMenu::MenuOption; NumberedMenu NAME = NumberedMenu(INITLIST); 

#endif