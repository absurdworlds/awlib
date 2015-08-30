/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>
#include <cstring>
#include <dirent.h>
#include <sys/stat.h>

#include <awrts/io/IDirectory.h>

void print_file(char const* path, char const* name)
{
	std::string filename = path;
	if(filename.back() != '/') {
		filename += "/";
	}
	filename += name;
	
	printf("%s\n", filename.c_str());
}

int listdir_dirent(char const* path)
{
	struct dirent *entry;
	DIR *dp;

	dp = opendir(path);
	if (dp == NULL) {
		perror("opendir");
		return -1;
	}

	struct stat dstat;

	while((entry = readdir(dp))) {		
		print_file(path, entry->d_name);
	}

	closedir(dp);
	return 0;
}

int listdir_hrengin(char const* path)
{
	using namespace awrts;

	io::IDirectory* dir = io::openDirectory(path);

	if(!dir) {
		return 1;
	}

	io::Dirent dent;

	while(dir->read(dent) > 0) {
		print_file(path, dent.name.c_str());
	}

	return 0;
}

int main ()
{
	char* buf;
	size_t len;

	getline(&buf, &len, stdin);

	char *pos = strchr(buf, '\n');
	if (pos != NULL) {
		*pos = '\0';
	}
	
	printf("\e[1;34mNative: >>>\e[0;32m\n");
	listdir_dirent(buf);
	printf("\e[1;34mawrts: >>>\e[0;35m\n");
	listdir_hrengin(buf);

	return 0;
}
