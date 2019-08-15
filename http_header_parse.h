#pragma once
#include <map>
#include <string>

class http_header_parse
{
public:
	http_header_parse(std::string http_header_string);
	~http_header_parse();

	bool init();
	std::string get_header_string_info();

	bool set_host(std::string host);
	bool set_path(std::string path);

	std::string get_host();
	std::string get_path();

private:
	std::map<std::string, std::string> _http_header_info_map;
	
	std::string _method;
	std::string _path;
	std::string _version;

	std::string _body;

	std::string _http_header_string_info;
};

