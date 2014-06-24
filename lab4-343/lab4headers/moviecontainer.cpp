#ifndef MOVIE_CONTAINER_CPP
#define MOVIE_CONTAINER_CPP

#define TOTAL_MOVIE_GENRES 26

#include "moviecontainer.h"

MovieContainer::MovieContainer() {
	types = new BinTree[TOTAL_MOVIE_GENRES];
	type  = 'M';
}

MovieContainer::~MovieContainer() {
	delete[] types; types = NULL;
}

Item* MovieContainer::get(Item* item) {
	Movie* movie = static_cast<Movie*>(item);
	Generic* find = NULL;
	Generic* target = static_cast<Generic*>(movie);
	types[hash(movie->getGenre())].retrieve(*target, find);
	return static_cast<Item*>(find);
}

// insert new movie
bool MovieContainer::add(Item* item) {
	Movie* movie = static_cast<Movie*>(item);
	bool success = types[hash(movie->getGenre())].insert(item);
	return success;
}

int MovieContainer::hash(char c) const {
	return (int)(c - 'A') % TOTAL_MOVIE_GENRES;
}

void MovieContainer::printAll() const {
	for (int i = 0; i < TOTAL_MOVIE_GENRES; i++) {
		if (types[i].size() > 0) {
			cout << static_cast<Movie*>(types[i].getRoot()->getData())->getHeader() << endl;
		
			cout << types[i] << endl;
		}
	}
}

bool MovieContainer::remove(Item* item) {
	return types[hash(
						static_cast<Movie*>(item)->getGenre()
					 )
	            ].remove(static_cast<Generic&>(*item));
}

#endif