#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

// Class storing menu options with corresponding text and function callbacks
template<class T>
class NumberedMenu
{
public:
	typedef std::pair < std::string, std::function<T()>> MenuOption;

	NumberedMenu() {};
	NumberedMenu(const std::initializer_list<MenuOption> options) : MenuData()
	{
		AddOptions(options);
	}

	~NumberedMenu() {};

	inline T SelectOption(const size_t option)
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

	void AddOptions(const std::initializer_list<MenuOption> options)
	{
		for (auto& opt : options)
		{
			MenuData.push_back(opt);
		}
	}

	void AddOption(const MenuOption& option)
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
#define CREATE_NUMBERED_MENU_INIT(NAME, RETURNTYPE, INITLIST) using NumberedMenu = NumberedMenu<RETURNTYPE>; using MenuOption = NumberedMenu::MenuOption; NumberedMenu NAME = NumberedMenu(INITLIST); 

#endif