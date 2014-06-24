/**
 * OptParser class.
 *
 * A Class to parse CLI Options in a readable and easy way.
 * inspired by Rubys OptionParser
 *
 * @package   Kanedo::OptParser
 * @author    kanedo <software@kanedo.net>
 * @license   MIT
 * @link      http://kanedo.net
 * @copyright 2014 kanedo
 * @version   1.0.0
 */

#ifndef OPTPARSER_H
#define OPTPARSER_H
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

namespace Kanedo{
	using std::cout;
	using std::endl;
	using std::vector;
	using std::unordered_map;
	using std::max;
	using std::string;
	using std::ostream;

	/**
	 * Class OptParser
	 * use this class to parse CLI Options.
	 * inspired by Rubys OptionParser class
	 */
	class OptParser {
	protected:
		struct Option{
			string name;
			string short_opt;
			string long_opt;
			string descr;
			bool required;
			string default_val;
			bool use_default;
		};
		unordered_map<string, string> values;
		vector<string> required;
		unordered_map<string, Option> options;
		unordered_map<string, string> defaults;
		string help;
		void	setOption(string name, string short_opt, string long_opt, string descr, bool required, string default_val, bool use_default);
		
		bool strict;
		string getUsageText();
		ostream *output;
		
		unordered_map<string, Option>::iterator findOption(string argv);
	public:
		OptParser();
		/**
		 * constructor
		 * @param ostream& output define output stream for usage text. default std::cout
		 */
		OptParser(ostream &output);
		
		/**
		 * define intro text.
		 * usually a short description of what the application does
		 * @param text the intro text
		 */
		void	setHelpText(string text);
		/**
		 * define an option
		 * @param string name      the name of the option used in @see OptParser::getValue	
		 * @param string short_opt the short variant of this option (w/o -)
		 * @param string long_opt  the long variant of this option (w/o --)
		 * @param string descr     a description of what this options is used for
		 */
		void	setOption(string name, string short_opt, string long_opt, string descr);

		/**
		 * define an option
		 * @param string name      the name of the option used in @see OptParser::getValue	
		 * @param string short_opt the short variant of this option (w/o -)
		 * @param string long_opt  the long variant of this option (w/o --)
		 * @param string descr     a description of what this options is used for
		 * @param bool   required  set to true if this option is required
		 */
		void	setOption(string name, string short_opt, string long_opt, string descr, bool required);
		/**
		 * [setOption description]
		 * @param string name        the name of the option used in @see OptParser::getValue
		 * @param string short_opt   the short variant of this option (w/o -)
		 * @param string long_opt    the long variant of this option (w/o --)
		 * @param string descr       a description of what this options is used for
		 * @param bool   required    set to true if this option is required
		 * @param string default_val define a default value for this option (only makes sense if required is set to false)
		 */
		void	setOption(string name, string short_opt, string long_opt, string descr, bool required, string default_val);

		/**
		 * define default value for option later
		 * @param string name  the name of the option
		 * @param string value the default value
		 */
		void	setDefaultValue(string name, string value);

		/**
		 * returns the value of given option. 
		 * If option does not exists it'll return an empty string
		 * If option is not set an has a default value the default is used
		 * @param  string name name of the option
		 * @return string
		 */
		string	getValue(string name);
		
		/**
		 * return the Help text
		 * @return string
		 */
		string	getHelpText();

		/**
		 * show the usage text to stream defined in @see OptParser::OptParser 
		 * default is std::cout
		 */
		void	showUsage();

		/**
		 * parse the options (usually parameters of main()).
		 * @param  int    argc the size of argv
		 * @param  char** argv parameters array
		 * @return bool        true if parsing went well, false otherwise. Usage is shown automatically
		 */
		bool	parseOptions(int argc, const char* argv[]);
		
	};}
#endif