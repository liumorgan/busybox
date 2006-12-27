/* vi: set sw=4 ts=4: */
/*
 * Licensed under GPLv2 or later, see file LICENSE in this tarball for details.
 */
#include <stdio.h>
#include "unarchive.h"

void header_list(const file_header_t *file_header)
{
	puts(file_header->name);
}
