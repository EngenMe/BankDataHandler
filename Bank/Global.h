#pragma once

#include "clsUser.h"
#include "clsDate.h"

// Declare and initialize current_user as an instance of clsUser
// The Find method is used to find a user with an empty username and password
// This typically retrieves a default or anonymous user object
clsUser current_user = clsUser::Find("", "");
