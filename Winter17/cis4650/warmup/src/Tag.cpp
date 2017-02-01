/* Tag.cpp                                                      */
/* Tag class method definitons                                  */
/* Created by Jeffrey-David Kapp; 0832671                       */
/* 1 Feburary 2017 - Last modifed 1/2/2017                      */

#include "sgml.h"
#include "Tag.h"

Tag::Tag(string value) {
    this->value = value;
    NormaliseTag();
    DetermineTagType();
}

void Tag::NormaliseTag() {
    int i;
    int start = 0, end = 0;
    transform(value.begin(), value.end(), value.begin(), ::toupper);
    for (i = 0; i < value.length(); i++ ) {
        if ( start == 0 && isalnum(value.at(i)) != 0 ) {
            start = i;
        } else if ( start != 0 && end == 0 && isalnum(value.at(i)) == 0 ) {
            end = i;
        }
    }
    value = value.substr( start, end-start );
}

void Tag::DetermineTagType() {
    if ( value.compare("TEXT") == 0 ) {
        tagType = TEXT;
    } else if ( value.compare("DATE") == 0 ) {
        tagType = DATE;
    } else if ( value.compare("DOC") == 0 ) {
        tagType = DOC;
    } else if ( value.compare("DOCNO") == 0 ) {
        tagType = DOCNO;
    } else if ( value.compare("HEADLINE") == 0 ) {
        tagType = HEADLINE;
    } else if ( value.compare("LENGTH") == 0 ) {
        tagType = LENGTH;
    } else if ( value.compare("P") == 0 ) {
        tagType = P;
    } else {
        tagType = IRRELEVANT;
    }
}

tag_t Tag::getTagType() {
    return tagType;
}

string Tag::getValue() {
    return value;
}
