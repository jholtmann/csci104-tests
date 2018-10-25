/*  Created 10/25/2018
    Author: Jonathan Holtmann
    Invokes the search executable from the command line */

#pragma once

#include <gtest/gtest.h>

#include <vector>
#include <string>

testing::AssertionResult runSearch(std::string & output, std::string testName, int letters, int rows, int cols, std::string map);
