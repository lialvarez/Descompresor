#include <stdio.h>
#include <boost\filesystem.hpp>
#include <algorithm>
#include "Callback.h"

int Callback(char *key, char *value, void *userData)
{
	int ret = CALLBACK_ERROR;
	std::string sKey;
	std::string sValue;
	float threshold;
	CallbackData * data = (CallbackData *)userData;
	if (key == NULL)	//Path
	{
		sValue = std::string(value);
		boost::filesystem::path path(sValue);
		if (boost::filesystem::exists(path)) //Si el path ingresado es valido
		{
			if (boost::filesystem::is_directory(path))	//Si el path ingresado es un directorio
			{
				data->path = sValue;
				ret = CALLBACK_OK;
			}
		}
	}
	return ret;
}