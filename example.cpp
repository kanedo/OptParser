#include "OptParser.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace Kanedo;

int main(int argc, char const *argv[])
{
	OptParser *options = new OptParser();
	options->setHelpText("this is an example app to demonstrate the usage of OptParser");
	options->setOption("required_option", "ro", "required-option", "This is a required option you must specify", true);
	options->setOption("option_default", "d", "default-option", "This is an option with a default value", false, "default value");
	options->setOption("option", "o", "option", "This is a normal option");
	options->addFlag("flag", "f", "flag", "use flags to add binary values");
	if(!options->parseOptions(argc, argv)){
		return EXIT_FAILURE;
	}

	string required_option = options->getValue("required_option");
	string option_default  = options->getValue("option_default");	// returns "default value" if not specified
	string option          = options->getValue("option");			// return an empty string if not specified
	cout << required_option << endl;
	if(options->isSet("flag")){
		cout << "flag is set " << endl;
	}
	return 0;
}