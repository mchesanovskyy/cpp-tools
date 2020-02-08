#include <iostream>
#include "command_container.h"
#include "palindrome_cmd.h"
#include "simple_calculator_cmd.h"
#include "pyramid_cmd.h"

using namespace std;

void main()
{
	// Create an instance of cmd_container_builder
	cmd_container container;

	//register custom commands in container
	container.add(new palindrome_cmd);
	container.add(new simple_calculator_cmd);
	container.add(new pyramid_cmd);

	// Run a static method with command handler flow
	cmd_env::start(container);
}
