#pragma once

void error(const char *error_from_module, const char *error_msg);
void warn(const char *warn_from_module, const char *warn_msg);
void notify(const char *notify_from_module, const char *msg);
