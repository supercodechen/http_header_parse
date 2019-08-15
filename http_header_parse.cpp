#include "http_header_parse.h"



http_header_parse::http_header_parse(std::string http_header_string):
	_http_header_string_info(http_header_string)
{
}


http_header_parse::~http_header_parse()
{
}

bool http_header_parse::init()
{
	size_t pos_http_header_end = _http_header_string_info.find("\r\n\r\n");
	if (pos_http_header_end == std::string::npos)
	{
		return false;
	}

	if (pos_http_header_end + 4 == _http_header_string_info.size())
	{
		_body = "";
	}
	else
	{
		_body = _http_header_string_info.substr(pos_http_header_end + 4, _http_header_string_info.size() - pos_http_header_end - 4);
	}

	std::string Temp = _http_header_string_info.substr(0, pos_http_header_end + 2);

	_method = Temp.substr(0, Temp.find(" "));
	_path = Temp.substr(_method.size() + 1, Temp.find(" ", _method.size() + 1) - _method.size() - 1);
	_version = Temp.substr(_method.size() + 1 + _path.size() + 1, Temp.find("\r\n") - _method.size() - 1 - _path.size() - 1);

	size_t pos_count = Temp.find(_version) + _version.size() + 2;
	while (true)
	{
		size_t pos_line_end = Temp.find("\r\n", pos_count);
		if (pos_line_end == std::string::npos)
		{
			break;
		}
		size_t pos_line_half = Temp.find(":", pos_count);
		if (pos_line_half == std::string::npos)
		{
			break;
		}

		std::string http_header_key = Temp.substr(pos_count, pos_line_half - pos_count);
		std::string http_header_value = Temp.substr(pos_line_half + 1, pos_line_end - pos_line_half - 1);

		_http_header_info_map.insert(std::make_pair(http_header_key, http_header_value));
		pos_count = pos_line_end + 2;
	}

	return true;
}

std::string http_header_parse::get_header_string_info()
{
	std::string Temp;
	Temp.append(_method);
	Temp.append(" ");
	Temp.append(_path);
	Temp.append(" ");
	Temp.append(_version);
	Temp.append("\r\n");

	std::map<std::string, std::string>::iterator it = _http_header_info_map.begin();
	while (it != _http_header_info_map.end())
	{
		Temp.append(it->first);
		Temp.append(":");
		Temp.append(it->second);
		Temp.append("\r\n");
		it++;
	}

	Temp.append("\r\n");
	Temp.append(_body);

	return Temp;
}

bool http_header_parse::set_host(std::string host)
{
	std::map<std::string, std::string>::iterator it = _http_header_info_map.find("Host");
	if (it == _http_header_info_map.end())
	{
		return false;
	}

	it->second = host;
	return true;
}

bool http_header_parse::set_path(std::string path)
{
	_path = path;
}

std::string http_header_parse::get_host()
{
	std::map<std::string, std::string>::iterator it = _http_header_info_map.find("Host");
	if (it == _http_header_info_map.end())
	{
		return "";
	}

	return it->second;
}

std::string http_header_parse::get_path()
{
	return _path;
}
