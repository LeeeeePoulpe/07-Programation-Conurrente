#ifndef SEARCH_IMAGE_DATA_HPP_
#define SEARCH_IMAGE_DATA_HPP_

// Class to store the results of image search
class SearchImageData {
public:
    int match;  // Best match value (lower is better)
    int x;      // X coordinate of the best match
    int y;      // Y coordinate of the best match

    SearchImageData() : match(0), x(0), y(0) {}
};

#endif // SEARCH_IMAGE_DATA_HPP_