#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <cctype>
#include "cmaptel"

#ifdef __cplusplus
namespace jnp1 {
#endif

typedef unsigned long ul;

static ul lastId = 0;
static std::map<ul, std::unordered_map<std::string, std::string> > maptel;

static void debug(const std::string &message) {
	#if DEBUG
		std::cerr << message << std::endl;
	#endif
}

unsigned long maptel_create() {
	lastId++;
	maptel[lastId] = std::unordered_map<std::string, std::string>();
	return lastId;
}

void maptel_delete(unsigned long id) {
	if (maptel.find(id) != maptel.end()) {
		maptel.erase(id);
	}
	else {
		std::cerr << "Nie istnieje maptel o takim numerze."; //TODO zmienić komunikat
	}
}

static bool validNumber(const std::string &number) {
	if(number.empty() || number.size() > TEL_NUM_MAX_LEN) {
		debug("Numer ma niepoprawną długość."); //TODO zmienić komunikat
		return false;
	}
	
	for(size_t i = 0; i < number.size(); i++) {
		if(!isdigit(number[i])) {
			debug("Numer ma niepoprawny znak."); //TODO zmienić komunikat
			return false;
		}
	}
	
	return true;
}

static bool maptel_exists(ul id) {
	if(maptel.find(id) == maptel.end()) {
		debug("Nie istnieje maptel o takim numerze."); //TODO zmienić komunikat
		return false;
	}
	return true;
}

void maptel_insert(unsigned long id, char const *tel_src, char const *tel_dst) {
	if(!maptel_exists(id)) {
		return;
	}
	
	std::string src(tel_src);
	std::string dst(tel_dst);
	
	if(!validNumber(src) || !validNumber(dst)) {
		return;
	}
	
	maptel[id][src] = dst;
}

static bool maptel_key_exists(ul id, const std::string &key) {
	if(maptel[id].find(key) == maptel[id].end()) {
		debug("Nie istnieje taki klucz w mapie o numerze " + std::to_string(id)); //TODO zmienić komunikat
		return false;
	}
	return true;
}

static bool correctArguments(ul id, char const *tel_src, std::string &result) {
	if(!maptel_exists(id)) {
		return false;
	}
	
	std::string src(tel_src);
	if(!validNumber(src)) {
		return false;
	}
	
	if(!maptel_key_exists(id, src)) {
		return false;
	}
	
	result = src;
	return true;
}

void maptel_erase(unsigned long id, char const *tel_src) {
	std::string src;
	if(!correctArguments(id, tel_src, src)) {
		return;
	}
	
	maptel[id].erase(src);
}

void maptel_transform(unsigned long id, char const *tel_src, char *tel_dst, size_t len) {
	std::string src;
	if(!correctArguments(id, tel_src, src)) {
		return;
	}
	
	std::string current = src;
	std::set<std::string> occurencies;
	
	occurencies.insert(current);
	
	while(occurencies.find(current) == occurencies.end()) {
		current = maptel[id][current];
		if(!maptel_key_exists(id, current)) {
			break;
		}
	}
	
	if(current.size() >= len) {
		debug("Bufor wynikowy jest za mały."); //TODO zmienić komunikat
		return;
	}
	
	for(size_t i = 0; i < current.size(); i++) {
		tel_dst[i] = current[i];
	}
	tel_dst[current.size()] = '\0';
	
}

size_t TEL_NUM_MAX_LEN = 22;

#ifdef __cplusplus
}
#endif
