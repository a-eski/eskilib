/* Copyright (C) eskilib by Alex Eski 2025 */

#ifndef _DEFAULT_SOURCE
#	define _DEFAULT_SOURCE // for anon enum DT_*
#endif /* ifndef _DEFAULT_SOURCE */

#include <dirent.h>
#include <sys/stat.h>

[[nodiscard]]
bool edir_is_dir(struct dirent* dir)
{
#ifdef _DIRENT_HAVE_D_TYPE
    if (dir->d_type != DT_UNKNOWN) {
	return dir->d_type == DT_DIR;
    }
#endif /* ifdef _DIRENT_HAVE_D_TYPE */

    struct stat sb;
    return !stat(dir->d_name, &sb) && S_ISDIR(sb.st_mode);
}
