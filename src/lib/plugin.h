#ifndef _STARDICT_PLUGIN_H_
#define _STARDICT_PLUGIN_H_

#include <gtk/gtk.h>
#include <string>
#include <list>


#define PLUGIN_SYSTEM_VERSION "3.0.0"

enum StarDictPlugInType {
	StarDictPlugInType_UNKNOWN,
	StarDictPlugInType_VIRTUALDICT,
	StarDictPlugInType_TTS,
	StarDictPlugInType_MISC,
};

/*struct VirtualDictLookupResponse {
	const char *bookname;
	const char *word;
	std::list<char *> datalist;
};*/

struct StarDictPluginSystemService {
	//typedef void (*on_stardict_virtual_dict_plugin_lookup_end_func_t)(const struct VirtualDictLookupResponse *);
	//on_stardict_virtual_dict_plugin_lookup_end_func_t on_lookup_end;
	typedef void (*get_http_response_func_t)(char *buffer, size_t buffer_len, int userdata);
	typedef void (*send_http_request_func_t)(const char* shost, const char* sfile, get_http_response_func_t callback_func, int userdata);
	send_http_request_func_t send_http_request;
	typedef void (*show_url_func_t)(const char *url);
	show_url_func_t show_url;
};

struct StarDictPluginSystemInfo {
	const char *datadir;
	GtkWidget *mainwin;
};

// Notice: You need to init these structs' members before creating a StarDictPlugins object.
extern StarDictPluginSystemInfo oStarDictPluginSystemInfo;
extern StarDictPluginSystemService oStarDictPluginSystemService;

typedef void (*plugin_configure_func_t)();

struct StarDictPlugInObject {
	StarDictPlugInObject();
	~StarDictPlugInObject();

	const char* version_str;
	StarDictPlugInType type;
	char* info_xml;
	plugin_configure_func_t configure_func;

	const StarDictPluginSystemInfo *plugin_info;
	const StarDictPluginSystemService *plugin_service;
};

#endif
