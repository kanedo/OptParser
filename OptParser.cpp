#include "OptParser.h"
namespace Kanedo{
	OptParser::OptParser(){
		this->output		= &cout;
		this->help			= "";
		this->binary_name	= "";
		this->required		= vector<string>();
		this->strict		= false;
		this->max_name		= 0;
		this->max_long		= 0;
		this->max_short		= 0;
	}

	OptParser::OptParser(ostream &output){
		this->output	= &output;
	}

	void OptParser::setHelpText(string text){
		this->help = text;
	}

	string OptParser::getHelpText(){
		return  this->help;
	}

	string OptParser::getUsageText(){
		string output = this->getHelpText();
		output += "\n";
		output += "Usage: ";
		output += this->binary_name;
		output += " [options] \n";

		for(unordered_map<string, Option>::iterator option = this->options.begin(); option != this->options.end(); ++option){
			Option opt = option->second;
			output += "  ";
			//
			// short option
			//
			output += "-";
			output += opt.short_opt;
			for (size_t i = 0; i < (this->max_short - opt.short_opt.length()) + 1; ++i) {
				output += " ";
			}

			//
			// long option
			// 
			output += "--";
			output += opt.long_opt;
			for (size_t i = 0; i < (this->max_long - opt.long_opt.length()) + 1; ++i) {
				output += " ";
			}

			//
			// option name
			// 
			output += opt.name;
			for (size_t i = 0; i < (this->max_name - opt.name.length()) + 1; ++i) {
				output += " ";
			}

			//
			// required flag
			// 
			if(opt.required){
				output.append("(required)");
				output.append(" ");
			}

			//
			// default value
			// 
			if(opt.use_default){
				output.append("[default: ");
				output.append(opt.default_val);
				output.append("] ");
			}

			//
			// description
			// 
			output.append(opt.descr);
			output.append("\n");
		}
		return output;
	}

	void OptParser::showUsage(){
		*this->output << this->getUsageText();
	}


	void OptParser::setOption(string name, string short_opt, string long_opt, string descr, bool required, string default_val, bool use_default){
		Option opt;
		opt.name = name;
		opt.short_opt = short_opt;
		opt.long_opt = long_opt;
		opt.descr = descr;
		opt.required = required;
		if (required) {
			this->required.push_back(name);
		}
		opt.default_val = default_val;
		opt.use_default = use_default;
		if(use_default){
			this->defaults.insert(make_pair(name, default_val));
		}
		this->options.insert(make_pair(name, opt));
		this->max_short = max(this->max_short, short_opt.length());
		this->max_long = max(this->max_long, long_opt.length());
		this->max_name = max(this->max_name, name.length());
	}

	void OptParser::setOption(string name, string short_opt, string long_opt, string descr){
		this->setOption(name, short_opt, long_opt, descr, false, "", false);
	}

	void OptParser::setOption(string name, string short_opt, string long_opt, string descr, bool required){
		this->setOption(name, short_opt, long_opt, descr, required, "", false);
	}

	void OptParser::setOption(string name, string short_opt, string long_opt, string descr, bool required, string default_val){
		this->setOption(name, short_opt, long_opt, descr, required, default_val, true);
	}

	void OptParser::setDefaultValue(string name, string value){
		if(this->options.find(name) != this->options.end()){
			this->options[name].default_val = value;
			this->options[name].use_default = true;
			this->defaults.insert(make_pair(name, value));
		}
	}

	std::unordered_map<string, OptParser::Option>::iterator OptParser::findOption(string argv){
		if (argv.size() > 1) {
			if (argv.substr(0, 1).compare("-") == 0) {
				argv.erase(0, 1);
				if(argv.substr(0, 1).compare("-") == 0){
					// long option
					argv.erase(0, 1);
					for (std::unordered_map<string, OptParser::Option>::iterator option = this->options.begin(); option != this->options.end(); ++option) {
						if(option->second.long_opt.compare(argv) == 0){
							return option;
						}
					}
				}else{
					// short option
					for (std::unordered_map<string, OptParser::Option>::iterator option = this->options.begin(); option != this->options.end(); ++option) {
						if(option->second.short_opt.compare(argv) == 0){
							return option;
						}
					}
				}
			}
		}
		return this->options.end();
	}

	bool OptParser::parseOptions(int argc, const char* argv[]){
		if(argc > 0){
			this->binary_name = string(argv[0]);
		}
		if((argc-1)/2 < this->required.size()){
			*this->output << "error: not enough options given" << endl;
			this->showUsage();
			return false;
		}
		
		if(this->strict && (argc-1)/2 > this->options.size()){
			*this->output << "error: strict usage on - too many options " << endl;
			this->showUsage();
			return false;
		}
		vector<string> required = this->required;
		unordered_map<string, string> defaults = this->defaults;
		for (int i = 0; i < argc-1; ++i) {
			string arg_name = string(argv[i]);
			std::unordered_map<string, OptParser::Option>::iterator opt_iterator = this->findOption(argv[i]);
			if (opt_iterator != this->options.end()) {
				Option opt = opt_iterator->second;
				if(opt.required){
					for (size_t i = 0; i < required.size(); ++i) {
						if(opt.name.compare(required[i]) == 0){
							required.erase(required.begin()+i);
							break;
						}
					}
				}
				this->values.insert(make_pair(arg_name, argv[++i]));
				if(defaults.find(arg_name) != defaults.end()){
					defaults.erase(arg_name);
				}
			}
		}
		if(required.size() > 0){
			*this->output << "error: missing required options " << endl;
			for(vector<string>::iterator req = required.begin(); req != required.end(); ++req){
				*this->output << "\t" << *req << endl;
			}
			this->showUsage();
			return false;
		}
		for(unordered_map<string, string>::iterator opt = defaults.begin(); opt != defaults.end(); ++opt){
			this->values.insert(*opt);
		}
		return true;
	}


	string OptParser::getValue(string name){
		return this->values[name];
	}
}
