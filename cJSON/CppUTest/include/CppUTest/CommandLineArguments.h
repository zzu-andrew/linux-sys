/***
 * Excerpted from "Test-Driven Development for Embedded C",
 * published by The Pragmatic Bookshelf.
 * Copyrights apply to this code. It may not be used to create training material, 
 * courses, books, articles, and the like. Contact us if you are in doubt.
 * We make no guarantees that this code is fit for any purpose. 
 * Visit http://www.pragmaticprogrammer.com/titles/jgade for more book information.
***/
#ifndef D_CommandLineArguments_H
#define D_CommandLineArguments_H

///////////////////////////////////////////////////////////////////////////////
//
//  CommandLineArguments is responsible for ...
//
///////////////////////////////////////////////////////////////////////////////
#include "SimpleString.h"
#include "TestOutput.h"

class TestPlugin;

class CommandLineArguments
{
public:
	explicit CommandLineArguments(int ac, const char** av);
	virtual ~CommandLineArguments();

	bool parse(TestPlugin* plugin);
	bool isVerbose() const;
	int getRepeatCount() const;
	SimpleString getGroupFilter() const;
	SimpleString getNameFilter() const;
	bool isJUnitOutput() const;
	bool isEclipseOutput() const;
	const char* usage() const;

private:

	enum OutputType
	{
		OUTPUT_ECLIPSE, OUTPUT_JUNIT
	};
	int ac_;
	const char** av_;

	bool verbose_;
	int repeat_;
	SimpleString groupFilter_;
	SimpleString nameFilter_;
	OutputType outputType_;

	SimpleString getParameterField(int ac, const char** av, int& i);
	void SetRepeatCount(int ac, const char** av, int& index);
	void SetGroupFilter(int ac, const char** av, int& index);
	void SetNameFilter(int ac, const char** av, int& index);
	bool SetOutputType(int ac, const char** av, int& index);

	CommandLineArguments(const CommandLineArguments&);
	CommandLineArguments& operator=(const CommandLineArguments&);

};

#endif  // D_CommandLineArguments_H
