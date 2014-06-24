#OptParser

CLI-Optionsparser for C++ inspired by Rubys OptionParser class

## Usage
First of all include `OptParser.h`  
the following sample code should make it clear:  
```c++

OptParser *options = new OptParser();
options->setHelpText("this is an example app to demonstrate the usage of OptParser");
options->setOption("required_option", "r", "required-option", "This is a required option you must specify", true);
options->setOption("option_default", "d", "default-option", "This is an option with a default value", false, "default value");
options->setOption("option", "o", "option", "This is a normal option");
if(!options->parseOptions(argc, argv)){
	return EXIT_FAILURE;
}

string required_option = options->getValue("required_option");
string option_default  = options->getValue("option_default");	// returns "default value" if not specified
string option          = options->getValue("option");			// return an empty string if not specified

```

## Changelog

### 1.0.0 (2014-06-24)
initial Version. 