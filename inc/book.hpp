#include <iostream>
#include <uuid/uuid.h>

#include "date.hpp"

#ifndef BOOK_H_
#define BOOK_H_

struct Book {
    std::string isbn;
    std::string title;
    std::string author;
    std::string publication_date;
};


#endif // BOOK_H_
