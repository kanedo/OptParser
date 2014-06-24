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
options->addFlag("flag", "f", "flag", "use flags to add binary values");
if(!options->parseOptions(argc, argv)){
	return EXIT_FAILURE;
}

string required_option = options->getValue("required_option");
string option_default  = options->getValue("option_default");	// returns "default value" if not specified
string option          = options->getValue("option");			// return an empty string if not specified
if(options->isSet("flag")){
		cout << "flag is set " << endl;
}

```

## Sample output

```
error: not enough options given
this is an example app to demonstrate the usage of OptParser
Usage: ./example_app [options] 
  -o  --option          option          This is a normal option
  -d  --default-option  option_default  [default: default value] This is an option with a default value
  -f  --flag            flag            use flags to add binary values
  -ro --required-option required_option (required) This is a required option you must specify
```

## Changelog

### 1.0.0 (2014-06-24)
initial Version. 

### 1.0.1 (2014-06-24)

- bugfix: use const for argc in parseOptions
- use 3-colum layout for usage. Short-Opts and long-opts are now prettier aligned
- added `example.cpp` with usage examples

### 1.0.2 (2014-06-24)

- fixed typo (thanks @badboy)
- use 4-col layout for usage. No short-opts, long-opts and names are aligned pretty
- added flags. Options without values. Just binary. e.g help or -h is now possible
- made the generation of usage text a bit more efficient and better readable
