#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

// Class storing menu options with corresponding text and function callbacks
template<class T>
class NumberedMenu
{
public:
	typedef std::pair < std::string, std::function<T()>> MenuOption;

	NumberedMenu() {};
	NumberedMenu(std::initializer_list<MenuOption> items) : MenuData()
	{
		for (auto& item : items)
		{
			MenuData.push_back(item);
		}
	}

	~NumberedMenu() {};
		
	inline T operator()(size_t option)
	{
		int correctedOpt = option - 1;
		if ( correctedOpt <= MenuData.size())
		{
			auto func = MenuData[correctedOpt].second;
			return func();
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

#define CREATE_NUMBERED_MENU(NAME, RETURNTYPE) using NumberedMenu = NumberedMenu<RETURNTYPE>; using MenuOption = NumberedMenu::MenuOption; NumberedMenu NAME = NumberedMenu(); 
#define CREATE_NUMBERED_MENU(NAME, RETURNTYPE, INITLIST) using NumberedMenu = NumberedMenu<RETURNTYPE>; using MenuOption = NumberedMenu::MenuOption; NumberedMenu NAME = NumberedMenu(INITLIST); 

#endif